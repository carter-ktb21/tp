# from pathlib import Path
# import sys
import argparse

# DTK_PATH = Path("build/tools/dtk.exe")

from gclib.gcm import GCM
from gclib.rarc import RARC
# from gclib.yaz0_yay0 import Yaz0
# from gclib.gclib_file import GCLibFile
from io import BytesIO
# import shutil


class INF1_Entry:
    def __init__(self):
        self.entry_index = 0
        self.dat1_offset = bytes(0)
        self.msg_id = bytes(0)
        self.padding = bytes(0)
        self.display_style = bytes(0)
        self.print_style = bytes(0)
        self.position_flag = bytes(0)
        self.other_attributes = bytes(0)


class INF1_Section:
    def __init__(self):
        self.magic = bytes(0)
        self.length = bytes(0)
        self.num_entries = bytes(0)
        self.entry_size = bytes(0)
        self.padding = bytes(0)
        self.entries = [INF1_Entry()]


class DAT1_Tag:
    def __init__(self):
        self.tag_size = 0
        self.tag_group = 0
        self.tag_number = 0


class DAT1_Entry:
    def __init__(self):
        self.offset = bytes(0)
        self.message = bytes(0)
        self.message_length = 0
        self.tags = []


class MID1_Entry:
    def __init__(self):
        self.entry_index = 0
        self.id = bytes(0)


class MID1_Section:
    def __init__(self):
        self.magic = bytes(0)
        self.unknown = bytes(0)
        self.num_entries = bytes(0)
        self.padding = bytes(0)
        self.entries = [MID1_Entry()]
        self.end_padding = bytes(0)


class FLW1_Entry:
    def __init__(self):
        self.type = bytes(0)


