#include "JSystem/JSystem.h" // IWYU pragma: keep

#include "JSystem/J2DGraph/J2DMaterialFactory.h"
#include "JSystem/J2DGraph/J2DMaterial.h"
#include "JSystem/J2DGraph/J2DScreen.h"
#include "JSystem/JSupport/JSupport.h"
#include "JSystem/JUtility/JUTResource.h"
#include "string.h"
#include "dolphin/types.h"

/* The J2DMaterialFactory constructor takes the provided J2DMaterialBlock (which is made up of the MAT1 section of a .blo file) and
   sets pointers to the appropriate offsets defined in that block for each member variable. Each offset is the start of a section that, for each
   member variable, could contain multiple sets of data of whatever type is specified by the pointer. Hence why most members are accessed via array index. */
J2DMaterialFactory::J2DMaterialFactory(J2DMaterialBlock const& i_matBlock) {
    mMaterialNum = i_matBlock.material_num;
    mMatInitData = JSUConvertOffsetToPtr<J2DMaterialInitData>(&i_matBlock, (void*)i_matBlock.mat_init_data_offset);
    mMatInitDataIndexes = JSUConvertOffsetToPtr<u16>(&i_matBlock, (void*)i_matBlock.mat_init_data_indexes_offset);
    if (i_matBlock.ind_init_data_offset && i_matBlock.ind_init_data_offset - i_matBlock.offset_3 > 4) {
        mIndInitData = JSUConvertOffsetToPtr<J2DIndInitData>(&i_matBlock, (void*)i_matBlock.ind_init_data_offset);
    }
    else {
        mIndInitData = NULL;
    }
    mCullMode = JSUConvertOffsetToPtr<_GXCullMode>(&i_matBlock, (void*)i_matBlock.cull_mode_offset);
    mMatColor = JSUConvertOffsetToPtr<GXColor>(&i_matBlock, (void*)i_matBlock.mat_color_offset);
    mColorChanNum = JSUConvertOffsetToPtr<u8>(&i_matBlock, (void*)i_matBlock.color_chan_num_offset);
    mColorChanInfo = JSUConvertOffsetToPtr<J2DColorChanInfo>(&i_matBlock, (void*)i_matBlock.color_chan_info_offset);
    mTexGenNum = JSUConvertOffsetToPtr<u8>(&i_matBlock, (void*)i_matBlock.tex_gen_num_offset);
    mTexCoordInfo = JSUConvertOffsetToPtr<J2DTexCoordInfo>(&i_matBlock, (void*)i_matBlock.tex_coord_info_offset);
    mTexMtxInfo = JSUConvertOffsetToPtr<J2DTexMtxInfo>(&i_matBlock, (void*)i_matBlock.tex_mtx_info_offset);
    mTexNo = JSUConvertOffsetToPtr<u16>(&i_matBlock, (void*)i_matBlock.tex_no_offset);
    mFontNo = JSUConvertOffsetToPtr<u16>(&i_matBlock, (void*)i_matBlock.font_no_offset);
    mTevOrderInfo = JSUConvertOffsetToPtr<J2DTevOrderInfo>(&i_matBlock, (void*)i_matBlock.tev_order_info_offset);
    mTevColor = JSUConvertOffsetToPtr<_GXColorS10>(&i_matBlock, (void*)i_matBlock.tev_color_offset);
    mTevKColor = JSUConvertOffsetToPtr<GXColor>(&i_matBlock, (void*)i_matBlock.tev_k_color_offset);
    mTevStageNum = JSUConvertOffsetToPtr<u8>(&i_matBlock, (void*)i_matBlock.tev_stage_num_offset);
    mTevStageInfo = JSUConvertOffsetToPtr<J2DTevStageInfo>(&i_matBlock, (void*)i_matBlock.tev_stage_info_offset);
    mTevSwapModeInfo = JSUConvertOffsetToPtr<J2DTevSwapModeInfo>(&i_matBlock, (void*)i_matBlock.tev_swap_mode_info_offset);
    mTevSwapModeTableInfo = JSUConvertOffsetToPtr<J2DTevSwapModeTableInfo>(&i_matBlock, (void*)i_matBlock.tev_mode_swap_tbl_info_offset);
    mAlphaCompInfo = JSUConvertOffsetToPtr<J2DAlphaCompInfo>(&i_matBlock, (void*)i_matBlock.alpha_comp_info_offset);
    mBlendInfo = JSUConvertOffsetToPtr<J2DBlendInfo>(&i_matBlock, (void*)i_matBlock.blend_info_offset);
    mDither = JSUConvertOffsetToPtr<u8>(&i_matBlock, (void*)i_matBlock.dither_offset);
}

