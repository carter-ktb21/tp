#ifndef J2DMATERIALFACTORY_H
#define J2DMATERIALFACTORY_H

#include "JSystem/J2DGraph/J2DManage.h"
#include "JSystem/J2DGraph/J2DMatBlock.h"

/**
 * @ingroup jsystem-j2d
 * 
 */
struct J2DMaterialBlock {
    /* 0x00 */ u32 magic;
    /* 0x04 */ u32 mat1_section_size;
    /* 0x08 */ u16 material_num;
    /* 0x0A */ u16 padding;
    /* 0x0C */ u32 mat_init_data_offset;
    /* 0x10 */ u32 mat_init_data_indexes_offset;
    /* 0x14 */ u32 offset_3;
    /* 0x18 */ u32 ind_init_data_offset;
    /* 0x1C */ u32 cull_mode_offset;
    /* 0x20 */ u32 mat_color_offset;
    /* 0x24 */ u32 color_chan_num_offset;
    /* 0x28 */ u32 color_chan_info_offset;
    /* 0x2C */ u32 tex_gen_num_offset;
    /* 0x30 */ u32 tex_coord_info_offset;
    /* 0x34 */ u32 tex_mtx_info_offset;
    /* 0x38 */ u32 tex_no_offset;
    /* 0x3C */ u32 font_no_offset;
    /* 0x40 */ u32 tev_order_info_offset;
    /* 0x44 */ u32 tev_color_offset;
    /* 0x48 */ u32 tev_k_color_offset;
    /* 0x4C */ u32 tev_stage_num_offset;
    /* 0x50 */ u32 tev_stage_info_offset;
    /* 0x54 */ u32 tev_swap_mode_info_offset;
    /* 0x58 */ u32 tev_mode_swap_tbl_info_offset;
    /* 0x5C */ u32 alpha_comp_info_offset;
    /* 0x60 */ u32 blend_info_offset;
    /* 0x64 */ u32 dither_offset;
};

typedef struct _GXColor GXColor;
typedef struct _GXColorS10 GXColorS10;
struct J2DAlphaCompInfo;
struct J2DBlendInfo;
struct J2DColorChanInfo;
class J2DMaterial;

/**
 * @ingroup jsystem-j2d
 * 
 */
struct J2DIndInitData {
    u8 field_0x0;
    u8 tex_stage_num;
    u8 field_0x2[2];
    J2DIndTexOrderInfo tex_order_info[4];
    J2DIndTexMtxInfo tex_mtx_info[3];
    J2DIndTexCoordScaleInfo tex_coord_scale_info[4];
    J2DIndTevStageInfo tev_stage_info[4];
    u8 field_0xac[0x90];
};

/**
 * @ingroup jsystem-j2d
 * 
 */
struct J2DMaterialInitData {
    u8 mat_mode;
    u8 cull_mode_idx;
    u8 color_chan_num_idx;
    u8 tex_gen_num_idx;
    u8 tev_stage_num_idx;
    u8 dither_idx;
    u8 mat_alpha_calc;
    u8 field_0x7;
    u16 mat_color_idx_tbl[2];
    u16 color_chan_info_idx_tbl[4];
    u16 tex_coord_info_idx_tbl[8];
    u16 tex_mtx_info_idx_tbl[0xa];
    u16 tex_no_idx_tbl[8];
    u16 font_no_idx;
    u16 tev_k_color_idx_tbl[4];
    u8 tev_k_color_sel[0x10];
    u8 tev_k_alpha_sel[0x10];
    u16 tev_order_info_idx_tbl[0x10];
    u16 tev_color_idx_tbl[0x4];
    u16 tev_stage_info_idx_tbl[0x10];
    u16 tev_swap_mode_info_idx_tbl[0x10];
    u16 tev_swap_mode_tbl_info_idx_tbl[0x4];
    u16 alpha_comp_info_idx;
    u16 blend_info_idx;
    u16 field_0xe6;
};
struct J2DTevStageInfo;
struct J2DTevSwapModeTableInfo;
struct J2DTevSwapModeInfo;
struct J2DTevOrderInfo;
struct J2DTexCoordInfo;
struct J2DTexMtxInfo;
class JKRArchive;

