import subprocess
from pathlib import Path
import sys
import argparse
import os
from pathlib import Path
import sys
import time

# DTK_PATH = Path("build/tools/dtk.exe")

from gclib.gcm import GCM, GCMFileEntry
from gclib.rarc import RARC
from gclib.yaz0_yay0 import Yaz0
from gclib.gclib_file import GCLibFile
from io import BytesIO
import shutil

class DAT1_Tag:
    def __init__(self):
        self.tag_size = 0
        self.tag_group = 0
        self.tag_number = 0

class DAT1_Entry:
    def __init__(self):
        self.offset = 0
        self.padding_before_strings = []

class INF1_Entry:
    def __init__(self):
        self.dat1_offset = bytes(0)
        self.msg_id = bytes(0)
        self.display_style = bytes(0)
        self.print_style = bytes(0)
        self.position_flag = bytes(0)

class INF1_Section:
    def __init__(self):
        self.magic = "INF1"
        self.length = bytes(0)
        self.num_entries = bytes(0)
        self.entry_size = bytes(0)
        self.padding = bytes(0)
        self.entries = []

class BMG:
    def __init__(self, name, magic):
        self.name = name
        self.magic = magic
        self.file_size = bytes(0)
        self.num_sections = bytes(0)
        self.encoding = bytes(0)
        self.padding = bytes(0)
        self.inf1_section = INF1_Section()
        self.padding_before_dat1 = bytes(0)
        self.dat1_entries = []

def parse_bmg(bmg_bytes: BytesIO, name):
    bmg_bytes.seek(0)
    # HEADER
    # Name and magic
    new_bmg = BMG(name, bmg_bytes.read(8))
    # Size of File
    new_bmg.file_size = bmg_bytes.read(4)
    # Number of sections
    new_bmg.num_sections = bmg_bytes.read(4)
    # Encoding
    new_bmg.encoding = bmg_bytes.read(1)
    # Padding
    new_bmg.padding = bmg_bytes.read(19)

    # Gather INF1 section data
    new_bmg.inf1_section.length = bmg_bytes.read(4)
    new_bmg.inf1_section.num_entries = bmg_bytes.read(2)
    new_bmg.inf1_section.entry_size = bmg_bytes.read(2)
    new_bmg.inf1_section.padding = bmg_bytes.read(4)
    # Gather all INF1 entry data
    if name != "zel_unit.bmg":
        for index in range(int.from_bytes(new_bmg.inf1_section.num_entries, byteorder='big')):
            new_bmg.inf1_section.entries.append(INF1_Entry())
            new_bmg.inf1_section.entries[index].dat1_offset = bmg_bytes.read(4)
            new_bmg.inf1_section.entries[index].msg_id = bmg_bytes.read(4)
            new_bmg.inf1_section.entries[index].padding = bmg_bytes.read(1) # unknown attribute
            new_bmg.inf1_section.entries[index].display_style = bmg_bytes.read(1)
            new_bmg.inf1_section.entries[index].print_style = bmg_bytes.read(1)
            new_bmg.inf1_section.entries[index].position_flag = bmg_bytes.read(1)
    else:
        new_bmg.padding_before_dat1 = bmg_bytes.read(
            int.from_bytes(new_bmg.inf1_section.num_entries, byteorder='big') * int.from_bytes(new_bmg.inf1_section.entry_size, byteorder='big'))

    # Store padding before strings
    new_bmg.padding_before_dat1 += bmg_bytes.read(8) # 8 unknown attributes
    bytes = bmg_bytes.read(4)
    new_bmg.padding_before_dat1 += bytes
    while bytes != b"DAT1":
        bytes = bmg_bytes.read(4)
        new_bmg.padding_before_dat1 += bytes
    new_bmg.padding_before_dat1 += bmg_bytes.read(1)
    byte = bmg_bytes.read(1)
    new_bmg.padding_before_dat1 += byte
    while byte == b'\x00':
        byte = bmg_bytes.read(1)
        new_bmg.padding_before_dat1 += byte
    while byte != b'\x00':
        byte = bmg_bytes.read(1)
        new_bmg.padding_before_dat1 += byte
    while True:
        pos = bmg_bytes.tell()
        byte = bmg_bytes.read(1)
        if byte != b'\x00':
            bmg_bytes.seek(pos)  # rewind one byte
            break
        new_bmg.padding_before_dat1 += byte

    # Todo: Store DAT1 bytes
    return new_bmg

def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("vanilla_iso_path", nargs="?", default="orig/GZ2E01/baserom.iso", help="Path to a vanilla Twilight Princess ISO to use as a base.")
    parser.add_argument("output_iso_path", nargs="?", default="output_iso/modified.iso", help="Path to put the modified ISO.")
    parser.add_argument("decomp_repo_path", nargs="?", default="", help="Path to the root of the git repository containing the tp decompilation.")
    parser.add_argument("--map", help="Folder to place the symbol map for the modified ISO.")

    args = parser.parse_args()
    # decomp_build_path = args.decomp_repo_path / "build/GZ2E01"

    gcm = GCM(args.vanilla_iso_path)
    gcm.read_entire_disc()

    bmg_files = []

    for iso_path, gcm_file in gcm.files_by_path.items():
        if not iso_path.lower().endswith(".arc"):
            continue
        else:
            try:
                arc_data = gcm.read_file_data(iso_path)
                arc = RARC(arc_data)
                arc.read()

                for entry in arc.file_entries:
                    if (entry.name.lower().endswith(".bmg")):
                        bmg_files.append(entry)
            except Exception as e:
                print(f"  [failed to read ARC: {e}]")
                continue

    bmgs = []
    for entry in bmg_files:
        original = entry.data.getvalue()
        bmgs.append(parse_bmg(entry.data, entry.name))
        bmg = bmgs[-1]
        rebuilt = (
            bmg.magic +
            bmg.file_size +
            bmg.num_sections +
            bmg.encoding +
            bmg.padding +
            bmg.inf1_section.length +
            bmg.inf1_section.num_entries +
            bmg.inf1_section.entry_size +
            bmg.inf1_section.padding +
            b''.join(
                e.dat1_offset + e.msg_id +
                e.padding + e.display_style +
                e.print_style + e.position_flag
                for e in bmg.inf1_section.entries
        ) +
        bmg.padding_before_dat1
        # Todo: Add rest bytes when finished with storing logic for them and verify byte for byte with original file
)

    for bmg in bmgs:
        # Print main .bmg info
        print(f"{bmg.name}\nMagic: {bmg.magic} \nSize: {bmg.file_size}\nNumber of Sections: {bmg.num_sections}")
        # Print INF1 section info
        print(f"\tINF1 Section:\n\t\tLength: {bmg.inf1_section.length}\n\t\tEntries: {bmg.inf1_section.num_entries}\n\t\tEntry Size: {bmg.inf1_section.entry_size}\n")

if __name__ == "__main__":
    main()
