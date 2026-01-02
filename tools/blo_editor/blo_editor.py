import os
import argparse
from gclib.gcm import GCM
from gclib.rarc import RARC
from gclib.yaz0_yay0 import Yaz0
from io import BytesIO
from typing import List, Union
from pathlib import Path
import xml.etree.ElementTree as ET


class BLO:
    def __init__(self, data: BytesIO):
        self.tag = data.read(4)
        self.type = data.read(4)
        self.size = int.from_bytes(data.read(4), byteorder='big')
        self.blocks = int.from_bytes(data.read(4), byteorder='big')
        self.header_padding = data.read(16)
        self.inf1_section = INF1_Section(data)
        self.tex1_section = TEX1_Section(data)
        self.fnt1_section = FNT1_Section(data)
        self.mat1_section = MAT1_Section(data)
        self.elements = PAN2(data, True)


class INF1_Section:
    def __init__(self, data: BytesIO):
        self.magic = data.read(4)
        self.size = int.from_bytes(data.read(4), byteorder='big')
        self.unknown = data.read(8)
        padding_size = self.size - 16
        self.padding = data.read(padding_size)


# TEX1 ---------------------------------------------------------------------------------
class TEX1_Section:
    def __init__(self, data: BytesIO):
        self.header = TEX1_Header(data)
        self.size_after_header = self.header.section_size - self.header.header_size
        self.offset_count = data.read(2)
        self.offsets: List[bytes] = []
        for i in range(int.from_bytes(self.offset_count, byteorder='big')):
            self.offsets.insert(i, data.read(2))
        self.texture_refs: List[TEX1_Reference] = []
        for i in range(int.from_bytes(self.offset_count, byteorder='big')):
            if i + 1 < int.from_bytes(self.offset_count, byteorder='big'):
                ref = TEX1_Reference()
                ref_size = int.from_bytes(self.offsets[i + 1], byteorder='big') - int.from_bytes(self.offsets[i], byteorder='big')
                ref.res_type = data.read(1)
                ref.texture = data.read(ref_size)
                self.texture_refs.insert(i, ref)
            else:
                ref = TEX1_Reference()
                ref.res_type = data.read(1)
                size = (self.header.section_size - 10) - int.from_bytes(self.offsets[i], byteorder='big')
                ref.texture = data.read(size)
        # self.padding = bytes()


class TEX1_Header:
    def __init__(self, data: BytesIO):
        self.magic = data.read(4)
        self.section_size = int.from_bytes(data.read(4), byteorder='big')
        self.texture_count = data.read(2)
        self.padding = data.read(2)
        self.header_size = int.from_bytes(data.read(4), byteorder='big')


class TEX1_Reference:
    def __init__(self):
        self.res_type = bytes()
        self.texture = bytes()
# --------------------------------------------------------------------------------------


# FNT1 ---------------------------------------------------------------------------------
class FNT1_Section:
    def __init__(self, data: BytesIO):
        self.header = FNT1_Header(data)
        self.size_after_header = self.header.section_size - self.header.header_size
        self.offset_count = data.read(2)
        self.offsets: List[bytes] = []
        for i in range(int.from_bytes(self.offset_count, byteorder='big')):
            self.offsets.insert(i, data.read(2))
        self.font_refs: List[FNT1_Reference] = []
        for i in range(int.from_bytes(self.offset_count, byteorder='big')):
            if i + 1 < int.from_bytes(self.offset_count, byteorder='big'):
                ref = FNT1_Reference()
                ref_size = int.from_bytes(self.offsets[i + 1], byteorder='big') - int.from_bytes(self.offsets[i], byteorder='big')
                ref.res_type = data.read(1)
                ref.font = data.read(ref_size)
                self.font_refs.insert(i, ref)
            else:
                ref = FNT1_Reference()
                ref.res_type = data.read(1)
                size = (self.header.section_size - 10) - int.from_bytes(self.offsets[i], byteorder='big')
                ref.font = data.read(size)


