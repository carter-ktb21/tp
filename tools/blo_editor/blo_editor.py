import os
import argparse
import struct
from gclib.gcm import GCM
from gclib.rarc import RARC, RARCFileEntry
from gclib.yaz0_yay0 import Yaz0
from io import BytesIO
from typing import List, Union
import xml.etree.ElementTree as ET
from pathlib import Path
from tkinter import Tk
from tkinter.filedialog import askopenfilename, asksaveasfilename

Tk().withdraw()


# Bytes to int helper function
def bytes_to_int(data: bytes) -> int:
    return int.from_bytes(data, byteorder='big', signed=True)


def parse_blo(blo_bytes: BytesIO):
    return BLO(blo_bytes)


class BLO:
    def __init__(self, data: BytesIO):
        data.seek(0)
        self.tag = data.read(4)
        self.type = data.read(4)
        self.size = bytes_to_int(data.read(4))
        self.blocks = bytes_to_int(data.read(4))
        self.header_padding = data.read(16)
        self.inf1_section = INF1_Section(data)
        self.tex1_section = TEX1_Section(data)
        self.fnt1_section = FNT1_Section(data)
        self.mat1_section = MAT1_Section(data)
        self.elements = PAN2(data, True)

    def to_bytes(self):
        out = bytearray()
        


class INF1_Section:
    def __init__(self, data: BytesIO):
        self.magic = data.read(4)
        self.size = bytes_to_int(data.read(4))
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
        if bytes_to_int(self.header.texture_count) > 0:
            for i in range(int.from_bytes(self.offset_count, byteorder='big')):
                self.offsets.insert(i, data.read(2))
            self.texture_refs: List[TEX1_Reference] = []
            for i in range(int.from_bytes(self.offset_count, byteorder='big')):
                if i + 1 < int.from_bytes(self.offset_count, byteorder='big'):
                    ref = TEX1_Reference()
                    ref_size = int.from_bytes(self.offsets[i + 1], byteorder='big') - int.from_bytes(self.offsets[i], byteorder='big') - 1
                    ref.res_type = data.read(1)
                    ref.texture = data.read(ref_size)
                    self.texture_refs.insert(i, ref)
                else:
                    ref = TEX1_Reference()
                    ref.res_type = data.read(1)
                    size = self.size_after_header - int.from_bytes(self.offsets[i], byteorder='big') - 1
                    ref.texture = data.read(size)
                    self.texture_refs.insert(i, ref)
        else:
            self.padding = data.read(14)


class TEX1_Header:
    def __init__(self, data: BytesIO):
        self.magic = data.read(4)
        self.section_size = bytes_to_int(data.read(4))
        self.texture_count = data.read(2)
        self.padding = data.read(2)
        self.header_size = bytes_to_int(data.read(4))


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
        if bytes_to_int(self.header.font_count) > 0:
            for i in range(int.from_bytes(self.offset_count, byteorder='big')):
                self.offsets.insert(i, data.read(2))
            self.font_refs: List[FNT1_Reference] = []
            for i in range(int.from_bytes(self.offset_count, byteorder='big')):
                if i + 1 < int.from_bytes(self.offset_count, byteorder='big'):
                    ref = FNT1_Reference()
                    ref_size = int.from_bytes(self.offsets[i + 1], byteorder='big') - int.from_bytes(self.offsets[i], byteorder='big') - 1
                    ref.res_type = data.read(1)
                    ref.font = data.read(ref_size)
                    self.font_refs.insert(i, ref)
                else:
                    ref = FNT1_Reference()
                    ref.res_type = data.read(1)
                    size = self.size_after_header - int.from_bytes(self.offsets[i], byteorder='big') - 1
                    ref.font = data.read(size)
                    self.font_refs.insert(i, ref)
        else:
            self.padding = data.read(14)


class FNT1_Header:
    def __init__(self, data: BytesIO):
        self.magic = data.read(4)
        self.section_size = bytes_to_int(data.read(4))
        self.font_count = data.read(2)
        self.padding = data.read(2)
        self.header_size = bytes_to_int(data.read(4))


class FNT1_Reference:
    def __init__(self):
        self.res_type = bytes()
        self.font = bytes()
# --------------------------------------------------------------------------------------


# MAT1 ---------------------------------------------------------------------------------
class MAT1_Section:
    def __init__(self, data: BytesIO):
        self.magic = data.read(4)
        self.size = bytes_to_int(data.read(4))
        self.material_count = data.read(2)
        self.padding = data.read(2)
        self.offsets = MAT1_Section_Offsets(data)
        self.mat_init_section = Mat_Init_Data_Section(data, self.offsets)
        self.mat_init_idx_section = Mat_Init_Data_Idx_Section(data, self.offsets)
        self.unknown_section = Unknown_Section(data, self.offsets)
        self.ind_init_data_section = Ind_Init_Data_Section(data, self.offsets)
        self.cull_modes = Cull_Mode_Section(data, self.offsets, self.mat_init_section)
        self.mat_colors = Mat_Color_Section(data, self.offsets, self.mat_init_section)
        self.color_chan_num_section = Color_Chan_Num_Section(data, self.offsets, self.mat_init_section)
        self.color_chan_info_section = Color_Chan_Info_Section(data, self.offsets, self.mat_init_section)
        self.tex_gen_num_section = Tex_Gen_Num_Section(data, self.offsets, self.mat_init_section)
        self.tex_coord_info_section = Tex_Coord_Info_Section(data, self.offsets, self.mat_init_section)
        self.tex_mtx_info_section = Tex_Mtx_Info_Section(data, self.offsets, self.mat_init_section)
        self.tex_no_section = Tex_No_Section(data, self.offsets, self.mat_init_section)
        self.font_no_section = Font_No_Section(data, self.offsets, self.mat_init_section)
        self.tev_order_info_section = Tev_Order_Info_Section(data, self.offsets, self.mat_init_section)
        self.tev_color_section = Tev_Color_Section(data, self.offsets, self.mat_init_section)
        self.tev_k_color_section = Tev_K_Color_Section(data, self.offsets, self.mat_init_section)
        self.tev_stage_num_section = Tev_Stage_Num_Section(data, self.offsets, self.mat_init_section)
        self.tev_stage_info_section = Tev_Stage_Info_Section(data, self.offsets, self.mat_init_section)
        self.tev_swap_mode_info_section = Tev_Swap_Mode_Info_Section(data, self.offsets, self.mat_init_section)
        self.tev_swap_mode_table_info_section = Tev_Swap_Mode_Table_Info_Section(data, self.offsets, self.mat_init_section)
        self.alpha_comp_info_section = Alpha_Comp_Info_Section(data, self.offsets, self.mat_init_section)
        self.blend_info_section = Blend_Info_Section(data, self.offsets, self.mat_init_section)
        self.dither_section = Dither_Section(data, self, self.offsets, self.mat_init_section)


