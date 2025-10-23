/**
 * @file d_a_obj_grz_rock.cpp
 * 
*/

#include "d/dolzel_rel.h" // IWYU pragma: keep

#include "d/actor/d_a_obj_grz_rock.h"

/* 80C14BD8-80C14C54 000078 007C+00 2/2 0/0 0/0 .text            setBaseMtx__14daObjGrzRock_cFv */
void daObjGrzRock_c::setBaseMtx() {
    mDoMtx_stack_c::transS(current.pos.x, current.pos.y, current.pos.z);
    mDoMtx_stack_c::ZXYrotM(shape_angle.x, shape_angle.y, shape_angle.z);
    mpModel->setBaseTRMtx(mDoMtx_stack_c::get());
    MTXCopy(mDoMtx_stack_c::get(), mBgMtx);
}

/* 80C14C54-80C14CB0 0000F4 005C+00 1/1 0/0 0/0 .text            setEnvTevColor__14daObjGrzRock_cFv */
void daObjGrzRock_c::setEnvTevColor() {
    tevStr.YukaCol = dComIfG_Bgsp().GetPolyColor(mGndChk);
    tevStr.room_no = dComIfG_Bgsp().GetRoomId(mGndChk);
}

/* 80C14CB0-80C14CF0 000150 0040+00 1/1 0/0 0/0 .text            setRoomNo__14daObjGrzRock_cFv */
void daObjGrzRock_c::setRoomNo() {
    fopAcM_SetRoomNo(this, dComIfG_Bgsp().GetRoomId(mGndChk));
}

/* 80C14CF0-80C14DA0 000190 00B0+00 1/1 0/0 0/0 .text            setPrtcl__14daObjGrzRock_cFv */
void daObjGrzRock_c::setPrtcl() {
    static u16 const l_prticles_id[6] = {
        dPa_RM(ID_ZI_S_BOMBROCK_FL_BREAK_A), dPa_RM(ID_ZI_S_BOMBROCK_FL_BREAK_B), dPa_RM(ID_ZI_S_BOMBROCK_FL_BREAK_C),
        dPa_RM(ID_ZI_S_BOMBROCK_FL_BREAK_D), dPa_RM(ID_ZI_S_BOMBROCK_FL_BREAK_E), dPa_RM(ID_ZI_S_BOMBROCK_FL_BREAK_F),
    };

    cXyz i_scale(0.85f, 0.85f, 0.85f);
    for (int i = 0; i < 6; i++) {
        dComIfGp_particle_set(l_prticles_id[i], &current.pos, &tevStr, &current.angle, &i_scale);
    }
}

/* 80C14DA0-80C14EE0 000240 0140+00 1/0 0/0 0/0 .text            Create__14daObjGrzRock_cFv */
int daObjGrzRock_c::Create() {
    setBaseMtx();
    fopAcM_SetMtx(this, mpModel->getBaseTRMtx());
    J3DJoint* joint_p = mpModel->getModelData()->getJointNodePointer(0);
    fopAcM_setCullSizeBox(this, joint_p->getMin()->x, joint_p->getMin()->y, joint_p->getMin()->z, joint_p->getMax()->x, joint_p->getMax()->y, joint_p->getMax()->z);
    mAcchCir.SetWall(0.0f, 0.0f);
    mBgc.Set(fopAcM_GetPosition_p(this), fopAcM_GetOldPosition_p(this), this, 1, &mAcchCir, fopAcM_GetSpeed_p(this), fopAcM_GetAngle_p(this), fopAcM_GetShapeAngle_p(this));
    mBgc.CrrPos(dComIfG_Bgsp());
    mGndChk = mBgc.m_gnd;
    setEnvTevColor();
    setRoomNo();
    return 1;
}

/* 80C1538C-80C15390 -00001 0004+00 3/3 0/0 0/0 .data            l_arcName */
static char* l_arcName = "grZRock";

/* 80C14EE0-80C14F50 000380 0070+00 1/0 0/0 0/0 .text            CreateHeap__14daObjGrzRock_cFv */
int daObjGrzRock_c::CreateHeap() {
    J3DModelData* modelData = (J3DModelData*)dComIfG_getObjectRes(l_arcName, 4);
    JUT_ASSERT(246, modelData != NULL);
    mpModel = mDoExt_J3DModel__create(modelData, 0x80000, 0x11020084);
    if (mpModel == NULL) {
        return 0;
    }

    return 1;
}