class FNT1_Header:
    def __init__(self, data: BytesIO):
        self.magic = data.read(4)
        self.section_size = int.from_bytes(data.read(4), byteorder='big')
        self.font_count = data.read(2)
        self.padding = data.read(2)
        self.header_size = int.from_bytes(data.read(4), byteorder='big')


class FNT1_Reference:
    def __init__(self):
        self.res_type = bytes()
        self.font = bytes()
# --------------------------------------------------------------------------------------


# MAT1 ---------------------------------------------------------------------------------
class MAT1_Section:
    def __init__(self, data: BytesIO):
        self.magic = data.read(4)
        self.size = int.from_bytes(data.read(4), byteorder='big')
        self.material_count = data.read(2)
        self.padding = data.read(2)
        self.offsets = MAT1_Section_Offsets(data)
        self.mat_init_section = Mat_Init_Data_Section(data)
        self.mat_init_idx_section = Mat_Init_Data_Idx_Section()
        self.unknown_section = Unknown_Section()
        self.cull_modes = Cull_Mode_Section()
        self.mat_colors = Mat_Color_Section()
        self.color_chan_num_section = Color_Chan_Num_Section()
        self.color_chan_info_section = Color_Chan_Info_Section()
        self.tex_gen_num_section = Tex_Gen_Num_Section()
        self.tex_coord_info_section = Tex_Coord_Info_Section()
        self.tex_mtx_info_section = Tex_Mtx_Info_Section()
        self.tex_no_section = Tex_No_Section()
        self.font_no_section = Font_No_Section()
        self.tev_order_info_section = Tev_Order_Info_Section()
        self.tev_color_section = Tev_Color_Section()
        self.tev_k_color_section = Tev_K_Color_Section()
        self.tev_stage_num_section = Tev_Stage_Num_Section()
        self.tev_stage_info_section = Tev_Stage_Info_Section()
        self.tev_swap_mode_info_section = Tev_Swap_Mode_Info_Section()
        self.tev_swap_mode_table_info_section = Tev_Swap_Mode_Table_Info_Section()
        self.alpha_comp_info_section = Alpha_Comp_Info_Section()
        self.blend_info_section = Blend_Info_Section()
        self.dither_section = Dither_Section()


class MAT1_Section_Offsets:
    def __init__(self, data: BytesIO):
        self.mat_init_data_offset = int.from_bytes(data.read(4), byteorder='big')
        self.mat_init_data_indexes_offset = int.from_bytes(data.read(4), byteorder='big')
        self.offset_3 = int.from_bytes(data.read(4), byteorder='big')
        self.ind_init_data_offset = int.from_bytes(data.read(4), byteorder='big')
        self.cull_mode_offset = int.from_bytes(data.read(4), byteorder='big')
        self.mat_color_offset = int.from_bytes(data.read(4), byteorder='big')
        self.color_chan_num_offset = int.from_bytes(data.read(4), byteorder='big')
        self.color_chan_info_offset = int.from_bytes(data.read(4), byteorder='big')
        self.tex_gen_num_offset = int.from_bytes(data.read(4), byteorder='big')
        self.tex_coord_info_offset = int.from_bytes(data.read(4), byteorder='big')
        self.tex_mtx_info_offset = int.from_bytes(data.read(4), byteorder='big')
        self.tex_no_offset = int.from_bytes(data.read(4), byteorder='big')
        self.font_no_offset = int.from_bytes(data.read(4), byteorder='big')
        self.tev_order_info_offset = int.from_bytes(data.read(4), byteorder='big')
        self.tev_color_offset = int.from_bytes(data.read(4), byteorder='big')
        self.tev_k_color_offset = int.from_bytes(data.read(4), byteorder='big')
        self.tev_stage_num_offset = int.from_bytes(data.read(4), byteorder='big')
        self.tev_stage_info_offset = int.from_bytes(data.read(4), byteorder='big')
        self.tev_swap_mode_info_offset = int.from_bytes(data.read(4), byteorder='big')
        self.alpha_comp_info_offset = int.from_bytes(data.read(4), byteorder='big')
        self.blend_info_offset = int.from_bytes(data.read(4), byteorder='big')
        self.dither_offset = int.from_bytes(data.read(4), byteorder='big')


