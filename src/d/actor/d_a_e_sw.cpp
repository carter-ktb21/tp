/**
 * @file d_a_e_sw.cpp
 * 
*/

#include "d/actor/d_a_e_sw.h"
#include "dol2asm.h"
UNK_REL_DATA;
#include "f_op/f_op_actor_enemy.h"


//
// Forward References:
//

extern "C" void __ct__12daE_SW_HIO_cFv();
extern "C" void bckSet__8daE_SW_cFifUcf();
extern "C" void draw__8daE_SW_cFv();
extern "C" static void daE_SW_Draw__FP8daE_SW_c();
extern "C" void setBeforeJumpEffect__8daE_SW_cFv();
extern "C" void setJumpEffect__8daE_SW_cFv();
extern "C" void setSmokeEffect__8daE_SW_cFv();
extern "C" void setDiveEffect__8daE_SW_cFv();
extern "C" void setHideEffect__8daE_SW_cFv();
extern "C" void setActionMode__8daE_SW_cFss();
extern "C" static void s_b_sub__FPvPv();
extern "C" void search_bomb__8daE_SW_cFv();
extern "C" void bomb_check__8daE_SW_cFv();
extern "C" void setModeBack__8daE_SW_cFv();
extern "C" void checkFall__8daE_SW_cFv();
extern "C" void checkBeforeWall__8daE_SW_cFv();
extern "C" void executeWait__8daE_SW_cFv();
extern "C" void checkRunChase__8daE_SW_cFv();
extern "C" void executeChaseSlow__8daE_SW_cFv();
extern "C" void executeChaseFast__8daE_SW_cFv();
extern "C" void executeBomb__8daE_SW_cFv();
extern "C" void executeAttack__8daE_SW_cFv();
extern "C" void executeHook__8daE_SW_cFv();
extern "C" void executeMoveOut__8daE_SW_cFv();
extern "C" void executeChance__8daE_SW_cFv();
extern "C" void executeDive__8daE_SW_cFv();
extern "C" void executeDamage__8daE_SW_cFv();
extern "C" void executeDie__8daE_SW_cFv();
extern "C" static void s_child_sub__FPvPv();
extern "C" void executeMaster__8daE_SW_cFv();
extern "C" void checkSuddenAttack__8daE_SW_cFi();
extern "C" void executeSuddenAttack__8daE_SW_cFv();
extern "C" void executeFall__8daE_SW_cFv();
extern "C" void action__8daE_SW_cFv();
extern "C" void mtx_set__8daE_SW_cFv();
extern "C" void cc_set__8daE_SW_cFv();
extern "C" void damage_check__8daE_SW_cFv();
extern "C" void checkGroundSand__8daE_SW_cFv();
extern "C" void execute__8daE_SW_cFv();
extern "C" static void daE_SW_Execute__FP8daE_SW_c();
extern "C" static bool daE_SW_IsDelete__FP8daE_SW_c();
extern "C" void _delete__8daE_SW_cFv();
extern "C" static void daE_SW_Delete__FP8daE_SW_c();
extern "C" void CreateHeap__8daE_SW_cFv();
extern "C" static void useHeapInit__FP10fopAc_ac_c();
extern "C" void create__8daE_SW_cFv();
extern "C" void __dt__8cM3dGSphFv();
extern "C" void __dt__8cM3dGAabFv();
extern "C" void __dt__10dCcD_GSttsFv();
extern "C" void __dt__12dBgS_ObjAcchFv();
extern "C" void __dt__12dBgS_AcchCirFv();
extern "C" static void daE_SW_Create__FP8daE_SW_c();
extern "C" void d_setAction__8daE_SW_cFM8daE_SW_cFPCvPv_v();
extern "C" void d_checkFall__8daE_SW_cFv();
extern "C" void d_damage_check__8daE_SW_cFv();
extern "C" void d_action__8daE_SW_cFv();
extern "C" void d_bomb_check__8daE_SW_cFv();
extern "C" void d_bm_chase__8daE_SW_cFv();
extern "C" void d_wait__8daE_SW_cFv();
extern "C" void d_chaseCheck__8daE_SW_cFv();
extern "C" void d_chase__8daE_SW_cFv();
extern "C" void d_attk__8daE_SW_cFv();
extern "C" void d_chance__8daE_SW_cFv();
extern "C" void d_chance2__8daE_SW_cFv();
extern "C" void d_dive__8daE_SW_cFv();
extern "C" void d_damage__8daE_SW_cFv();
extern "C" void d_die__8daE_SW_cFv();
extern "C" void d_hook__8daE_SW_cFv();
extern "C" void __dt__8cM3dGPlaFv();
extern "C" void d_fall__8daE_SW_cFv();
extern "C" void d_execute__8daE_SW_cFv();
extern "C" void __dt__10cCcD_GSttsFv();
extern "C" void __dt__12daE_SW_HIO_cFv();
extern "C" void __sinit_d_a_e_sw_cpp();
extern "C" static void func_807AF8F4();
extern "C" static void func_807AF8FC();
extern "C" extern char const* const d_a_e_sw__stringBase0;

//
// External References:
//

extern "C" void mDoMtx_YrotS__FPA4_fs();
extern "C" void transM__14mDoMtx_stack_cFfff();
extern "C" void scaleM__14mDoMtx_stack_cFfff();
extern "C" void ZXYrotM__14mDoMtx_stack_cFRC5csXyz();
extern "C" void
__ct__16mDoExt_McaMorfSOFP12J3DModelDataP25mDoExt_McaMorfCallBack1_cP25mDoExt_McaMorfCallBack2_cP15J3DAnmTransformifiiP10Z2CreatureUlUl();
extern "C" void setAnm__16mDoExt_McaMorfSOFP15J3DAnmTransformiffff();
extern "C" void play__16mDoExt_McaMorfSOFUlSc();
extern "C" void entryDL__16mDoExt_McaMorfSOFv();
extern "C" void modelCalc__16mDoExt_McaMorfSOFv();
extern "C" void __ct__10fopAc_ac_cFv();
extern "C" void fopAc_IsActor__FPv();
extern "C" void fopAcM_SearchByID__FUiPP10fopAc_ac_c();
extern "C" void fopAcM_delete__FP10fopAc_ac_c();
extern "C" void fopAcM_createChild__FsUiUlPC4cXyziPC5csXyzPC4cXyzScPFPv_i();
extern "C" void fopAcM_entrySolidHeap__FP10fopAc_ac_cPFP10fopAc_ac_c_iUl();
extern "C" void fopAcM_SetMin__FP10fopAc_ac_cfff();
extern "C" void fopAcM_SetMax__FP10fopAc_ac_cfff();
extern "C" void fopAcM_posMoveF__FP10fopAc_ac_cPC4cXyz();
extern "C" void fopAcM_searchActorAngleY__FPC10fopAc_ac_cPC10fopAc_ac_c();
extern "C" void fopAcM_searchActorDistance__FPC10fopAc_ac_cPC10fopAc_ac_c();
extern "C" void fopAcM_createDisappear__FPC10fopAc_ac_cPC4cXyzUcUcUc();
extern "C" void gndCheck__11fopAcM_gc_cFPC4cXyz();
extern "C" void fpcEx_Search__FPFPvPv_PvPv();
extern "C" void fpcM_IsCreating__FUi();
extern "C" void dComIfG_resLoad__FP30request_of_phase_process_classPCc();
extern "C" void dComIfG_resDelete__FP30request_of_phase_process_classPCc();
extern "C" void dComIfGp_getReverb__Fi();
extern "C" void
dComIfGd_setShadow__FUlScP8J3DModelP4cXyzffffR13cBgS_PolyInfoP12dKy_tevstr_csfP9_GXTexObj();
extern "C" void onSwitch__10dSv_info_cFii();
extern "C" void isSwitch__10dSv_info_cCFii();
extern "C" void getRes__14dRes_control_cFPCclP11dRes_info_ci();
extern "C" void
set__13dPa_control_cFUcUsPC4cXyzPC12dKy_tevstr_cPC5csXyzPC4cXyzUcP18dPa_levelEcallBackScPC8_GXColorPC8_GXColorPC4cXyzf();
extern "C" void
set__13dPa_control_cFUlUcUsPC4cXyzPC12dKy_tevstr_cPC5csXyzPC4cXyzUcP18dPa_levelEcallBackScPC8_GXColorPC8_GXColorPC4cXyzf();
extern "C" void LockonTarget__12dAttention_cFl();
extern "C" void LockonTruth__12dAttention_cFv();
extern "C" void LineCross__4cBgSFP11cBgS_LinChk();
extern "C" void GroundCross__4cBgSFP11cBgS_GndChk();
extern "C" void GetTriPla__4cBgSCFRC13cBgS_PolyInfoP8cM3dGPla();
extern "C" void GetPolyAtt0__4dBgSFRC13cBgS_PolyInfo();
extern "C" void GetGroundCode__4dBgSFRC13cBgS_PolyInfo();
extern "C" void __ct__12dBgS_AcchCirFv();
extern "C" void SetWall__12dBgS_AcchCirFff();
extern "C" void __dt__9dBgS_AcchFv();
extern "C" void __ct__9dBgS_AcchFv();
extern "C" void Set__9dBgS_AcchFP4cXyzP4cXyzP10fopAc_ac_ciP12dBgS_AcchCirP4cXyzP5csXyzP5csXyz();
extern "C" void CrrPos__9dBgS_AcchFR4dBgS();
extern "C" void __ct__11dBgS_GndChkFv();
extern "C" void __dt__11dBgS_GndChkFv();
extern "C" void __ct__11dBgS_LinChkFv();
extern "C" void __dt__11dBgS_LinChkFv();
extern "C" void Set__11dBgS_LinChkFPC4cXyzPC4cXyzPC10fopAc_ac_c();
extern "C" void SetObj__16dBgS_PolyPassChkFv();
extern "C" void __ct__10dCcD_GSttsFv();
extern "C" void Move__10dCcD_GSttsFv();
extern "C" void Init__9dCcD_SttsFiiP10fopAc_ac_c();
extern "C" void __ct__12dCcD_GObjInfFv();
extern "C" void ChkTgHit__12dCcD_GObjInfFv();
extern "C" void GetTgHitObj__12dCcD_GObjInfFv();
extern "C" void Set__8dCcD_SphFRC11dCcD_SrcSph();
extern "C" void cc_at_check__FP10fopAc_ac_cP11dCcU_AtInfo();
extern "C" void settingTevStruct__18dScnKy_env_light_cFiP4cXyzP12dKy_tevstr_c();
extern "C" void setLightTevColorType_MAJI__18dScnKy_env_light_cFP12J3DModelDataP12dKy_tevstr_c();
extern "C" void dKy_darkworld_check__Fv();
extern "C" void Set__4cCcSFP8cCcD_Obj();
extern "C" void __mi__4cXyzCFRC3Vec();
extern "C" void __ct__5csXyzFsss();
extern "C" void cM_atan2s__Fff();
extern "C" void cM_rnd__Fv();
extern "C" void cM_rndF__Ff();
extern "C" void cM_rndFX__Ff();
extern "C" void SetPos__11cBgS_GndChkFPC4cXyz();
extern "C" void __dt__13cBgS_PolyInfoFv();
extern "C" void __dt__8cM3dGCirFv();
extern "C" void SetC__8cM3dGSphFRC4cXyz();
extern "C" void SetR__8cM3dGSphFf();
extern "C" void cLib_addCalc2__FPffff();
extern "C" void cLib_addCalcAngleS__FPsssss();
extern "C" void cLib_addCalcAngleS2__FPssss();
extern "C" void cLib_chaseF__FPfff();
extern "C" void cLib_chaseAngleS__FPsss();
extern "C" void cLib_targetAngleY__FPC3VecPC3Vec();
extern "C" void cLib_offsetPos__FP4cXyzPC4cXyzsPC4cXyz();
extern "C" void cLib_distanceAngleS__Fss();
extern "C" void __ct__15Z2CreatureEnemyFv();
extern "C" void init__15Z2CreatureEnemyFP3VecP3VecUcUc();
extern "C" void setLinkSearch__15Z2CreatureEnemyFb();
extern "C" void setEnemyName__15Z2CreatureEnemyFPCc();
extern "C" void* __nw__FUl();
extern "C" void __dl__FPv();
extern "C" void checkPass__12J3DFrameCtrlFf();
extern "C" void __construct_array();
extern "C" void __ptmf_test();
extern "C" void __ptmf_cmpr();
extern "C" void __ptmf_scall();
extern "C" void _savegpr_19();
extern "C" void _savegpr_26();
extern "C" void _savegpr_27();
extern "C" void _savegpr_28();
extern "C" void _savegpr_29();
extern "C" void _restgpr_19();
extern "C" void _restgpr_26();
extern "C" void _restgpr_27();
extern "C" void _restgpr_28();
extern "C" void _restgpr_29();
extern "C" extern void* __vt__8dCcD_Sph[36];
extern "C" extern void* __vt__9dCcD_Stts[11];
extern "C" extern void* __vt__12cCcD_SphAttr[25];
extern "C" extern void* __vt__14cCcD_ShapeAttr[22];
extern "C" extern void* __vt__9cCcD_Stts[8];
extern "C" u8 now__14mDoMtx_stack_c[48];
extern "C" u8 mGndCheck__11fopAcM_gc_c[84];
extern "C" u8 mSimpleTexObj__21dDlst_shadowControl_c[32];
extern "C" u8 sincosTable___5JMath[65536];
extern "C" f32 mGroundY__11fopAcM_gc_c;
extern "C" u8 m_midnaActor__9daPy_py_c[4];
extern "C" void __register_global_object();