class MAT1_Section_Offsets:
    def __init__(self, data: BytesIO):
        self.mat_init_data_offset = bytes_to_int(data.read(4))
        self.mat_init_data_indexes_offset = bytes_to_int(data.read(4))
        self.offset_3 = bytes_to_int(data.read(4))
        self.ind_init_data_offset = bytes_to_int(data.read(4))
        self.cull_mode_offset = bytes_to_int(data.read(4))
        self.mat_color_offset = bytes_to_int(data.read(4))
        self.color_chan_num_offset = bytes_to_int(data.read(4))
        self.color_chan_info_offset = bytes_to_int(data.read(4))
        self.tex_gen_num_offset = bytes_to_int(data.read(4))
        self.tex_coord_info_offset = bytes_to_int(data.read(4))
        self.tex_mtx_info_offset = bytes_to_int(data.read(4))
        self.tex_no_offset = bytes_to_int(data.read(4))
        self.font_no_offset = bytes_to_int(data.read(4))
        self.tev_order_info_offset = bytes_to_int(data.read(4))
        self.tev_color_offset = bytes_to_int(data.read(4))
        self.tev_k_color_offset = bytes_to_int(data.read(4))
        self.tev_stage_num_offset = bytes_to_int(data.read(4))
        self.tev_stage_info_offset = bytes_to_int(data.read(4))
        self.tev_swap_mode_info_offset = bytes_to_int(data.read(4))
        self.tev_swap_mode_table_info_offset = bytes_to_int(data.read(4))
        self.alpha_comp_info_offset = bytes_to_int(data.read(4))
        self.blend_info_offset = bytes_to_int(data.read(4))
        self.dither_offset = bytes_to_int(data.read(4))

    def find_next_valid_offset(self, current_offset: int):
        offsets = [
            self.mat_init_data_offset,
            self.mat_init_data_indexes_offset,
            self.offset_3,
            self.ind_init_data_offset,
            self.cull_mode_offset,
            self.mat_color_offset,
            self.color_chan_num_offset,
            self.color_chan_info_offset,
            self.tex_gen_num_offset,
            self.tex_coord_info_offset,
            self.tex_mtx_info_offset,
            self.tex_no_offset,
            self.font_no_offset,
            self.tev_order_info_offset,
            self.tev_color_offset,
            self.tev_k_color_offset,
            self.tev_stage_num_offset,
            self.tev_stage_info_offset,
            self.tev_swap_mode_info_offset,
            self.tev_swap_mode_table_info_offset,
            self.alpha_comp_info_offset,
            self.blend_info_offset,
            self.dither_offset,
        ]

        candidates = [
            o for o in offsets
            if o != 0 and o > current_offset
        ]

        if not candidates:
            return None

        return min(candidates)


