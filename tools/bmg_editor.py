# from pathlib import Path
# import sys
import argparse

# DTK_PATH = Path("build/tools/dtk.exe")

from gclib.gcm import GCM
from gclib.rarc import RARC
# from gclib.yaz0_yay0 import Yaz0
# from gclib.gclib_file import GCLibFile
from io import BytesIO
from typing import List, Union
from pathlib import Path
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
        self.end_padding = bytes(0)
        self.current_size = 0


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
        self.msgId = 0
        self.tags = []


class DAT1_Section:
    def __init__(self):
        self.magic = bytes(0)
        self.padded_size = bytes(0)
        self.entries = [DAT1_Entry()]


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


class Empty_Node:
    def __init__(self):
        self.type = bytes(0)
        self.padding = bytes(0)


class Continuation_Node:
    def __init__(self):
        self.type = bytes(0)
        self.unknown = bytes(0)
        self.inf1_index = bytes(0)
        self.flow_node_index = bytes(0)
        self.unused = bytes(0)


class Branch_Node:
    def __init__(self):
        self.type = bytes(0)
        self.unknown = bytes(0)
        self.query_func_idx = bytes(0)
        self.parameter = bytes(0)
        self.indirection_tbl_offset = bytes(0)


class Event_Node:
    def __init__(self):
        self.type = bytes(0)
        self.event_func_idx = bytes(0)
        self.indirection_tbl_idx = bytes(0)
        self.arguments = bytes(0)


class Indirection_Table:
    def __init__(self):
        self.index = [bytes(0)]


class FLW1_Section:
    def __init__(self):
        self.magic = bytes(0)
        self.unknown = bytes(0)
        self.num_flow_nodes = bytes(0)
        self.num_entries = bytes(0)
        self.padding = bytes(0)
        self.flow_nodes: List[Union[Empty_Node, Continuation_Node, Branch_Node, Event_Node]] = []
        self.indirection_tbl = Indirection_Table()


class FLI1_Entry:
    def __init__(self):
        self.id = bytes(0)
        self.unknown = bytes(0)
        self.flw1_idx = bytes(0)
        self.end_padding = bytes(0)


class FLI1_Section:
    def __init__(self):
        self.magic = bytes(0)
        self.padded_size = bytes(0)
        self.number_of_ids = bytes(0)
        self.end_padding = bytes(0)
        self.entries = [FLI1_Entry()]


class BMG:
    def __init__(self, name):
        self.name = name
        self.magic = bytes(0)
        self.file_size = bytes(0)
        self.num_sections = bytes(0)
        self.encoding = bytes(0)
        self.padding = bytes(0)
        self.inf1_section = INF1_Section()
        self.dat1_section = DAT1_Section()
        self.mid1_section = MID1_Section()
        self.flw1_section = FLW1_Section()
        self.padding_before_fli1 = bytes(0)
        self.fli1_section = FLI1_Section()

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
        out += self.inf1_section.end_padding

        # DAT1 Section
        out += self.dat1_section.magic
        out += self.dat1_section.padded_size
        for entry in self.dat1_section.entries:
            out += entry.message

        # MID1 Section
        out += self.mid1_section.magic
        out += self.mid1_section.unknown
        out += self.mid1_section.num_entries
        out += self.mid1_section.padding
        for entry in self.mid1_section.entries:
            out += entry.id
        out += self.mid1_section.end_padding

        # FLW1 Section
        out += self.flw1_section.magic
        out += self.flw1_section.unknown
        out += self.flw1_section.num_flow_nodes
        out += self.flw1_section.num_entries
        out += self.flw1_section.padding
        for node in self.flw1_section.flow_nodes:
            if node.type == b'\x01':
                out += node.type
                out += node.unknown
                out += node.inf1_index
                out += node.flow_node_index
                out += node.unused
            elif node.type == b'\x02':
                out += node.type
                out += node.unknown
                out += node.query_func_idx
                out += node.parameter
                out += node.indirection_tbl_offset
            elif node.type == b'\x03':
                out += node.type
                out += node.event_func_idx
                out += node.indirection_tbl_idx
                out += node.arguments
            elif node.type == b'\x00':
                out += node.padding
        for index in self.flw1_section.indirection_tbl.index:
            out += index
        out += self.padding_before_fli1

        # FLI1 Section
        out += self.fli1_section.magic
        out += self.fli1_section.padded_size
        out += self.fli1_section.number_of_ids
        out += self.fli1_section.end_padding
        for entry in self.fli1_section.entries:
            out += entry.id
            out += entry.unknown
            out += entry.flw1_idx
            out += entry.end_padding

        return bytes(out)

    def rebuild_bmg(self, path: str):
        data = self.to_bytes()
        with open(path, "wb") as f:
            f.write(data)