u32 J2DMaterialFactory::countStages(int index) const {
    J2DMaterialInitData* matInitData = &mMatInitData[mMatInitDataIndexes[index]];
    u32 uVar4 = 0;
    u32 uVar3 = 0;
    if (matInitData->tev_stage_num_idx != 0xff) {
        uVar3 = mTevStageNum[matInitData->tev_stage_num_idx];
    }

    for (int i = 0; i < 8; i++) {
        if (matInitData->tex_no_idx_tbl[i] != 0xffff) {
            uVar4++;
        }
    }

    if ((uVar3 != uVar4 && uVar4 != 0)) {
        if (uVar3 > uVar4) {
            return uVar3;
        }
        return uVar4;
    }
    return uVar3;
}

/* 802F2D1C-802F362C 2ED65C 0910+00 0/0 1/1 0/0 .text            create__18J2DMaterialFactoryCFP11J2DMaterialiUlP15J2DResReferenceP15J2DResReferenceP10JKRArchive */
J2DMaterial* J2DMaterialFactory::create(J2DMaterial* i_material, int index, u32 param_2,
                                    J2DResReference* i_texRes, J2DResReference* i_fontRes,
                                    JKRArchive* i_archive) const {
    u32 stages = countStages(index);
    u32 uVar1 = ((param_2 & 0x1f0000) >> 16);
    u32 r28 = stages > uVar1 ? stages : uVar1;

    u32 r25 = r28 <= 8 ? r28 : 8;

    s32 local_3bc = ((param_2 & 0x1000000) != 0);
    s32 indBlockType = (param_2 & 0x1f0000) ? local_3bc : 0;
    bool temp = (param_2 & 0x1f0000);
    i_material->mTevBlock = J2DMaterial::createTevBlock((u16)r28, temp);
    i_material->mIndBlock = J2DMaterial::createIndBlock(indBlockType, temp);
    i_material->mIndex = index;
    i_material->mMatMode = getMaterialMode(index);
    i_material->getColorBlock()->setColorChanNum(newColorChanNum(index));
    i_material->getColorBlock()->setCullMode(newCullMode(index));
    i_material->getTexGenBlock()->setTexGenNum(newTexGenNum(index));
    i_material->getPEBlock()->setAlphaComp(newAlphaComp(index));
    i_material->getPEBlock()->setBlend(newBlend(index));
    i_material->getPEBlock()->setDither(newDither(index));
    i_material->getTevBlock()->setTevStageNum(newTevStageNum(index));
    i_material->mMaterialAlphaCalc = getMaterialAlphaCalc(index);

    JUTResReference resReference;
    for (u8 i = 0; i < r25; i++) {
        u16 texNo = newTexNo(index, i);
        s8* texRef = i_texRes->getResReference(texNo);
        void* texture = NULL;
        if (texRef != NULL) {
            texture = resReference.getResource(texRef, 'TIMG', i_archive);
            if (texture == NULL && i_archive != NULL) {
                texture = resReference.getResource(texRef, 'TIMG', NULL);
            }

            if (texture == NULL && J2DScreen::getDataManage() != NULL) {
                char name[257];
                strcpy(name, i_texRes->getName(texNo));
                texture = J2DScreen::getDataManage()->get(name);
            }
        }

        i_material->getTevBlock()->insertTexture(i, (ResTIMG*)texture);
        i_material->getTevBlock()->setTexNo(i, texNo);
    }

    u16 fontNo = newFontNo(index);
    i_material->getTevBlock()->setFontNo(fontNo);
    s8* fntRef = i_fontRes->getResReference(i_material->getTevBlock()->getFontNo());
    void* font = NULL;
    if (fntRef != NULL) {
        font = resReference.getResource(fntRef, 'FONT', i_archive);
        if (font == NULL && i_archive != NULL) {
            font = resReference.getResource(fntRef, 'FONT', NULL);
        }

        if (font == NULL && J2DScreen::getDataManage() != NULL) {
            char name[257];
            strcpy(name, i_fontRes->getName(i_material->getTevBlock()->getFontNo()));
            font = J2DScreen::getDataManage()->get(name);
        }
    }
    i_material->getTevBlock()->setFont((ResFONT*)font);

    for (u8 i = 0; i < r28; i++) {
        i_material->getTevBlock()->setTevOrder(i, newTevOrder(index, i));
    }

    for (u8 i = 0; i < r28; i++) {
        J2DMaterialInitData* local_38c = &mMatInitData[mMatInitDataIndexes[index]];
        i_material->getTevBlock()->setTevStage(i, newTevStage(index, i));
        if (local_38c->tev_swap_mode_info_idx_tbl[i] != 0xffff) {
            i_material->getTevBlock()->getTevStage(i)->setTexSel(mTevSwapModeInfo[local_38c->tev_swap_mode_info_idx_tbl[i]].mTexSel);
            i_material->getTevBlock()->getTevStage(i)->setRasSel(mTevSwapModeInfo[local_38c->tev_swap_mode_info_idx_tbl[i]].mRasSel);
        }
    }

    for (u8 i = 0; i < 4; i++) {
        i_material->getTevBlock()->setTevKColor(i, newTevKColor(index, i));
    }

    for (u8 i = 0; i < 4; i++) {
        i_material->getTevBlock()->setTevColor(i, newTevColor(index, i));
    }

    for (u8 i = 0; i < 4; i++) {
        i_material->getTevBlock()->setTevSwapModeTable(i, newTevSwapModeTable(index, i));
    }

    for (u8 i = 0; i < 2; i++) {
        i_material->getColorBlock()->setMatColor(i, newMatColor(index, i));
    }

    for (u8 i = 0; i < 4; i++) {
        J2DColorChan colorChan = newColorChan(index, i);
        i_material->getColorBlock()->setColorChan(i, colorChan);
    }

    for (u8 i = 0; i < 8; i++) {
        J2DTexCoord texCoord = newTexCoord(index, i);
        i_material->getTexGenBlock()->setTexCoord(i, &texCoord);
    }

    for (u8 i = 0; i < 8; i++) {
        i_material->getTexGenBlock()->setTexMtx(i, newTexMtx(index, i));
    }

    J2DMaterialInitData* local_394 = &mMatInitData[mMatInitDataIndexes[index]];
    for (u8 i = 0; i < r28; i++) {
        i_material->getTevBlock()->setTevKColorSel(i, local_394->tev_k_color_sel[i]);
    }

    for (u8 i = 0; i < r28; i++) {
        i_material->getTevBlock()->setTevKAlphaSel(i, local_394->tev_k_alpha_sel[i]);
    }

    if (mIndInitData != NULL || indBlockType != 0) {
        u8 indTexStageNum = newIndTexStageNum(index);
        i_material->mIndBlock->setIndTexStageNum(indTexStageNum);
        for (u8 i = 0; i < indTexStageNum; i++) {
            i_material->getIndBlock()->setIndTexMtx(i, newIndTexMtx(index, i));
        }

        for (u8 i = 0; i < indTexStageNum; i++) {
            i_material->getIndBlock()->setIndTexOrder(i, newIndTexOrder(index, i));
        }

        for (u8 i = 0; i < indTexStageNum; i++) {
            i_material->getIndBlock()->setIndTexCoordScale(i, newIndTexCoordScale(index, i));
        }

        for (u8 i = 0; i < r28; i++) {
            i_material->getTevBlock()->setIndTevStage(i, newIndTevStage(index, i));
        }
    }
    return i_material;
}

