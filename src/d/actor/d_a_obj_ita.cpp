/**
 * @file d_a_obj_ita.cpp
 * 
*/

#include "d/dolzel_rel.h" // IWYU pragma: keep

#include "d/actor/d_a_obj_ita.h"
#include "d/actor/d_a_e_ymb.h"
#include "d/actor/d_a_player.h"
#include "d/d_s_play.h"

class daObj_ITA_HIO_c : public JORReflexible {
public:
    /* 80C2836C */ daObj_ITA_HIO_c();
    /* 80C29184 */ virtual ~daObj_ITA_HIO_c() {}

    void genMessage(JORMContext* ctx) {
        ctx->genLabel("ヒメクジ", 0x80000001, 0, NULL, 0xFFFF, 0xFFFF, 0x200, 0x18);
        ctx->genSlider("サーチエリア", &search_area, 0.0f, 2000.0f, 0, NULL, 0xFFFF, 0xFFFF, 0x200, 0x18);
        ctx->genSlider("飛ばし方向スピード", &launch_dir_spd, 0.0f, -100.0f, 0, NULL, 0xFFFF, 0xFFFF, 0x200, 0x18);
        ctx->genSlider("飛ばし方向Yスピード", &launch_dir_y_spd, 0.0f, 100.0f, 0, NULL, 0xFFFF, 0xFFFF, 0x200, 0x18);
        ctx->genSlider("重力設定", &gravity_settings, 0.0f, -20.0f, 0, NULL, 0xFFFF, 0xFFFF, 0x200, 0x18);
    }

    /* ヒメクジ */
    /* 0x04 */ s8 id;
    /* 0x08 */ f32 search_area;
    /* 0x0C */ f32 launch_dir_spd;
    /* 0x10 */ f32 launch_dir_y_spd;
    /* 0x14 */ f32 gravity_settings;
};

/* 80C29318-80C2931C -00001 0004+00 3/3 0/0 0/0 .data            l_arcName */
static char* l_arcName = "M_Ita";

/* 80C2836C-80C283AC 0000EC 0040+00 1/1 0/0 0/0 .text            __ct__15daObj_ITA_HIO_cFv */
daObj_ITA_HIO_c::daObj_ITA_HIO_c() {
    id = -1;
    search_area = 600.0f;
    launch_dir_spd = -16.0f;
    launch_dir_y_spd = 44.0f;
    gravity_settings = -9.0f;
}

static f32 dummy() {
    return 0.0f;
}

// Fakematch??? - Only way I could figure out how to get proper rodata placement
f32 daObjIta_c::dummy2() {
    return field_0x5c8;
}

/* 80C293DC-80C293F4 000014 0018+00 1/1 0/0 0/0 .bss             l_HIO */
static daObj_ITA_HIO_c l_HIO;

namespace {
    /* 80C293F4-80C293F8 00002C 0004+00 2/2 0/0 0/0 .bss             e_ymb__25@unnamed@d_a_obj_ita_cpp@ */
    static daE_YMB_c* e_ymb;

    /* 80C293F8-80C293FC 000030 0004+00 2/2 0/0 0/0 .bss e_ymb_Pos__25@unnamed@d_a_obj_ita_cpp@ */
    static cXyz* e_ymb_Pos;
} // namespace

/* 80C283AC-80C28674 00012C 02C8+00 1/1 0/0 0/0 .text            Search_Ymb__10daObjIta_cFv */
void daObjIta_c::Search_Ymb() {
    f32 zero = 0.0f;
    cXyz pos(e_ymb_Pos->x - current.pos.x, e_ymb_Pos->y - current.pos.y, e_ymb_Pos->z - current.pos.z);

    mDoMtx_stack_c::YrotS(-shape_angle.y);
    mDoMtx_stack_c::multVec(&pos, &pos);

    if (pos.x < BREG_F(0) + 750.0f && pos.x > -750.0f - BREG_F(0) && pos.z < 450.0f + BREG_F(1) && pos.z > -450.0f - BREG_F(1) && pos.y < BREG_F(7) + 600.0f) {
        f32 speed_f = fopAcM_GetSpeedF(e_ymb);
        zero = 0.0f;
        if (speed_f > zero) {
            field_0x5b0 = speed_f * (BREG_F(6) + 16.0f) + 256.0f;
            e_ymb->setHitBoardSe();
            field_0x5a0 = speed_f * (BREG_F(5) + 31.0f);

            if (field_0x5e5 == 0 && field_0x6c0 == 1) {
                field_0x5a8 = -5.0f;
                u8 i_pattern[6] = {0, 32, 1, 0, 16, 0};
                dComIfGp_getVibration().StartQuake(i_pattern, 1, 1, cXyz(0.0f, 1.0f, 0.0f));
                field_0x5e5 = 1;
                field_0x5e6 = 90;

                if (field_0x5a0 > 300.0f && field_0x5a0 < 1900.0f) {
                    fopAcM_seStart(this, Z2SE_OBJ_FLOATBOARD_SWING, 0);
                } else if (field_0x5a0 >= 1900.0f) {
                    fopAcM_seStart(this, Z2SE_OBJ_FLOATBOARD_SWING_L, 0);
                }
            }

            cLib_addCalc(&field_0x5d4, BREG_F(8) + -100.0f, 0.5f, 100.0f, 0.0f);
        }
    } else if (field_0x5e6 == 1) {
        dComIfGp_getVibration().StopQuake(31);
        field_0x5e5 = 0;
    }
}