//
// Declarations:
//

/* ############################################################################################## */
/* 807AFD58-807AFD5C 00002C 0004+00 0/4 0/0 0/0 .rodata          @3930 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_3930 = 1500.0f;
COMPILER_STRIP_GATE(0x807AFD58, &lit_3930);
#pragma pop

/* 807AFD5C-807AFD60 000030 0004+00 0/2 0/0 0/0 .rodata          @3931 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_3931 = 800.0f;
COMPILER_STRIP_GATE(0x807AFD5C, &lit_3931);
#pragma pop

/* 807AFD60-807AFD64 000034 0004+00 0/2 0/0 0/0 .rodata          @3932 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_3932 = 400.0f;
COMPILER_STRIP_GATE(0x807AFD60, &lit_3932);
#pragma pop

/* 807AFD64-807AFD68 000038 0004+00 0/9 0/0 0/0 .rodata          @3933 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_3933 = 1000.0f;
COMPILER_STRIP_GATE(0x807AFD64, &lit_3933);
#pragma pop

/* 807AFEB4-807AFEF4 000038 0040+00 1/1 0/0 0/0 .data cc_sph_src__22@unnamed@d_a_e_sw_cpp@ */
SECTION_DATA static u8 data_807AFEB4[64] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1D,
    0xD8, 0xFB, 0xFD, 0xFF, 0x00, 0x00, 0x00, 0x43, 0x00, 0x00, 0x00, 0x75, 0x0C, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x42, 0x20, 0x00, 0x00,
};

/* 807AFEF4-807AFEFC 000078 0008+00 1/1 0/0 0/0 .data            l_SW_DIVE_EFFECT_ID$4064 */
SECTION_DATA static u8 l_SW_DIVE_EFFECT_ID[8] = {
    0x83, 0x6F, 0x83, 0x70, 0x83, 0x71, 0x83, 0x72,
};

/* 807AFEFC-807AFF04 000080 0006+02 1/1 0/0 0/0 .data            l_SW_HIDE_EFFECT_ID$4083 */
SECTION_DATA static u8 l_SW_HIDE_EFFECT_ID[6 + 2 /* padding */] = {
    0x83,
    0x7C,
    0x83,
    0x7D,
    0x83,
    0x7E,
    /* padding */
    0x00,
    0x00,
};

/* 807AFF04-807AFF30 -00001 002C+00 1/1 0/0 0/0 .data            @5270 */
SECTION_DATA static void* lit_5270[11] = {
    (void*)(((char*)executeChance__8daE_SW_cFv) + 0x54),
    (void*)(((char*)executeChance__8daE_SW_cFv) + 0xB4),
    (void*)(((char*)executeChance__8daE_SW_cFv) + 0xF4),
    (void*)(((char*)executeChance__8daE_SW_cFv) + 0x318),
    (void*)(((char*)executeChance__8daE_SW_cFv) + 0x318),
    (void*)(((char*)executeChance__8daE_SW_cFv) + 0x2B8),
    (void*)(((char*)executeChance__8daE_SW_cFv) + 0x304),
    (void*)(((char*)executeChance__8daE_SW_cFv) + 0x318),
    (void*)(((char*)executeChance__8daE_SW_cFv) + 0x318),
    (void*)(((char*)executeChance__8daE_SW_cFv) + 0x318),
    (void*)(((char*)executeChance__8daE_SW_cFv) + 0x4C),
};

/* 807AFF30-807AFF68 -00001 0038+00 1/1 0/0 0/0 .data            @5661 */
SECTION_DATA static void* lit_5661[14] = {
    (void*)(((char*)action__8daE_SW_cFv) + 0xC0),  (void*)(((char*)action__8daE_SW_cFv) + 0xCC),
    (void*)(((char*)action__8daE_SW_cFv) + 0xDC),  (void*)(((char*)action__8daE_SW_cFv) + 0xEC),
    (void*)(((char*)action__8daE_SW_cFv) + 0xFC),  (void*)(((char*)action__8daE_SW_cFv) + 0x108),
    (void*)(((char*)action__8daE_SW_cFv) + 0x114), (void*)(((char*)action__8daE_SW_cFv) + 0x120),
    (void*)(((char*)action__8daE_SW_cFv) + 0x130), (void*)(((char*)action__8daE_SW_cFv) + 0x13C),
    (void*)(((char*)action__8daE_SW_cFv) + 0x148), (void*)(((char*)action__8daE_SW_cFv) + 0x154),
    (void*)(((char*)action__8daE_SW_cFv) + 0x160), (void*)(((char*)action__8daE_SW_cFv) + 0x16C),
};

/* 807AFF68-807AFF74 -00001 000C+00 1/1 0/0 0/0 .data            @5983 */
SECTION_DATA static void* lit_5983[3] = {
    (void*)NULL,
    (void*)0xFFFFFFFF,
    (void*)d_wait__8daE_SW_cFv,
};

/* 807AFF74-807AFF94 -00001 0020+00 1/0 0/0 0/0 .data            l_daE_SW_Method */
static actor_method_class l_daE_SW_Method = {
    (process_method_func)daE_SW_Create__FP8daE_SW_c,
    (process_method_func)daE_SW_Delete__FP8daE_SW_c,
    (process_method_func)daE_SW_Execute__FP8daE_SW_c,
    (process_method_func)daE_SW_IsDelete__FP8daE_SW_c,
    (process_method_func)daE_SW_Draw__FP8daE_SW_c,
};

/* 807AFF94-807AFFC4 -00001 0030+00 0/0 0/0 1/0 .data            g_profile_E_SW */
extern actor_process_profile_definition g_profile_E_SW = {
  fpcLy_CURRENT_e,        // mLayerID
  7,                      // mListID
  fpcPi_CURRENT_e,        // mListPrio
  PROC_E_SW,              // mProcName
  &g_fpcLf_Method.base,  // sub_method
  sizeof(daE_SW_c),       // mSize
  0,                      // mSizeOther
  0,                      // mParameters
  &g_fopAc_Method.base,   // sub_method
  191,                    // mPriority
  &l_daE_SW_Method,       // sub_method
  0x000C0100,             // mStatus
  fopAc_ENEMY_e,          // mActorType
  fopAc_CULLBOX_CUSTOM_e, // cullType
};