# Mat Init Data ------------------------
class Mat_Init_Data_Section:
    def __init__(self, data: BytesIO, offsets: MAT1_Section_Offsets):
        blockCount = (offsets.mat_init_data_indexes_offset - offsets.mat_init_data_offset) // 232
        self.mat_init_data: List[J2D_Material_Init_Data] = []
        for i in range(blockCount):
            initData = J2D_Material_Init_Data(data)
            self.mat_init_data.insert(i, initData)
        self.padding = data.read((offsets.mat_init_data_indexes_offset - offsets.mat_init_data_offset) - (blockCount * 232))

        # Get number of values for each data section
        self.cull_mode_count = int(0)
        self.mat_color_count = int(0)
        self.color_chan_num_count = int(0)
        self.color_chan_info_count = int(0)
        self.tex_gen_num_count = int(0)
        self.tex_coord_info_count = int(0)
        self.tex_mtx_info_count = int(0)
        self.tex_no_count = int(0)
        self.font_no_count = int(0)
        self.tev_order_info_count = int(0)
        self.tev_color_count = int(0)
        self.tev_k_color_count = int(0)
        self.tev_stage_num_count = int(0)
        self.tev_stage_info_count = int(0)
        self.tev_swap_mode_info_count = int(0)
        self.tev_swap_mode_table_info_count = int(0)
        self.alpha_comp_info_count = int(0)
        self.blend_info_count = int(0)
        self.dither_count = int(0)
        for i, matInitData in enumerate(self.mat_init_data):
            # Cull Modes
            cullModeCount = bytes_to_int(self.mat_init_data[i].cull_mode_idx)
            if cullModeCount > self.cull_mode_count:
                self.cull_mode_count = cullModeCount
            
            # Mat Colors
            for j in range(1):
                matColorCount = bytes_to_int(self.mat_init_data[i].mat_color_idx_tbl[j])
                if matColorCount > self.mat_color_count:
                    self.mat_color_count = matColorCount

            # Color Chan Nums
            colorChanNumCount = bytes_to_int(self.mat_init_data[i].color_chan_num_idx)
            if colorChanNumCount > self.color_chan_num_count:
                self.color_chan_num_count = colorChanNumCount

            # Color Chan Info
            for j in range(3):
                colorChanInfoCount = bytes_to_int(self.mat_init_data[i].color_chan_info_idx_tbl[j])
                if colorChanInfoCount > self.color_chan_info_count:
                    self.color_chan_info_count = colorChanInfoCount

            # Tex Gen Num
            texGenNumCount = bytes_to_int(self.mat_init_data[i].tex_gen_num_idx)
            if texGenNumCount > self.tex_gen_num_count:
                self.tex_gen_num_count = texGenNumCount

            # Tex Coord Info
            for j in range(7):
                texCoordInfoCount = bytes_to_int(self.mat_init_data[i].tex_coord_info_idx_tbl[j])
                if texCoordInfoCount > self.tex_coord_info_count:
                    self.tex_coord_info_count = texCoordInfoCount

            # Tex Mtx Info
            for j in range(9):
                texMtxInfoCount = bytes_to_int(self.mat_init_data[i].tex_mtx_info_idx_tbl[j])
                if texMtxInfoCount > self.tex_mtx_info_count:
                    self.tex_mtx_info_count = texMtxInfoCount

            # Tex No
            for j in range(7):
                texNoCount = bytes_to_int(self.mat_init_data[i].tex_no_idx_tbl[j])
                if texNoCount > self.tex_no_count:
                    self.tex_no_count = texNoCount

            # Font No
            fontNoCount = bytes_to_int(self.mat_init_data[i].font_no_idx)
            if fontNoCount > self.font_no_count:
                self.font_no_count = fontNoCount

            # Tev Order Info
            for j in range(15):
                tevOrderInfoCount = bytes_to_int(self.mat_init_data[i].tev_order_info_idx_tbl[j])
                if tevOrderInfoCount > self.tev_order_info_count:
                    self.tev_order_info_count = tevOrderInfoCount

            # Tev Color
            for j in range(3):
                tevColorCount = bytes_to_int(self.mat_init_data[i].tev_color_idx_tbl[j])
                if tevColorCount > self.tev_color_count:
                    self.tev_color_count = tevColorCount

            # TevK Color
            for j in range(3):
                tevKColorCount = bytes_to_int(self.mat_init_data[i].tev_k_color_idx_tbl[j])
                if tevKColorCount > self.tev_k_color_count:
                    self.tev_k_color_count = tevKColorCount

            # Tev Stage Num
            tevStageNumCount = bytes_to_int(self.mat_init_data[i].tev_stage_num_idx)
            if tevStageNumCount > self.tev_stage_num_count:
                self.tev_stage_num_count = tevStageNumCount

            # Tev Stage Info
            for j in range(15):
                tevStageInfoCount = bytes_to_int(self.mat_init_data[i].tev_stage_info_idx_tbl[j])
                if tevStageInfoCount > self.tev_stage_info_count:
                    self.tev_stage_info_count = tevStageInfoCount

            # Tev Swap Mode Info
            for j in range(15):
                tevSwapModeInfoCount = bytes_to_int(self.mat_init_data[i].tev_swap_mode_info_idx_tbl[j])
                if tevSwapModeInfoCount > self.tev_swap_mode_info_count:
                    self.tev_swap_mode_info_count = tevSwapModeInfoCount

            # Tev Swap Mode Table Info
            for j in range(3):
                tevSwapModeTableInfoCount = bytes_to_int(self.mat_init_data[i].tev_swap_mode_tbl_info_idx_tbl[j])
                if tevSwapModeTableInfoCount > self.tev_swap_mode_table_info_count:
                    self.tev_swap_mode_table_info_count = tevSwapModeTableInfoCount

            # Alpha Comp Info
            alphaCompInfoCount = bytes_to_int(self.mat_init_data[i].alpha_comp_info_idx)
            if alphaCompInfoCount > self.alpha_comp_info_count:
                self.alpha_comp_info_count = alphaCompInfoCount

            # Blend Info
            blendInfoCount = bytes_to_int(self.mat_init_data[i].blend_info_idx)
            if blendInfoCount > self.blend_info_count:
                self.blend_info_count = blendInfoCount

            # Dither
            ditherCount = bytes_to_int(self.mat_init_data[i].dither_idx)
            if ditherCount > self.dither_count:
                self.dither_count = ditherCount
        self.cull_mode_count += 1
        self.mat_color_count += 1
        self.color_chan_num_count += 1
        self.color_chan_info_count += 1
        self.tex_gen_num_count += 1
        self.tex_coord_info_count += 1
        self.tex_mtx_info_count += 1
        self.tex_no_count += 1
        self.font_no_count += 1
        self.tev_order_info_count += 1
        self.tev_color_count += 1
        self.tev_k_color_count += 1
        self.tev_stage_num_count += 1
        self.tev_stage_info_count += 1
        self.tev_swap_mode_info_count += 1
        self.tev_swap_mode_table_info_count += 1
        self.alpha_comp_info_count += 1
        self.blend_info_count += 1
        self.dither_count += 1