def parse_bmg(bmg_bytes: BytesIO, name):
    bmg_bytes.seek(0)
    # HEADER
    # Name
    new_bmg = BMG(name)
    # Magic
    new_bmg.magic = bmg_bytes.read(8)
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
    new_bmg.inf1_section.current_size += 16

    # Gather all INF1 entry data
    if name != "zel_unit.bmg":
        for index in range(int.from_bytes(new_bmg.inf1_section.num_entries, byteorder='big')):
            entry = INF1_Entry()
            entry.dat1_offset = bmg_bytes.read(4)
            entry.msg_id = bmg_bytes.read(2)
            entry.padding = bmg_bytes.read(3)  # unknown attribute
            entry.display_style = bmg_bytes.read(1)
            entry.print_style = bmg_bytes.read(1)
            entry.position_flag = bmg_bytes.read(1)
            entry.other_attributes = bmg_bytes.read(8)
            new_bmg.inf1_section.entries.insert(index, entry)
            new_bmg.inf1_section.current_size += 20
    else:
        for index in range(int.from_bytes(new_bmg.inf1_section.num_entries, byteorder='big')):
            entry = INF1_Entry()
            entry.entry_index = index
            entry.dat1_offset = bmg_bytes.read(4)
            entry.msg_id = bmg_bytes.read(4)
            new_bmg.inf1_section.entries.append(entry)
            new_bmg.inf1_section.current_size += 8

    while new_bmg.inf1_section.current_size < int.from_bytes(new_bmg.inf1_section.length, byteorder='big'):
        new_bmg.inf1_section.end_padding += bmg_bytes.read(1)
        new_bmg.inf1_section.current_size += 1

    if name == "zel_unit.bmg":
        byte = bmg_bytes.read(9)
        new_bmg.inf1_section.end_padding += byte

    # print(bmg_bytes.read(40))
    # DAT1 Section
    new_bmg.dat1_section.magic = bmg_bytes.read(4)
    new_bmg.dat1_section.padded_size = bmg_bytes.read(4)
    num_entries = int.from_bytes(new_bmg.inf1_section.num_entries, byteorder='big')
    for index in range(num_entries):
        entry = DAT1_Entry()
        entry.offset = new_bmg.inf1_section.entries[index].dat1_offset

        if index < num_entries - 1:
            next_offset = int.from_bytes(new_bmg.inf1_section.entries[index + 1].dat1_offset, "big")
            entry.message_length = next_offset - int.from_bytes(entry.offset, byteorder='big')
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

        new_bmg.dat1_section.entries.insert(index, entry)
        new_bmg.dat1_section.entries[index].msgId = int.from_bytes(new_bmg.inf1_section.entries[index].msg_id, byteorder='big')

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

    for index in range(int.from_bytes(new_bmg.flw1_section.num_flow_nodes, byteorder='big')):
        byte = bmg_bytes.read(1)
        if byte == b'\x01':
            node = Continuation_Node()
            node.type = byte
            node.unknown = bmg_bytes.read(1)
            node.inf1_index = bmg_bytes.read(2)
            node.flow_node_index = bmg_bytes.read(2)
            node.unused = bmg_bytes.read(2)
            new_bmg.flw1_section.flow_nodes.insert(index, node)
        elif byte == b'\x02':
            node = Branch_Node()
            node.type = byte
            node.unknown = bmg_bytes.read(1)
            node.query_func_idx = bmg_bytes.read(2)
            node.parameter = bmg_bytes.read(2)
            node.indirection_tbl_offset = bmg_bytes.read(2)
            new_bmg.flw1_section.flow_nodes.insert(index, node)
        elif byte == b'\x03':
            node = Event_Node()
            node.type = byte
            node.event_func_idx = bmg_bytes.read(1)
            node.indirection_tbl_idx = bmg_bytes.read(2)
            node.arguments = bmg_bytes.read(4)
            new_bmg.flw1_section.flow_nodes.insert(index, node)
        elif byte == b'\x00':
            node = Empty_Node()
            node.type = byte
            node.padding += bmg_bytes.read(7)
            new_bmg.flw1_section.flow_nodes.insert(index, node)

    indirection_tbl = Indirection_Table()
    for index in range(int.from_bytes(new_bmg.flw1_section.num_entries, byteorder='big')):
        indirection_tbl.index.insert(index, bmg_bytes.read(2))
    new_bmg.flw1_section.indirection_tbl = indirection_tbl

    padding = bytearray()
    while True:
        pos = bmg_bytes.tell()
        chunk = bmg_bytes.read(4)

        if len(chunk) < 4:
            break

        if chunk in (b'FLI1'):
            bmg_bytes.seek(pos)
            break

        bmg_bytes.seek(pos)
        padding.append(bmg_bytes.read(1)[0])
    new_bmg.padding_before_fli1 = bytes(padding)

    # FLI1 Section
    new_bmg.fli1_section.magic = bmg_bytes.read(4)
    new_bmg.fli1_section.padded_size = bmg_bytes.read(4)
    new_bmg.fli1_section.number_of_ids = bmg_bytes.read(2)
    new_bmg.fli1_section.end_padding = bmg_bytes.read(6)

    for index in range(int.from_bytes(new_bmg.fli1_section.number_of_ids, byteorder='big')):
        entry = FLI1_Entry()
        entry.id = bmg_bytes.read(2)
        entry.unknown = bmg_bytes.read(2)
        entry.flw1_idx = bmg_bytes.read(2)
        entry.end_padding = bmg_bytes.read(2)
        new_bmg.fli1_section.entries.insert(index, entry)

    # print(bmg_bytes.read(40))
    return new_bmg


