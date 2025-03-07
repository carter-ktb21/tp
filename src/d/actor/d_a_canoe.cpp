/**
 * @file d_a_canoe.cpp
 * 
*/

#include "d/actor/d_a_canoe.h"
#include "dol2asm.h"
#include "d/d_com_inf_game.h"
#include "d/d_meter2_info.h"



//
// Forward References:
//

extern "C" static void daCanoe_searchTagWaterFall__FP10fopAc_ac_cPv();
extern "C" void __dt__4cXyzFv();
extern "C" void createHeap__9daCanoe_cFv();
extern "C" static void daCanoe_createHeap__FP10fopAc_ac_c();
extern "C" void create__9daCanoe_cFv();
extern "C" void __dt__8dCcD_CylFv();
extern "C" void __ct__8dCcD_CylFv();
extern "C" void __dt__8cM3dGCylFv();
extern "C" void __dt__8cM3dGAabFv();
extern "C" void __dt__13dBgS_LinkAcchFv();
extern "C" void __ct__13dBgS_LinkAcchFv();
extern "C" void __dt__12dBgS_AcchCirFv();
extern "C" void __dt__10dCcD_GSttsFv();
extern "C" static void daCanoe_Create__FP10fopAc_ac_c();
extern "C" void __dt__9daCanoe_cFv();
extern "C" static void daCanoe_Delete__FP9daCanoe_c();
extern "C" void setRoomInfo__9daCanoe_cFv();
extern "C" void setMatrix__9daCanoe_cFv();
extern "C" void setCollision__9daCanoe_cFv();
extern "C" void posMove__9daCanoe_cFv();
extern "C" void checkGomikabe__9daCanoe_cFR13cBgS_PolyInfo();
extern "C" void setFrontBackPos__9daCanoe_cFv();
extern "C" void frontBackBgCheck__9daCanoe_cFv();
extern "C" void __dt__8cM3dGPlaFv();
extern "C" void setPaddleEffect__9daCanoe_cFv();
extern "C" void setCanoeSliderEffect__9daCanoe_cFv();
extern "C" void execute__9daCanoe_cFv();
extern "C" static void daCanoe_Execute__FP9daCanoe_c();
extern "C" void draw__9daCanoe_cFv();
extern "C" static void daCanoe_Draw__FP9daCanoe_c();
extern "C" void __dt__10cCcD_GSttsFv();
extern "C" static void func_804DD5BC();
extern "C" static void func_804DD5C4();
extern "C" extern char const* const d_a_canoe__stringBase0;

//
// External References:
//