# Mat Init Data ------------------------
class Mat_Init_Data_Section:
    def __init__(self, data: BytesIO):
        self.mat_init_data: List[J2D_Material_Init_Data] = []
        while True:
            initData = J2D_Material_Init_Data(data)
        self.padding = bytes()


class J2D_Material_Init_Data:
    def __init__(self, data: BytesIO):
        self.mat_mode = data.read(1)
        self.cull_mode_idx = data.read(1)
        self.color_chan_num_idx = bytes()
        self.tex_gen_num_idx = bytes()
        self.tev_stage_num_idx = bytes()
        self.dither_idx = bytes()
        self.mat_alpha_calc = bytes()
        self.unknown_field_7 = bytes()
        self.mat_color_idx_tbl: List[bytes] = []
        self.color_chan_info_idx_tbl: List[bytes] = []
        self.tex_coord_info_idx_tbl: List[bytes] = []
        self.tex_mtx_info_idx_tbl: List[bytes] = []
        self.tex_no_idx_tbl: List[bytes] = []
        self.font_no_idx = bytes()
        self.tev_k_color_idx_tbl: List[bytes] = []
        self.tev_k_color_sel: List[bytes] = []
        self.tev_k_alpha_sel: List[bytes] = []
        self.tev_order_info_idx_tbl: List[bytes] = []
        self.tev_color_idx_tbl: List[bytes] = []
        self.tev_stage_info_idx_tbl: List[bytes] = []
        self.tev_swap_mode_info_idx_tbl: List[bytes] = []
        self.tev_swap_mode_tbl_info_idx_tbl: List[bytes] = []
        self.alpha_comp_info_idx = bytes()
        self.blend_info_idx = bytes()
        self.unknown_field_E6 = bytes()
# --------------------------------------


# Mat Init Data Idx ---------------------
class Mat_Init_Data_Idx_Section:
    def __init__(self):
        self.indexes: List[bytes] = []
        self.padding = bytes()
# --------------------------------------


class Unknown_Section:
    def __init__(self):
        self.data = bytes()


# Cull Modes ---------------------------
class Cull_Mode_Section:
    def __init__(self):
        self.cull_modes: List[int] = []
        self.padding = bytes()
# --------------------------------------


# Mat Colors ---------------------------
class Mat_Color_Section:
    def __init__(self):
        self.colors: List[GXColor] = []
        self.padding = bytes()


class GXColor:
    def __init__(self):
        self.r = bytes()
        self.g = bytes()
        self.b = bytes()
        self.a = bytes()
# --------------------------------------


# Color Chan Nums ----------------------
class Color_Chan_Num_Section:
    def __init__(self):
        self.color_chan_num: List[bytes] = []
        self.padding = bytes()
# --------------------------------------


# Color Chan Info ----------------------
class Color_Chan_Info_Section:
    def __init__(self):
        self.color_chan_info: List[J2D_Color_Chan_Info] = []
        self.padding = bytes()


class J2D_Color_Chan_Info:
    def __init__(self):
        self.field_0x0 = bytes()
        self.field_0x1 = bytes()
        self.field_0x2 = bytes()
        self.field_0x3 = bytes()
# --------------------------------------


# Tex Gen Num --------------------------
class Tex_Gen_Num_Section:
    def __init__(self):
        self.tex_gen_num: List[bytes] = []
        self.padding = bytes()
# --------------------------------------


# Tex Coord Info -----------------------
class Tex_Coord_Info_Section:
    def __init__(self):
        self.tex_coord_info: List[J2D_Tex_Coord_Info] = []
        self.padding = bytes()


class J2D_Tex_Coord_Info:
    def __init__(self):
        self.tex_gen_type = bytes()
        self.tex_gen_src = bytes()
        self.tex_gen_mtx = bytes()
        self.padding = bytes()