/* 80C28674-80C28788 0003F4 0114+00 1/1 0/0 0/0 .text            Check_RideOn__10daObjIta_cFv */
BOOL daObjIta_c::Check_RideOn() {
    daPy_py_c* player = daPy_getPlayerActorClass();
    cXyz& pos = fopAcM_GetPosition(player);

    field_0x6c0 = 1;
    cXyz vecTrans(pos.x - current.pos.x, pos.y - current.pos.y, pos.z - current.pos.z);
    mDoMtx_stack_c::YrotS(-shape_angle.y);
    mDoMtx_stack_c::multVec(&vecTrans, &vecTrans);

    if (vecTrans.x < 1000.0f && vecTrans.x > -1000.0f && vecTrans.z < 700.0f && vecTrans.z > -700.0f && fopAcM_GetSpeedF(player) > 0.0f) {
        cLib_addCalcAngleS(&field_0x5b0, 0x150, 11, 0x100, 0);
        field_0x5c8 = 0x400;
    }

    return FALSE;
}

/* 80C28788-80C287B4 000508 002C+00 1/1 0/0 0/0 .text            initBaseMtx__10daObjIta_cFv */
void daObjIta_c::initBaseMtx() {
    fopAcM_SetMtx(this, mpModel->getBaseTRMtx());
    setBaseMtx();
}

/* 80C287B4-80C28838 000534 0084+00 2/2 0/0 0/0 .text            setBaseMtx__10daObjIta_cFv */
void daObjIta_c::setBaseMtx() {
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(shape_angle.y);
    mDoMtx_stack_c::XrotM(shape_angle.z);
    mDoMtx_stack_c::ZrotM(shape_angle.x);
    mpModel->setBaseTRMtx(mDoMtx_stack_c::get());
    MTXCopy(mDoMtx_stack_c::get(), mBgMtx);
}

/* 80C28838-80C28890 0005B8 0058+00 1/1 0/0 0/0 .text            rideCallBack__FP4dBgWP10fopAc_ac_cP10fopAc_ac_c */
static void rideCallBack(dBgW* param_1, fopAc_ac_c* a_this, fopAc_ac_c* i_player) {
    daObjIta_c* i_this = (daObjIta_c*)a_this;

    if (fopAcM_GetName(i_player) == PROC_ALINK) {
        daPy_py_c* player = daPy_getPlayerActorClass();
        if (i_this->field_0x5ac < 0.0f) {
            i_this->field_0x5a8 = i_this->field_0x5ac * 0.8f;
            i_this->field_0x5ac = 0.0f;
        }

        i_this->Check_RideOn();
    }
}

/* 80C28890-80C288BC 000610 002C+00 1/0 0/0 0/0 .text            daObjIta_Draw__FP10daObjIta_c */
static int daObjIta_Draw(daObjIta_c* i_this) {
    return i_this->MoveBGDraw();
}

/* 80C288BC-80C288DC 00063C 0020+00 1/0 0/0 0/0 .text            daObjIta_Execute__FP10daObjIta_c */
static int daObjIta_Execute(daObjIta_c* i_this) {
    return i_this->MoveBGExecute();
}

/* 80C288DC-80C288E4 00065C 0008+00 1/0 0/0 0/0 .text            daObjIta_IsDelete__FP10daObjIta_c */
static int daObjIta_IsDelete(daObjIta_c* i_this) {
    return 1;
}