JUtility::TColor J2DMaterialFactory::newMatColor(int matInitDataIdx, int matColorIdx) const {
    GXColor color = {0xff,0xff,0xff,0xff};
    JUtility::TColor defaultColor = GXColor(color);
    J2DMaterialInitData* matInitData = &mMatInitData[mMatInitDataIndexes[matInitDataIdx]];
    if (matInitData->mat_color_idx_tbl[matColorIdx] != 0xffff) {
        return mMatColor[matInitData->mat_color_idx_tbl[matColorIdx]];
    }
    return defaultColor;
}

u8 J2DMaterialFactory::newColorChanNum(int matInitDataIdx) const {
    J2DMaterialInitData* matInitData = &mMatInitData[mMatInitDataIndexes[matInitDataIdx]];
    if (matInitData->color_chan_num_idx != 0xff) {
        return mColorChanNum[matInitData->color_chan_num_idx];
    }
    return 0;
}

J2DColorChan J2DMaterialFactory::newColorChan(int matInitDataIdx, int colorChanInfoIdx) const {
    J2DMaterialInitData* matInitData = &mMatInitData[mMatInitDataIndexes[matInitDataIdx]];
    if (matInitData->color_chan_info_idx_tbl[colorChanInfoIdx] != 0xffff) {
        return J2DColorChan(mColorChanInfo[matInitData->color_chan_info_idx_tbl[colorChanInfoIdx]]);
    }
    return J2DColorChan();
}