/* 807AFFC4-807AFFD0 -00001 000C+00 0/1 0/0 0/0 .data            @6217 */
#pragma push
#pragma force_active on
SECTION_DATA static void* lit_6217[3] = {
    (void*)NULL,
    (void*)0xFFFFFFFF,
    (void*)d_hook__8daE_SW_cFv,
};
#pragma pop

/* 807AFFD0-807AFFDC -00001 000C+00 0/1 0/0 0/0 .data            @6219 */
#pragma push
#pragma force_active on
SECTION_DATA static void* lit_6219[3] = {
    (void*)NULL,
    (void*)0xFFFFFFFF,
    (void*)d_fall__8daE_SW_cFv,
};
#pragma pop

/* 807AFFDC-807AFFE8 -00001 000C+00 0/1 0/0 0/0 .data            @6221 */
#pragma push
#pragma force_active on
SECTION_DATA static void* lit_6221[3] = {
    (void*)NULL,
    (void*)0xFFFFFFFF,
    (void*)d_attk__8daE_SW_cFv,
};
#pragma pop

/* 807AFFE8-807AFFF4 -00001 000C+00 0/1 0/0 0/0 .data            @6237 */
#pragma push
#pragma force_active on
SECTION_DATA static void* lit_6237[3] = {
    (void*)NULL,
    (void*)0xFFFFFFFF,
    (void*)d_fall__8daE_SW_cFv,
};
#pragma pop

/* 807AFFF4-807B0000 -00001 000C+00 0/1 0/0 0/0 .data            @6260 */
#pragma push
#pragma force_active on
SECTION_DATA static void* lit_6260[3] = {
    (void*)NULL,
    (void*)0xFFFFFFFF,
    (void*)d_damage__8daE_SW_cFv,
};
#pragma pop

/* 807B0000-807B000C -00001 000C+00 0/1 0/0 0/0 .data            @6262 */
#pragma push
#pragma force_active on
SECTION_DATA static void* lit_6262[3] = {
    (void*)NULL,
    (void*)0xFFFFFFFF,
    (void*)d_die__8daE_SW_cFv,
};
#pragma pop

/* 807B000C-807B0018 -00001 000C+00 0/1 0/0 0/0 .data            @6271 */
#pragma push
#pragma force_active on
SECTION_DATA static void* lit_6271[3] = {
    (void*)NULL,
    (void*)0xFFFFFFFF,
    (void*)d_chance__8daE_SW_cFv,
};
#pragma pop

/* 807B0018-807B0024 -00001 000C+00 0/1 0/0 0/0 .data            @6297 */
#pragma push
#pragma force_active on
SECTION_DATA static void* lit_6297[3] = {
    (void*)NULL,
    (void*)0xFFFFFFFF,
    (void*)d_damage__8daE_SW_cFv,
};
#pragma pop

/* 807B0024-807B0030 -00001 000C+00 0/1 0/0 0/0 .data            @6303 */
#pragma push
#pragma force_active on
SECTION_DATA static void* lit_6303[3] = {
    (void*)NULL,
    (void*)0xFFFFFFFF,
    (void*)d_damage__8daE_SW_cFv,
};
#pragma pop

/* 807B0030-807B003C -00001 000C+00 0/1 0/0 0/0 .data            @6307 */
#pragma push
#pragma force_active on
SECTION_DATA static void* lit_6307[3] = {
    (void*)NULL,
    (void*)0xFFFFFFFF,
    (void*)d_hook__8daE_SW_cFv,
};
#pragma pop

/* 807B003C-807B0048 -00001 000C+00 0/1 0/0 0/0 .data            @6313 */
#pragma push
#pragma force_active on
SECTION_DATA static void* lit_6313[3] = {
    (void*)NULL,
    (void*)0xFFFFFFFF,
    (void*)d_chance2__8daE_SW_cFv,
};
#pragma pop

/* 807B0048-807B0054 -00001 000C+00 0/1 0/0 0/0 .data            @6317 */
#pragma push
#pragma force_active on
SECTION_DATA static void* lit_6317[3] = {
    (void*)NULL,
    (void*)0xFFFFFFFF,
    (void*)d_chance2__8daE_SW_cFv,
};
#pragma pop

/* 807B0054-807B0060 -00001 000C+00 0/1 0/0 0/0 .data            @6319 */
#pragma push
#pragma force_active on
SECTION_DATA static void* lit_6319[3] = {
    (void*)NULL,
    (void*)0xFFFFFFFF,
    (void*)d_damage__8daE_SW_cFv,
};
#pragma pop

/* 807B0060-807B006C -00001 000C+00 1/1 0/0 0/0 .data            @6411 */
SECTION_DATA static void* lit_6411[3] = {
    (void*)NULL,
    (void*)0xFFFFFFFF,
    (void*)d_wait__8daE_SW_cFv,
};

/* 807B006C-807B0078 -00001 000C+00 1/1 0/0 0/0 .data            @6426 */
SECTION_DATA static void* lit_6426[3] = {
    (void*)NULL,
    (void*)0xFFFFFFFF,
    (void*)d_attk__8daE_SW_cFv,
};

/* 807B0078-807B0084 -00001 000C+00 1/1 0/0 0/0 .data            @6521 */
SECTION_DATA static void* lit_6521[3] = {
    (void*)NULL,
    (void*)0xFFFFFFFF,
    (void*)d_bm_chase__8daE_SW_cFv,
};

/* 807B0084-807B0090 -00001 000C+00 1/1 0/0 0/0 .data            @6527 */
SECTION_DATA static void* lit_6527[3] = {
    (void*)NULL,
    (void*)0xFFFFFFFF,
    (void*)d_chase__8daE_SW_cFv,
};

/* 807B0090-807B009C -00001 000C+00 0/1 0/0 0/0 .data            @6613 */
#pragma push
#pragma force_active on
SECTION_DATA static void* lit_6613[3] = {
    (void*)NULL,
    (void*)0xFFFFFFFF,
    (void*)d_wait__8daE_SW_cFv,
};
#pragma pop

/* 807B009C-807B00A8 -00001 000C+00 0/1 0/0 0/0 .data            @6617 */
#pragma push
#pragma force_active on
SECTION_DATA static void* lit_6617[3] = {
    (void*)NULL,
    (void*)0xFFFFFFFF,
    (void*)d_wait__8daE_SW_cFv,
};
#pragma pop

/* 807B00A8-807B00B4 -00001 000C+00 0/1 0/0 0/0 .data            @6621 */
#pragma push
#pragma force_active on
SECTION_DATA static void* lit_6621[3] = {
    (void*)NULL,
    (void*)0xFFFFFFFF,
    (void*)d_attk__8daE_SW_cFv,
};
#pragma pop

/* 807B00B4-807B00C0 -00001 000C+00 0/1 0/0 0/0 .data            @6726 */
#pragma push
#pragma force_active on
SECTION_DATA static void* lit_6726[3] = {
    (void*)NULL,
    (void*)0xFFFFFFFF,
    (void*)d_bm_chase__8daE_SW_cFv,
};
#pragma pop

/* 807B00C0-807B00CC -00001 000C+00 0/1 0/0 0/0 .data            @6739 */
#pragma push
#pragma force_active on
SECTION_DATA static void* lit_6739[3] = {
    (void*)NULL,
    (void*)0xFFFFFFFF,
    (void*)d_chance__8daE_SW_cFv,
};
#pragma pop

/* 807B00CC-807B00D8 -00001 000C+00 0/1 0/0 0/0 .data            @6753 */
#pragma push
#pragma force_active on
SECTION_DATA static void* lit_6753[3] = {
    (void*)NULL,
    (void*)0xFFFFFFFF,
    (void*)d_wait__8daE_SW_cFv,
};
#pragma pop

/* 807B00D8-807B00E4 -00001 000C+00 0/1 0/0 0/0 .data            @6758 */
#pragma push
#pragma force_active on
SECTION_DATA static void* lit_6758[3] = {
    (void*)NULL,
    (void*)0xFFFFFFFF,
    (void*)d_wait__8daE_SW_cFv,
};
#pragma pop

/* 807B00E4-807B00F0 -00001 000C+00 1/1 0/0 0/0 .data            @6858 */
SECTION_DATA static void* lit_6858[3] = {
    (void*)NULL,
    (void*)0xFFFFFFFF,
    (void*)d_hook__8daE_SW_cFv,
};

/* 807B00F0-807B00FC -00001 000C+00 1/1 0/0 0/0 .data            @6887 */
SECTION_DATA static void* lit_6887[3] = {
    (void*)NULL,
    (void*)0xFFFFFFFF,
    (void*)d_dive__8daE_SW_cFv,
};

/* 807B00FC-807B0108 -00001 000C+00 1/1 0/0 0/0 .data            @6929 */
SECTION_DATA static void* lit_6929[3] = {
    (void*)NULL,
    (void*)0xFFFFFFFF,
    (void*)d_chance__8daE_SW_cFv,
};

/* 807B0108-807B0114 -00001 000C+00 1/1 0/0 0/0 .data            @6959 */
SECTION_DATA static void* lit_6959[3] = {
    (void*)NULL,
    (void*)0xFFFFFFFF,
    (void*)d_wait__8daE_SW_cFv,
};

/* 807B0114-807B0120 -00001 000C+00 1/1 0/0 0/0 .data            @6993 */
SECTION_DATA static void* lit_6993[3] = {
    (void*)NULL,
    (void*)0xFFFFFFFF,
    (void*)d_die__8daE_SW_cFv,
};