/**
 * @ingroup jsystem-j2d
 * 
 */
class J2DMaterialFactory {
public:
    J2DMaterialFactory(J2DMaterialBlock const&);
    u32 countStages(int) const;
    J2DMaterial* create(J2DMaterial*, int, u32, J2DResReference*, J2DResReference*,
                               JKRArchive*) const;
    JUtility::TColor newMatColor(int, int) const;
    u8 newColorChanNum(int) const;
    J2DColorChan newColorChan(int, int) const;
    u32 newTexGenNum(int) const;
    J2DTexCoord newTexCoord(int, int) const;
    J2DTexMtx* newTexMtx(int, int) const;
    u8 newCullMode(int) const;
    u16 newTexNo(int, int) const;
    u16 newFontNo(int) const;
    J2DTevOrder newTevOrder(int, int) const;
    J2DGXColorS10 newTevColor(int, int) const;
    JUtility::TColor newTevKColor(int, int) const;
    u8 newTevStageNum(int) const;
    J2DTevStage newTevStage(int, int) const;
    J2DTevSwapModeTable newTevSwapModeTable(int, int) const;
    u8 newIndTexStageNum(int) const;
    J2DIndTexOrder newIndTexOrder(int, int) const;
    J2DIndTexMtx newIndTexMtx(int, int) const;
    J2DIndTevStage newIndTevStage(int, int) const;
    J2DIndTexCoordScale newIndTexCoordScale(int, int) const;
    J2DAlphaComp newAlphaComp(int) const;
    J2DBlend newBlend(int) const;
    u8 newDither(int) const;

    u32 getMaterialMode(int idx) const {
        return mMatInitData[mMatInitDataIndexes[idx]].mat_mode;
    }

    u8 getMaterialAlphaCalc(int idx) const {
        return mMatInitData[mMatInitDataIndexes[idx]].mat_alpha_calc;
    }

private:
    /* 0x00 */ u16 mMaterialNum;
    /* 0x02 */ u16 field_0x2;
    /* 0x04 */ J2DMaterialInitData* mMatInitData;
    /* 0x08 */ u16* mMatInitDataIndexes;
    /* 0x0C */ J2DIndInitData* mIndInitData;
    /* 0x10 */ GXColor* mMatColor;
    /* 0x14 */ u8* mColorChanNum;
    /* 0x18 */ J2DColorChanInfo* mColorChanInfo;
    /* 0x1C */ u8* mTexGenNum;
    /* 0x20 */ J2DTexCoordInfo* mTexCoordInfo;
    /* 0x24 */ J2DTexMtxInfo* mTexMtxInfo;
    /* 0x28 */ u16* mTexNo;
    /* 0x2C */ u16* mFontNo;
    /* 0x30 */ _GXCullMode* mCullMode;
    /* 0x34 */ J2DTevOrderInfo* mTevOrderInfo;
    /* 0x38 */ _GXColorS10* mTevColor;
    /* 0x3C */ GXColor* mTevKColor;
    /* 0x40 */ u8* mTevStageNum;
    /* 0x44 */ J2DTevStageInfo* mTevStageInfo;
    /* 0x48 */ J2DTevSwapModeInfo* mTevSwapModeInfo;
    /* 0x4C */ J2DTevSwapModeTableInfo* mTevSwapModeTableInfo;
    /* 0x50 */ J2DAlphaCompInfo* mAlphaCompInfo;
    /* 0x54 */ J2DBlendInfo* mBlendInfo;
    /* 0x58 */ u8* mDither;
};

#endif /* J2DMATERIALFACTORY_H */