extern "C" void mDoMtx_XYZrotM__FPA4_fsss();
extern "C" void transM__14mDoMtx_stack_cFfff();
extern "C" void ZXYrotM__14mDoMtx_stack_cFRC5csXyz();
extern "C" void mDoExt_modelUpdateDL__FP8J3DModel();
extern "C" void mDoExt_J3DModel__create__FP12J3DModelDataUlUl();
extern "C" void __ct__10fopAc_ac_cFv();
extern "C" void __dt__10fopAc_ac_cFv();
extern "C" void fopAcIt_Executor__FPFPvPv_iPv();
extern "C" void fopAcM_entrySolidHeap__FP10fopAc_ac_cPFP10fopAc_ac_c_iUl();
extern "C" void fopAcM_SetMin__FP10fopAc_ac_cfff();
extern "C" void fopAcM_SetMax__FP10fopAc_ac_cfff();
extern "C" void fopAcM_getWaterStream__FPC4cXyzRC13cBgS_PolyInfoP4cXyzPii();
extern "C" void waterCheck__11fopAcM_wt_cFPC4cXyz();
extern "C" void fopKyM_createWpillar__FPC4cXyzfi();
extern "C" void dComIfG_resLoad__FP30request_of_phase_process_classPCc();
extern "C" void dComIfG_resDelete__FP30request_of_phase_process_classPCc();
extern "C" void dComIfGp_getReverb__Fi();
extern "C" void
dComIfGd_setShadow__FUlScP8J3DModelP4cXyzffffR13cBgS_PolyInfoP12dKy_tevstr_csfP9_GXTexObj();
extern "C" void isEventBit__11dSv_event_cCFUs();
extern "C" void getRes__14dRes_control_cFPCclP11dRes_info_ci();
extern "C" void getEmitter__Q213dPa_control_c7level_cFUl();
extern "C" void
setWaterRipple__13dPa_control_cFPUlR13cBgS_PolyInfoPC4cXyzfPC12dKy_tevstr_cPC4cXyzSc();
extern "C" void
set__13dPa_control_cFUlUcUsPC4cXyzPC12dKy_tevstr_cPC5csXyzPC4cXyzUcP18dPa_levelEcallBackScPC8_GXColorPC8_GXColorPC4cXyzf();
extern "C" void addReal__21dDlst_shadowControl_cFUlP8J3DModel();
extern "C" void StartShock__12dVibration_cFii4cXyz();
extern "C" void LineCross__4cBgSFP11cBgS_LinChk();
extern "C" void GetActorPointer__4cBgSCFi();
extern "C" void GetTriPla__4cBgSCFRC13cBgS_PolyInfoP8cM3dGPla();
extern "C" void GetPolyColor__4dBgSFRC13cBgS_PolyInfo();
extern "C" void GetRoomId__4dBgSFRC13cBgS_PolyInfo();
extern "C" void __ct__12dBgS_AcchCirFv();
extern "C" void SetWall__12dBgS_AcchCirFff();
extern "C" void __dt__9dBgS_AcchFv();
extern "C" void __ct__9dBgS_AcchFv();
extern "C" void Set__9dBgS_AcchFP4cXyzP4cXyzP10fopAc_ac_ciP12dBgS_AcchCirP4cXyzP5csXyzP5csXyz();
extern "C" void Set__9dBgS_AcchFP10fopAc_ac_ciP12dBgS_AcchCir();
extern "C" void CrrPos__9dBgS_AcchFR4dBgS();
extern "C" void Set__11dBgS_LinChkFPC4cXyzPC4cXyzPC10fopAc_ac_c();
extern "C" void __ct__15dBgS_LinkLinChkFv();
extern "C" void __dt__15dBgS_LinkLinChkFv();
extern "C" void SetLink__16dBgS_PolyPassChkFv();
extern "C" void GetAc__22dCcD_GAtTgCoCommonBaseFv();
extern "C" void __ct__10dCcD_GSttsFv();
extern "C" void Move__10dCcD_GSttsFv();
extern "C" void Init__9dCcD_SttsFiiP10fopAc_ac_c();
extern "C" void __ct__12dCcD_GObjInfFv();
extern "C" void __dt__12dCcD_GObjInfFv();
extern "C" void ChkCoHit__12dCcD_GObjInfFv();
extern "C" void Set__8dCcD_CylFRC11dCcD_SrcCyl();
extern "C" void getMoveBGActorName__9daAlink_cFR13cBgS_PolyInfoi();
extern "C" void getCanoeMaxSpeed__9daAlink_cCFv();
extern "C" void getCanoeBackMaxSpeed__9daAlink_cCFv();
extern "C" void getCanoeCres__9daAlink_cCFv();
extern "C" void getCanoeMaxRotSpeed__9daAlink_cCFv();
extern "C" void getCanoeLocalPaddleTop__9daAlink_cFv();
extern "C" void getCanoePaddleMatrix__9daAlink_cFv();
extern "C" void checkCanoePaddleGrab__9daAlink_cCFP10fopAc_ac_c();
extern "C" void checkFishingRodItem__9daPy_py_cFi();
extern "C" void settingTevStruct__18dScnKy_env_light_cFiP4cXyzP12dKy_tevstr_c();
extern "C" void setLightTevColorType_MAJI__18dScnKy_env_light_cFP12J3DModelDataP12dKy_tevstr_c();
extern "C" void setMiniGameCount__13dMeter2Info_cFSc();
extern "C" void ClrCcMove__9cCcD_SttsFv();
extern "C" void SetVsGrp__10cCcD_ObjCoFUl();
extern "C" void Set__4cCcSFP8cCcD_Obj();
extern "C" void __pl__4cXyzCFRC3Vec();
extern "C" void __mi__4cXyzCFRC3Vec();
extern "C" void __ml__4cXyzCFf();
extern "C" void atan2sX_Z__4cXyzCFv();
extern "C" void atan2sY_XZ__4cXyzCFv();
extern "C" void cM_rad2s__Ff();
extern "C" void cM_atan2s__Fff();
extern "C" void cM_rndF__Ff();
extern "C" void __dt__13cBgS_PolyInfoFv();
extern "C" void __dt__8cM3dGCirFv();
extern "C" void SetC__8cM3dGCylFRC4cXyz();
extern "C" void cLib_addCalc__FPfffff();
extern "C" void cLib_addCalcPosXZ__FP4cXyzRC4cXyzfff();
extern "C" void cLib_addCalcAngleS__FPsssss();
extern "C" void cLib_addCalcAngleS2__FPssss();
extern "C" void cLib_chaseF__FPfff();
extern "C" void cLib_distanceAngleS__Fss();
extern "C" void func_802807E0();
extern "C" void seStart__7Z2SeMgrF10JAISoundIDPC3VecUlScffffUc();
extern "C" void __dt__14Z2SoundObjBaseFv();
extern "C" void deleteObject__14Z2SoundObjBaseFv();
extern "C" void __ct__16Z2SoundObjSimpleFv();
extern "C" void __dl__FPv();
extern "C" void __destroy_arr();
extern "C" void __construct_array();
extern "C" void __cvt_fp2unsigned();
extern "C" void _savegpr_19();
extern "C" void _savegpr_24();
extern "C" void _savegpr_25();
extern "C" void _savegpr_26();
extern "C" void _savegpr_27();
extern "C" void _savegpr_28();
extern "C" void _savegpr_29();
extern "C" void _restgpr_19();
extern "C" void _restgpr_24();
extern "C" void _restgpr_25();
extern "C" void _restgpr_26();
extern "C" void _restgpr_27();
extern "C" void _restgpr_28();
extern "C" void _restgpr_29();
extern "C" u8 saveBitLabels__16dSv_event_flag_c[1644 + 4 /* padding */];
extern "C" extern void* __vt__8dCcD_Cyl[36];
extern "C" extern void* __vt__9dCcD_Stts[11];
extern "C" extern void* __vt__12cCcD_CylAttr[25];
extern "C" extern void* __vt__14cCcD_ShapeAttr[22];
extern "C" extern void* __vt__9cCcD_Stts[8];
extern "C" extern void* __vt__16Z2SoundObjSimple[8];
extern "C" u8 now__14mDoMtx_stack_c[48];
extern "C" u8 mWaterCheck__11fopAcM_wt_c[84 + 4 /* padding */];
extern "C" u8 mSimpleTexObj__21dDlst_shadowControl_c[32];
extern "C" f32 Zero__4cXyz[3];
extern "C" u8 sincosTable___5JMath[65536];
extern "C" f32 mWaterY__11fopAcM_wt_c[1 + 1 /* padding */];
extern "C" u8 mAudioMgrPtr__10Z2AudioMgr[4 + 4 /* padding */];
extern "C" void __register_global_object();
extern "C" void BreakSet__15daObjGOMIKABE_cFv();
extern "C" void checkHitWaterFall__16daTagWaterFall_cF4cXyz();

//
// Declarations:
//

/* 804DA54C-804DA5B8 0000EC 006C+00 1/1 0/0 0/0 .text daCanoe_searchTagWaterFall__FP10fopAc_ac_cPv
 */
static void daCanoe_searchTagWaterFall(fopAc_ac_c* param_0, void* param_1) {
    // NONMATCHING
}

/* 804DA5B8-804DA5F4 000158 003C+00 2/2 0/0 0/0 .text            __dt__4cXyzFv */
// cXyz::~cXyz() {
extern "C" void __dt__4cXyzFv() {
    // NONMATCHING
}

/* 804DA5F4-804DA720 000194 012C+00 1/1 0/0 0/0 .text            createHeap__9daCanoe_cFv */
void daCanoe_c::createHeap() {
    // NONMATCHING
}

/* 804DA720-804DA740 0002C0 0020+00 1/1 0/0 0/0 .text            daCanoe_createHeap__FP10fopAc_ac_c
 */
static void daCanoe_createHeap(fopAc_ac_c* param_0) {
    // NONMATCHING
}

/* ############################################################################################## */
/* 804DD5DC-804DD5E8 000000 000C+00 8/8 0/0 0/0 .rodata          @3766 */
SECTION_RODATA static u8 const lit_3766[12] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
COMPILER_STRIP_GATE(0x804DD5DC, &lit_3766);

