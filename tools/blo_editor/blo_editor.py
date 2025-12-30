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
    def __init__(self):
        self.tag = bytes()
        self.type = bytes()
        self.size = 0
        self.blocks = 0
        self.header_padding = bytes()
        self.inf1_section = INF1_Section()
        self.tex1_section = TEX1_Section()
        self.fnt1_section = FNT1_Section()
        self.mat1_section = MAT1_Section()


class INF1_Section:
    def __init__(self):
        self.magic = bytes()
        self.size = 0
        self.unknown = bytes()
        self.padding = bytes()


# TEX1 ---------------------------------------------------------------------------------
class TEX1_Section:
    def __init__(self):
        self.header = TEX1_Header()
        self.size_after_header = self.header.section_size - self.header.header_size
        self.offset_count = 0
        self.offsets: List[int] = []
        self.texture_refs: List[TEX1_Reference] = []
        self.padding = bytes()


class TEX1_Header:
    def __init__(self):
        self.magic = bytes()
        self.section_size = 0
        self.texture_count = 0
        self.padding = bytes()
        self.header_size = 0


class TEX1_Reference:
    def __init__(self):
        self.res_type = bytes()
        self.texture = bytes()
# --------------------------------------------------------------------------------------


# FNT1 ---------------------------------------------------------------------------------
class FNT1_Section:
    def __init__(self):
        self.header = FNT1_Header()
        self.size_after_header = self.header.section_size - self.header.header_size
        self.offset_count = 0
        self.offsets: List[int] = []
        self.texture_refs: List[FNT1_Reference] = []
        self.padding = bytes()


class FNT1_Header:
    def __init__(self):
        self.magic = bytes()
        self.section_size = 0
        self.font_count = 0
        self.padding = bytes()
        self.header_size = 0


class FNT1_Reference:
    def __init__(self):
        self.res_type = bytes()
        self.font = bytes()
# --------------------------------------------------------------------------------------


# MAT1 ---------------------------------------------------------------------------------
class MAT1_Section:
    def __init__(self):
        self.magic = bytes()
        self.size = 0
        self.material_count = bytes()
        self.padding = bytes()
# --------------------------------------------------------------------------------------