/* 807B0120-807B012C -00001 000C+00 1/1 0/0 0/0 .data            @6996 */
SECTION_DATA static void* lit_6996[3] = {
    (void*)NULL,
    (void*)0xFFFFFFFF,
    (void*)d_chance__8daE_SW_cFv,
};

/* 807B012C-807B0138 -00001 000C+00 1/1 0/0 0/0 .data            @7081 */
SECTION_DATA static void* lit_7081[3] = {
    (void*)NULL,
    (void*)0xFFFFFFFF,
    (void*)d_chance__8daE_SW_cFv,
};

/* 807B0138-807B0144 0002BC 000C+00 2/2 0/0 0/0 .data            __vt__8cM3dGPla */
SECTION_DATA extern void* __vt__8cM3dGPla[3] = {
    (void*)NULL /* RTTI */,
    (void*)NULL,
    (void*)__dt__8cM3dGPlaFv,
};

/* 807B0144-807B0150 0002C8 000C+00 1/1 0/0 0/0 .data            __vt__12dBgS_AcchCir */
SECTION_DATA extern void* __vt__12dBgS_AcchCir[3] = {
    (void*)NULL /* RTTI */,
    (void*)NULL,
    (void*)__dt__12dBgS_AcchCirFv,
};

/* 807B0150-807B015C 0002D4 000C+00 2/2 0/0 0/0 .data            __vt__10cCcD_GStts */
SECTION_DATA extern void* __vt__10cCcD_GStts[3] = {
    (void*)NULL /* RTTI */,
    (void*)NULL,
    (void*)__dt__10cCcD_GSttsFv,
};

/* 807B015C-807B0168 0002E0 000C+00 1/1 0/0 0/0 .data            __vt__10dCcD_GStts */
SECTION_DATA extern void* __vt__10dCcD_GStts[3] = {
    (void*)NULL /* RTTI */,
    (void*)NULL,
    (void*)__dt__10dCcD_GSttsFv,
};

/* 807B0168-807B0174 0002EC 000C+00 2/2 0/0 0/0 .data            __vt__8cM3dGSph */
SECTION_DATA extern void* __vt__8cM3dGSph[3] = {
    (void*)NULL /* RTTI */,
    (void*)NULL,
    (void*)__dt__8cM3dGSphFv,
};

/* 807B0174-807B0180 0002F8 000C+00 2/2 0/0 0/0 .data            __vt__8cM3dGAab */
SECTION_DATA extern void* __vt__8cM3dGAab[3] = {
    (void*)NULL /* RTTI */,
    (void*)NULL,
    (void*)__dt__8cM3dGAabFv,
};

/* 807B0180-807B01A4 000304 0024+00 2/2 0/0 0/0 .data            __vt__12dBgS_ObjAcch */
SECTION_DATA extern void* __vt__12dBgS_ObjAcch[9] = {
    (void*)NULL /* RTTI */,
    (void*)NULL,
    (void*)__dt__12dBgS_ObjAcchFv,
    (void*)NULL,
    (void*)NULL,
    (void*)func_807AF8FC,
    (void*)NULL,
    (void*)NULL,
    (void*)func_807AF8F4,
};

/* 807B01A4-807B01B0 000328 000C+00 2/2 0/0 0/0 .data            __vt__12daE_SW_HIO_c */
SECTION_DATA extern void* __vt__12daE_SW_HIO_c[3] = {
    (void*)NULL /* RTTI */,
    (void*)NULL,
    (void*)__dt__12daE_SW_HIO_cFv,
};

/* 807A740C-807A7460 0000EC 0054+00 1/1 0/0 0/0 .text            __ct__12daE_SW_HIO_cFv */
daE_SW_HIO_c::daE_SW_HIO_c() {
    // NONMATCHING
}

/* ############################################################################################## */
/* 807AFD68-807AFD6C 00003C 0004+00 1/3 0/0 0/0 .rodata          @3947 */
SECTION_RODATA static f32 const lit_3947 = -1.0f;
COMPILER_STRIP_GATE(0x807AFD68, &lit_3947);

/* 807AFE70-807AFE70 000144 0000+00 0/0 0/0 0/0 .rodata          @stringBase0 */
#pragma push
#pragma force_active on
SECTION_DEAD static char const* const stringBase_807AFE70 = "E_SW";
#pragma pop

/* 807A7460-807A7504 000140 00A4+00 22/22 0/0 0/0 .text            bckSet__8daE_SW_cFifUcf */
void daE_SW_c::bckSet(int param_0, f32 param_1, u8 param_2, f32 param_3) {
    // NONMATCHING
}

/* ############################################################################################## */
/* 807AFD6C-807AFD70 000040 0004+00 0/1 0/0 0/0 .rodata          @3986 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_3986 = 700.0f;
COMPILER_STRIP_GATE(0x807AFD6C, &lit_3986);
#pragma pop

/* 807A7504-807A76C4 0001E4 01C0+00 1/1 0/0 0/0 .text            draw__8daE_SW_cFv */
void daE_SW_c::draw() {
    // NONMATCHING
}

/* 807A76C4-807A76E4 0003A4 0020+00 1/0 0/0 0/0 .text            daE_SW_Draw__FP8daE_SW_c */
static void daE_SW_Draw(daE_SW_c* param_0) {
    // NONMATCHING
}

/* 807A76E4-807A77CC 0003C4 00E8+00 5/5 0/0 0/0 .text            setBeforeJumpEffect__8daE_SW_cFv */
void daE_SW_c::setBeforeJumpEffect() {
    // NONMATCHING
}

/* 807A77CC-807A78B4 0004AC 00E8+00 2/2 0/0 0/0 .text            setJumpEffect__8daE_SW_cFv */
void daE_SW_c::setJumpEffect() {
    // NONMATCHING
}

/* 807A78B4-807A7A08 000594 0154+00 9/9 0/0 0/0 .text            setSmokeEffect__8daE_SW_cFv */
void daE_SW_c::setSmokeEffect() {
    // NONMATCHING
}

/* 807A7A08-807A7AC0 0006E8 00B8+00 2/2 0/0 0/0 .text            setDiveEffect__8daE_SW_cFv */
void daE_SW_c::setDiveEffect() {
    // NONMATCHING
}

/* 807A7AC0-807A7B64 0007A0 00A4+00 2/2 0/0 0/0 .text            setHideEffect__8daE_SW_cFv */
void daE_SW_c::setHideEffect() {
    // NONMATCHING
}

/* ############################################################################################## */
/* 807B01B8-807B01BC 000008 0001+03 1/1 0/0 0/0 .bss             @1109 */
static u8 lit_1109[1 + 3 /* padding */];

/* 807B01BC-807B01C0 00000C 0001+03 0/0 0/0 0/0 .bss             @1107 */
#pragma push
#pragma force_active on
static u8 lit_1107[1 + 3 /* padding */];
#pragma pop

/* 807B01C0-807B01C4 000010 0001+03 0/0 0/0 0/0 .bss             @1105 */
#pragma push
#pragma force_active on
static u8 lit_1105[1 + 3 /* padding */];
#pragma pop

/* 807B01C4-807B01C8 000014 0001+03 0/0 0/0 0/0 .bss             @1104 */
#pragma push
#pragma force_active on
static u8 lit_1104[1 + 3 /* padding */];
#pragma pop

/* 807B01C8-807B01CC 000018 0001+03 0/0 0/0 0/0 .bss             @1099 */
#pragma push
#pragma force_active on
static u8 lit_1099[1 + 3 /* padding */];
#pragma pop

/* 807B01CC-807B01D0 00001C 0001+03 0/0 0/0 0/0 .bss             @1097 */
#pragma push
#pragma force_active on
static u8 lit_1097[1 + 3 /* padding */];
#pragma pop

/* 807B01D0-807B01D4 000020 0001+03 0/0 0/0 0/0 .bss             @1095 */
#pragma push
#pragma force_active on
static u8 lit_1095[1 + 3 /* padding */];
#pragma pop

/* 807B01D4-807B01D8 000024 0001+03 0/0 0/0 0/0 .bss             @1094 */
#pragma push
#pragma force_active on
static u8 lit_1094[1 + 3 /* padding */];
#pragma pop

/* 807B01D8-807B01DC 000028 0001+03 0/0 0/0 0/0 .bss             @1057 */
#pragma push
#pragma force_active on
static u8 lit_1057[1 + 3 /* padding */];
#pragma pop

/* 807B01DC-807B01E0 00002C 0001+03 0/0 0/0 0/0 .bss             @1055 */
#pragma push
#pragma force_active on
static u8 lit_1055[1 + 3 /* padding */];
#pragma pop

/* 807B01E0-807B01E4 000030 0001+03 0/0 0/0 0/0 .bss             @1053 */
#pragma push
#pragma force_active on
static u8 lit_1053[1 + 3 /* padding */];
#pragma pop

/* 807B01E4-807B01E8 000034 0001+03 0/0 0/0 0/0 .bss             @1052 */
#pragma push
#pragma force_active on
static u8 lit_1052[1 + 3 /* padding */];
#pragma pop

/* 807B01E8-807B01EC 000038 0001+03 0/0 0/0 0/0 .bss             @1014 */
#pragma push
#pragma force_active on
static u8 lit_1014[1 + 3 /* padding */];
#pragma pop

/* 807B01EC-807B01F0 00003C 0001+03 0/0 0/0 0/0 .bss             @1012 */
#pragma push
#pragma force_active on
static u8 lit_1012[1 + 3 /* padding */];
#pragma pop

/* 807B01F0-807B01F4 000040 0001+03 0/0 0/0 0/0 .bss             @1010 */
#pragma push
#pragma force_active on
static u8 lit_1010[1 + 3 /* padding */];
#pragma pop