/* 80C14F50-80C150DC 0003F0 018C+00 1/1 0/0 0/0 .text            create__14daObjGrzRock_cFv */
cPhs__Step daObjGrzRock_c::create() {
    fopAcM_ct(this, daObjGrzRock_c);

    if (dComIfGs_isSwitch((fopAcM_GetParam(this) >> 8) & 0xFF, fopAcM_GetRoomNo(this))) {
        return cPhs_ERROR_e;
    }

    int dzb_id = 0;
    int i = 0;
    cPhs__Step phase;
    for (; i < 1; i++) {
        phase = (cPhs__Step)dComIfG_resLoad(&mPhase[i], l_arcName);
        if (phase == cPhs_ERROR_e || phase == cPhs_UNK3_e) {
            return cPhs_ERROR_e;
        }

        if (phase == cPhs_COMPLEATE_e) {
            dzb_id++;
        }
    }

    if (i == dzb_id) {
        dzb_id = dComIfG_getObjctResName2Index(l_arcName, "grZRock.dzb");
        JUT_ASSERT(302, dzb_id != -1);

        phase = (cPhs__Step)MoveBGCreate(l_arcName, dzb_id, dBgS_MoveBGProc_TypicalRotY, 0x1030, NULL);
        if (phase == cPhs_ERROR_e) {
            return phase;
        }

        mSmashFlag = 0;
    }

    return phase;
}

/* 80C1514C-80C151A4 0005EC 0058+00 1/0 0/0 0/0 .text            Execute__14daObjGrzRock_cFPPA3_A4_f */
int daObjGrzRock_c::Execute(Mtx** mtx) {
    if (mSmashFlag) {
        setPrtcl();
        fopAcM_delete(this);
        return 1;
    }

    *mtx = &mBgMtx;
    setBaseMtx();
    return 1;
}

/* 80C151A4-80C15248 000644 00A4+00 1/0 0/0 0/0 .text            Draw__14daObjGrzRock_cFv */
int daObjGrzRock_c::Draw() {
    g_env_light.settingTevStruct(16, &current.pos, &tevStr);
    g_env_light.setLightTevColorType_MAJI(mpModel, &tevStr);
    dComIfGd_setListBG();
    mDoExt_modelUpdateDL(mpModel);
    dComIfGd_setList();
    return 1;
}

/* 80C15248-80C152B4 0006E8 006C+00 1/0 0/0 0/0 .text            Delete__14daObjGrzRock_cFv */
int daObjGrzRock_c::Delete() {
    for (int i = 0; i < 1; i++) {
        dComIfG_resDelete(&mPhase[i], l_arcName);
    }

    if (mpBgW != NULL && mpBgW->ChkUsed()) {
        if (dComIfG_Bgsp().Release(mpBgW)) {
            OS_REPORT("Release Error\n");
        }
    }

    return 1;
}

/* 80C152B4-80C152E0 000754 002C+00 1/0 0/0 0/0 .text daObjGrzRock_Draw__FP14daObjGrzRock_c */
static int daObjGrzRock_Draw(daObjGrzRock_c* i_this) {
    return i_this->Draw();
}

/* 80C152E0-80C15300 000780 0020+00 1/0 0/0 0/0 .text daObjGrzRock_Execute__FP14daObjGrzRock_c */
static int daObjGrzRock_Execute(daObjGrzRock_c* i_this) {
    return i_this->MoveBGExecute();
}

/* 80C15300-80C15308 0007A0 0008+00 1/0 0/0 0/0 .text daObjGrzRock_IsDelete__FP14daObjGrzRock_c */
static int daObjGrzRock_IsDelete(daObjGrzRock_c* i_this) {
    return 1;
}

/* 80C15308-80C15328 0007A8 0020+00 1/0 0/0 0/0 .text daObjGrzRock_Delete__FP14daObjGrzRock_c */
static int daObjGrzRock_Delete(daObjGrzRock_c* i_this) {
    return i_this->MoveBGDelete();
}

/* 80C15328-80C15348 0007C8 0020+00 1/0 0/0 0/0 .text            daObjGrzRock_create__FP10fopAc_ac_c */
static int daObjGrzRock_create(fopAc_ac_c* a_this) {
    return static_cast<daObjGrzRock_c*>(a_this)->create();
}

/* 80C15390-80C153B0 -00001 0020+00 1/0 0/0 0/0 .data            l_daObjGrzRock_Method */
static actor_method_class l_daObjGrzRock_Method = {
    (process_method_func)daObjGrzRock_create,
    (process_method_func)daObjGrzRock_Delete,
    (process_method_func)daObjGrzRock_Execute,
    (process_method_func)daObjGrzRock_IsDelete,
    (process_method_func)daObjGrzRock_Draw,
};

/* 80C153B0-80C153E0 -00001 0030+00 0/0 0/0 1/0 .data            g_profile_Obj_GrzRock */
extern actor_process_profile_definition g_profile_Obj_GrzRock = {
  fpcLy_CURRENT_e,        // mLayerID
  3,                      // mListID
  fpcPi_CURRENT_e,        // mListPrio
  PROC_Obj_GrzRock,       // mProcName
  &g_fpcLf_Method.base,  // sub_method
  sizeof(daObjGrzRock_c), // mSize
  0,                      // mSizeOther
  0,                      // mParameters
  &g_fopAc_Method.base,   // sub_method
  610,                    // mPriority
  &l_daObjGrzRock_Method, // sub_method
  0x00044100,             // mStatus
  fopAc_ACTOR_e,          // mActorType
  fopAc_CULLBOX_CUSTOM_e, // cullType
};