class J2D_Material_Init_Data:
    def __init__(self, data: BytesIO):
        self.mat_mode = data.read(1)
        self.cull_mode_idx = data.read(1)
        self.color_chan_num_idx = data.read(1)
        self.tex_gen_num_idx = data.read(1)
        self.tev_stage_num_idx = data.read(1)
        self.dither_idx = data.read(1)
        self.mat_alpha_calc = data.read(1)
        self.unknown_field_7 = data.read(1)
        self.mat_color_idx_tbl: List[bytes] = [data.read(2), data.read(2)]
        self.color_chan_info_idx_tbl: List[bytes] = [data.read(2), data.read(2), data.read(2), data.read(2)]
        self.tex_coord_info_idx_tbl: List[bytes] = [data.read(2), data.read(2), data.read(2), data.read(2), data.read(2), data.read(2), data.read(2), data.read(2)]
        self.tex_mtx_info_idx_tbl: List[bytes] = [data.read(2), data.read(2), data.read(2), data.read(2), data.read(2), data.read(2), data.read(2), data.read(2), data.read(2), data.read(2)]
        self.tex_no_idx_tbl: List[bytes] = [data.read(2), data.read(2), data.read(2), data.read(2), data.read(2), data.read(2), data.read(2), data.read(2)]
        self.font_no_idx = data.read(2)
        self.tev_k_color_idx_tbl: List[bytes] = [data.read(2), data.read(2), data.read(2), data.read(2)]
        self.tev_k_color_sel: List[bytes] = [data.read(1), data.read(1), data.read(1), data.read(1), data.read(1), data.read(1), data.read(1), data.read(1),
                                             data.read(1), data.read(1), data.read(1), data.read(1), data.read(1), data.read(1), data.read(1), data.read(1)]
        self.tev_k_alpha_sel: List[bytes] = [data.read(1), data.read(1), data.read(1), data.read(1), data.read(1), data.read(1), data.read(1), data.read(1),
                                             data.read(1), data.read(1), data.read(1), data.read(1), data.read(1), data.read(1), data.read(1), data.read(1)]
        self.tev_order_info_idx_tbl: List[bytes] = [data.read(2), data.read(2), data.read(2), data.read(2), data.read(2), data.read(2), data.read(2), data.read(2),
                                                    data.read(2), data.read(2), data.read(2), data.read(2), data.read(2), data.read(2), data.read(2), data.read(2)]
        self.tev_color_idx_tbl: List[bytes] = [data.read(2), data.read(2), data.read(2), data.read(2)]
        self.tev_stage_info_idx_tbl: List[bytes] = [data.read(2), data.read(2), data.read(2), data.read(2), data.read(2), data.read(2), data.read(2), data.read(2),
                                                    data.read(2), data.read(2), data.read(2), data.read(2), data.read(2), data.read(2), data.read(2), data.read(2)]
        self.tev_swap_mode_info_idx_tbl: List[bytes] = [data.read(2), data.read(2), data.read(2), data.read(2), data.read(2), data.read(2), data.read(2), data.read(2),
                                                        data.read(2), data.read(2), data.read(2), data.read(2), data.read(2), data.read(2), data.read(2), data.read(2)]
        self.tev_swap_mode_tbl_info_idx_tbl: List[bytes] = [data.read(2), data.read(2), data.read(2), data.read(2)]
        self.alpha_comp_info_idx = data.read(2)
        self.blend_info_idx = data.read(2)
        self.unknown_field_E6 = data.read(2)
# --------------------------------------


# Mat Init Data Idx ---------------------
class Mat_Init_Data_Idx_Section:
    def __init__(self, data: BytesIO, offsets: MAT1_Section_Offsets):
        if offsets.mat_init_data_indexes_offset > 0:
            indexCount = (offsets.mat_init_data_indexes_offset - offsets.mat_init_data_offset) // 232
            self.indexes: List[bytes] = []
            for i in range(indexCount):
                index = data.read(2)
                self.indexes.insert(i, index)
            # In each section, the padding variable reads the number of bytes left in the section until the next offset. (This can be zero!!!)
            next_offset = offsets.find_next_valid_offset(offsets.mat_init_data_indexes_offset)
            self.padding = data.read((next_offset - offsets.mat_init_data_indexes_offset) - (indexCount * 2))
# --------------------------------------


class Unknown_Section:
    def __init__(self, data: BytesIO, offsets: MAT1_Section_Offsets):
        if offsets.ind_init_data_offset > 0:
            self.data = data.read(offsets.ind_init_data_offset - offsets.offset_3)
        else:
            self.data = data.read(offsets.cull_mode_offset - offsets.offset_3)


# Ind Init Data ------------------------
class Ind_Init_Data_Section:
    def __init__(self, data: BytesIO, offsets: MAT1_Section_Offsets):
        if offsets.ind_init_data_offset > 0:
            data.read(offsets.cull_mode_offset - offsets.ind_init_data_offset)
# --------------------------------------


# Cull Modes ---------------------------
class Cull_Mode_Section:
    def __init__(self, data: BytesIO, offsets: MAT1_Section_Offsets, initData: Mat_Init_Data_Section):
        if offsets.cull_mode_offset > 0:
            self.cull_modes: List[int] = []
            for i in range(initData.cull_mode_count):
                self.cull_modes.insert(i, bytes_to_int(data.read(4)))
            next_offset = offsets.find_next_valid_offset(offsets.cull_mode_offset)
            self.padding = data.read((next_offset - offsets.cull_mode_offset) - ((initData.cull_mode_count) * 4))
# --------------------------------------