/* 804DD5E8-804DD5F0 00000C 0006+02 0/1 0/0 0/0 .rodata          l_arcName */
#pragma push
#pragma force_active on
SECTION_RODATA static u8 const l_arcName[6 + 2 /* padding */] = {
    0x43,
    0x61,
    0x6E,
    0x6F,
    0x65,
    0x00,
    /* padding */
    0x00,
    0x00,
};
COMPILER_STRIP_GATE(0x804DD5E8, &l_arcName);
#pragma pop

/* 804DD5F0-804DD5F8 000014 0007+01 0/1 0/0 0/0 .rodata          l_arcName2 */
#pragma push
#pragma force_active on
SECTION_RODATA static u8 const l_arcName2[7 + 1 /* padding */] = {
    0x43,
    0x61,
    0x6E,
    0x6F,
    0x65,
    0x42,
    0x00,
    /* padding */
    0x00,
};
COMPILER_STRIP_GATE(0x804DD5F0, &l_arcName2);
#pragma pop

/* 804DD5F8-804DD600 00001C 0008+00 0/1 0/0 0/0 .rodata          l_arcName3 */
#pragma push
#pragma force_active on
SECTION_RODATA static u8 const l_arcName3[8] = {
    0x43, 0x61, 0x6E, 0x6F, 0x65, 0x45, 0x33, 0x00,
};
COMPILER_STRIP_GATE(0x804DD5F8, &l_arcName3);
#pragma pop

/* 804DD600-804DD614 000024 0014+00 2/3 0/0 0/0 .rodata          l_cylOffsetZ */
SECTION_RODATA static u8 const l_cylOffsetZ[20] = {
    0x43, 0x48, 0x00, 0x00, 0x42, 0xDC, 0x00, 0x00, 0x41, 0xA0,
    0x00, 0x00, 0xC2, 0x8C, 0x00, 0x00, 0xC3, 0x20, 0x00, 0x00,
};
COMPILER_STRIP_GATE(0x804DD600, &l_cylOffsetZ);

/* 804DD614-804DD618 000038 0004+00 0/1 0/0 0/0 .rodata          @4328 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_4328 = -80.0f;
COMPILER_STRIP_GATE(0x804DD614, &lit_4328);
#pragma pop

/* 804DD618-804DD61C 00003C 0004+00 0/1 0/0 0/0 .rodata          @4329 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_4329 = -40.0f;
COMPILER_STRIP_GATE(0x804DD618, &lit_4329);
#pragma pop

/* 804DD61C-804DD620 000040 0004+00 0/1 0/0 0/0 .rodata          @4330 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_4330 = -230.0f;
COMPILER_STRIP_GATE(0x804DD61C, &lit_4330);
#pragma pop

/* 804DD620-804DD624 000044 0004+00 0/1 0/0 0/0 .rodata          @4331 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_4331 = 80.0f;
COMPILER_STRIP_GATE(0x804DD620, &lit_4331);
#pragma pop

/* 804DD624-804DD628 000048 0004+00 0/1 0/0 0/0 .rodata          @4332 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_4332 = 90.0f;
COMPILER_STRIP_GATE(0x804DD624, &lit_4332);
#pragma pop

/* 804DD628-804DD62C 00004C 0004+00 0/1 0/0 0/0 .rodata          @4333 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_4333 = 280.0f;
COMPILER_STRIP_GATE(0x804DD628, &lit_4333);
#pragma pop

/* 804DD62C-804DD630 000050 0004+00 0/1 0/0 0/0 .rodata          @4334 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_4334 = 10.0f;
COMPILER_STRIP_GATE(0x804DD62C, &lit_4334);
#pragma pop

/* 804DD630-804DD634 000054 0004+00 0/2 0/0 0/0 .rodata          @4335 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_4335 = 60.0f;
COMPILER_STRIP_GATE(0x804DD630, &lit_4335);
#pragma pop

/* 804DD634-804DD638 000058 0004+00 0/3 0/0 0/0 .rodata          @4336 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_4336 = 40.0f;
COMPILER_STRIP_GATE(0x804DD634, &lit_4336);
#pragma pop

/* 804DD6E8-804DD6E8 00010C 0000+00 0/0 0/0 0/0 .rodata          @stringBase0 */
#pragma push
#pragma force_active on
SECTION_DEAD static char const* const stringBase_804DD6E8 = "F_SP127";
#pragma pop

/* 804DD6F0-804DD734 000000 0044+00 1/1 0/0 0/0 .data            l_cylSrc */
static dCcD_SrcCyl l_cylSrc = {
    {
        {0x0, {{0x0, 0x0, 0x0}, {0xd8fbfdff, 0x10}, 0x79}}, // mObj
        {dCcD_SE_NONE, 0x0, 0x0, 0x0, 0x0}, // mGObjAt
        {dCcD_SE_NONE, 0x0, 0x0, 0x0, 0x4}, // mGObjTg
        {0x0}, // mGObjCo
    }, // mObjInf
    {
        {0.0f, 0.0f, 0.0f}, // mCenter
        55.0f, // mRadius
        80.0f // mHeight
    } // mCyl
};

/* 804DA740-804DAB18 0002E0 03D8+00 1/1 0/0 0/0 .text            create__9daCanoe_cFv */
void daCanoe_c::create() {
    // NONMATCHING
}

/* ############################################################################################## */
/* 804DD734-804DD754 -00001 0020+00 1/0 0/0 0/0 .data            l_daCanoe_Method */
static actor_method_class l_daCanoe_Method = {
    (process_method_func)daCanoe_Create__FP10fopAc_ac_c,
    (process_method_func)daCanoe_Delete__FP9daCanoe_c,
    (process_method_func)daCanoe_Execute__FP9daCanoe_c,
    0,
    (process_method_func)daCanoe_Draw__FP9daCanoe_c,
};

/* 804DD754-804DD784 -00001 0030+00 0/0 0/0 1/0 .data            g_profile_CANOE */
extern actor_process_profile_definition g_profile_CANOE = {
  fpcLy_CURRENT_e,         // mLayerID
  4,                       // mListID
  fpcPi_CURRENT_e,         // mListPrio
  PROC_CANOE,              // mProcName
  &g_fpcLf_Method.base,   // sub_method
  sizeof(daCanoe_c),       // mSize
  0,                       // mSizeOther
  0,                       // mParameters
  &g_fopAc_Method.base,    // sub_method
  724,                     // mPriority
  &l_daCanoe_Method,       // sub_method
  0x00044100,              // mStatus
  fopAc_ENV_e,             // mActorType
  fopAc_CULLBOX_CUSTOM_e,  // cullType
};