/* 807B01F4-807B01F8 000044 0001+03 0/0 0/0 0/0 .bss             @1009 */
#pragma push
#pragma force_active on
static u8 lit_1009[1 + 3 /* padding */];
#pragma pop

/* 807B01F8-807B01FC 000048 0004+00 1/2 0/0 0/0 .bss target_info__22@unnamed@d_a_e_sw_cpp@ */
static u8 data_807B01F8[4];

/* 807B01FC-807B0200 00004C 0004+00 1/2 0/0 0/0 .bss target_dist__22@unnamed@d_a_e_sw_cpp@ */
static u8 data_807B01FC[4];

/* 807B0200-807B0204 -00001 0004+00 10/10 0/0 0/0 .bss             None */
/* 807B0200 0001+00 data_807B0200 None */
/* 807B0201 0001+00 data_807B0201 None */
/* 807B0202 0001+00 data_807B0202 None */
/* 807B0203 0001+00 data_807B0203 None */
static u8 struct_807B0200[4];

/* 807A7B64-807A7B9C 000844 0038+00 17/17 0/0 0/0 .text            setActionMode__8daE_SW_cFss */
void daE_SW_c::setActionMode(s16 param_0, s16 param_1) {
    // NONMATCHING
}

/* 807A7B9C-807A7C50 00087C 00B4+00 1/1 0/0 0/0 .text            s_b_sub__FPvPv */
static void s_b_sub(void* param_0, void* param_1) {
    // NONMATCHING
}

/* ############################################################################################## */
/* 807B0204-807B0210 000054 000C+00 1/1 0/0 0/0 .bss             @3925 */
static u8 lit_3925[12];

/* 807B0210-807B0234 000060 0024+00 12/13 0/0 0/0 .bss             l_HIO */
static u8 l_HIO[36];

/* 807A7C50-807A7CD0 000930 0080+00 2/2 0/0 0/0 .text            search_bomb__8daE_SW_cFv */
void daE_SW_c::search_bomb() {
    // NONMATCHING
}

/* 807A7CD0-807A7D48 0009B0 0078+00 4/4 0/0 0/0 .text            bomb_check__8daE_SW_cFv */
void daE_SW_c::bomb_check() {
    // NONMATCHING
}

/* 807A7D48-807A7DAC 000A28 0064+00 2/2 0/0 0/0 .text            setModeBack__8daE_SW_cFv */
void daE_SW_c::setModeBack() {
    // NONMATCHING
}

/* ############################################################################################## */
/* 807AFD70-807AFD74 000044 0004+00 0/2 0/0 0/0 .rodata          @4187 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_4187 = -1000000000.0f;
COMPILER_STRIP_GATE(0x807AFD70, &lit_4187);
#pragma pop

/* 807A7DAC-807A7EFC 000A8C 0150+00 1/1 0/0 0/0 .text            checkFall__8daE_SW_cFv */
void daE_SW_c::checkFall() {
    // NONMATCHING
}

/* 807A7EFC-807A7F88 000BDC 008C+00 1/1 0/0 0/0 .text            checkBeforeWall__8daE_SW_cFv */
void daE_SW_c::checkBeforeWall() {
    // NONMATCHING
}

/* ############################################################################################## */
/* 807AFD74-807AFD78 000048 0004+00 0/4 0/0 0/0 .rodata          @4271 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_4271 = 2.0f;
COMPILER_STRIP_GATE(0x807AFD74, &lit_4271);
#pragma pop

/* 807AFD78-807AFD7C 00004C 0004+00 0/17 0/0 0/0 .rodata          @4272 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_4272 = 10.0f;
COMPILER_STRIP_GATE(0x807AFD78, &lit_4272);
#pragma pop

/* 807AFD7C-807AFD80 000050 0004+00 0/1 0/0 0/0 .rodata          @4273 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_4273 = 600.0f;
COMPILER_STRIP_GATE(0x807AFD7C, &lit_4273);
#pragma pop

/* 807AFD80-807AFD84 000054 0004+00 0/2 0/0 0/0 .rodata          @4274 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_4274 = 60000.0f;
COMPILER_STRIP_GATE(0x807AFD80, &lit_4274);
#pragma pop

/* 807AFD84-807AFD88 000058 0004+00 0/2 0/0 0/0 .rodata          @4275 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_4275 = 1.0f / 5.0f;
COMPILER_STRIP_GATE(0x807AFD84, &lit_4275);
#pragma pop

/* 807AFD88-807AFD8C 00005C 0004+00 0/7 0/0 0/0 .rodata          @4276 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_4276 = 20.0f;
COMPILER_STRIP_GATE(0x807AFD88, &lit_4276);
#pragma pop

/* 807A7F88-807A8290 000C68 0308+00 1/1 0/0 0/0 .text            executeWait__8daE_SW_cFv */
void daE_SW_c::executeWait() {
    // NONMATCHING
}

/* ############################################################################################## */
/* 807AFD8C-807AFD90 000060 0004+00 1/6 0/0 0/0 .rodata          @4293 */
SECTION_RODATA static f32 const lit_4293 = 19.0f;
COMPILER_STRIP_GATE(0x807AFD8C, &lit_4293);

/* 807AFD90-807AFD94 000064 0004+00 1/10 0/0 0/0 .rodata          @4294 */
SECTION_RODATA static f32 const lit_4294 = 30.0f;
COMPILER_STRIP_GATE(0x807AFD90, &lit_4294);

/* 807A8290-807A831C 000F70 008C+00 2/2 0/0 0/0 .text            checkRunChase__8daE_SW_cFv */
void daE_SW_c::checkRunChase() {
    // NONMATCHING
}

/* ############################################################################################## */
/* 807AFD94-807AFD98 000068 0004+00 0/6 0/0 0/0 .rodata          @4497 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_4497 = 5.0f;
COMPILER_STRIP_GATE(0x807AFD94, &lit_4497);
#pragma pop

/* 807AFD98-807AFD9C 00006C 0004+00 0/14 0/0 0/0 .rodata          @4498 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_4498 = 15.0f;
COMPILER_STRIP_GATE(0x807AFD98, &lit_4498);
#pragma pop

/* 807AFD9C-807AFDA0 000070 0004+00 0/1 0/0 0/0 .rodata          @4499 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_4499 = 70.0f;
COMPILER_STRIP_GATE(0x807AFD9C, &lit_4499);
#pragma pop

/* 807AFDA0-807AFDA4 000074 0004+00 0/8 0/0 0/0 .rodata          @4500 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_4500 = 0.5f;
COMPILER_STRIP_GATE(0x807AFDA0, &lit_4500);
#pragma pop

/* 807AFDA4-807AFDA8 000078 0004+00 0/4 0/0 0/0 .rodata          @4501 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_4501 = 50.0f;
COMPILER_STRIP_GATE(0x807AFDA4, &lit_4501);
#pragma pop

/* 807AFDA8-807AFDAC 00007C 0004+00 0/2 0/0 0/0 .rodata          @4502 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_4502 = 150.0f;
COMPILER_STRIP_GATE(0x807AFDA8, &lit_4502);
#pragma pop

/* 807AFDAC-807AFDB0 000080 0004+00 0/7 0/0 0/0 .rodata          @4503 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_4503 = 200.0f;
COMPILER_STRIP_GATE(0x807AFDAC, &lit_4503);
#pragma pop

/* 807AFDB0-807AFDB4 000084 0004+00 0/1 0/0 0/0 .rodata          @4504 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_4504 = 3.0f / 10.0f;
COMPILER_STRIP_GATE(0x807AFDB0, &lit_4504);
#pragma pop

/* 807AFDB4-807AFDB8 000088 0004+00 0/3 0/0 0/0 .rodata          @4505 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_4505 = 300.0f;
COMPILER_STRIP_GATE(0x807AFDB4, &lit_4505);
#pragma pop

/* 807AFDB8-807AFDBC 00008C 0004+00 0/1 0/0 0/0 .rodata          @4506 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_4506 = 130.0f;
COMPILER_STRIP_GATE(0x807AFDB8, &lit_4506);
#pragma pop

/* 807A831C-807A8B98 000FFC 087C+00 1/1 0/0 0/0 .text            executeChaseSlow__8daE_SW_cFv */
void daE_SW_c::executeChaseSlow() {
    // NONMATCHING
}