# Mat Colors ---------------------------
class Mat_Color_Section:
    def __init__(self, data: BytesIO, offsets: MAT1_Section_Offsets, initData: Mat_Init_Data_Section):
        if offsets.mat_color_offset > 0:
            self.colors: List[GXColor] = []
            for i in range(initData.mat_color_count):
                self.colors.insert(i, GXColor(data))
            next_offset = offsets.find_next_valid_offset(offsets.mat_color_offset)
            self.padding = data.read((next_offset - offsets.mat_color_offset) - ((initData.mat_color_count) * 4))


class GXColor:
    def __init__(self, data: BytesIO):
        self.r = data.read(1)
        self.g = data.read(1)
        self.b = data.read(1)
        self.a = data.read(1)
# --------------------------------------


# Color Chan Nums ----------------------
class Color_Chan_Num_Section:
    def __init__(self, data: BytesIO, offsets: MAT1_Section_Offsets, initData: Mat_Init_Data_Section):
        if offsets.color_chan_num_offset > 0:
            self.color_chan_num: List[bytes] = []
            for i in range(initData.color_chan_num_count):
                self.color_chan_num.insert(i, data.read(1))
            next_offset = offsets.find_next_valid_offset(offsets.color_chan_num_offset)
            self.padding = data.read((next_offset - offsets.color_chan_num_offset) - ((initData.color_chan_num_count)))
# --------------------------------------


# Color Chan Info ----------------------
class Color_Chan_Info_Section:
    def __init__(self, data: BytesIO, offsets: MAT1_Section_Offsets, initData: Mat_Init_Data_Section):
        if offsets.color_chan_info_offset > 0:
            self.color_chan_info: List[J2D_Color_Chan_Info] = []
            for i in range(initData.color_chan_info_count):
                self.color_chan_info.insert(i, J2D_Color_Chan_Info(data))
            next_offset = offsets.find_next_valid_offset(offsets.color_chan_info_offset)
            self.padding = data.read((next_offset - offsets.color_chan_info_offset) - ((initData.color_chan_info_count) * 4))


class J2D_Color_Chan_Info:
    def __init__(self, data: BytesIO):
        self.field_0x0 = data.read(1)
        self.field_0x1 = data.read(1)
        self.field_0x2 = data.read(1)
        self.field_0x3 = data.read(1)
# --------------------------------------


# Tex Gen Num --------------------------
class Tex_Gen_Num_Section:
    def __init__(self, data: BytesIO, offsets: MAT1_Section_Offsets, initData: Mat_Init_Data_Section):
        if offsets.tex_gen_num_offset > 0:
            self.tex_gen_num: List[bytes] = []
            for i in range(initData.tex_gen_num_count):
                self.tex_gen_num.insert(i, data.read(1))
            next_offset = offsets.find_next_valid_offset(offsets.tex_gen_num_offset)
            self.padding = data.read((next_offset - offsets.tex_gen_num_offset) - (initData.tex_gen_num_count))
# --------------------------------------


# Tex Coord Info -----------------------
class Tex_Coord_Info_Section:
    def __init__(self, data: BytesIO, offsets: MAT1_Section_Offsets, initData: Mat_Init_Data_Section):
        if offsets.tex_coord_info_offset > 0:
            count = (offsets.tex_mtx_info_offset - offsets.tex_coord_info_offset) // 4
            self.tex_coord_info: List[J2D_Tex_Coord_Info] = []
            for i in range(initData.tex_coord_info_count):
                self.tex_coord_info.insert(i, J2D_Tex_Coord_Info(data))
            next_offset = offsets.find_next_valid_offset(offsets.tex_coord_info_offset)
            self.padding = data.read((next_offset - offsets.tex_coord_info_offset) - ((initData.tex_coord_info_count) * 4))


class J2D_Tex_Coord_Info:
    def __init__(self, data: BytesIO):
        self.tex_gen_type = data.read(1)
        self.tex_gen_src = data.read(1)
        self.tex_gen_mtx = data.read(1)
        self.padding = data.read(1)
# --------------------------------------


# Tex Mtx Info -------------------------
class Tex_Mtx_Info_Section:
    def __init__(self, data: BytesIO, offsets: MAT1_Section_Offsets, initData: Mat_Init_Data_Section):
        if offsets.tex_mtx_info_offset > 0:
            self.tex_mtx_info: List[J2D_Tex_Mtx_Info] = []
            for i in range(initData.tex_mtx_info_count):
                self.tex_mtx_info.insert(i, J2D_Tex_Mtx_Info(data))
            next_offset = offsets.find_next_valid_offset(offsets.tex_mtx_info_offset)
            self.padding = data.read((next_offset - offsets.tex_mtx_info_offset) - ((initData.tex_mtx_info_count) * 36))


class J2D_Tex_Mtx_Info:
    def __init__(self, data: BytesIO):
        self.tex_mtx_type = data.read(1)
        self.tex_mtx_dcc = data.read(1)
        self.field_0x2 = data.read(1)
        self.field_0x3 = data.read(1)
        self.center_x = struct.unpack('>f', data.read(4))[0]
        self.center_y = struct.unpack('>f', data.read(4))[0]
        self.center_z = struct.unpack('>f', data.read(4))[0]
        self.tex_srt_info = J2D_Texture_SRT_Info(data)


class J2D_Texture_SRT_Info:
    def __init__(self, data: BytesIO):
        self.scale_x = struct.unpack('>f', data.read(4))[0]
        self.scale_y = struct.unpack('>f', data.read(4))[0]
        self.rotation_deg = struct.unpack('>f', data.read(4))[0]
        self.translation_x = struct.unpack('>f', data.read(4))[0]
        self.translation_y = struct.unpack('>f', data.read(4))[0]
# --------------------------------------