/* 804DD784-804DD790 000094 000C+00 2/2 0/0 0/0 .data            __vt__8cM3dGPla */
SECTION_DATA extern void* __vt__8cM3dGPla[3] = {
    (void*)NULL /* RTTI */,
    (void*)NULL,
    (void*)__dt__8cM3dGPlaFv,
};

/* 804DD790-804DD79C 0000A0 000C+00 3/3 0/0 0/0 .data            __vt__10cCcD_GStts */
SECTION_DATA extern void* __vt__10cCcD_GStts[3] = {
    (void*)NULL /* RTTI */,
    (void*)NULL,
    (void*)__dt__10cCcD_GSttsFv,
};

/* 804DD79C-804DD7A8 0000AC 000C+00 2/2 0/0 0/0 .data            __vt__10dCcD_GStts */
SECTION_DATA extern void* __vt__10dCcD_GStts[3] = {
    (void*)NULL /* RTTI */,
    (void*)NULL,
    (void*)__dt__10dCcD_GSttsFv,
};

/* 804DD7A8-804DD7B4 0000B8 000C+00 1/1 0/0 0/0 .data            __vt__12dBgS_AcchCir */
SECTION_DATA extern void* __vt__12dBgS_AcchCir[3] = {
    (void*)NULL /* RTTI */,
    (void*)NULL,
    (void*)__dt__12dBgS_AcchCirFv,
};

/* 804DD7B4-804DD7D8 0000C4 0024+00 2/2 0/0 0/0 .data            __vt__13dBgS_LinkAcch */
SECTION_DATA extern void* __vt__13dBgS_LinkAcch[9] = {
    (void*)NULL /* RTTI */,
    (void*)NULL,
    (void*)__dt__13dBgS_LinkAcchFv,
    (void*)NULL,
    (void*)NULL,
    (void*)func_804DD5C4,
    (void*)NULL,
    (void*)NULL,
    (void*)func_804DD5BC,
};

/* 804DD7D8-804DD7E4 0000E8 000C+00 3/3 0/0 0/0 .data            __vt__8cM3dGAab */
SECTION_DATA extern void* __vt__8cM3dGAab[3] = {
    (void*)NULL /* RTTI */,
    (void*)NULL,
    (void*)__dt__8cM3dGAabFv,
};

/* 804DD7E4-804DD7F0 0000F4 000C+00 3/3 0/0 0/0 .data            __vt__8cM3dGCyl */
SECTION_DATA extern void* __vt__8cM3dGCyl[3] = {
    (void*)NULL /* RTTI */,
    (void*)NULL,
    (void*)__dt__8cM3dGCylFv,
};

/* 804DAB18-804DABE4 0006B8 00CC+00 2/2 0/0 0/0 .text            __dt__8dCcD_CylFv */
// dCcD_Cyl::~dCcD_Cyl() {
extern "C" void __dt__8dCcD_CylFv() {
    // NONMATCHING
}

/* 804DABE4-804DAC68 000784 0084+00 1/1 0/0 0/0 .text            __ct__8dCcD_CylFv */
// dCcD_Cyl::dCcD_Cyl() {
extern "C" void __ct__8dCcD_CylFv() {
    // NONMATCHING
}

/* 804DAC68-804DACB0 000808 0048+00 1/0 0/0 0/0 .text            __dt__8cM3dGCylFv */
// cM3dGCyl::~cM3dGCyl() {
extern "C" void __dt__8cM3dGCylFv() {
    // NONMATCHING
}

/* 804DACB0-804DACF8 000850 0048+00 1/0 0/0 0/0 .text            __dt__8cM3dGAabFv */
// cM3dGAab::~cM3dGAab() {
extern "C" void __dt__8cM3dGAabFv() {
    // NONMATCHING
}

/* 804DACF8-804DAD68 000898 0070+00 5/4 0/0 0/0 .text            __dt__13dBgS_LinkAcchFv */
// dBgS_LinkAcch::~dBgS_LinkAcch() {
extern "C" void __dt__13dBgS_LinkAcchFv() {
    // NONMATCHING
}

/* 804DAD68-804DADBC 000908 0054+00 1/1 0/0 0/0 .text            __ct__13dBgS_LinkAcchFv */
// dBgS_LinkAcch::dBgS_LinkAcch() {
extern "C" void __ct__13dBgS_LinkAcchFv() {
    // NONMATCHING
}

/* 804DADBC-804DAE2C 00095C 0070+00 3/2 0/0 0/0 .text            __dt__12dBgS_AcchCirFv */
// dBgS_AcchCir::~dBgS_AcchCir() {
extern "C" void __dt__12dBgS_AcchCirFv() {
    // NONMATCHING
}

/* 804DAE2C-804DAE88 0009CC 005C+00 1/0 0/0 0/0 .text            __dt__10dCcD_GSttsFv */
// dCcD_GStts::~dCcD_GStts() {
extern "C" void __dt__10dCcD_GSttsFv() {
    // NONMATCHING
}

/* 804DAE88-804DAEA8 000A28 0020+00 1/0 0/0 0/0 .text            daCanoe_Create__FP10fopAc_ac_c */
static void daCanoe_Create(fopAc_ac_c* param_0) {
    // NONMATCHING
}

/* 804DAEA8-804DAFE0 000A48 0138+00 1/1 0/0 0/0 .text            __dt__9daCanoe_cFv */
daCanoe_c::~daCanoe_c() {
    // NONMATCHING
}

/* 804DAFE0-804DB008 000B80 0028+00 1/0 0/0 0/0 .text            daCanoe_Delete__FP9daCanoe_c */
static void daCanoe_Delete(daCanoe_c* param_0) {
    // NONMATCHING
}

/* ############################################################################################## */
/* 804DD638-804DD63C 00005C 0004+00 1/1 0/0 0/0 .rodata          @4480 */
SECTION_RODATA static f32 const lit_4480 = -1000000000.0f;
COMPILER_STRIP_GATE(0x804DD638, &lit_4480);

/* 804DB008-804DB0B0 000BA8 00A8+00 1/1 0/0 0/0 .text            setRoomInfo__9daCanoe_cFv */
void daCanoe_c::setRoomInfo() {
    // NONMATCHING
}