class FLW1_Section:
    def __init__(self):
        self.magic = bytes(0)
        self.unknown = bytes(0)
        self.num_flow_nodes = bytes(0)
        self.num_entries = bytes(0)
        self.padding = bytes(0)
        self.entries = [FLW1_Entry()]


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
        self.dat1_entries = [DAT1_Entry()]
        self.mid1_section = MID1_Section()
        self.flw1_section = FLW1_Section()

    def to_bytes(self) -> bytes:
        out = bytearray()

        # Header bytes
        out += self.magic
        out += self.file_size
        out += self.num_sections
        out += self.encoding
        out += self.padding

        # INF1 Section
        out += self.inf1_section.magic
        out += self.inf1_section.length
        out += self.inf1_section.num_entries
        out += self.inf1_section.entry_size
        out += self.inf1_section.padding
        for entry in self.inf1_section.entries:
            out += entry.dat1_offset
            out += entry.msg_id
            out += entry.padding
            out += entry.display_style
            out += entry.print_style
            out += entry.position_flag
            out += entry.other_attributes
        out += self.padding_before_dat1

        # DAT1 Section
        for entry in self.dat1_entries:
            out += entry.message

        return bytes(out)


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
    new_bmg.padding = bmg_bytes.read(15)

    # Gather INF1 section data
    new_bmg.inf1_section.magic = bmg_bytes.read(4)
    new_bmg.inf1_section.length = bmg_bytes.read(4)
    new_bmg.inf1_section.num_entries = bmg_bytes.read(2)
    new_bmg.inf1_section.entry_size = bmg_bytes.read(2)
    new_bmg.inf1_section.padding = bmg_bytes.read(4)

    # Gather all INF1 entry data
    if name != "zel_unit.bmg":
        for index in range(int.from_bytes(new_bmg.inf1_section.num_entries, byteorder='big')):
            entry = INF1_Entry()
            entry.dat1_offset = bmg_bytes.read(4)
            entry.msg_id = bmg_bytes.read(4)
            entry.padding = bmg_bytes.read(1)  # unknown attribute
            entry.display_style = bmg_bytes.read(1)
            entry.print_style = bmg_bytes.read(1)
            entry.position_flag = bmg_bytes.read(1)
            entry.other_attributes = bmg_bytes.read(8)
            new_bmg.inf1_section.entries.insert(index, entry)
    else:
        for index in range(int.from_bytes(new_bmg.inf1_section.num_entries, byteorder='big')):
            entry = INF1_Entry()
            entry.entry_index = index
            entry.dat1_offset = bmg_bytes.read(4)
            entry.msg_id = bmg_bytes.read(4)
            new_bmg.inf1_section.entries.append(entry)

    # Store padding before strings
    byte = bmg_bytes.read(4)
    new_bmg.padding_before_dat1 += byte
    while byte != b"DAT1":
        byte = bmg_bytes.read(4)
        new_bmg.padding_before_dat1 += byte
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
            bmg_bytes.seek(pos)  # go back one byte
            break
        new_bmg.padding_before_dat1 += byte

    if name == "zel_unit.bmg":
        byte = bmg_bytes.read(9)
        new_bmg.padding_before_dat1 += byte

    # Store DAT1 bytes
    num_entries = int.from_bytes(new_bmg.inf1_section.num_entries, byteorder='big')
    for index in range(num_entries):
        entry = DAT1_Entry()
        entry.offset = int.from_bytes(new_bmg.inf1_section.entries[index].dat1_offset, byteorder='big')

        if index < num_entries - 1:
            next_offset = int.from_bytes(new_bmg.inf1_section.entries[index + 1].dat1_offset, "big")
            entry.message_length = next_offset - entry.offset
            entry.message = bmg_bytes.read(entry.message_length)
        else:
            # Last Message
            message = bytearray()

            while True:
                pos = bmg_bytes.tell()
                chunk = bmg_bytes.read(4)

                if len(chunk) < 4:
                    break

                if chunk in (b"MID1", b"FLW1"):
                    bmg_bytes.seek(pos)
                    break

                bmg_bytes.seek(pos)
                message.append(bmg_bytes.read(1)[0])

            entry.message = bytes(message)
            entry.message_length = len(entry.message)

        new_bmg.dat1_entries.insert(index, entry)

    # MID1 Section
    if name != "zel_unit.bmg":
        new_bmg.mid1_section.magic = bmg_bytes.read(4)
        new_bmg.mid1_section.unknown = bmg_bytes.read(4)
        new_bmg.mid1_section.num_entries = bmg_bytes.read(2)
        new_bmg.mid1_section.padding = bmg_bytes.read(6)

        for index in range(int.from_bytes(new_bmg.mid1_section.num_entries, byteorder='big')):
            entry = MID1_Entry()
            entry.entry_index = index
            entry.id = bmg_bytes.read(4)
            new_bmg.mid1_section.entries.insert(index, entry)
        padding = bytes(0)
        pos = bmg_bytes.tell()
        while True:
            pos = bmg_bytes.tell()
            byte = bmg_bytes.read(1)
            if byte != b'\x00':
                bmg_bytes.seek(pos)
                break
            else:
                padding += byte
        new_bmg.mid1_section.end_padding = padding

    # FLW1 Section
    new_bmg.flw1_section.magic = bmg_bytes.read(4)
    new_bmg.flw1_section.unknown = bmg_bytes.read(4)
    new_bmg.flw1_section.num_flow_nodes = bmg_bytes.read(2)
    new_bmg.flw1_section.num_entries = bmg_bytes.read(2)
    new_bmg.flw1_section.padding = bmg_bytes.read(4)

    # print(bmg_bytes.read(40))
    return new_bmg


def main():
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
        bmgs.append(parse_bmg(entry.data, entry.name))

    # data = bmgs[1].to_bytes()  # or bmgs[1].to_bytes()
    # for i, byte in enumerate(data):
    #     if i >= 6254 * 16:
    #         print(f"{byte:02X} ", end="")
        # print(f"{byte:02X} ", end="")
        # if (i + 1) % 16 == 0:
        #     print()
    #     if (i + 1) % 16 == 0 and i >= 6254 * 16:
    #         input()

    # for bmg in bmgs:
    #     # Print main .bmg info
    #     print(
    #             f"{bmg.name}\nMagic: {bmg.magic}" +
    #             f"\nSize: {hex(int.from_bytes(bmg.file_size, byteorder='big'))}" +
    #             f"\nNumber of Sections: {int.from_bytes(bmg.num_sections, byteorder='big')}"
    #         )
    #     # Print INF1 section info
    #     print(
    #             "\tINF1 Section:\n\t\t" +
    #             f"Length: {hex(int.from_bytes(bmg.inf1_section.length, byteorder='big'))}\n\t\t" +
    #             f"Number of entries: {int.from_bytes(bmg.inf1_section.num_entries, byteorder='big')}\n\t\t" +
    #             f"Entry Size: {hex(int.from_bytes(bmg.inf1_section.entry_size, byteorder='big'))}\n"
    #         )


if __name__ == "__main__":
    main()