u32 J2DMaterialFactory::newTexGenNum(int matInitDataIdx) const {
    J2DMaterialInitData* matInitData = &mMatInitData[mMatInitDataIndexes[matInitDataIdx]];
    if (matInitData->tex_gen_num_idx != 0xff) {
        return mTexGenNum[matInitData->tex_gen_num_idx];
    }
    return 0;
}

J2DTexCoord J2DMaterialFactory::newTexCoord(int matInitDataIdx, int texCoordInfoIdx) const {
    J2DMaterialInitData* matInitData = &mMatInitData[mMatInitDataIndexes[matInitDataIdx]];
    if (matInitData->tex_coord_info_idx_tbl[texCoordInfoIdx] != 0xffff) {
        return J2DTexCoord(mTexCoordInfo[matInitData->tex_coord_info_idx_tbl[texCoordInfoIdx]]);
    }
    return J2DTexCoord();
}

J2DTexMtx* J2DMaterialFactory::newTexMtx(int matInitDataIdx, int texMtxInfoIdx) const {
    J2DTexMtx* rv = NULL;
    J2DMaterialInitData* matInitData = &mMatInitData[mMatInitDataIndexes[matInitDataIdx]];
    if (matInitData->tex_mtx_info_idx_tbl[texMtxInfoIdx] != 0xffff) {
        rv = new J2DTexMtx(mTexMtxInfo[matInitData->tex_mtx_info_idx_tbl[texMtxInfoIdx]]);
        rv->calc();
    }
    return rv;
}

u8 J2DMaterialFactory::newCullMode(int matInitDataIdx) const {
    J2DMaterialInitData* matInitData = &mMatInitData[mMatInitDataIndexes[matInitDataIdx]];
    if (matInitData->cull_mode_idx != 0xff) {
        return mCullMode[matInitData->cull_mode_idx];
    }
    return 0xff;
}

u16 J2DMaterialFactory::newTexNo(int matInitDataIdx, int texNoIdx) const {
    J2DMaterialInitData* matInitData = &mMatInitData[mMatInitDataIndexes[matInitDataIdx]];
    if (matInitData->tex_no_idx_tbl[texNoIdx] != 0xffff) {
        return mTexNo[matInitData->tex_no_idx_tbl[texNoIdx]];
    }
    return 0x1FFFF;
}

u16 J2DMaterialFactory::newFontNo(int matInitDataIdx) const {
    J2DMaterialInitData* matInitData = &mMatInitData[mMatInitDataIndexes[matInitDataIdx]];
    if (matInitData->font_no_idx != 0xffff) {
        return mFontNo[matInitData->font_no_idx];
    }
    return 0x1FFFF;
}

J2DTevOrder J2DMaterialFactory::newTevOrder(int matInitDataIdx, int tevOrderInfoIdx) const {
    J2DMaterialInitData* matInitData = &mMatInitData[mMatInitDataIndexes[matInitDataIdx]];
    if (matInitData->tev_order_info_idx_tbl[tevOrderInfoIdx] != 0xffff) {
        return J2DTevOrder(mTevOrderInfo[matInitData->tev_order_info_idx_tbl[tevOrderInfoIdx]]);
    }
    return J2DTevOrder();
}

J2DGXColorS10 J2DMaterialFactory::newTevColor(int matInitDataIdx, int tevColorIdx) const {
    GXColorS10 color = {0, 0, 0, 0};
    J2DGXColorS10 defaultColor = color;
    J2DMaterialInitData* matInitData = &mMatInitData[mMatInitDataIndexes[matInitDataIdx]];

    if (matInitData->tev_color_idx_tbl[tevColorIdx] != 0xffff) {
        return mTevColor[matInitData->tev_color_idx_tbl[tevColorIdx]];
    }
    
    return defaultColor;
}

JUtility::TColor J2DMaterialFactory::newTevKColor(int matInitDataIdx, int tevKColorIdx) const {
    JUtility::TColor defaultColor = (GXColor){0xFF, 0xFF, 0xFF, 0xFF};
    J2DMaterialInitData* matInitData = &mMatInitData[mMatInitDataIndexes[matInitDataIdx]];
    if (matInitData->tev_k_color_idx_tbl[tevKColorIdx] != 0xffff) {
        return mTevKColor[matInitData->tev_k_color_idx_tbl[tevKColorIdx]];
    }
    return defaultColor;
}

u8 J2DMaterialFactory::newTevStageNum(int matInitDataIdx) const {
    J2DMaterialInitData* matInitData = &mMatInitData[mMatInitDataIndexes[matInitDataIdx]];
    if (matInitData->tev_stage_num_idx != 0xff) {
        return mTevStageNum[matInitData->tev_stage_num_idx];
    }
    return 0xFF;
}