# Tex No -------------------------------
class Tex_No_Section:
    def __init__(self, data: BytesIO, offsets: MAT1_Section_Offsets, initData: Mat_Init_Data_Section):
        if offsets.tex_no_offset > 0:
            self.tex_no: List[bytes] = []
            for i in range(initData.tex_no_count):
                self.tex_no.insert(i, data.read(2))
            next_offset = offsets.find_next_valid_offset(offsets.tex_no_offset)
            self.padding = data.read((next_offset - offsets.tex_no_offset) - ((initData.tex_no_count) * 2))
# --------------------------------------


# Font No ------------------------------
class Font_No_Section:
    def __init__(self, data: BytesIO, offsets: MAT1_Section_Offsets, initData: Mat_Init_Data_Section):
        if offsets.font_no_offset > 0:
            self.font_no: List[bytes] = []
            for i in range(initData.font_no_count):
                self.font_no.insert(i, data.read(2))
            next_offset = offsets.find_next_valid_offset(offsets.font_no_offset)
            self.padding = data.read((next_offset - offsets.font_no_offset) - ((initData.font_no_count) * 2))
# --------------------------------------


# Tev Order Info -----------------------
class Tev_Order_Info_Section:
    def __init__(self, data: BytesIO, offsets: MAT1_Section_Offsets, initData: Mat_Init_Data_Section):
        if offsets.tev_order_info_offset > 0:
            self.tev_order_info: List[J2D_Tev_Order_Info] = []
            for i in range(initData.tev_order_info_count):
                self.tev_order_info.insert(i, J2D_Tev_Order_Info(data))
                print(self.tev_order_info[i].tex_coord)
            next_offset = offsets.find_next_valid_offset(offsets.tev_order_info_offset)
            self.padding = data.read((next_offset - offsets.tev_order_info_offset) - ((initData.tev_order_info_count) * 4))


class J2D_Tev_Order_Info:
    def __init__(self, data: BytesIO):
        self.tex_coord = data.read(1)
        self.tex_map = data.read(1)
        self.color = data.read(1)
        self.field_0x3 = data.read(1)
# --------------------------------------


# Tev Color ----------------------------
class Tev_Color_Section:
    def __init__(self, data: BytesIO, offsets: MAT1_Section_Offsets, initData: Mat_Init_Data_Section):
        if offsets.tev_color_offset > 0:
            self.tev_color: List[GXColorS10] = []
            for i in range(initData.tev_color_count):
                self.tev_color.insert(i, GXColorS10(data))
            next_offset = offsets.find_next_valid_offset(offsets.tev_color_offset)
            self.padding = data.read((next_offset - offsets.tev_color_offset) - ((initData.tev_color_count) * 8))


class GXColorS10:
    def __init__(self, data: BytesIO):
        self.r = data.read(2)
        self.g = data.read(2)
        self.b = data.read(2)
        self.a = data.read(2)
# --------------------------------------


# TevK Color ---------------------------
class Tev_K_Color_Section:
    def __init__(self, data: BytesIO, offsets: MAT1_Section_Offsets, initData: Mat_Init_Data_Section):
        if offsets.tev_k_color_offset > 0:
            self.tev_k_color: List[GXColor] = []
            for i in range(initData.tev_k_color_count):
                self.tev_k_color.insert(i, GXColor(data))
            next_offset = offsets.find_next_valid_offset(offsets.tev_k_color_offset)
            self.padding = data.read((next_offset - offsets.tev_k_color_offset) - ((initData.tev_k_color_count) * 4))
# --------------------------------------


# Tev Stage Num ------------------------
class Tev_Stage_Num_Section:
    def __init__(self, data: BytesIO, offsets: MAT1_Section_Offsets, initData: Mat_Init_Data_Section):
        if offsets.tev_stage_num_offset > 0:
            self.tev_stage_num: List[bytes] = []
            for i in range(initData.tev_stage_num_count):
                self.tev_stage_num.insert(i, data.read(1))
            next_offset = offsets.find_next_valid_offset(offsets.tev_stage_num_offset)
            self.padding = data.read((next_offset - offsets.tev_stage_num_offset) - (initData.tev_stage_num_count))
# --------------------------------------


# Tev Stage Info -----------------------
class Tev_Stage_Info_Section:
    def __init__(self, data: BytesIO, offsets: MAT1_Section_Offsets, initData: Mat_Init_Data_Section):
        if offsets.tev_stage_info_offset > 0:
            self.tev_stage_info: List[J2D_Tev_Stage_Info] = []
            for i in range(initData.tev_stage_info_count):
                self.tev_stage_info.insert(i, J2D_Tev_Stage_Info(data))
            next_offset = offsets.find_next_valid_offset(offsets.tev_stage_info_offset)
            self.padding = data.read((next_offset - offsets.tev_stage_info_offset) - ((initData.tev_stage_info_count) * 20))


class J2D_Tev_Stage_Info:
    def __init__(self, data: BytesIO):
        self.field_0x0 = data.read(1)
        self.color_a = data.read(1)
        self.color_b = data.read(1)
        self.color_c = data.read(1)
        self.color_d = data.read(1)
        self.c_op = data.read(1)
        self.c_bias = data.read(1)
        self.c_scale = data.read(1)
        self.c_clamp = data.read(1)
        self.c_reg = data.read(1)
        self.alpha_a = data.read(1)
        self.alpha_b = data.read(1)
        self.alpha_c = data.read(1)
        self.alpha_d = data.read(1)
        self.a_op = data.read(1)
        self.a_bias = data.read(1)
        self.a_scale = data.read(1)
        self.a_clamp = data.read(1)
        self.a_reg = data.read(1)
        self.field_0x13 = data.read(1)
# --------------------------------------