def string_cleanup(data: bytes) -> str:
    out = []
    i = 0

    while i < len(data):
        b = data[i]

        if b == 0x00:
            b = data[i + 1]
            i += 1

        if b == 0x1A:
            out.append("{Tag - ")
            i += 1
            out.append(f"{data[i]} bytes | Group ")
            i += 1
            group = data[i]
            if group == 0xFF:
                out.append("FF | Name: ")
            else:
                out.append(f"0{group} | Name: ")
            i += 1

            match group:
                case 0:
                    type = data[i + 1]
                    match type:
                        case 0x00:
                            out.append("link}")
                            i += 2
                            continue

                        case 0x01:
                            out.append("instant}")
                            i += 2
                            continue

                        case 0x02:
                            out.append("type}")
                            i += 2
                            continue

                        case 0x04:
                            out.append("autobox - frame_count = ")
                            i += 2
                            out.append(f"{(data[i] << 8) | data[i + 1]}" + "}")
                            i += 2
                            continue

                        case 0x05:
                            out.append("boxatmost - frame_count = ")
                            i += 2
                            out.append(f"{(data[i] << 8) | data[i + 1]}" + "}")
                            i += 2
                            continue

                        case 0x07:
                            out.append("pause - frame_count = ")
                            i += 2
                            out.append(f"{(data[i] << 8) | data[i + 1]}" + "}")
                            i += 2
                            continue

                        case 0x0A:
                            out.append("A}")
                            i += 2
                            continue

                        case 0x0B:
                            out.append("B}")
                            i += 2
                            continue

                        case 0x0C:
                            out.append("C}")
                            i += 2
                            continue

                        case 0x0D:
                            out.append("L}")
                            i += 2
                            continue

                        case 0x0E:
                            out.append("R}")
                            i += 2
                            continue

                        case 0x0F:
                            out.append("X}")
                            i += 2
                            continue

                        case 0x10:
                            out.append("Y}")
                            i += 2
                            continue

                        case 0x11:
                            out.append("Z}")
                            i += 2
                            continue

                        case 0x12:
                            out.append("D}")
                            i += 2
                            continue

                        case 0x20:
                            out.append("softnl}")
                            i += 2
                            continue

                        case 0x21:
                            out.append("nop000021}")
                            i += 2
                            continue

                        case 0x26:
                            out.append("acknowledge}")
                            i += 2
                            continue

                        case 0x28:
                            out.append("boxatleast - frame_count = ")
                            i += 2
                            out.append(f"{(data[i] << 24) | (data[i + 1] << 16) | (data[i + 2] << 8) | data[i + 3]}" + "}")
                            i += 4
                            continue

                        case 0x36:
                            out.append("boxatleast - frame_count = ")
                            i += 2
                            out.append(f"{(data[i] << 8) | data[i + 1]}" + "}")
                            i += 2
                            continue

                case 3:
                    type = data[i + 1]
                    match type:
                        case 0x00:
                            out.append("wii-divert-to-idx - idx = ")
                            i += 2
                            out.append(f"{(data[i] << 24) | (data[i + 1] << 16) | (data[i + 2] << 8) | data[i + 3]}" + "}")
                            i += 4
                            continue

                case 0xFF:
                    type = data[i + 1]
                    match type:
                        case 0x00:
                            out.append("color - hue = ")
                            i += 2
                            out.append(f"{data[i]}" + "}")
                            i += 1
                            continue

                        case 0x01:
                            out.append("size - pct = ")
                            i += 2
                            out.append(f"{(data[i] << 8) | data[i + 1]}" + "}")
                            i += 2
                            continue
                        
            b = data[i]

        if b == 0x0A:
            out.append("\\n")
        elif 32 <= b <= 126:
            out.append(chr(b))
        else:
            out.append(f"\\x{b:02X}")

        i += 1

    return "".join(out)


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("vanilla_iso_path", nargs="?", default="orig/GZ2E01/baserom.iso", help="Path to a vanilla Twilight Princess ISO to use as a base.")
    parser.add_argument("output_path", nargs="?", help="Path to put the modified ISO.")
    parser.add_argument("decomp_repo_path", nargs="?", default="", help="Path to the root of the git repository containing the tp decompilation.")
    parser.add_argument("--map", help="Folder to place the symbol map for the modified ISO.")

    args = parser.parse_args()
    # decomp_build_path = args.decomp_repo_path / "build/GZ2E01"
    output_path = args.output_path

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

    bmgs = [BMG(None)]
    for entry in bmg_files:
        bmgs.append(parse_bmg(entry.data, entry.name))

    # data = bmgs[1].to_bytes()
    # for i, byte in enumerate(data):
    #     print(f"{byte:02X} ", end="")
    #     if (i + 1) % 16 == 0:
    #         print()
    while True:
        print("--------------------\n" +
              "1) Search by message ID\n" +
              "2) Search by phrase\n" +
              "3) Rebuild bmg files\n" +
              "4) Cancel\n" +
              "--------------------\n")
        choice = int(input("Enter menu choice: "))
        match choice:
            case 1:
                msg_id_target = int(input("Enter msgId (hex): "), 16)
                for bmg in bmgs:
                    for dat1_entry in bmg.dat1_section.entries:
                        if dat1_entry.msgId == msg_id_target:
                            print(f"\n{bmg.name}")
                            print(f"{string_cleanup(dat1_entry.message)}\n")

            case 3:
                for bmg in bmgs:
                    bmg.rebuild_bmg(Path(f"C:/BMG_Test/{bmg.name}"))

            case 4:
                break


if __name__ == "__main__":
    main()