/* ############################################################################################## */
/* 804DD63C-804DD640 000060 0004+00 0/3 0/0 0/0 .rodata          @4626 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_4626 = 5.0f;
COMPILER_STRIP_GATE(0x804DD63C, &lit_4626);
#pragma pop

/* 804DD640-804DD644 000064 0004+00 0/1 0/0 0/0 .rodata          @4627 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_4627 = -5.0f;
COMPILER_STRIP_GATE(0x804DD640, &lit_4627);
#pragma pop

/* 804DD644-804DD648 000068 0004+00 0/2 0/0 0/0 .rodata          @4628 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_4628 = 1.0f / 10.0f;
COMPILER_STRIP_GATE(0x804DD644, &lit_4628);
#pragma pop

/* 804DD648-804DD64C 00006C 0004+00 0/2 0/0 0/0 .rodata          @4629 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_4629 = 13.0f / 20.0f;
COMPILER_STRIP_GATE(0x804DD648, &lit_4629);
#pragma pop

/* 804DD64C-804DD650 000070 0004+00 0/6 0/0 0/0 .rodata          @4630 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_4630 = 1.0f;
COMPILER_STRIP_GATE(0x804DD64C, &lit_4630);
#pragma pop

/* 804DD650-804DD654 000074 0004+00 0/3 0/0 0/0 .rodata          @4631 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_4631 = 0.5f;
COMPILER_STRIP_GATE(0x804DD650, &lit_4631);
#pragma pop

/* 804DD654-804DD658 000078 0004+00 0/1 0/0 0/0 .rodata          @4632 */
#pragma push
#pragma force_active on
SECTION_RODATA static u32 const lit_4632 = 0x3EA0D97C;
COMPILER_STRIP_GATE(0x804DD654, &lit_4632);
#pragma pop

/* 804DD658-804DD65C 00007C 0004+00 0/1 0/0 0/0 .rodata          @4633 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_4633 = 1.0f / 20.0f;
COMPILER_STRIP_GATE(0x804DD658, &lit_4633);
#pragma pop

/* 804DD65C-804DD660 000080 0004+00 0/2 0/0 0/0 .rodata          @4634 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_4634 = 7.0f / 5.0f;
COMPILER_STRIP_GATE(0x804DD65C, &lit_4634);
#pragma pop

/* 804DD660-804DD664 000084 0004+00 0/4 0/0 0/0 .rodata          @4635 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_4635 = -1.0f;
COMPILER_STRIP_GATE(0x804DD660, &lit_4635);
#pragma pop

/* 804DD664-804DD668 000088 0004+00 0/6 0/0 0/0 .rodata          @4636 */
#pragma push
#pragma force_active on
SECTION_RODATA static u8 const lit_4636[4] = {
    0x00,
    0x00,
    0x00,
    0x00,
};
COMPILER_STRIP_GATE(0x804DD664, &lit_4636);
#pragma pop

/* 804DD668-804DD66C 00008C 0004+00 0/1 0/0 0/0 .rodata          @4637 */
#pragma push
#pragma force_active on
SECTION_RODATA static u32 const lit_4637 = 0x38D1B717;
COMPILER_STRIP_GATE(0x804DD668, &lit_4637);
#pragma pop

/* 804DD66C-804DD670 000090 0004+00 0/1 0/0 0/0 .rodata          @4638 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_4638 = -0.5f;
COMPILER_STRIP_GATE(0x804DD66C, &lit_4638);
#pragma pop

/* 804DD670-804DD674 000094 0004+00 0/2 0/0 0/0 .rodata          @4639 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_4639 = 3.0f;
COMPILER_STRIP_GATE(0x804DD670, &lit_4639);
#pragma pop

/* 804DD674-804DD678 000098 0004+00 0/1 0/0 0/0 .rodata          @4640 */
#pragma push
#pragma force_active on
SECTION_RODATA static u32 const lit_4640 = 0x3C75C28F;
COMPILER_STRIP_GATE(0x804DD674, &lit_4640);
#pragma pop

/* 804DD678-804DD67C 00009C 0004+00 0/1 0/0 0/0 .rodata          @4641 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_4641 = 97.0f / 100.0f;
COMPILER_STRIP_GATE(0x804DD678, &lit_4641);
#pragma pop

/* 804DD67C-804DD680 0000A0 0004+00 0/1 0/0 0/0 .rodata          @4642 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_4642 = 35.0f;
COMPILER_STRIP_GATE(0x804DD67C, &lit_4642);
#pragma pop

/* 804DB0B0-804DB3F4 000C50 0344+00 2/2 0/0 0/0 .text            setMatrix__9daCanoe_cFv */
void daCanoe_c::setMatrix() {
    // NONMATCHING
}

/* ############################################################################################## */
/* 804DD680-804DD684 0000A4 0004+00 1/2 0/0 0/0 .rodata          @4683 */
SECTION_RODATA static f32 const lit_4683 = 30.0f;
COMPILER_STRIP_GATE(0x804DD680, &lit_4683);

/* 804DB3F4-804DB578 000F94 0184+00 1/1 0/0 0/0 .text            setCollision__9daCanoe_cFv */
void daCanoe_c::setCollision() {
    // NONMATCHING
}

/* ############################################################################################## */
/* 804DD684-804DD68C 0000A8 0008+00 0/3 0/0 0/0 .rodata          @4738 */
#pragma push
#pragma force_active on
SECTION_RODATA static u8 const lit_4738[8] = {
    0x43, 0x30, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00,
};
COMPILER_STRIP_GATE(0x804DD684, &lit_4738);
#pragma pop

/* 804DB578-804DB754 001118 01DC+00 1/1 0/0 0/0 .text            posMove__9daCanoe_cFv */
void daCanoe_c::posMove() {
    // NONMATCHING
}

/* 804DB754-804DB7AC 0012F4 0058+00 2/2 0/0 0/0 .text checkGomikabe__9daCanoe_cFR13cBgS_PolyInfo
 */
void daCanoe_c::checkGomikabe(cBgS_PolyInfo& param_0) {
    // NONMATCHING
}

/* 804DB7AC-804DB828 00134C 007C+00 3/3 0/0 0/0 .text            setFrontBackPos__9daCanoe_cFv */
void daCanoe_c::setFrontBackPos() {
    // NONMATCHING
}