# --------------------------------------


# Tex Mtx Info -------------------------
class Tex_Mtx_Info_Section:
    def __init__(self):
        self.tex_mtx_info: List[J2D_Tex_Mtx_Info] = []
        self.padding = bytes()


class J2D_Tex_Mtx_Info:
    def __init__(self):
        self.tex_mtx_type = bytes()
        self.tex_mtx_dcc = bytes()
        self.field_0x2 = bytes()
        self.field_0x3 = bytes()
        self.center_x = 0.0
        self.center_y = 0.0
        self.center_z = 0.0
        self.tex_srt_info = J2D_Texture_SRT_Info()


class J2D_Texture_SRT_Info:
    def __init__(self):
        self.scale_x = 0.0
        self.scale_y = 0.0
        self.rotation_deg = 0.0
        self.translation_x = 0.0
        self.translation_y = 0.0
# --------------------------------------


# Tex No -------------------------------
class Tex_No_Section:
    def __init__(self):
        self.tex_no: List[bytes] = []
        self.padding = bytes()
# --------------------------------------


# Font No ------------------------------
class Font_No_Section:
    def __init__(self):
        self.font_no: List[bytes] = []
        self.padding = bytes()
# --------------------------------------


# Tev Order Info -----------------------
class Tev_Order_Info_Section:
    def __init__(self):
        self.tev_order_info: List[J2D_Tev_Order_Info] = []
        self.padding = bytes()


class J2D_Tev_Order_Info:
    def __init__(self):
        self.tex_coord = bytes()
        self.tex_map = bytes()
        self.color = bytes()
        self.field_0x3 = bytes()
# --------------------------------------


# Tev Color ----------------------------
class Tev_Color_Section:
    def __init__(self):
        self.tev_color: List[GXColorS10] = []
        self.padding = bytes()


class GXColorS10:
    def __init__(self):
        self.r = bytes()
        self.g = bytes()
        self.b = bytes()
        self.a = bytes()
# --------------------------------------


# TevK Color ---------------------------
class Tev_K_Color_Section:
    def __init__(self):
        self.tev_k_color: List[GXColor] = []
        self.padding = bytes()
# --------------------------------------


# Tev Stage Num ------------------------
class Tev_Stage_Num_Section:
    def __init__(self):
        self.tev_stage_num: List[bytes] = []
        self.padding = bytes()
# --------------------------------------


# Tev Stage Info -----------------------
class Tev_Stage_Info_Section:
    def __init__(self):
        self.tev_stage_info: List[J2D_Tev_Stage_Info] = []
        self.padding = bytes()


class J2D_Tev_Stage_Info:
    def __init__(self):
        self.field_0x0 = bytes()
        self.color_a = bytes()
        self.color_b = bytes()
        self.color_c = bytes()
        self.color_d = bytes()
        self.c_op = bytes()
        self.c_bias = bytes()
        self.c_scale = bytes()
        self.c_clamp = bytes()
        self.c_reg = bytes()
        self.alpha_a = bytes()
        self.alpha_b = bytes()
        self.alpha_c = bytes()
        self.alpha_d = bytes()
        self.a_op = bytes()
        self.a_bias = bytes()
        self.a_scale = bytes()
        self.a_clamp = bytes()
        self.a_reg = bytes()
        self.field_0x13 = bytes()
# --------------------------------------


# Tev Swap Mode Info -------------------
class Tev_Swap_Mode_Info_Section:
    def __init__(self):
        self.tev_swap_mode_info: List[J2D_Tev_Swap_Mode_Info] = []
        self.padding = bytes()


class J2D_Tev_Swap_Mode_Info:
    def __init__(self):
        self.ras_sel = bytes()
        self.tex_sel = bytes()
        self.field_0x2 = bytes()
        self.field_0x3 = bytes()
# --------------------------------------