/* 80C288E4-80C28908 000664 0024+00 1/0 0/0 0/0 .text            daObjIta_Delete__FP10daObjIta_c */
static int daObjIta_Delete(daObjIta_c* i_this) {
    fpc_ProcID id = fopAcM_GetID(i_this);
    i_this->MoveBGDelete();
    return 1;
}

/* 80C28908-80C28928 000688 0020+00 1/0 0/0 0/0 .text            daObjIta_Create__FP10fopAc_ac_c */
static int daObjIta_Create(fopAc_ac_c* a_this) {
    daObjIta_c* i_this = (daObjIta_c*)a_this;
    fpc_ProcID id = fopAcM_GetID(a_this);
    return i_this->create();
}

/* 80C28BB0-80C28C28 000930 0078+00 1/0 0/0 0/0 .text            CreateHeap__10daObjIta_cFv */
int daObjIta_c::CreateHeap() {
    J3DModelData* modelData = (J3DModelData*)dComIfG_getObjectRes(l_arcName, "M_FloatingDust00.bmd");
    JUT_ASSERT(735, modelData != NULL);
    mpModel = mDoExt_J3DModel__create(modelData, 0x80000, 0x11000084);
    if (mpModel == NULL) {
        return 0;
    }

    return 1;
}

/* 80C28928-80C28B40 0006A8 0218+00 1/1 0/0 0/0 .text            create__10daObjIta_cFv */
cPhs__Step daObjIta_c::create() {
    fopAcM_ct(this, daObjIta_c);

    cPhs__Step phase = (cPhs__Step)dComIfG_resLoad(&mPhase, l_arcName);
    if (phase == cPhs_COMPLEATE_e) {
        int dzb_id = dComIfG_getObjctResName2Index(l_arcName, "M_FloatingDust00.dzb");
        JUT_ASSERT(763, dzb_id != -1);
        phase = (cPhs__Step)MoveBGCreate(l_arcName, dzb_id, dBgS_MoveBGProc_TypicalRotY, 0x1320, NULL);
        if (phase == cPhs_ERROR_e) {
            return phase;
        }
    }

    mBgc.Set(fopAcM_GetPosition_p(this), fopAcM_GetOldPosition_p(this), this, 1, &mAcchCir, fopAcM_GetSpeed_p(this), NULL, NULL);
    mAcchCir.SetWall(100.0f, 200.0f);
    field_0x5b0 = 0x100;
    mBgc.CrrPos(dComIfG_Bgsp());
    fopAcM_setCullSizeBox(this, -750.0f, -50.0f, -450.0f, 750.0f, 50.0f, 450.0f);

    cXyz pos(current.pos.x, current.pos.y + 300.0f, current.pos.z);
    if (fopAcM_wt_c::waterCheck(&pos)) {
        current.pos.y = oREG_F(0) + HREG_F(0) + fopAcM_wt_c::getWaterY() + 50.0f;
    }

    return phase;
}

/* 80C28C28-80C28C70 0009A8 0048+00 1/0 0/0 0/0 .text            Create__10daObjIta_cFv */
int daObjIta_c::Create() {
    initBaseMtx();
    mpBgW->SetRideCallback(rideCallBack);
    fopAcM_wt_c::waterCheck(&current.pos);
    return cPhs_COMPLEATE_e;
}