J2DTevStage J2DMaterialFactory::newTevStage(int matInitDataIdx, int tevStageInfoIdx) const {
    J2DMaterialInitData* matInitData = &mMatInitData[mMatInitDataIndexes[matInitDataIdx]];
    if (matInitData->tev_stage_info_idx_tbl[tevStageInfoIdx] != 0xffff) {
        return J2DTevStage(mTevStageInfo[matInitData->tev_stage_info_idx_tbl[tevStageInfoIdx]]);
    }
    return J2DTevStage();
}

J2DTevSwapModeTable J2DMaterialFactory::newTevSwapModeTable(int matInitDataIdx, int tevSwapModeTblInfoIdx) const {
    J2DMaterialInitData* matInitData = &mMatInitData[mMatInitDataIndexes[matInitDataIdx]];
    if (matInitData->tev_swap_mode_tbl_info_idx_tbl[tevSwapModeTblInfoIdx] != 0xffff) {
        return J2DTevSwapModeTable(mTevSwapModeTableInfo[matInitData->tev_swap_mode_tbl_info_idx_tbl[tevSwapModeTblInfoIdx]]);
    }
    return J2DTevSwapModeTable(j2dDefaultTevSwapModeTable);
}

u8 J2DMaterialFactory::newIndTexStageNum(int indInitDataIdx) const {
    if (mIndInitData != NULL) {
        if (mIndInitData[indInitDataIdx].field_0x0 == 1) {
            return mIndInitData[indInitDataIdx].tex_stage_num;
        }
    }
    return 0;
}

J2DIndTexOrder J2DMaterialFactory::newIndTexOrder(int indInitDataIdx, int texOrderInfoIdx) const {
    J2DIndTexOrder rv;
    if (mIndInitData != NULL) {
        if (mIndInitData[indInitDataIdx].field_0x0 == 1) {
            return J2DIndTexOrder(mIndInitData[indInitDataIdx].tex_order_info[texOrderInfoIdx]);
        }
    }
    return rv;
}

J2DIndTexMtx J2DMaterialFactory::newIndTexMtx(int indInitDataIdx, int texMtxInfoIdx) const {
    J2DIndTexMtx rv;
    if (mIndInitData != NULL) {
        if (mIndInitData[indInitDataIdx].field_0x0 == 1) {
            return J2DIndTexMtx(mIndInitData[indInitDataIdx].tex_mtx_info[texMtxInfoIdx]);
        }
    }
    return rv;
}

J2DIndTevStage J2DMaterialFactory::newIndTevStage(int indInitDataIdx, int tevStageInfoIdx) const {
    J2DIndTevStage rv;
    if (mIndInitData != NULL) {
        if (mIndInitData[indInitDataIdx].field_0x0 == 1) {
            return J2DIndTevStage(mIndInitData[indInitDataIdx].tev_stage_info[tevStageInfoIdx]);
        }
    }
    return rv;
}

J2DIndTexCoordScale J2DMaterialFactory::newIndTexCoordScale(int indInitDataIdx, int texCoordScaleInfoIdx) const {
    J2DIndTexCoordScale rv;
    if (mIndInitData != NULL) {
        if (mIndInitData[indInitDataIdx].field_0x0 == 1) {
            return J2DIndTexCoordScale(mIndInitData[indInitDataIdx].tex_coord_scale_info[texCoordScaleInfoIdx]);
        }
    }
    return rv;
}

J2DAlphaComp J2DMaterialFactory::newAlphaComp(int matInitDataIdx) const {
    J2DMaterialInitData* matInitData = &mMatInitData[mMatInitDataIndexes[matInitDataIdx]];
    if (matInitData->alpha_comp_info_idx != 0xffff) {
        return J2DAlphaComp(mAlphaCompInfo[matInitData->alpha_comp_info_idx]);
    }
    return J2DAlphaComp();
}

J2DBlend J2DMaterialFactory::newBlend(int matInitDataIdx) const {
    J2DMaterialInitData* matInitData = &mMatInitData[mMatInitDataIndexes[matInitDataIdx]];
    if (matInitData->blend_info_idx != 0xffff) {
        return J2DBlend(mBlendInfo[matInitData->blend_info_idx]);
    }
    return J2DBlend();
}

u8 J2DMaterialFactory::newDither(int matInitDataIdx) const {
    J2DMaterialInitData* matInitData = &mMatInitData[mMatInitDataIndexes[matInitDataIdx]];
    if (matInitData->dither_idx != 0xff) {
        return mDither[matInitData->dither_idx];
    }
    return 0;
}