# Tev Swap Mode Table Info -------------
class Tev_Swap_Mode_Table_Info_Section:
    def __init__(self):
        self.tev_swap_mode_table_info: List[J2D_Tev_Swap_Mode_Table_Info] = []
        self.padding = bytes()


class J2D_Tev_Swap_Mode_Table_Info:
    def __init__(self):
        self.field_0x0 = bytes()
        self.field_0x1 = bytes()
        self.field_0x2 = bytes()
        self.field_0x3 = bytes()
# --------------------------------------


# Alpha Comp Info ----------------------
class Alpha_Comp_Info_Section:
    def __init__(self):
        self.alpha_comp_info: List[J2D_Alpha_Comp_Info] = []
        self.padding = bytes()


class J2D_Alpha_Comp_Info:
    def __init__(self):
        self.field_0x0 = bytes()
        self.field_0x1 = bytes()
        self.ref_0 = bytes()
        self.ref_1 = bytes()
        self.field_0x4 = bytes()
        self.field_0x5 = bytes()
        self.field_0x6 = bytes()
        self.field_0x7 = bytes()
# --------------------------------------


# Blend Info ---------------------------
class Blend_Info_Section:
    def __init__(self):
        self.blend_info: List[J2D_Blend_Info] = []
        self.padding = bytes()


class J2D_Blend_Info:
    def __init__(self):
        self.type = bytes()
        self.src_factor = bytes()
        self.dst_factor = bytes()
        self.op = bytes()
# --------------------------------------


# Dither -------------------------------
class Dither_Section:
    def __init__(self):
        self.dither: List[bytes] = []
        self.padding = bytes()
# --------------------------------------
# --------------------------------------------------------------------------------------


# Elements -----------------------------------------------------------------------------
class PAN1:
    def __init__(self):
        self.magic = bytes()
        self.size = 0
        self.param_num = bytes()
        self.visible = bytes()
        self.padding = bytes()
        self.info_tag = bytes()
        self.bounds_x0 = bytes()
        self.bounds_y0 = bytes()
        self.panel_height = bytes()
        self.panel_width = bytes()
        self.angle = bytes()
        self.anchor = bytes()
        self.alpha = bytes()
        self.inherit_alpha = bytes()