/* 80C28C70-80C290AC 0009F0 043C+00 1/0 0/0 0/0 .text            Execute__10daObjIta_cFPPA3_A4_f */
int daObjIta_c::Execute(Mtx** mtx) {
    fopAcM_seStartLevel(this, Z2SE_OBJ_FLOATBOARD, 0);

    field_0x5e6--;
    if (field_0x5e6 < 0) {
        field_0x5e6 = 0;
    }

    daPy_py_c* player = daPy_getPlayerActorClass();
    cXyz& playerSpeed = fopAcM_GetSpeed(player);

    if (fopAcM_SearchByName(PROC_E_YMB, (fopAc_ac_c**)&e_ymb) != 0 && e_ymb != NULL) {
        e_ymb_Pos = &fopAcM_GetPosition(e_ymb);
    }

    if (playerSpeed.y != 0.0f) {
        field_0x5ac = playerSpeed.y;
    }

    field_0x5ca += (TREG_F(1) + 768.0f) + (HREG_F(1) + 2.0f) * field_0x5a4 + (BREG_F(3) + 2.0f) * field_0x5a0;
    field_0x5cc += (TREG_F(2) + 768.0f) + (HREG_F(2) + 2.0f) * field_0x5a4 + (BREG_F(3) + 2.0f) * field_0x5a0;

    if (e_ymb != NULL) {
        Search_Ymb();
    }

    f32 posY = current.pos.y;
    cXyz pos(current.pos.x, current.pos.y + 300.0f, current.pos.z);
    if (fopAcM_wt_c::waterCheck(&pos)) {
        posY = fopAcM_wt_c::getWaterY() - 40.0f;
    }

    cLib_addCalc(&current.pos.y, field_0x5d4 + (posY + 60.0f + field_0x5a8 * (HREG_F(0) + 5.0f) + cM_ssin(field_0x5cc) * 20.0f), 0.1f, 15.0f, 0.1f);
    cLib_addCalcAngleS(&shape_angle.x, field_0x5ce.x + (nREG_F(0) + 1.0f) * field_0x5b0 * cM_ssin(field_0x5ca + oREG_F(1) + 0x2000), 2, 0x1000, 1);
    cLib_addCalcAngleS(&shape_angle.z, field_0x5ce.z + (nREG_F(1) + 1.0f) * field_0x5b0 * cM_ssin(field_0x5cc), 2, 0x1000, 1);
    cLib_addCalc(&field_0x5a4, field_0x5c8, HREG_F(13) + 0.05f, 100.0f, 0.0f);
    cLib_addCalc2(&field_0x5a8, 0.0f, HREG_F(1) + 0.1f, 10.0f);
    cLib_addCalc(&field_0x5a0, 0.0f, HREG_F(13) + 0.01f, 100.0f, 0.0f);
    cLib_addCalc(&field_0x5d4, 0.0f, 0.1f, 100.0f, 0.0f);
    cLib_addCalcAngleS(&field_0x5b0, 0x100, 11, 0x100, 0);
    cLib_addCalcAngleS(&field_0x5ce.x, 0, 2, 0x100, 1);
    cLib_addCalcAngleS(&field_0x5ce.z, 0, 2, 0x100, 1);

    field_0x5c8 = 0;
    field_0x6c0 = 0;
    fopAcM_posMoveF(this, mStts.GetCCMoveP());
    *mtx = &mBgMtx;
    setBaseMtx();
    mBgc.CrrPos(dComIfG_Bgsp());

    return 1;
}

/* 80C290AC-80C29150 000E2C 00A4+00 1/0 0/0 0/0 .text            Draw__10daObjIta_cFv */
int daObjIta_c::Draw() {
    g_env_light.settingTevStruct(16, &current.pos, &tevStr);
    g_env_light.setLightTevColorType_MAJI(mpModel, &tevStr);
    dComIfGd_setListBG();
    mDoExt_modelUpdateDL(mpModel);
    dComIfGd_setList();
    return 1;
}

/* 80C29150-80C29184 000ED0 0034+00 1/0 0/0 0/0 .text            Delete__10daObjIta_cFv */
int daObjIta_c::Delete() {
    dComIfG_resDelete(&mPhase, l_arcName);
    return 1;
}

/* 80C2931C-80C2933C -00001 0020+00 1/0 0/0 0/0 .data            l_daObjIta_Method */
static actor_method_class l_daObjIta_Method = {
    (process_method_func)daObjIta_Create,
    (process_method_func)daObjIta_Delete,
    (process_method_func)daObjIta_Execute,
    (process_method_func)daObjIta_IsDelete,
    (process_method_func)daObjIta_Draw,
};

/* 80C2933C-80C2936C -00001 0030+00 0/0 0/0 1/0 .data            g_profile_Obj_ITA */
extern actor_process_profile_definition g_profile_Obj_ITA = {
  fpcLy_CURRENT_e,        // mLayerID
  3,                      // mListID
  fpcPi_CURRENT_e,        // mListPrio
  PROC_Obj_ITA,           // mProcName
  &g_fpcLf_Method.base,  // sub_method
  sizeof(daObjIta_c),     // mSize
  0,                      // mSizeOther
  0,                      // mParameters
  &g_fopAc_Method.base,   // sub_method
  474,                    // mPriority
  &l_daObjIta_Method,     // sub_method
  0x00040100,             // mStatus
  fopAc_ACTOR_e,          // mActorType
  fopAc_CULLBOX_CUSTOM_e, // cullType
};
