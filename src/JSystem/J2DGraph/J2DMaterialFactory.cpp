#include "JSystem/JSystem.h" // IWYU pragma: keep

#include "JSystem/J2DGraph/J2DMaterialFactory.h"
#include "JSystem/J2DGraph/J2DMaterial.h"
#include "JSystem/J2DGraph/J2DScreen.h"
#include "JSystem/JSupport/JSupport.h"
#include "JSystem/JUtility/JUTResource.h"
#include "string.h"
#include "dolphin/types.h"

J2DMaterialFactory::J2DMaterialFactory(J2DMaterialBlock const& i_matBlock) {
    mMaterialNum = i_matBlock.material_num;
    mMatInitData = JSUConvertOffsetToPtr<J2DMaterialInitData>(&i_matBlock, (void*)i_matBlock.mat_init_data_offset);
    field_0x8 = JSUConvertOffsetToPtr<u16>(&i_matBlock, (void*)i_matBlock.offset_2);
    if (i_matBlock.ind_init_data_offset && i_matBlock.ind_init_data_offset - i_matBlock.offset_3 > 4) {
        mIndInitData = JSUConvertOffsetToPtr<J2DIndInitData>(&i_matBlock, (void*)i_matBlock.ind_init_data_offset);
    }
    else {
        mIndInitData = NULL;
    }
    mCullModes = JSUConvertOffsetToPtr<_GXCullMode>(&i_matBlock, (void*)i_matBlock.cull_modes_offset);
    field_0x10 = JSUConvertOffsetToPtr<GXColor>(&i_matBlock, (void*)i_matBlock.offset_6);
    field_0x14 = JSUConvertOffsetToPtr<u8>(&i_matBlock, (void*)i_matBlock.offset_7);
    field_0x18 = JSUConvertOffsetToPtr<J2DColorChanInfo>(&i_matBlock, (void*)i_matBlock.offset_8);
    field_0x1c = JSUConvertOffsetToPtr<u8>(&i_matBlock, (void*)i_matBlock.offset_9);
    field_0x20 = JSUConvertOffsetToPtr<J2DTexCoordInfo>(&i_matBlock, (void*)i_matBlock.offset_10);
    field_0x24 = JSUConvertOffsetToPtr<J2DTexMtxInfo>(&i_matBlock, (void*)i_matBlock.offset_11);
    field_0x28 = JSUConvertOffsetToPtr<u16>(&i_matBlock, (void*)i_matBlock.offset_12);
    field_0x2c = JSUConvertOffsetToPtr<u16>(&i_matBlock, (void*)i_matBlock.offset_13);
    field_0x34 = JSUConvertOffsetToPtr<J2DTevOrderInfo>(&i_matBlock, (void*)i_matBlock.offset_14);
    field_0x38 = JSUConvertOffsetToPtr<_GXColorS10>(&i_matBlock, (void*)i_matBlock.offset_15);
    field_0x3c = JSUConvertOffsetToPtr<GXColor>(&i_matBlock, (void*)i_matBlock.offset_16);
    field_0x40 = JSUConvertOffsetToPtr<u8>(&i_matBlock, (void*)i_matBlock.offset_17);
    field_0x44 = JSUConvertOffsetToPtr<J2DTevStageInfo>(&i_matBlock, (void*)i_matBlock.offset_18);
    field_0x48 = JSUConvertOffsetToPtr<J2DTevSwapModeInfo>(&i_matBlock, (void*)i_matBlock.offset_19);
    field_0x4c = JSUConvertOffsetToPtr<J2DTevSwapModeTableInfo>(&i_matBlock, (void*)i_matBlock.offset_20);
    field_0x50 = JSUConvertOffsetToPtr<J2DAlphaCompInfo>(&i_matBlock, (void*)i_matBlock.offset_21);
    field_0x54 = JSUConvertOffsetToPtr<J2DBlendInfo>(&i_matBlock, (void*)i_matBlock.offset_22);
    field_0x58 = JSUConvertOffsetToPtr<u8>(&i_matBlock, (void*)i_matBlock.offset_23);
}

