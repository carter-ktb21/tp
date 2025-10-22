#ifndef D_A_OBJ_ITAMATO_H
#define D_A_OBJ_ITAMATO_H

#include "f_op/f_op_actor_mng.h"
#include "d/actor/d_a_arrow.h"
#include "d/d_cc_d.h"

/**
 * @ingroup actors-objects
 * @class daObj_ItaMato_c
 * @brief Plank Target
 *
 * @details
 *
*/

struct daObj_ItaMato_HIOParam {
    /* 0x00 */ f32 attn_offset;
    /* 0x04 */ f32 gravity;
    /* 0x08 */ f32 scale;
    /* 0x0C */ f32 real_shadow_size;
    /* 0x10 */ f32 shake_pow;
};

class daObj_ItaMato_HIO_c : public mDoHIO_entry_c {
    void genMessage(JORMContext* ctx) {
        ctx->genSlider("注目オフセット　", &param.attn_offset, 0.0f, 1000.0f, 0, NULL, 0xFFFF, 0xFFFF, 0x200, 0x18);
        ctx->genSlider("重力　　　　　　", &param.gravity, -100.0f, 100.0f, 0, NULL, 0xFFFF, 0xFFFF, 0x200, 0x18);
        ctx->genSlider("スケ−ル　　　　", &param.scale, 0.0f, 100.0f, 0, NULL, 0xFFFF, 0xFFFF, 0x200, 0x18);
        ctx->genSlider("リアル影サイズ　", &param.real_shadow_size, 0.0f, 10000.0f, 0, NULL, 0xFFFF, 0xFFFF, 0x200, 0x18);
        ctx->genSlider("揺れパワ−　　　", &param.shake_pow, 0.0f, 90.0f, 0, NULL, 0xFFFF, 0xFFFF, 0x200, 0x18);
        ctx->genButton("ファイル書き出し", 0x40000002, 0, NULL, 0xFFFF, 0xFFFF, 0x200, 0x18);
    }

    /* 0x0 */ daObj_ItaMato_HIOParam param;
};

class daObj_ItaMato_Param_c {
public:
    /* 80C2AB04 */ virtual ~daObj_ItaMato_Param_c() {}

    static daObj_ItaMato_HIOParam const m;
};

class daObj_ItaMato_c : public fopAc_ac_c {
public:
    /* 80C2971C */ cPhs__Step create();
    /* 80C29CD8 */ int CreateHeap();
    /* 80C29DAC */ int Delete();
    /* 80C29DE0 */ int Execute();
    /* 80C2A44C */ int Draw();
    /* 80C2A5D0 */ static int createHeapCallBack(fopAc_ac_c*);
    /* 80C2A5F0 */ static void tgHitCallBack(fopAc_ac_c*, dCcD_GObjInf*, fopAc_ac_c*, dCcD_GObjInf*);
    /* 80C2A620 */ const char* getResName();
    /* 80C2A630 */ void setSwayParam(fopAc_ac_c*);
    /* 80C2A7C4 */ void setPrtcls();
    /* 80C2A890 */ void setEnvTevColor();
    /* 80C2A8EC */ void setRoomNo();
    /* 80C2A930 */ void setMtx();

    u8 getType() { return 0; }
    u8 getBitSW() { return (fopAcM_GetParam(this) & 0xFF00) >> 8; }
    u8 getBitSW2() { return (fopAcM_GetParam(this) & 0xFF0000) >> 16; }

    int checkCrs(fopAc_ac_c* param_0, cXyz param_1, cXyz param_2, f32 param_3) {
        daArrow_c* arrow_p = (daArrow_c*)param_0;
        cM3dGSph sp38;
        cXyz sp2C;
        cXyz sp20;

        JUT_ASSERT(170, NULL != arrow_p);

        if (field_0xa16 != 0 || health == 0) {
            return 0;
        }

        sp38.Set(mSph.GetShapeP()->GetC(), mSph.GetShapeP()->GetR() + (arrow_p->getArrowAtR() * 2.0f));
        if ((param_1 - current.pos).abs() < param_3) {
            mLin.SetStartEnd(param_1, param_2);
            if (cM3d_Cross_LinSph(&mLin, &sp38)) {
                return 3;
            }
        }

        return 0;
    }

    int getNo() {
        u8 var_r31 = fopAcM_GetParam(this) & 0xFF;

        int no;
        if (var_r31 == 0xFF) {
            no = -1;
        } else {
            no = var_r31;
        }

        return no;
    }

    BOOL checkBrk() {
        if (field_0xa15 != 0) {
            return 4;
        }

        return 0;
    }

    void onFake() { mFake = true; }

private:
    /* 0x568 */ daObj_ItaMato_HIO_c* mHIO;
    /* 0x56C */ request_of_phase_process_class mPhase;
    /* 0x574 */ J3DModel* mpModels[2];
    /* 0x57C */ dBgS_ObjAcch mBgc;
    /* 0x754 */ dCcD_Stts mStts;
    /* 0x790 */ dBgS_AcchCir mAcchCir;
    /* 0x7D0 */ cBgS_GndChk mGndChk;
    /* 0x80C */ dCcD_Sph mSph;
    /* 0x944 */ cM3dGLin mLin;
    /* 0x960 */ dBgS_LinChk mLinChk;
    /* 0x9D0 */ csXyz field_0x9d0[3];
    /* 0x9E4 */ u32 mCutType;
    /* 0x9E8 */ int field_0x9e8;
    /* 0x9EC */ f32 mGroundH;
    /* 0x9F0 */ f32 field_0x9f0[3];
    /* 0x9FC */ s16 field_0x9fc[3];
    /* 0xA02 */ s16 field_0xa02;
    /* 0xA04 */ u32 mShadowKey;
    /* 0xA08 */ u32 mPrtcls[3];
    /* 0xA14 */ u8 mType;
    /* 0xA15 */ u8 field_0xa15;
    /* 0xA15 */ u8 field_0xa16;
    /* 0xA17 */ u8 field_0xa17;
    /* 0xA18 */ u8 field_0xa18;
    /* 0xA19 */ u8 mFake;

    /* 80C294EC */ virtual ~daObj_ItaMato_c();
};

STATIC_ASSERT(sizeof(daObj_ItaMato_c) == 0xa20);

#endif /* D_A_OBJ_ITAMATO_H */