# Tev Swap Mode Info -------------------
class Tev_Swap_Mode_Info_Section:
    def __init__(self, data: BytesIO, offsets: MAT1_Section_Offsets, initData: Mat_Init_Data_Section):
        if offsets.tev_swap_mode_info_offset > 0:
            self.tev_swap_mode_info: List[J2D_Tev_Swap_Mode_Info] = []
            for i in range(initData.tev_swap_mode_info_count):
                self.tev_swap_mode_info.insert(i, J2D_Tev_Swap_Mode_Info(data))
            next_offset = offsets.find_next_valid_offset(offsets.tev_swap_mode_info_offset)
            self.padding = data.read((next_offset - offsets.tev_swap_mode_info_offset) - ((initData.tev_swap_mode_info_count) * 4))


class J2D_Tev_Swap_Mode_Info:
    def __init__(self, data: BytesIO):
        self.ras_sel = data.read(1)
        self.tex_sel = data.read(1)
        self.field_0x2 = data.read(1)
        self.field_0x3 = data.read(1)
# --------------------------------------


# Tev Swap Mode Table Info -------------
class Tev_Swap_Mode_Table_Info_Section:
    def __init__(self, data: BytesIO, offsets: MAT1_Section_Offsets, initData: Mat_Init_Data_Section):
        if offsets.tev_swap_mode_table_info_offset > 0:
            self.tev_swap_mode_table_info: List[J2D_Tev_Swap_Mode_Table_Info] = []
            for i in range(initData.tev_swap_mode_table_info_count):
                self.tev_swap_mode_table_info.insert(i, J2D_Tev_Swap_Mode_Table_Info(data))
            next_offset = offsets.find_next_valid_offset(offsets.tev_swap_mode_table_info_offset)
            self.padding = data.read((next_offset - offsets.tev_swap_mode_table_info_offset) - ((initData.tev_swap_mode_table_info_count) * 4))


class J2D_Tev_Swap_Mode_Table_Info:
    def __init__(self, data: BytesIO):
        self.field_0x0 = data.read(1)
        self.field_0x1 = data.read(1)
        self.field_0x2 = data.read(1)
        self.field_0x3 = data.read(1)
# --------------------------------------


# Alpha Comp Info ----------------------
class Alpha_Comp_Info_Section:
    def __init__(self, data: BytesIO, offsets: MAT1_Section_Offsets, initData: Mat_Init_Data_Section):
        if offsets.alpha_comp_info_offset > 0:
            self.alpha_comp_info: List[J2D_Alpha_Comp_Info] = []
            for i in range(initData.alpha_comp_info_count):
                self.alpha_comp_info.insert(i, J2D_Alpha_Comp_Info(data))
            next_offset = offsets.find_next_valid_offset(offsets.alpha_comp_info_offset)
            self.padding = data.read((next_offset - offsets.alpha_comp_info_offset) - ((initData.alpha_comp_info_count) * 8))


class J2D_Alpha_Comp_Info:
    def __init__(self, data: BytesIO):
        self.field_0x0 = data.read(1)
        self.field_0x1 = data.read(1)
        self.ref_0 = data.read(1)
        self.ref_1 = data.read(1)
        self.field_0x4 = data.read(1)
        self.field_0x5 = data.read(1)
        self.field_0x6 = data.read(1)
        self.field_0x7 = data.read(1)
# --------------------------------------


# Blend Info ---------------------------
class Blend_Info_Section:
    def __init__(self, data: BytesIO, offsets: MAT1_Section_Offsets, initData: Mat_Init_Data_Section):
        if offsets.blend_info_offset > 0:
            self.blend_info: List[J2D_Blend_Info] = []
            for i in range(initData.blend_info_count):
                self.blend_info.insert(i, J2D_Blend_Info(data))
            next_offset = offsets.find_next_valid_offset(offsets.blend_info_offset)
            self.padding = data.read((next_offset - offsets.blend_info_offset) - ((initData.blend_info_count) * 4))


class J2D_Blend_Info:
    def __init__(self, data: BytesIO):
        self.type = data.read(1)
        self.src_factor = data.read(1)
        self.dst_factor = data.read(1)
        self.op = data.read(1)
# --------------------------------------