u32 J2DMaterialFactory::countStages(int param_0) const {
    J2DMaterialInitData* iVar5 = &mMatInitData[field_0x8[param_0]];
    u32 uVar4 = 0;
    u32 uVar3 = 0;
    if (iVar5->field_0x4 != 0xff) {
        uVar3 = field_0x40[iVar5->field_0x4];
    }
    for (int i = 0; i < 8; i++) {
        if (iVar5->field_0x38[i] != 0xffff) {
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

/* 802F2D1C-802F362C 2ED65C 0910+00 0/0 1/1 0/0 .text
 * create__18J2DMaterialFactoryCFP11J2DMaterialiUlP15J2DResReferenceP15J2DResReferenceP10JKRArchive
 */
J2DMaterial* J2DMaterialFactory::create(J2DMaterial* i_material, int index, u32 param_2,
                                    J2DResReference* i_texRes, J2DResReference* i_fontRes,
                                    JKRArchive* i_archive) const {
    u32 stages = countStages(index);
    u32 uVar1 = ((param_2 & 0x1f0000) >> 16);
    u32 r28 = stages > uVar1 ? stages : uVar1;

    u32 r25 = r28 <= 8 ? r28 : 8;

    s32 local_3bc = ((param_2 & 0x1000000) != 0);
    s32 local_3c0 = (param_2 & 0x1f0000) ? local_3bc : 0;
    bool temp = (param_2 & 0x1f0000);
    i_material->mTevBlock = J2DMaterial::createTevBlock((u16)r28, temp);
    i_material->mIndBlock = J2DMaterial::createIndBlock(local_3c0, temp);
    i_material->mIndex = index;
    i_material->field_0x8 = getMaterialMode(index);
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
        J2DMaterialInitData* local_38c = &mMatInitData[field_0x8[index]];
        i_material->getTevBlock()->setTevStage(i, newTevStage(index, i));
        if (local_38c->field_0xba[i] != 0xffff) {
            i_material->getTevBlock()->getTevStage(i)->setTexSel(field_0x48[local_38c->field_0xba[i]].mTexSel);
            i_material->getTevBlock()->getTevStage(i)->setRasSel(field_0x48[local_38c->field_0xba[i]].mRasSel);
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
    J2DMaterialInitData* local_394 = &mMatInitData[field_0x8[index]];
    for (u8 i = 0; i < r28; i++) {
        i_material->getTevBlock()->setTevKColorSel(i, local_394->field_0x52[i]);
    }
    for (u8 i = 0; i < r28; i++) {
        i_material->getTevBlock()->setTevKAlphaSel(i, local_394->field_0x62[i]);
    }
    if (mIndInitData != NULL || local_3c0 != 0) {
        u8 local_410 = newIndTexStageNum(index);
        i_material->mIndBlock->setIndTexStageNum(local_410);
        for (u8 i = 0; i < local_410; i++) {
            i_material->getIndBlock()->setIndTexMtx(i, newIndTexMtx(index, i));
        }
        for (u8 i = 0; i < local_410; i++) {
            i_material->getIndBlock()->setIndTexOrder(i, newIndTexOrder(index, i));
        }
        for (u8 i = 0; i < local_410; i++) {
            i_material->getIndBlock()->setIndTexCoordScale(i, newIndTexCoordScale(index, i));
        }
        for (u8 i = 0; i < r28; i++) {
            i_material->getTevBlock()->setIndTevStage(i, newIndTevStage(index, i));
        }
    }
    return i_material;
}

JUtility::TColor J2DMaterialFactory::newMatColor(int param_0, int param_1) const {
    GXColor color = {0xff,0xff,0xff,0xff};
    JUtility::TColor local_20 = GXColor(color);
    J2DMaterialInitData* iVar2 = &mMatInitData[field_0x8[param_0]];
    if (iVar2->field_0x8[param_1] != 0xffff) {
        return field_0x10[iVar2->field_0x8[param_1]];
    }
    return local_20;
}

u8 J2DMaterialFactory::newColorChanNum(int param_0) const {
    J2DMaterialInitData* iVar2 = &mMatInitData[field_0x8[param_0]];
    if (iVar2->field_0x2 != 0xff) {
        return field_0x14[iVar2->field_0x2];
    }
    return 0;
}

J2DColorChan J2DMaterialFactory::newColorChan(int param_0, int param_1) const {
    J2DMaterialInitData* iVar2 = &mMatInitData[field_0x8[param_0]];
    if (iVar2->field_0xc[param_1] != 0xffff) {
        return J2DColorChan(field_0x18[iVar2->field_0xc[param_1]]);
    }
    return J2DColorChan();
}

u32 J2DMaterialFactory::newTexGenNum(int param_0) const {
    J2DMaterialInitData* iVar2 = &mMatInitData[field_0x8[param_0]];
    if (iVar2->field_0x3 != 0xff) {
        return field_0x1c[iVar2->field_0x3];
    }
    return 0;
}

J2DTexCoord J2DMaterialFactory::newTexCoord(int param_0, int param_1) const {
    J2DMaterialInitData* iVar2 = &mMatInitData[field_0x8[param_0]];
    if (iVar2->field_0x14[param_1] != 0xffff) {
        return J2DTexCoord(field_0x20[iVar2->field_0x14[param_1]]);
    }
    return J2DTexCoord();
}

J2DTexMtx* J2DMaterialFactory::newTexMtx(int param_0, int param_1) const {
    J2DTexMtx* rv = NULL;
    J2DMaterialInitData* iVar2 = &mMatInitData[field_0x8[param_0]];
    if (iVar2->field_0x24[param_1] != 0xffff) {
        rv = new J2DTexMtx(field_0x24[iVar2->field_0x24[param_1]]);
        rv->calc();
    }
    return rv;
}

u8 J2DMaterialFactory::newCullMode(int param_0) const {
    J2DMaterialInitData* iVar2 = &mMatInitData[field_0x8[param_0]];
    if (iVar2->field_0x1 != 0xff) {
        return mCullModes[iVar2->field_0x1];
    }
    return 0xff;
}

u16 J2DMaterialFactory::newTexNo(int param_0, int param_1) const {
    J2DMaterialInitData* iVar2 = &mMatInitData[field_0x8[param_0]];
    if (iVar2->field_0x38[param_1] != 0xffff) {
        return field_0x28[iVar2->field_0x38[param_1]];
    }
    return 0x1FFFF;
}

u16 J2DMaterialFactory::newFontNo(int param_0) const {
    J2DMaterialInitData* iVar2 = &mMatInitData[field_0x8[param_0]];
    if (iVar2->field_0x48 != 0xffff) {
        return field_0x2c[iVar2->field_0x48];
    }
    return 0x1FFFF;
}

J2DTevOrder J2DMaterialFactory::newTevOrder(int param_0, int param_1) const {
    J2DMaterialInitData* iVar2 = &mMatInitData[field_0x8[param_0]];
    if (iVar2->field_0x72[param_1] != 0xffff) {
        return J2DTevOrder(field_0x34[iVar2->field_0x72[param_1]]);
    }
    return J2DTevOrder();
}

J2DGXColorS10 J2DMaterialFactory::newTevColor(int param_0, int param_1) const {
    GXColorS10 color = {0, 0, 0, 0};
    J2DGXColorS10 rv = color;
    J2DMaterialInitData* iVar2 = &mMatInitData[field_0x8[param_0]];

    if (iVar2->field_0x92[param_1] != 0xffff) {
        return field_0x38[iVar2->field_0x92[param_1]];
    }
    
    return rv;
}

JUtility::TColor J2DMaterialFactory::newTevKColor(int param_0, int param_1) const {
    JUtility::TColor local_20 = (GXColor){0xFF, 0xFF, 0xFF, 0xFF};
    J2DMaterialInitData* iVar2 = &mMatInitData[field_0x8[param_0]];
    if (iVar2->field_0x4a[param_1] != 0xffff) {
        return field_0x3c[iVar2->field_0x4a[param_1]];
    }
    return local_20;
}

u8 J2DMaterialFactory::newTevStageNum(int param_0) const {
    J2DMaterialInitData* iVar2 = &mMatInitData[field_0x8[param_0]];
    if (iVar2->field_0x4 != 0xff) {
        return field_0x40[iVar2->field_0x4];
    }
    return 0xFF;
}

J2DTevStage J2DMaterialFactory::newTevStage(int param_0, int param_1) const {
    J2DMaterialInitData* iVar2 = &mMatInitData[field_0x8[param_0]];
    if (iVar2->field_0x9a[param_1] != 0xffff) {
        return J2DTevStage(field_0x44[iVar2->field_0x9a[param_1]]);
    }
    return J2DTevStage();
}

J2DTevSwapModeTable J2DMaterialFactory::newTevSwapModeTable(int param_0, int param_1) const {
    J2DMaterialInitData* iVar2 = &mMatInitData[field_0x8[param_0]];
    if (iVar2->field_0xda[param_1] != 0xffff) {
        return J2DTevSwapModeTable(field_0x4c[iVar2->field_0xda[param_1]]);
    }
    return J2DTevSwapModeTable(j2dDefaultTevSwapModeTable);
}

u8 J2DMaterialFactory::newIndTexStageNum(int param_0) const {
    if (mIndInitData != NULL) {
        if (mIndInitData[param_0].field_0x0 == 1) {
            return mIndInitData[param_0].field_0x1;
        }
    }
    return 0;
}

J2DIndTexOrder J2DMaterialFactory::newIndTexOrder(int param_0, int param_1) const {
    J2DIndTexOrder rv;
    if (mIndInitData != NULL) {
        if (mIndInitData[param_0].field_0x0 == 1) {
            return J2DIndTexOrder(mIndInitData[param_0].field_0x4[param_1]);
        }
    }
    return rv;
}

J2DIndTexMtx J2DMaterialFactory::newIndTexMtx(int param_0, int param_1) const {
    J2DIndTexMtx rv;
    if (mIndInitData != NULL) {
        if (mIndInitData[param_0].field_0x0 == 1) {
            return J2DIndTexMtx(mIndInitData[param_0].field_0xc[param_1]);
        }
    }
    return rv;
}

J2DIndTevStage J2DMaterialFactory::newIndTevStage(int param_0, int param_1) const {
    J2DIndTevStage rv;
    if (mIndInitData != NULL) {
        if (mIndInitData[param_0].field_0x0 == 1) {
            return J2DIndTevStage(mIndInitData[param_0].field_0x68[param_1]);
        }
    }
    return rv;
}

J2DIndTexCoordScale J2DMaterialFactory::newIndTexCoordScale(int param_0, int param_1) const {
    J2DIndTexCoordScale rv;
    if (mIndInitData != NULL) {
        if (mIndInitData[param_0].field_0x0 == 1) {
            return J2DIndTexCoordScale(mIndInitData[param_0].field_0x60[param_1]);
        }
    }
    return rv;
}

J2DAlphaComp J2DMaterialFactory::newAlphaComp(int param_0) const {
    J2DMaterialInitData* iVar2 = &mMatInitData[field_0x8[param_0]];
    if (iVar2->field_0xe2 != 0xffff) {
        return J2DAlphaComp(field_0x50[iVar2->field_0xe2]);
    }
    return J2DAlphaComp();
}

J2DBlend J2DMaterialFactory::newBlend(int param_0) const {
    J2DMaterialInitData* iVar2 = &mMatInitData[field_0x8[param_0]];
    if (iVar2->field_0xe4 != 0xffff) {
        return J2DBlend(field_0x54[iVar2->field_0xe4]);
    }
    return J2DBlend();
}

u8 J2DMaterialFactory::newDither(int param_0) const {
    J2DMaterialInitData* iVar2 = &mMatInitData[field_0x8[param_0]];
    if (iVar2->field_0x5 != 0xff) {
        return field_0x58[iVar2->field_0x5];
    }
    return 0;
}