/* ############################################################################################## */
/* 804DD68C-804DD694 0000B0 0008+00 0/1 0/0 0/0 .rodata          @5087 */
#pragma push
#pragma force_active on
SECTION_RODATA static u8 const lit_5087[8] = {
    0x3F, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
COMPILER_STRIP_GATE(0x804DD68C, &lit_5087);
#pragma pop

/* 804DD694-804DD69C 0000B8 0008+00 0/1 0/0 0/0 .rodata          @5088 */
#pragma push
#pragma force_active on
SECTION_RODATA static u8 const lit_5088[8] = {
    0x40, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
COMPILER_STRIP_GATE(0x804DD694, &lit_5088);
#pragma pop

/* 804DD69C-804DD6A4 0000C0 0008+00 0/1 0/0 0/0 .rodata          @5089 */
#pragma push
#pragma force_active on
SECTION_RODATA static u8 const lit_5089[8] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
COMPILER_STRIP_GATE(0x804DD69C, &lit_5089);
#pragma pop

/* 804DD6A4-804DD6A8 0000C8 0004+00 0/1 0/0 0/0 .rodata          @5090 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_5090 = -50.0f;
COMPILER_STRIP_GATE(0x804DD6A4, &lit_5090);
#pragma pop

/* 804DD6A8-804DD6AC 0000CC 0004+00 0/2 0/0 0/0 .rodata          @5091 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_5091 = 400.0f;
COMPILER_STRIP_GATE(0x804DD6A8, &lit_5091);
#pragma pop

/* 804DD6AC-804DD6B0 0000D0 0004+00 0/1 0/0 0/0 .rodata          @5092 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_5092 = 3.0f / 5.0f;
COMPILER_STRIP_GATE(0x804DD6AC, &lit_5092);
#pragma pop

/* 804DB828-804DC2E8 0013C8 0AC0+00 1/1 0/0 0/0 .text            frontBackBgCheck__9daCanoe_cFv */
void daCanoe_c::frontBackBgCheck() {
    // NONMATCHING
}

/* 804DC2E8-804DC330 001E88 0048+00 1/0 0/0 0/0 .text            __dt__8cM3dGPlaFv */
// cM3dGPla::~cM3dGPla() {
extern "C" void __dt__8cM3dGPlaFv() {
    // NONMATCHING
}

/* ############################################################################################## */
/* 804DD6B0-804DD6B4 0000D4 0004+00 0/1 0/0 0/0 .rodata          @5172 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_5172 = 7.0f / 10.0f;
COMPILER_STRIP_GATE(0x804DD6B0, &lit_5172);
#pragma pop

/* 804DD6B4-804DD6B8 0000D8 0004+00 0/1 0/0 0/0 .rodata          @5173 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_5173 = 3.0f / 10.0f;
COMPILER_STRIP_GATE(0x804DD6B4, &lit_5173);
#pragma pop

/* 804DD7F8-804DD7FC 000008 0001+03 2/2 0/0 0/0 .bss             @1109 */
static u8 lit_1109[1 + 3 /* padding */];

/* 804DD7FC-804DD800 00000C 0001+03 0/0 0/0 0/0 .bss             @1107 */
#pragma push
#pragma force_active on
static u8 lit_1107[1 + 3 /* padding */];
#pragma pop

/* 804DD800-804DD804 000010 0001+03 0/0 0/0 0/0 .bss             @1105 */
#pragma push
#pragma force_active on
static u8 lit_1105[1 + 3 /* padding */];
#pragma pop

/* 804DD804-804DD808 000014 0001+03 0/0 0/0 0/0 .bss             @1104 */
#pragma push
#pragma force_active on
static u8 lit_1104[1 + 3 /* padding */];
#pragma pop

/* 804DD808-804DD80C 000018 0001+03 0/0 0/0 0/0 .bss             @1099 */
#pragma push
#pragma force_active on
static u8 lit_1099[1 + 3 /* padding */];
#pragma pop

/* 804DD80C-804DD810 00001C 0001+03 0/0 0/0 0/0 .bss             @1097 */
#pragma push
#pragma force_active on
static u8 lit_1097[1 + 3 /* padding */];
#pragma pop

/* 804DD810-804DD814 000020 0001+03 0/0 0/0 0/0 .bss             @1095 */
#pragma push
#pragma force_active on
static u8 lit_1095[1 + 3 /* padding */];
#pragma pop

/* 804DD814-804DD818 000024 0001+03 0/0 0/0 0/0 .bss             @1094 */
#pragma push
#pragma force_active on
static u8 lit_1094[1 + 3 /* padding */];
#pragma pop

/* 804DD818-804DD81C 000028 0001+03 0/0 0/0 0/0 .bss             @1057 */
#pragma push
#pragma force_active on
static u8 lit_1057[1 + 3 /* padding */];
#pragma pop

/* 804DD81C-804DD820 00002C 0001+03 0/0 0/0 0/0 .bss             @1055 */
#pragma push
#pragma force_active on
static u8 lit_1055[1 + 3 /* padding */];
#pragma pop

/* 804DD820-804DD824 000030 0001+03 0/0 0/0 0/0 .bss             @1053 */
#pragma push
#pragma force_active on
static u8 lit_1053[1 + 3 /* padding */];
#pragma pop

/* 804DD824-804DD828 000034 0001+03 0/0 0/0 0/0 .bss             @1052 */
#pragma push
#pragma force_active on
static u8 lit_1052[1 + 3 /* padding */];
#pragma pop

/* 804DD828-804DD82C 000038 0001+03 0/0 0/0 0/0 .bss             @1014 */
#pragma push
#pragma force_active on
static u8 lit_1014[1 + 3 /* padding */];
#pragma pop

/* 804DD82C-804DD830 00003C 0001+03 0/0 0/0 0/0 .bss             @1012 */
#pragma push
#pragma force_active on
static u8 lit_1012[1 + 3 /* padding */];
#pragma pop

/* 804DD830-804DD834 000040 0001+03 0/0 0/0 0/0 .bss             @1010 */
#pragma push
#pragma force_active on
static u8 lit_1010[1 + 3 /* padding */];
#pragma pop

/* 804DD834-804DD838 000044 0001+03 0/0 0/0 0/0 .bss             @1009 */
#pragma push
#pragma force_active on
static u8 lit_1009[1 + 3 /* padding */];
#pragma pop

/* 804DD838-804DD848 000048 000C+04 0/1 0/0 0/0 .bss             @5103 */
#pragma push
#pragma force_active on
static u8 lit_5103[12 + 4 /* padding */];
#pragma pop

/* 804DD848-804DD854 000058 000C+00 0/1 0/0 0/0 .bss             paddleRippleScale$5102 */
#pragma push
#pragma force_active on
static u8 paddleRippleScale[12];
#pragma pop

/* 804DC330-804DC554 001ED0 0224+00 1/1 0/0 0/0 .text            setPaddleEffect__9daCanoe_cFv */
void daCanoe_c::setPaddleEffect() {
    // NONMATCHING
}

/* ############################################################################################## */
/* 804DD6B8-804DD6BC 0000DC 0004+00 0/1 0/0 0/0 .rodata          effName$5177 */
#pragma push
#pragma force_active on
SECTION_RODATA static u8 const effName[4] = {
    0x8A,
    0x5A,
    0x8A,
    0x5B,
};
COMPILER_STRIP_GATE(0x804DD6B8, &effName);
#pragma pop

/* 804DD6BC-804DD6C0 0000E0 0004+00 0/1 0/0 0/0 .rodata          @5280 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_5280 = 25.0f;
COMPILER_STRIP_GATE(0x804DD6BC, &lit_5280);
#pragma pop

/* 804DC554-804DC7B4 0020F4 0260+00 1/1 0/0 0/0 .text            setCanoeSliderEffect__9daCanoe_cFv
 */
void daCanoe_c::setCanoeSliderEffect() {
    // NONMATCHING
}

/* ############################################################################################## */
/* 804DD6C0-804DD6C4 0000E4 0004+00 0/1 0/0 0/0 .rodata          @5504 */
#pragma push
#pragma force_active on
SECTION_RODATA static u32 const lit_5504 = 0x3E567750;
COMPILER_STRIP_GATE(0x804DD6C0, &lit_5504);
#pragma pop

/* 804DD6C4-804DD6C8 0000E8 0004+00 0/1 0/0 0/0 .rodata          @5505 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_5505 = 6.0f;
COMPILER_STRIP_GATE(0x804DD6C4, &lit_5505);
#pragma pop

/* 804DD6C8-804DD6CC 0000EC 0004+00 0/1 0/0 0/0 .rodata          @5506 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_5506 = 1.0f / 100.0f;
COMPILER_STRIP_GATE(0x804DD6C8, &lit_5506);
#pragma pop

/* 804DD6CC-804DD6D0 0000F0 0004+00 0/1 0/0 0/0 .rodata          @5507 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_5507 = 2.0f;
COMPILER_STRIP_GATE(0x804DD6CC, &lit_5507);
#pragma pop

/* 804DD6D0-804DD6D4 0000F4 0004+00 0/1 0/0 0/0 .rodata          @5508 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_5508 = 127.0f;
COMPILER_STRIP_GATE(0x804DD6D0, &lit_5508);
#pragma pop

/* 804DD854-804DD864 000064 000C+04 0/1 0/0 0/0 .bss             @5356 */
#pragma push
#pragma force_active on
static u8 lit_5356[12 + 4 /* padding */];
#pragma pop

/* 804DD864-804DD870 000074 000C+00 0/1 0/0 0/0 .bss             bodyRippleScale$5355 */
#pragma push
#pragma force_active on
static u8 bodyRippleScale[12];
#pragma pop

/* 804DC7B4-804DD33C 002354 0B88+00 1/1 0/0 0/0 .text            execute__9daCanoe_cFv */
void daCanoe_c::execute() {
    // NONMATCHING
}

/* 804DD33C-804DD35C 002EDC 0020+00 1/0 0/0 0/0 .text            daCanoe_Execute__FP9daCanoe_c */
static void daCanoe_Execute(daCanoe_c* param_0) {
    // NONMATCHING
}

/* ############################################################################################## */
/* 804DD6D4-804DD6D8 0000F8 0004+00 0/1 0/0 0/0 .rodata          @5573 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_5573 = 23.0f;
COMPILER_STRIP_GATE(0x804DD6D4, &lit_5573);
#pragma pop

/* 804DD6D8-804DD6DC 0000FC 0004+00 0/1 0/0 0/0 .rodata          @5574 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_5574 = 175.0f;
COMPILER_STRIP_GATE(0x804DD6D8, &lit_5574);
#pragma pop

/* 804DD6DC-804DD6E0 000100 0004+00 0/1 0/0 0/0 .rodata          @5575 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_5575 = 20.0f;
COMPILER_STRIP_GATE(0x804DD6DC, &lit_5575);
#pragma pop

/* 804DD6E0-804DD6E4 000104 0004+00 0/1 0/0 0/0 .rodata          @5576 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_5576 = 29.0f;
COMPILER_STRIP_GATE(0x804DD6E0, &lit_5576);
#pragma pop

/* 804DD6E4-804DD6E8 000108 0004+00 0/1 0/0 0/0 .rodata          @5577 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_5577 = 800.0f;
COMPILER_STRIP_GATE(0x804DD6E4, &lit_5577);
#pragma pop

/* 804DD35C-804DD554 002EFC 01F8+00 1/1 0/0 0/0 .text            draw__9daCanoe_cFv */
void daCanoe_c::draw() {
    // NONMATCHING
}

/* 804DD554-804DD574 0030F4 0020+00 1/0 0/0 0/0 .text            daCanoe_Draw__FP9daCanoe_c */
static void daCanoe_Draw(daCanoe_c* param_0) {
    // NONMATCHING
}

/* 804DD574-804DD5BC 003114 0048+00 1/0 0/0 0/0 .text            __dt__10cCcD_GSttsFv */
// cCcD_GStts::~cCcD_GStts() {
extern "C" void __dt__10cCcD_GSttsFv() {
    // NONMATCHING
}

/* 804DD5BC-804DD5C4 00315C 0008+00 1/0 0/0 0/0 .text            @36@__dt__13dBgS_LinkAcchFv */
static void func_804DD5BC() {
    // NONMATCHING
}

/* 804DD5C4-804DD5CC 003164 0008+00 1/0 0/0 0/0 .text            @20@__dt__13dBgS_LinkAcchFv */
static void func_804DD5C4() {
    // NONMATCHING
}

/* ############################################################################################## */
/* 804DD870-804DD874 000080 0004+00 0/0 0/0 0/0 .bss
 * sInstance__40JASGlobalInstance<19JASDefaultBankTable>        */
#pragma push
#pragma force_active on
static u8 data_804DD870[4];
#pragma pop

/* 804DD874-804DD878 000084 0004+00 0/0 0/0 0/0 .bss
 * sInstance__35JASGlobalInstance<14JASAudioThread>             */
#pragma push
#pragma force_active on
static u8 data_804DD874[4];
#pragma pop

/* 804DD878-804DD87C 000088 0004+00 0/0 0/0 0/0 .bss sInstance__27JASGlobalInstance<7Z2SeMgr> */
#pragma push
#pragma force_active on
static u8 data_804DD878[4];
#pragma pop

/* 804DD87C-804DD880 00008C 0004+00 0/0 0/0 0/0 .bss sInstance__28JASGlobalInstance<8Z2SeqMgr> */
#pragma push
#pragma force_active on
static u8 data_804DD87C[4];
#pragma pop

/* 804DD880-804DD884 000090 0004+00 0/0 0/0 0/0 .bss sInstance__31JASGlobalInstance<10Z2SceneMgr>
 */
#pragma push
#pragma force_active on
static u8 data_804DD880[4];
#pragma pop

/* 804DD884-804DD888 000094 0004+00 0/0 0/0 0/0 .bss sInstance__32JASGlobalInstance<11Z2StatusMgr>
 */
#pragma push
#pragma force_active on
static u8 data_804DD884[4];
#pragma pop

/* 804DD888-804DD88C 000098 0004+00 0/0 0/0 0/0 .bss sInstance__31JASGlobalInstance<10Z2DebugSys>
 */
#pragma push
#pragma force_active on
static u8 data_804DD888[4];
#pragma pop

/* 804DD88C-804DD890 00009C 0004+00 0/0 0/0 0/0 .bss
 * sInstance__36JASGlobalInstance<15JAISoundStarter>            */
#pragma push
#pragma force_active on
static u8 data_804DD88C[4];
#pragma pop

/* 804DD890-804DD894 0000A0 0004+00 0/0 0/0 0/0 .bss
 * sInstance__35JASGlobalInstance<14Z2SoundStarter>             */
#pragma push
#pragma force_active on
static u8 data_804DD890[4];
#pragma pop

/* 804DD894-804DD898 0000A4 0004+00 0/0 0/0 0/0 .bss
 * sInstance__33JASGlobalInstance<12Z2SpeechMgr2>               */
#pragma push
#pragma force_active on
static u8 data_804DD894[4];
#pragma pop

/* 804DD898-804DD89C 0000A8 0004+00 0/0 0/0 0/0 .bss sInstance__28JASGlobalInstance<8JAISeMgr> */
#pragma push
#pragma force_active on
static u8 data_804DD898[4];
#pragma pop

/* 804DD89C-804DD8A0 0000AC 0004+00 0/0 0/0 0/0 .bss sInstance__29JASGlobalInstance<9JAISeqMgr> */
#pragma push
#pragma force_active on
static u8 data_804DD89C[4];
#pragma pop

/* 804DD8A0-804DD8A4 0000B0 0004+00 0/0 0/0 0/0 .bss
 * sInstance__33JASGlobalInstance<12JAIStreamMgr>               */
#pragma push
#pragma force_active on
static u8 data_804DD8A0[4];
#pragma pop

/* 804DD8A4-804DD8A8 0000B4 0004+00 0/0 0/0 0/0 .bss sInstance__31JASGlobalInstance<10Z2SoundMgr>
 */
#pragma push
#pragma force_active on
static u8 data_804DD8A4[4];
#pragma pop

/* 804DD8A8-804DD8AC 0000B8 0004+00 0/0 0/0 0/0 .bss
 * sInstance__33JASGlobalInstance<12JAISoundInfo>               */
#pragma push
#pragma force_active on
static u8 data_804DD8A8[4];
#pragma pop

/* 804DD8AC-804DD8B0 0000BC 0004+00 0/0 0/0 0/0 .bss
 * sInstance__34JASGlobalInstance<13JAUSoundTable>              */
#pragma push
#pragma force_active on
static u8 data_804DD8AC[4];
#pragma pop

/* 804DD8B0-804DD8B4 0000C0 0004+00 0/0 0/0 0/0 .bss
 * sInstance__38JASGlobalInstance<17JAUSoundNameTable>          */
#pragma push
#pragma force_active on
static u8 data_804DD8B0[4];
#pragma pop

/* 804DD8B4-804DD8B8 0000C4 0004+00 0/0 0/0 0/0 .bss
 * sInstance__33JASGlobalInstance<12JAUSoundInfo>               */
#pragma push
#pragma force_active on
static u8 data_804DD8B4[4];
#pragma pop

/* 804DD8B8-804DD8BC 0000C8 0004+00 0/0 0/0 0/0 .bss sInstance__32JASGlobalInstance<11Z2SoundInfo>
 */
#pragma push
#pragma force_active on
static u8 data_804DD8B8[4];
#pragma pop

/* 804DD8BC-804DD8C0 0000CC 0004+00 0/0 0/0 0/0 .bss
 * sInstance__34JASGlobalInstance<13Z2SoundObjMgr>              */
#pragma push
#pragma force_active on
static u8 data_804DD8BC[4];
#pragma pop

/* 804DD8C0-804DD8C4 0000D0 0004+00 0/0 0/0 0/0 .bss sInstance__31JASGlobalInstance<10Z2Audience>
 */
#pragma push
#pragma force_active on
static u8 data_804DD8C0[4];
#pragma pop

/* 804DD8C4-804DD8C8 0000D4 0004+00 0/0 0/0 0/0 .bss sInstance__32JASGlobalInstance<11Z2FxLineMgr>
 */
#pragma push
#pragma force_active on
static u8 data_804DD8C4[4];
#pragma pop

/* 804DD8C8-804DD8CC 0000D8 0004+00 0/0 0/0 0/0 .bss sInstance__31JASGlobalInstance<10Z2EnvSeMgr>
 */
#pragma push
#pragma force_active on
static u8 data_804DD8C8[4];
#pragma pop

/* 804DD8CC-804DD8D0 0000DC 0004+00 0/0 0/0 0/0 .bss sInstance__32JASGlobalInstance<11Z2SpeechMgr>
 */
#pragma push
#pragma force_active on
static u8 data_804DD8CC[4];
#pragma pop

/* 804DD8D0-804DD8D4 0000E0 0004+00 0/0 0/0 0/0 .bss
 * sInstance__34JASGlobalInstance<13Z2WolfHowlMgr>              */
#pragma push
#pragma force_active on
static u8 data_804DD8D0[4];
#pragma pop

/* 804DD8D4-804DD8D8 0000E4 0004+00 0/0 0/0 0/0 .bss
 * sInstance__35JASGlobalInstance<14JAUSectionHeap>             */
#pragma push
#pragma force_active on
static u8 data_804DD8D4[4];
#pragma pop

/* 804DD6E8-804DD6E8 00010C 0000+00 0/0 0/0 0/0 .rodata          @stringBase0 */