# Dither -------------------------------
class Dither_Section:
    def __init__(self, data: BytesIO, mat1Section: MAT1_Section, offsets: MAT1_Section_Offsets, initData: Mat_Init_Data_Section):
        if offsets.dither_offset > 0:
            self.dither: List[bytes] = []
            for i in range(initData.dither_count):
                self.dither.insert(i, data.read(1))
                print(self.dither[i])
            # This last padding formula is a little different as there is not a "next offset" to calculate with
            self.padding = data.read((mat1Section.size - offsets.dither_offset) - ((initData.dither_count)))
            print(self.padding)
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
        # Check for BGN1 tag
        old_pos = data.tell()
        tag = data.read(4)
        if tag == b'BGN1':
            self.tag = tag
            self.tag_size = bytes_to_int(data.read(4))
        else:
            data.seek(old_pos)

        # Parse PAN2 data
        self.magic = data.read(4)
        print(self.magic)
        self.size = bytes_to_int(data.read(4))
        self.field_0x8 = data.read(2)
        self.field_0xa = data.read(2)
        self.visible = data.read(1)
        self.base_position = data.read(1)
        self.padding = data.read(2)
        self.info_tag = data.read(8)
        print(self.info_tag)
        self.user_info_tag = data.read(8)
        self.rot_offset_x = struct.unpack('>f', data.read(4))[0]
        self.rot_offset_y = struct.unpack('>f', data.read(4))[0]
        self.scale_x = struct.unpack('>f', data.read(4))[0]
        self.scale_y = struct.unpack('>f', data.read(4))[0]
        self.rotate_x = struct.unpack('>f', data.read(4))[0]
        self.rotate_y = struct.unpack('>f', data.read(4))[0]
        self.rotate_z = struct.unpack('>f', data.read(4))[0]
        self.translate_x = struct.unpack('>f', data.read(4))[0]
        self.translate_y = struct.unpack('>f', data.read(4))[0]
        self.end_padding = data.read(4)

        if isParent:
            self.child_nodes: List[Union[PAN2 | PIC2 | TBX2]] = []
            while True:
                old_pos = data.tell()
                tag = data.read(4)
                self.tag = tag
                if tag == b'BGN1':
                    tag_size = bytes_to_int(data.read(4))
                    data.seek(old_pos)
                    data.read(tag_size)
                    # Determine child node(s) type
                    magic = data.read(4)
                    data.seek(old_pos)
                    match magic:
                        case b'PAN2':
                            self.child_nodes.append(PAN2(data, True))
                        case b'PIC2':
                            self.child_nodes.append(PIC2(data))
                        case b'TBX2':
                            self.child_nodes.append(TBX2(data))
                        case b'WIN2':
                            self.child_nodes.append(WIN2(data))
                elif tag == b'PAN2':
                    data.seek(old_pos)
                    self.child_nodes.append(PAN2(data, True))
                elif tag == b'PIC2':
                    data.seek(old_pos)
                    self.child_nodes.append(PIC2(data))
                elif tag == b'TBX2':
                    data.seek(old_pos)
                    self.child_nodes.append(TBX2(data))
                elif tag == b'WIN2':
                    data.seek(old_pos)
                    self.child_nodes.append(WIN2(data))
                elif tag in (b'END1', b'EXT1', b'TEND1'):
                    self.end_tag = tag
                    print(tag)
                    self.tag_size = bytes_to_int(data.read(4))
                    break
                else:
                    break


class PIC2:
    def __init__(self, data: BytesIO):
        old_pos = data.tell()
        tag = data.read(4)
        if tag == b'BGN1':
            self.tag = tag
            self.tag_size = bytes_to_int(data.read(4))
        else:
            data.seek(old_pos)

        current_pos = 0
        self.magic = data.read(4)
        self.size = bytes_to_int(data.read(4))
        self.base_pan2 = PAN2(data, False)
        self.field_0x0 = data.read(2)
        self.material_num = data.read(2)
        self.field_0x4 = data.read(2)
        self.field_0x6 = data.read(2)
        self.field_0x8: List[bytes] = [data.read(2), data.read(2), data.read(2), data.read(2)]
        self.field_0x10: List[bytes] = [data.read(2), data.read(2), data.read(2), data.read(2), data.read(2), data.read(2), data.read(2), data.read(2)]
        self.corner_color: List[bytes] = [data.read(4), data.read(4), data.read(4), data.read(4)]

        # old_pos = data.tell()
        # tag = data.read(4)
        # if tag == b''
        # current_pos += 56 + self.base_pan2.size
        # self.end_padding = data.read(self.size - current_pos)
        # print(self.end_padding)


class TBX2:
    def __init__(self, data: BytesIO):
        old_pos = data.tell()
        tag = data.read(4)
        if tag == b'BGN1':
            self.tag = tag
            self.tag_size = bytes_to_int(data.read(4))
        else:
            data.seek(old_pos)

        current_pos = 0
        self.magic = data.read(4)
        self.size = bytes_to_int(data.read(4))
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
        current_pos += 40 + self.base_pan2.size
        self.end_padding = data.read(self.size - current_pos)


class WIN2:
    def __init__(self, data: BytesIO):
        old_pos = data.tell()
        tag = data.read(4)
        if tag == b'BGN1':
            self.tag = tag
            self.tag_size = bytes_to_int(data.read(4))
        else:
            data.seek(old_pos)
        
        self.magic = data.read(4)
        print(self.magic)
        self.size = bytes_to_int(data.read(4))
        self.base_pan2 = PAN2(data, False)
        self.data = data.read((self.size - 8) - self.base_pan2.size)
# --------------------------------------------------------------------------------------

def main():
    Tk().withdraw()

    iso_filepath = askopenfilename(
        title="Select ISO file (GZ2E01 ONLY)",
        filetypes=[("ISO files", "*.iso"), ("All files", "*.*")]
    )
    if not iso_filepath:
        print("No iso selected")
        exit()

    # blo_filepath = askopenfilename(
    #     title="Select blo file",
    #     filetypes=[("BLO files", "*.blo"), ("All files", "*.*")]
    # )
    # if not blo_filepath:
    #     print("No file selected")
    #     exit()

    gcm = GCM(iso_filepath)
    gcm.read_entire_disc()

    blo_files: List[RARCFileEntry] = []

    for iso_path, gcm_file in gcm.files_by_path.items():
        if not iso_path.lower().endswith(".arc"):
            continue
        else:
            try:
                arc_data = gcm.read_file_data(iso_path)
                arc = RARC(arc_data)
                arc.read()

                for entry in arc.file_entries:
                    if (entry.name.lower().endswith(".blo")):
                        # Skip file_error.blo as it utilizes older blo1 sections
                        if not entry.name.lower().endswith("file_error.blo"):
                            entry.decompress_data_if_necessary()
                            blo_files.append(entry)
            except Exception as e:
                print(f"  [failed to read ARC: {e}]")
                continue

    print(f"Found {len(blo_files)} BLO files")
    blos: List[BLO] = []
    for i, entry in enumerate(blo_files):
        print(entry.name)
        blos.insert(i, parse_blo(entry.data))

    for blo in blos:
        print(blo.tag)

if __name__ == "__main__":
    main()