class PAN2:
    def __init__(self, data: BytesIO, isParent: bool):
        #     self.tag = bytes()
        #     self.tag_size = 0
        #     self.magic = bytes()
        #     self.size = 0
        #     self.field_0x8 = bytes()
        #     self.field_0xa = bytes()
        #     self.visible = bytes()
        #     self.base_position = bytes()
        #     self.padding = bytes()
        #     self.info_tag = bytes()
        #     self.user_info_tag = bytes()
        #     self.rot_offset_x = 0.0
        #     self.rot_offset_y = 0.0
        #     self.scale_x = 0.0
        #     self.scale_y = 0.0
        #     self.rotate_x = 0.0
        #     self.rotate_y = 0.0
        #     self.rotate_z = 0.0
        #     self.translate_x = 0.0
        #     self.translate_y = 0.0
        #     self.end_padding = bytes()
        #     self.child_nodes: List[Union[PAN2 | PIC2 | TBX2]] = []
        #     self.end_tag = bytes()
        #     self.end_tag_size = 0

        # def parse_bytes(self, data: BytesIO):
        # Check for BGN1 tag
        old_pos = data.tell()
        tag = data.read(4)
        if tag:
            self.tag = tag
            self.tag_size = int.from_bytes(data.read(4), byteorder='big')
        else:
            data.seek(old_pos)

        # Parse PAN2 data
        self.magic = data.read(4)
        self.size = int.from_bytes(data.read(4), byteorder='big')
        self.field_0x8 = data.read(2)
        self.field_0xa = data.read(2)
        self.visible = data.read(1)
        self.base_position = data.read(1)
        self.padding = data.read(2)
        self.info_tag = data.read(8)
        self.user_info_tag = data.read(8)
        self.rot_offset_x = float.fromhex(data.read(4).hex())
        self.rot_offset_y = float.fromhex(data.read(4).hex())
        self.scale_x = float.fromhex(data.read(4).hex())
        self.scale_y = float.fromhex(data.read(4).hex())
        self.rotate_x = float.fromhex(data.read(4).hex())
        self.rotate_y = float.fromhex(data.read(4).hex())
        self.rotate_z = float.fromhex(data.read(4).hex())
        self.translate_x = float.fromhex(data.read(4).hex())
        self.translate_y = float.fromhex(data.read(4).hex())
        self.end_padding = data.read(4)

        if isParent:
            self.child_nodes: List[Union[PAN2 | PIC2 | TBX2]] = []
            while True:
                old_pos = data.tell()
                tag = data.read(4)
                if tag == b'BGN1':
                    tag_size = data.read(int.from_bytes(data.read(4), byteorder='big'))
                    data.seek(old_pos)
                    data.read(tag_size)
                    # Determine child node(s) type
                    magic = data.read(4)
                    data.seek(old_pos)
                    match magic:
                        case b'PAN2':
                            if self.child_nodes[0]:
                                self.child_nodes.append(PAN2(data, True))
                            else:
                                self.child_nodes.insert(0, PAN2(data, True))

                        case b'PIC2':
                            if self.child_nodes[0]:
                                self.child_nodes.append(PIC2(data))
                            else:
                                self.child_nodes.insert(0, PIC2(data))

                        case b'TBX2':
                            if self.child_nodes[0]:
                                self.child_nodes.append(TBX2(data))
                            else:
                                self.child_nodes.insert(0, TBX2(data))
                elif tag == b'PIC2':
                    if self.child_nodes[0]:
                        self.child_nodes.append(PIC2(data))
                    else:
                        self.child_nodes.insert(0, PIC2(data))
                elif tag == b'TBX2':
                    if self.child_nodes[0]:
                        self.child_nodes.append(TBX2(data))
                    else:
                        self.child_nodes.insert(0, TBX2(data))
                elif tag == b'END1' or tag == b'EXT1':
                    break

            self.end_tag = tag
            self.end_tag_size = data.read(4)

    def to_bytes(self) -> bytes:
        out = bytearray()
        return out


class PIC2:
    def __init__(self, data: BytesIO):
        current_pos = 0
        self.magic = data.read(4)
        self.size = int.from_bytes(data.read(4), byteorder='big')
        self.base_pan2 = PAN2(data, False)
        self.field_0x0 = data.read(2)
        self.material_num = data.read(2)
        self.field_0x4 = data.read(2)
        self.field_0x6 = data.read(2)
        self.field_0x8: List[bytes] = [data.read(2), data.read(2), data.read(2), data.read(2)]
        self.field_0x10: List[bytes] = [data.read(2), data.read(2), data.read(2), data.read(2), data.read(2), data.read(2), data.read(2), data.read(2)]
        self.corner_color: List[bytes] = [data.read(4), data.read(4), data.read(4), data.read(4)]
        current_pos += 56 + len(self.base_pan2)
        self.end_padding = data.read(self.size - current_pos)


class TBX2:
    def __init__(self, data: BytesIO):
        current_pos = 0
        self.magic = data.read(4)
        self.size = int.from_bytes(data.read(4), byteorder='big')
        self.base_pan2 = PAN2(data, False)
        self.field_0x0 = data.read(2)
        self.field_0x2 = data.read(2)
        self.material_num = data.read(2)
        self.char_space = data.read(2)
        self.line_space = data.read(2)
        self.font_size_x = data.read(2)
        self.font_size_y = data.read(2)
        self.h_bind = data.read(1)
        self.v_bind = data.read(1)
        self.char_color = data.read(4)
        self.grad_color = data.read(4)
        self.connected = data.read(1)
        self.field_0x19 = data.read(3)
        self.field_0x1c = data.read(2)
        self.field_0x1e = data.read(2)
        current_pos += 40 + len(self.base_pan2)
        self.end_padding = data.read(self.size - current_pos)
# --------------------------------------------------------------------------------------