/* ############################################################################################## */
/* 807AFDBC-807AFDC0 000090 0004+00 0/1 0/0 0/0 .rodata          @4872 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_4872 = 12288.0f;
COMPILER_STRIP_GATE(0x807AFDBC, &lit_4872);
#pragma pop

/* 807AFDC0-807AFDC4 000094 0004+00 0/2 0/0 0/0 .rodata          @4873 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_4873 = -200.0f;
COMPILER_STRIP_GATE(0x807AFDC0, &lit_4873);
#pragma pop

/* 807AFDC4-807AFDCC 000098 0008+00 0/1 0/0 0/0 .rodata          @4874 */
#pragma push
#pragma force_active on
SECTION_RODATA static u8 const lit_4874[8] = {
    0x3F, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
COMPILER_STRIP_GATE(0x807AFDC4, &lit_4874);
#pragma pop

/* 807AFDCC-807AFDD0 0000A0 0004+00 0/1 0/0 0/0 .rodata          @4875 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_4875 = 350.0f;
COMPILER_STRIP_GATE(0x807AFDCC, &lit_4875);
#pragma pop

/* 807AFDD0-807AFDD4 0000A4 0004+00 0/3 0/0 0/0 .rodata          @4876 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_4876 = -3.0f;
COMPILER_STRIP_GATE(0x807AFDD0, &lit_4876);
#pragma pop

/* 807AFDD4-807AFDD8 0000A8 0004+00 0/1 0/0 0/0 .rodata          @4877 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_4877 = 250.0f;
COMPILER_STRIP_GATE(0x807AFDD4, &lit_4877);
#pragma pop

/* 807AFDD8-807AFDDC 0000AC 0004+00 0/1 0/0 0/0 .rodata          @4878 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_4878 = 500.0f;
COMPILER_STRIP_GATE(0x807AFDD8, &lit_4878);
#pragma pop

/* 807AFDDC-807AFDE0 0000B0 0004+00 0/7 0/0 0/0 .rodata          @4879 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_4879 = 3.0f;
COMPILER_STRIP_GATE(0x807AFDDC, &lit_4879);
#pragma pop

/* 807A8B98-807A9580 001878 09E8+00 1/1 0/0 0/0 .text            executeChaseFast__8daE_SW_cFv */
void daE_SW_c::executeChaseFast() {
    // NONMATCHING
}

/* ############################################################################################## */
/* 807AFDE0-807AFDE4 0000B4 0004+00 0/5 0/0 0/0 .rodata          @4913 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_4913 = 1.0f / 10.0f;
COMPILER_STRIP_GATE(0x807AFDE0, &lit_4913);
#pragma pop

/* 807A9580-807A9768 002260 01E8+00 1/1 0/0 0/0 .text            executeBomb__8daE_SW_cFv */
void daE_SW_c::executeBomb() {
    // NONMATCHING
}

/* ############################################################################################## */
/* 807AFDE4-807AFDE8 0000B8 0004+00 0/3 0/0 0/0 .rodata          @5057 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_5057 = -4.0f;
COMPILER_STRIP_GATE(0x807AFDE4, &lit_5057);
#pragma pop

/* 807AFDE8-807AFDEC 0000BC 0004+00 0/2 0/0 0/0 .rodata          @5058 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_5058 = 60.0f;
COMPILER_STRIP_GATE(0x807AFDE8, &lit_5058);
#pragma pop

/* 807AFDEC-807AFDF0 0000C0 0004+00 0/2 0/0 0/0 .rodata          @5059 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_5059 = 25.0f;
COMPILER_STRIP_GATE(0x807AFDEC, &lit_5059);
#pragma pop

/* 807AFDF0-807AFDF4 0000C4 0004+00 0/1 0/0 0/0 .rodata          @5060 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_5060 = 24.0f;
COMPILER_STRIP_GATE(0x807AFDF0, &lit_5060);
#pragma pop

/* 807AFDF4-807AFDF8 0000C8 0004+00 0/1 0/0 0/0 .rodata          @5061 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_5061 = 23.0f;
COMPILER_STRIP_GATE(0x807AFDF4, &lit_5061);
#pragma pop

/* 807AFDF8-807AFDFC 0000CC 0004+00 0/2 0/0 0/0 .rodata          @5062 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_5062 = 120.0f;
COMPILER_STRIP_GATE(0x807AFDF8, &lit_5062);
#pragma pop

/* 807AFDFC-807AFE00 0000D0 0004+00 0/8 0/0 0/0 .rodata          @5063 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_5063 = -5.0f;
COMPILER_STRIP_GATE(0x807AFDFC, &lit_5063);
#pragma pop

/* 807AFE00-807AFE04 0000D4 0004+00 0/2 0/0 0/0 .rodata          @5064 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_5064 = -60.0f;
COMPILER_STRIP_GATE(0x807AFE00, &lit_5064);
#pragma pop

/* 807AFE04-807AFE08 0000D8 0004+00 0/5 0/0 0/0 .rodata          @5065 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_5065 = -120.0f;
COMPILER_STRIP_GATE(0x807AFE04, &lit_5065);
#pragma pop

/* 807A9768-807A9E58 002448 06F0+00 1/1 0/0 0/0 .text            executeAttack__8daE_SW_cFv */
void daE_SW_c::executeAttack() {
    // NONMATCHING
}

/* ############################################################################################## */
/* 807AFE08-807AFE0C 0000DC 0004+00 0/2 0/0 0/0 .rodata          @5104 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_5104 = 40.0f;
COMPILER_STRIP_GATE(0x807AFE08, &lit_5104);
#pragma pop

/* 807AFE0C-807AFE10 0000E0 0004+00 0/2 0/0 0/0 .rodata          @5105 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_5105 = -40.0f;
COMPILER_STRIP_GATE(0x807AFE0C, &lit_5105);
#pragma pop

/* 807A9E58-807AA050 002B38 01F8+00 2/2 0/0 0/0 .text            executeHook__8daE_SW_cFv */
void daE_SW_c::executeHook() {
    // NONMATCHING
}

/* ############################################################################################## */
/* 807AFE10-807AFE14 0000E4 0004+00 0/1 0/0 0/0 .rodata          @5206 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_5206 = 4096.0f;
COMPILER_STRIP_GATE(0x807AFE10, &lit_5206);
#pragma pop

/* 807AFE14-807AFE1C 0000E8 0008+00 0/4 0/0 0/0 .rodata          @5208 */
#pragma push
#pragma force_active on
SECTION_RODATA static u8 const lit_5208[8] = {
    0x43, 0x30, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00,
};
COMPILER_STRIP_GATE(0x807AFE14, &lit_5208);
#pragma pop

/* 807AA050-807AA44C 002D30 03FC+00 1/1 0/0 0/0 .text            executeMoveOut__8daE_SW_cFv */
void daE_SW_c::executeMoveOut() {
    // NONMATCHING
}

/* 807AA44C-807AA784 00312C 0338+00 2/1 0/0 0/0 .text            executeChance__8daE_SW_cFv */
void daE_SW_c::executeChance() {
    // NONMATCHING
}

/* ############################################################################################## */
/* 807AFE1C-807AFE20 0000F0 0004+00 0/2 0/0 0/0 .rodata          @5264 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_5264 = 36.0f;
COMPILER_STRIP_GATE(0x807AFE1C, &lit_5264);
#pragma pop

/* 807AFE20-807AFE24 0000F4 0004+00 0/1 0/0 0/0 .rodata          @5265 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_5265 = 7.0f;
COMPILER_STRIP_GATE(0x807AFE20, &lit_5265);
#pragma pop

/* 807AFE24-807AFE28 0000F8 0004+00 0/1 0/0 0/0 .rodata          @5266 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_5266 = 32000.0f;
COMPILER_STRIP_GATE(0x807AFE24, &lit_5266);
#pragma pop

/* 807AFE28-807AFE2C 0000FC 0004+00 0/1 0/0 0/0 .rodata          @5267 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_5267 = 8000.0f;
COMPILER_STRIP_GATE(0x807AFE28, &lit_5267);
#pragma pop

/* 807AFE2C-807AFE30 000100 0004+00 0/1 0/0 0/0 .rodata          @5268 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_5268 = 12.0f;
COMPILER_STRIP_GATE(0x807AFE2C, &lit_5268);
#pragma pop

/* 807AFE30-807AFE34 000104 0004+00 0/1 0/0 0/0 .rodata          @5269 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_5269 = 35.0f;
COMPILER_STRIP_GATE(0x807AFE30, &lit_5269);
#pragma pop

/* 807AFE34-807AFE38 000108 0004+00 0/1 0/0 0/0 .rodata          @5300 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_5300 = 14.0f;
COMPILER_STRIP_GATE(0x807AFE34, &lit_5300);
#pragma pop

/* 807AA784-807AA91C 003464 0198+00 1/1 0/0 0/0 .text            executeDive__8daE_SW_cFv */
void daE_SW_c::executeDive() {
    // NONMATCHING
}

/* ############################################################################################## */
/* 807AFE38-807AFE3C 00010C 0004+00 0/2 0/0 0/0 .rodata          @5327 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_5327 = 48.0f;
COMPILER_STRIP_GATE(0x807AFE38, &lit_5327);
#pragma pop

/* 807AFE3C-807AFE40 000110 0004+00 0/2 0/0 0/0 .rodata          @5328 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_5328 = 28.0f;
COMPILER_STRIP_GATE(0x807AFE3C, &lit_5328);
#pragma pop

/* 807AFE40-807AFE44 000114 0004+00 0/2 0/0 0/0 .rodata          @5329 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_5329 = 8.0f;
COMPILER_STRIP_GATE(0x807AFE40, &lit_5329);
#pragma pop

/* 807AA91C-807AAB7C 0035FC 0260+00 1/1 0/0 0/0 .text            executeDamage__8daE_SW_cFv */
void daE_SW_c::executeDamage() {
    // NONMATCHING
}

/* ############################################################################################## */
/* 807AFE44-807AFE48 000118 0004+00 0/4 0/0 0/0 .rodata          @5365 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_5365 = -50.0f;
COMPILER_STRIP_GATE(0x807AFE44, &lit_5365);
#pragma pop

/* 807AAB7C-807AAD28 00385C 01AC+00 1/1 0/0 0/0 .text            executeDie__8daE_SW_cFv */
void daE_SW_c::executeDie() {
    // NONMATCHING
}

/* 807AAD28-807AADCC 003A08 00A4+00 1/1 0/0 0/0 .text            s_child_sub__FPvPv */
static void s_child_sub(void* param_0, void* param_1) {
    // NONMATCHING
}

/* ############################################################################################## */
/* 807AFE48-807AFE4C 00011C 0004+00 0/1 0/0 0/0 .rodata          @5428 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_5428 = 10000.0f;
COMPILER_STRIP_GATE(0x807AFE48, &lit_5428);
#pragma pop

/* 807AADCC-807AAF70 003AAC 01A4+00 1/1 0/0 0/0 .text            executeMaster__8daE_SW_cFv */
void daE_SW_c::executeMaster() {
    // NONMATCHING
}

/* 807AAF70-807AB310 003C50 03A0+00 3/3 0/0 0/0 .text            checkSuddenAttack__8daE_SW_cFi */
void daE_SW_c::checkSuddenAttack(int param_0) {
    // NONMATCHING
}

/* 807AB310-807AB5C4 003FF0 02B4+00 1/1 0/0 0/0 .text            executeSuddenAttack__8daE_SW_cFv */
void daE_SW_c::executeSuddenAttack() {
    // NONMATCHING
}

/* 807AB5C4-807AB6C4 0042A4 0100+00 1/1 0/0 0/0 .text            executeFall__8daE_SW_cFv */
void daE_SW_c::executeFall() {
    // NONMATCHING
}

/* 807AB6C4-807AB884 0043A4 01C0+00 2/1 0/0 0/0 .text            action__8daE_SW_cFv */
void daE_SW_c::action() {
    // NONMATCHING
}

/* 807AB884-807AB930 004564 00AC+00 2/2 0/0 0/0 .text            mtx_set__8daE_SW_cFv */
void daE_SW_c::mtx_set() {
    // NONMATCHING
}

/* 807AB930-807ABAB0 004610 0180+00 2/2 0/0 0/0 .text            cc_set__8daE_SW_cFv */
void daE_SW_c::cc_set() {
    // NONMATCHING
}

/* 807ABAB0-807ABD28 004790 0278+00 1/1 0/0 0/0 .text            damage_check__8daE_SW_cFv */
void daE_SW_c::damage_check() {
    // NONMATCHING
}

/* 807ABD28-807ABE50 004A08 0128+00 2/2 0/0 0/0 .text            checkGroundSand__8daE_SW_cFv */
void daE_SW_c::checkGroundSand() {
    // NONMATCHING
}

/* ############################################################################################## */
/* 807AFE4C-807AFE50 000120 0004+00 0/1 0/0 0/0 .rodata          @5895 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_5895 = 5000.0f;
COMPILER_STRIP_GATE(0x807AFE4C, &lit_5895);
#pragma pop

/* 807AFE50-807AFE54 000124 0004+00 0/3 0/0 0/0 .rodata          @5896 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_5896 = 1.5f;
COMPILER_STRIP_GATE(0x807AFE50, &lit_5896);
#pragma pop

/* 807ABE50-807AC148 004B30 02F8+00 1/1 0/0 0/0 .text            execute__8daE_SW_cFv */
void daE_SW_c::execute() {
    // NONMATCHING
}

/* 807AC148-807AC168 004E28 0020+00 2/1 0/0 0/0 .text            daE_SW_Execute__FP8daE_SW_c */
static void daE_SW_Execute(daE_SW_c* param_0) {
    // NONMATCHING
}

/* 807AC168-807AC170 004E48 0008+00 1/0 0/0 0/0 .text            daE_SW_IsDelete__FP8daE_SW_c */
static bool daE_SW_IsDelete(daE_SW_c* param_0) {
    return true;
}

/* 807AC170-807AC1E4 004E50 0074+00 1/1 0/0 0/0 .text            _delete__8daE_SW_cFv */
void daE_SW_c::_delete() {
    // NONMATCHING
}

/* 807AC1E4-807AC204 004EC4 0020+00 1/0 0/0 0/0 .text            daE_SW_Delete__FP8daE_SW_c */
static void daE_SW_Delete(daE_SW_c* param_0) {
    // NONMATCHING
}

/* 807AC204-807AC2FC 004EE4 00F8+00 1/1 0/0 0/0 .text            CreateHeap__8daE_SW_cFv */
void daE_SW_c::CreateHeap() {
    // NONMATCHING
}

/* 807AC2FC-807AC31C 004FDC 0020+00 1/1 0/0 0/0 .text            useHeapInit__FP10fopAc_ac_c */
static void useHeapInit(fopAc_ac_c* param_0) {
    // NONMATCHING
}

/* ############################################################################################## */
/* 807AFE54-807AFE58 000128 0004+00 0/1 0/0 0/0 .rodata          @6115 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_6115 = 1000000000.0f;
COMPILER_STRIP_GATE(0x807AFE54, &lit_6115);
#pragma pop

/* 807AFE58-807AFE5C 00012C 0004+00 0/2 0/0 0/0 .rodata          @6116 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_6116 = -10.0f;
COMPILER_STRIP_GATE(0x807AFE58, &lit_6116);
#pragma pop

/* 807AFE5C-807AFE64 000130 0008+00 0/1 0/0 0/0 .rodata          @6118 */
#pragma push
#pragma force_active on
SECTION_RODATA static u8 const lit_6118[8] = {
    0x43, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
COMPILER_STRIP_GATE(0x807AFE5C, &lit_6118);
#pragma pop

/* 807AFE70-807AFE70 000144 0000+00 0/0 0/0 0/0 .rodata          @stringBase0 */
#pragma push
#pragma force_active on
SECTION_DEAD static char const* const stringBase_807AFE75 = "E_sw";
#pragma pop

/* 807AC31C-807AC854 004FFC 0538+00 1/1 0/0 0/0 .text            create__8daE_SW_cFv */
void daE_SW_c::create() {
    // NONMATCHING
}

/* 807AC854-807AC89C 005534 0048+00 1/0 0/0 0/0 .text            __dt__8cM3dGSphFv */
// cM3dGSph::~cM3dGSph() {
extern "C" void __dt__8cM3dGSphFv() {
    // NONMATCHING
}

/* 807AC89C-807AC8E4 00557C 0048+00 1/0 0/0 0/0 .text            __dt__8cM3dGAabFv */
// cM3dGAab::~cM3dGAab() {
extern "C" void __dt__8cM3dGAabFv() {
    // NONMATCHING
}

/* 807AC8E4-807AC940 0055C4 005C+00 1/0 0/0 0/0 .text            __dt__10dCcD_GSttsFv */
// dCcD_GStts::~dCcD_GStts() {
extern "C" void __dt__10dCcD_GSttsFv() {
    // NONMATCHING
}

/* 807AC940-807AC9B0 005620 0070+00 3/2 0/0 0/0 .text            __dt__12dBgS_ObjAcchFv */
// dBgS_ObjAcch::~dBgS_ObjAcch() {
extern "C" void __dt__12dBgS_ObjAcchFv() {
    // NONMATCHING
}

/* 807AC9B0-807ACA20 005690 0070+00 2/1 0/0 0/0 .text            __dt__12dBgS_AcchCirFv */
// dBgS_AcchCir::~dBgS_AcchCir() {
extern "C" void __dt__12dBgS_AcchCirFv() {
    // NONMATCHING
}

/* 807ACA20-807ACA40 005700 0020+00 1/0 0/0 0/0 .text            daE_SW_Create__FP8daE_SW_c */
static void daE_SW_Create(daE_SW_c* param_0) {
    // NONMATCHING
}

/* 807ACA40-807ACAE4 005720 00A4+00 12/12 0/0 0/0 .text d_setAction__8daE_SW_cFM8daE_SW_cFPCvPv_v
 */
void daE_SW_c::d_setAction(void (daE_SW_c::*param_0)()) {
    // NONMATCHING
}

/* 807ACAE4-807ACCB0 0057C4 01CC+00 1/1 0/0 0/0 .text            d_checkFall__8daE_SW_cFv */
void daE_SW_c::d_checkFall() {
    // NONMATCHING
}

/* 807ACCB0-807ACFF8 005990 0348+00 1/1 0/0 0/0 .text            d_damage_check__8daE_SW_cFv */
void daE_SW_c::d_damage_check() {
    // NONMATCHING
}

/* 807ACFF8-807AD10C 005CD8 0114+00 1/1 0/0 0/0 .text            d_action__8daE_SW_cFv */
void daE_SW_c::d_action() {
    // NONMATCHING
}

/* 807AD10C-807AD17C 005DEC 0070+00 1/1 0/0 0/0 .text            d_bomb_check__8daE_SW_cFv */
void daE_SW_c::d_bomb_check() {
    // NONMATCHING
}

/* 807AD17C-807AD4A8 005E5C 032C+00 2/0 0/0 0/0 .text            d_bm_chase__8daE_SW_cFv */
void daE_SW_c::d_bm_chase() {
    // NONMATCHING
}

/* ############################################################################################## */
/* 807AFE64-807AFE68 000138 0004+00 0/1 0/0 0/0 .rodata          @6540 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_6540 = 32768.0f;
COMPILER_STRIP_GATE(0x807AFE64, &lit_6540);
#pragma pop

/* 807AFE68-807AFE6C 00013C 0004+00 0/1 0/0 0/0 .rodata          @6541 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_6541 = 30000.0f;
COMPILER_STRIP_GATE(0x807AFE68, &lit_6541);
#pragma pop

/* 807AD4A8-807AD7C0 006188 0318+00 7/0 0/0 0/0 .text            d_wait__8daE_SW_cFv */
void daE_SW_c::d_wait() {
    // NONMATCHING
}

/* 807AD7C0-807ADA08 0064A0 0248+00 1/1 0/0 0/0 .text            d_chaseCheck__8daE_SW_cFv */
void daE_SW_c::d_chaseCheck() {
    // NONMATCHING
}

/* 807ADA08-807ADE50 0066E8 0448+00 1/0 0/0 0/0 .text            d_chase__8daE_SW_cFv */
void daE_SW_c::d_chase() {
    // NONMATCHING
}

/* ############################################################################################## */
/* 807AFE6C-807AFE70 000140 0004+00 0/1 0/0 0/0 .rodata          @6852 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_6852 = 65.0f;
COMPILER_STRIP_GATE(0x807AFE6C, &lit_6852);
#pragma pop

/* 807ADE50-807AE4B4 006B30 0664+00 3/0 0/0 0/0 .text            d_attk__8daE_SW_cFv */
void daE_SW_c::d_attk() {
    // NONMATCHING
}

/* 807AE4B4-807AE7F4 007194 0340+00 5/0 0/0 0/0 .text            d_chance__8daE_SW_cFv */
void daE_SW_c::d_chance() {
    // NONMATCHING
}

/* 807AE7F4-807AE968 0074D4 0174+00 2/0 0/0 0/0 .text            d_chance2__8daE_SW_cFv */
void daE_SW_c::d_chance2() {
    // NONMATCHING
}

/* 807AE968-807AEB08 007648 01A0+00 1/0 0/0 0/0 .text            d_dive__8daE_SW_cFv */
void daE_SW_c::d_dive() {
    // NONMATCHING
}

/* 807AEB08-807AEE44 0077E8 033C+00 4/0 0/0 0/0 .text            d_damage__8daE_SW_cFv */
void daE_SW_c::d_damage() {
    // NONMATCHING
}

/* 807AEE44-807AF01C 007B24 01D8+00 2/0 0/0 0/0 .text            d_die__8daE_SW_cFv */
void daE_SW_c::d_die() {
    // NONMATCHING
}

/* 807AF01C-807AF46C 007CFC 0450+00 3/0 0/0 0/0 .text            d_hook__8daE_SW_cFv */
void daE_SW_c::d_hook() {
    // NONMATCHING
}

/* 807AF46C-807AF4B4 00814C 0048+00 1/0 0/0 0/0 .text            __dt__8cM3dGPlaFv */
// cM3dGPla::~cM3dGPla() {
extern "C" void __dt__8cM3dGPlaFv() {
    // NONMATCHING
}

/* 807AF4B4-807AF57C 008194 00C8+00 2/0 0/0 0/0 .text            d_fall__8daE_SW_cFv */
void daE_SW_c::d_fall() {
    // NONMATCHING
}

/* 807AF57C-807AF828 00825C 02AC+00 1/1 0/0 0/0 .text            d_execute__8daE_SW_cFv */
void daE_SW_c::d_execute() {
    // NONMATCHING
}

/* 807AF828-807AF870 008508 0048+00 1/0 0/0 0/0 .text            __dt__10cCcD_GSttsFv */
// cCcD_GStts::~cCcD_GStts() {
extern "C" void __dt__10cCcD_GSttsFv() {
    // NONMATCHING
}

/* 807AF870-807AF8B8 008550 0048+00 2/1 0/0 0/0 .text            __dt__12daE_SW_HIO_cFv */
daE_SW_HIO_c::~daE_SW_HIO_c() {
    // NONMATCHING
}

/* 807AF8B8-807AF8F4 008598 003C+00 0/0 1/0 0/0 .text            __sinit_d_a_e_sw_cpp */
void __sinit_d_a_e_sw_cpp() {
    // NONMATCHING
}

#pragma push
#pragma force_active on
REGISTER_CTORS(0x807AF8B8, __sinit_d_a_e_sw_cpp);
#pragma pop

/* 807AF8F4-807AF8FC 0085D4 0008+00 1/0 0/0 0/0 .text            @36@__dt__12dBgS_ObjAcchFv */
static void func_807AF8F4() {
    // NONMATCHING
}

/* 807AF8FC-807AF904 0085DC 0008+00 1/0 0/0 0/0 .text            @20@__dt__12dBgS_ObjAcchFv */
static void func_807AF8FC() {
    // NONMATCHING
}

/* ############################################################################################## */
/* 807B0234-807B0238 000084 0004+00 0/0 0/0 0/0 .bss
 * sInstance__40JASGlobalInstance<19JASDefaultBankTable>        */
#pragma push
#pragma force_active on
static u8 data_807B0234[4];
#pragma pop

/* 807B0238-807B023C 000088 0004+00 0/0 0/0 0/0 .bss
 * sInstance__35JASGlobalInstance<14JASAudioThread>             */
#pragma push
#pragma force_active on
static u8 data_807B0238[4];
#pragma pop

/* 807B023C-807B0240 00008C 0004+00 0/0 0/0 0/0 .bss sInstance__27JASGlobalInstance<7Z2SeMgr> */
#pragma push
#pragma force_active on
static u8 data_807B023C[4];
#pragma pop

/* 807B0240-807B0244 000090 0004+00 0/0 0/0 0/0 .bss sInstance__28JASGlobalInstance<8Z2SeqMgr> */
#pragma push
#pragma force_active on
static u8 data_807B0240[4];
#pragma pop

/* 807B0244-807B0248 000094 0004+00 0/0 0/0 0/0 .bss sInstance__31JASGlobalInstance<10Z2SceneMgr>
 */
#pragma push
#pragma force_active on
static u8 data_807B0244[4];
#pragma pop

/* 807B0248-807B024C 000098 0004+00 0/0 0/0 0/0 .bss sInstance__32JASGlobalInstance<11Z2StatusMgr>
 */
#pragma push
#pragma force_active on
static u8 data_807B0248[4];
#pragma pop

/* 807B024C-807B0250 00009C 0004+00 0/0 0/0 0/0 .bss sInstance__31JASGlobalInstance<10Z2DebugSys>
 */
#pragma push
#pragma force_active on
static u8 data_807B024C[4];
#pragma pop

/* 807B0250-807B0254 0000A0 0004+00 0/0 0/0 0/0 .bss
 * sInstance__36JASGlobalInstance<15JAISoundStarter>            */
#pragma push
#pragma force_active on
static u8 data_807B0250[4];
#pragma pop

/* 807B0254-807B0258 0000A4 0004+00 0/0 0/0 0/0 .bss
 * sInstance__35JASGlobalInstance<14Z2SoundStarter>             */
#pragma push
#pragma force_active on
static u8 data_807B0254[4];
#pragma pop

/* 807B0258-807B025C 0000A8 0004+00 0/0 0/0 0/0 .bss
 * sInstance__33JASGlobalInstance<12Z2SpeechMgr2>               */
#pragma push
#pragma force_active on
static u8 data_807B0258[4];
#pragma pop

/* 807B025C-807B0260 0000AC 0004+00 0/0 0/0 0/0 .bss sInstance__28JASGlobalInstance<8JAISeMgr> */
#pragma push
#pragma force_active on
static u8 data_807B025C[4];
#pragma pop

/* 807B0260-807B0264 0000B0 0004+00 0/0 0/0 0/0 .bss sInstance__29JASGlobalInstance<9JAISeqMgr> */
#pragma push
#pragma force_active on
static u8 data_807B0260[4];
#pragma pop

/* 807B0264-807B0268 0000B4 0004+00 0/0 0/0 0/0 .bss
 * sInstance__33JASGlobalInstance<12JAIStreamMgr>               */
#pragma push
#pragma force_active on
static u8 data_807B0264[4];
#pragma pop

/* 807B0268-807B026C 0000B8 0004+00 0/0 0/0 0/0 .bss sInstance__31JASGlobalInstance<10Z2SoundMgr>
 */
#pragma push
#pragma force_active on
static u8 data_807B0268[4];
#pragma pop

/* 807B026C-807B0270 0000BC 0004+00 0/0 0/0 0/0 .bss
 * sInstance__33JASGlobalInstance<12JAISoundInfo>               */
#pragma push
#pragma force_active on
static u8 data_807B026C[4];
#pragma pop

/* 807B0270-807B0274 0000C0 0004+00 0/0 0/0 0/0 .bss
 * sInstance__34JASGlobalInstance<13JAUSoundTable>              */
#pragma push
#pragma force_active on
static u8 data_807B0270[4];
#pragma pop

/* 807B0274-807B0278 0000C4 0004+00 0/0 0/0 0/0 .bss
 * sInstance__38JASGlobalInstance<17JAUSoundNameTable>          */
#pragma push
#pragma force_active on
static u8 data_807B0274[4];
#pragma pop

/* 807B0278-807B027C 0000C8 0004+00 0/0 0/0 0/0 .bss
 * sInstance__33JASGlobalInstance<12JAUSoundInfo>               */
#pragma push
#pragma force_active on
static u8 data_807B0278[4];
#pragma pop

/* 807B027C-807B0280 0000CC 0004+00 0/0 0/0 0/0 .bss sInstance__32JASGlobalInstance<11Z2SoundInfo>
 */
#pragma push
#pragma force_active on
static u8 data_807B027C[4];
#pragma pop

/* 807B0280-807B0284 0000D0 0004+00 0/0 0/0 0/0 .bss
 * sInstance__34JASGlobalInstance<13Z2SoundObjMgr>              */
#pragma push
#pragma force_active on
static u8 data_807B0280[4];
#pragma pop

/* 807B0284-807B0288 0000D4 0004+00 0/0 0/0 0/0 .bss sInstance__31JASGlobalInstance<10Z2Audience>
 */
#pragma push
#pragma force_active on
static u8 data_807B0284[4];
#pragma pop

/* 807B0288-807B028C 0000D8 0004+00 0/0 0/0 0/0 .bss sInstance__32JASGlobalInstance<11Z2FxLineMgr>
 */
#pragma push
#pragma force_active on
static u8 data_807B0288[4];
#pragma pop

/* 807B028C-807B0290 0000DC 0004+00 0/0 0/0 0/0 .bss sInstance__31JASGlobalInstance<10Z2EnvSeMgr>
 */
#pragma push
#pragma force_active on
static u8 data_807B028C[4];
#pragma pop

/* 807B0290-807B0294 0000E0 0004+00 0/0 0/0 0/0 .bss sInstance__32JASGlobalInstance<11Z2SpeechMgr>
 */
#pragma push
#pragma force_active on
static u8 data_807B0290[4];
#pragma pop

/* 807B0294-807B0298 0000E4 0004+00 0/0 0/0 0/0 .bss
 * sInstance__34JASGlobalInstance<13Z2WolfHowlMgr>              */
#pragma push
#pragma force_active on
static u8 data_807B0294[4];
#pragma pop

/* 807AFE70-807AFE70 000144 0000+00 0/0 0/0 0/0 .rodata          @stringBase0 */
