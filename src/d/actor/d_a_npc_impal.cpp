/**
 * @file d_a_npc_impal.cpp
 * 
*/

#include "d/actor/d_a_npc_impal.h"
#include "dol2asm.h"

//
// Forward References:
//

extern "C" void __ct__12daNpcImpal_cFv();
extern "C" void __dt__8cM3dGCylFv();
extern "C" void __dt__8cM3dGAabFv();
extern "C" void __dt__12daNpcImpal_cFv();
extern "C" void Create__12daNpcImpal_cFv();
extern "C" void CreateHeap__12daNpcImpal_cFv();
extern "C" void __dt__15J3DTevKColorAnmFv();
extern "C" void __ct__15J3DTevKColorAnmFv();
extern "C" void __dt__14J3DTevColorAnmFv();
extern "C" void __ct__14J3DTevColorAnmFv();
extern "C" void __dt__11J3DTexNoAnmFv();
extern "C" void __ct__11J3DTexNoAnmFv();
extern "C" void __dt__12J3DTexMtxAnmFv();
extern "C" void __ct__12J3DTexMtxAnmFv();
extern "C" void __dt__14J3DMatColorAnmFv();
extern "C" void __ct__14J3DMatColorAnmFv();
extern "C" void Delete__12daNpcImpal_cFv();
extern "C" void Execute__12daNpcImpal_cFv();
extern "C" void Draw__12daNpcImpal_cFv();
extern "C" void ctrlJoint__12daNpcImpal_cFP8J3DJointP8J3DModel();
extern "C" void createHeapCallBack__12daNpcImpal_cFP10fopAc_ac_c();
extern "C" void ctrlJointCallBack__12daNpcImpal_cFP8J3DJointi();
extern "C" void setExpressionAnm__12daNpcImpal_cFib();
extern "C" void setExpressionBtp__12daNpcImpal_cFi();
extern "C" void setMotionAnm__12daNpcImpal_cFif();
extern "C" void reset__12daNpcImpal_cFv();
extern "C" void setAction__12daNpcImpal_cFM12daNpcImpal_cFPCvPvPv_b();
extern "C" static void s_sub1__FPvPv();
extern "C" void wait__12daNpcImpal_cFPv();
extern "C" void setMotion__12daNpcImpal_cFifi();
extern "C" void setExpression__12daNpcImpal_cFif();
extern "C" void talk__12daNpcImpal_cFPv();
extern "C" void demo__12daNpcImpal_cFPv();
extern "C" void EvCut_ImpalAppear1__12daNpcImpal_cFi();
extern "C" void EvCut_ImpalAppear2__12daNpcImpal_cFi();
extern "C" void EvCut_CopyRod__12daNpcImpal_cFi();
extern "C" static void daNpcImpal_Create__FPv();
extern "C" static void daNpcImpal_Delete__FPv();
extern "C" static void daNpcImpal_Execute__FPv();
extern "C" static void daNpcImpal_Draw__FPv();
extern "C" static bool daNpcImpal_IsDelete__FPv();
extern "C" void calc__11J3DTexNoAnmCFPUs();
extern "C" void setParam__12daNpcImpal_cFv();
extern "C" void main__12daNpcImpal_cFv();
extern "C" void ctrlBtk__12daNpcImpal_cFv();
extern "C" void setAttnPos__12daNpcImpal_cFv();
extern "C" void lookat__12daNpcImpal_cFv();
extern "C" bool drawDbgInfo__12daNpcImpal_cFv();
extern "C" void func_80A0B954(void* _this, s16);
extern "C" void __sinit_d_a_npc_impal_cpp();
extern "C" void __dt__18daNpcF_ActorMngr_cFv();
extern "C" void __ct__18daNpcF_ActorMngr_cFv();
extern "C" void __dt__15daNpcF_Lookat_cFv();
extern "C" void __dt__5csXyzFv();
extern "C" void __ct__5csXyzFv();
extern "C" void __dt__4cXyzFv();
extern "C" void __ct__4cXyzFv();
extern "C" void __dt__8daNpcF_cFv();
extern "C" void __ct__8daNpcF_cFv();
extern "C" void __dt__12dBgS_AcchCirFv();
extern "C" void __dt__10dCcD_GSttsFv();
extern "C" void __dt__12dBgS_ObjAcchFv();
extern "C" void __dt__12J3DFrameCtrlFv();
extern "C" void adjustShapeAngle__8daNpcF_cFv();
extern "C" void setCollisions__8daNpcF_cFv();
extern "C" void drawOtherMdls__8daNpcF_cFv();
extern "C" void __dt__10cCcD_GSttsFv();
extern "C" void __dt__18daNpcImpal_Param_cFv();
extern "C" static void func_80A0C24C();
extern "C" static void func_80A0C254();
extern "C" u8 const m__18daNpcImpal_Param_c[112];
extern "C" extern char const* const d_a_npc_impal__stringBase0;
extern "C" u8 mEvtSeqList__12daNpcImpal_c[48];

//
// External References:
//

extern "C" void mDoMtx_YrotM__FPA4_fs();
extern "C" void transS__14mDoMtx_stack_cFRC4cXyz();
extern "C" void changeBckOnly__13mDoExt_bckAnmFP15J3DAnmTransform();
extern "C" void
__ct__16mDoExt_McaMorfSOFP12J3DModelDataP25mDoExt_McaMorfCallBack1_cP25mDoExt_McaMorfCallBack2_cP15J3DAnmTransformifiiP10Z2CreatureUlUl();
extern "C" void modelCalc__16mDoExt_McaMorfSOFv();
extern "C" void stopZelAnime__16mDoExt_McaMorfSOFv();
extern "C" void __ct__10fopAc_ac_cFv();
extern "C" void __dt__10fopAc_ac_cFv();
extern "C" void fopAc_IsActor__FPv();
extern "C" void fopAcM_delete__FP10fopAc_ac_c();
extern "C" void fopAcM_entrySolidHeap__FP10fopAc_ac_cPFP10fopAc_ac_c_iUl();
extern "C" void fopAcM_setCullSizeBox__FP10fopAc_ac_cffffff();
extern "C" void fopAcM_searchActorAngleY__FPC10fopAc_ac_cPC10fopAc_ac_c();
extern "C" void fopAcM_orderChangeEventId__FP10fopAc_ac_csUsUs();
extern "C" void fopAcM_createItemForPresentDemo__FPC4cXyziUciiPC5csXyzPC4cXyz();
extern "C" void gndCheck__11fopAcM_gc_cFPC4cXyz();
extern "C" void fpcEx_Search__FPFPvPv_PvPv();
extern "C" void dComIfG_resLoad__FP30request_of_phase_process_classPCc();
extern "C" void dComIfG_resDelete__FP30request_of_phase_process_classPCc();
extern "C" void isSwitch__12dSv_memBit_cCFi();
extern "C" void isSwitch__10dSv_info_cCFii();
extern "C" void getRes__14dRes_control_cFPCclP11dRes_info_ci();
extern "C" void reset__14dEvt_control_cFv();
extern "C" void reset__14dEvt_control_cFPv();
extern "C" void setPtI_Id__14dEvt_control_cFUi();
extern "C" void getEventIdx__16dEvent_manager_cFP10fopAc_ac_cPCcUc();
extern "C" void endCheck__16dEvent_manager_cFs();
extern "C" void getMyStaffId__16dEvent_manager_cFPCcP10fopAc_ac_ci();
extern "C" void getIsAddvance__16dEvent_manager_cFi();
extern "C" void getMyNowCutName__16dEvent_manager_cFi();
extern "C" void cutEnd__16dEvent_manager_cFi();
extern "C" void getRunEventName__16dEvent_manager_cFv();
extern "C" void ChkPresentEnd__16dEvent_manager_cFv();
extern "C" void __ct__12dBgS_AcchCirFv();
extern "C" void SetWallR__12dBgS_AcchCirFf();
extern "C" void SetWall__12dBgS_AcchCirFff();
extern "C" void __dt__9dBgS_AcchFv();
extern "C" void __ct__9dBgS_AcchFv();
extern "C" void Set__9dBgS_AcchFP4cXyzP4cXyzP10fopAc_ac_ciP12dBgS_AcchCirP4cXyzP5csXyzP5csXyz();
extern "C" void CrrPos__9dBgS_AcchFR4dBgS();
extern "C" void __ct__11dBgS_GndChkFv();
extern "C" void __dt__11dBgS_GndChkFv();
extern "C" void __ct__11dBgS_LinChkFv();
extern "C" void __dt__11dBgS_LinChkFv();
extern "C" void SetObj__16dBgS_PolyPassChkFv();
extern "C" void __ct__10dCcD_GSttsFv();
extern "C" void Init__9dCcD_SttsFiiP10fopAc_ac_c();
extern "C" void __ct__12dCcD_GObjInfFv();
extern "C" void __dt__12dCcD_GObjInfFv();
extern "C" void Set__8dCcD_CylFRC11dCcD_SrcCyl();
extern "C" void initialize__18daNpcF_ActorMngr_cFv();
extern "C" void entry__18daNpcF_ActorMngr_cFP10fopAc_ac_c();
extern "C" void remove__18daNpcF_ActorMngr_cFv();
extern "C" void getActorP__18daNpcF_ActorMngr_cFv();
extern "C" void initialize__15daNpcF_MatAnm_cFv();
extern "C" void initialize__15daNpcF_Lookat_cFv();
extern "C" void setParam__15daNpcF_Lookat_cFffffffffffffsP4cXyz();
extern "C" void calc__15daNpcF_Lookat_cFP10fopAc_ac_cPA4_fPP5csXyziii();
extern "C" void execute__8daNpcF_cFv();
extern "C" void draw__8daNpcF_cFiifP11_GXColorS10i();
extern "C" void setMtx__8daNpcF_cFv();
extern "C" void setMtx2__8daNpcF_cFv();
extern "C" void initialize__8daNpcF_cFv();
extern "C" void getTrnsfrmKeyAnmP__8daNpcF_cFPci();
extern "C" void getTexPtrnAnmP__8daNpcF_cFPci();
extern "C" void getTexSRTKeyAnmP__8daNpcF_cFPci();
extern "C" void setMcaMorfAnm__8daNpcF_cFP18J3DAnmTransformKeyffiii();
extern "C" void setBckAnm__8daNpcF_cFP15J3DAnmTransformfiiib();
extern "C" void setBtpAnm__8daNpcF_cFP16J3DAnmTexPatternP12J3DModelDatafi();
extern "C" void setBtkAnm__8daNpcF_cFP19J3DAnmTextureSRTKeyP12J3DModelDatafi();
extern "C" void setEnvTevColor__8daNpcF_cFv();
extern "C" void setRoomNo__8daNpcF_cFv();
extern "C" void playExpressionAnm__8daNpcF_cFPPPQ28daNpcF_c18daNpcF_anmPlayData();
extern "C" void playMotionAnm__8daNpcF_cFPPPQ28daNpcF_c18daNpcF_anmPlayData();
extern "C" void setLookatMtx__8daNpcF_cFiPif();
extern "C" void ctrlMsgAnm__8daNpcF_cFRiRiP10fopAc_ac_ci();
extern "C" void orderEvent__8daNpcF_cFiPcUsUsUcUs();
extern "C" void chkActorInSight__8daNpcF_cFP10fopAc_ac_cf();
extern "C" void chkActorInAttnArea__8daNpcF_cFP10fopAc_ac_cP10fopAc_ac_ci();
extern "C" void initTalk__8daNpcF_cFiPP10fopAc_ac_c();
extern "C" void talkProc__8daNpcF_cFPiiPP10fopAc_ac_c();
extern "C" void turn__8daNpcF_cFsfi();
extern "C" void setAngle__8daNpcF_cFs();
extern "C" void getDistTableIdx__8daNpcF_cFii();
extern "C" void daNpcF_chkEvtBit__FUl();
extern "C" void daNpcF_offTmpBit__FUl();
extern "C" void daNpcF_clearMessageTmpBit__Fv();
extern "C" void __ct__10dMsgFlow_cFv();
extern "C" void __dt__10dMsgFlow_cFv();
extern "C" void getEventId__10dMsgFlow_cFPi();
extern "C" void Set__4cCcSFP8cCcD_Obj();
extern "C" void __mi__4cXyzCFRC3Vec();
extern "C" void cM_atan2s__Fff();
extern "C" void __ct__11cBgS_GndChkFv();
extern "C" void __dt__11cBgS_GndChkFv();
extern "C" void __dt__13cBgS_PolyInfoFv();
extern "C" void __dt__8cM3dGCirFv();
extern "C" void SetC__8cM3dGCylFRC4cXyz();
extern "C" void SetH__8cM3dGCylFf();
extern "C" void SetR__8cM3dGCylFf();
extern "C" void cLib_targetAngleY__FPC3VecPC3Vec();
extern "C" void cLib_targetAngleX__FPC4cXyzPC4cXyz();
extern "C" void bgmStop__8Z2SeqMgrFUll();
extern "C" void bgmStreamPrepare__8Z2SeqMgrFUl();
extern "C" void bgmStreamPlay__8Z2SeqMgrFv();
extern "C" void bgmStreamStop__8Z2SeqMgrFUl();
extern "C" void __ct__10Z2CreatureFv();
extern "C" void __dt__10Z2CreatureFv();
extern "C" void init__10Z2CreatureFP3VecP3VecUcUc();
extern "C" void* __nw__FUl();
extern "C" void __dl__FPv();
extern "C" void init__12J3DFrameCtrlFs();
extern "C" void getTexNo__16J3DAnmTexPatternCFUsPUs();
extern "C" void initialize__14J3DMaterialAnmFv();
extern "C" void __destroy_arr();
extern "C" void __construct_array();
extern "C" void __ptmf_test();
extern "C" void __ptmf_scall();
extern "C" void _savegpr_26();
extern "C" void _savegpr_27();
extern "C" void _savegpr_28();
extern "C" void _savegpr_29();
extern "C" void _restgpr_26();
extern "C" void _restgpr_27();
extern "C" void _restgpr_28();
extern "C" void _restgpr_29();
extern "C" extern u8 const __ptmf_null[12 + 4 /* padding */];
extern "C" extern void* __vt__8dCcD_Cyl[36];
extern "C" extern void* __vt__9dCcD_Stts[11];
extern "C" u8 mCcDCyl__8daNpcF_c[68];
extern "C" extern void* __vt__8daNpcF_c[18];
extern "C" extern void* __vt__15daNpcF_MatAnm_c[4 + 6 /* padding */];
extern "C" extern void* __vt__12cCcD_CylAttr[25];
extern "C" extern void* __vt__14cCcD_ShapeAttr[22];
extern "C" extern void* __vt__9cCcD_Stts[8];
extern "C" extern void* __vt__14J3DMaterialAnm[4];
extern "C" u8 now__14mDoMtx_stack_c[48];
extern "C" u8 mCurrentMtx__6J3DSys[48];
extern "C" u8 sincosTable___5JMath[65536];
extern "C" f32 mGroundY__11fopAcM_gc_c;
extern "C" u8 mAudioMgrPtr__10Z2AudioMgr[4 + 4 /* padding */];
extern "C" void __register_global_object();

//
// Declarations:
//

/* ############################################################################################## */
/* 80A0C4C8-80A0C4C8 000258 0000+00 0/0 0/0 0/0 .rodata          @stringBase0 */
#pragma push
#pragma force_active on
SECTION_DEAD static char const* const stringBase_80A0C4C8 = "impal";
SECTION_DEAD static char const* const stringBase_80A0C4CE = "IMPAL_APPEAR1";
SECTION_DEAD static char const* const stringBase_80A0C4DC = "IMPAL_APPEAR2";
SECTION_DEAD static char const* const stringBase_80A0C4EA = "IMPAL_COPYROD";
#pragma pop

/* 80A0C524-80A0C530 000000 000C+00 4/4 0/0 0/0 .data            cNullVec__6Z2Calc */
SECTION_DATA static u8 cNullVec__6Z2Calc[12] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

/* 80A0C530-80A0C544 00000C 0004+10 0/0 0/0 0/0 .data            @1787 */
#pragma push
#pragma force_active on
SECTION_DATA static u32 lit_1787[1 + 4 /* padding */] = {
    0x02000201,
    /* padding */
    0x40080000,
    0x00000000,
    0x3FE00000,
    0x00000000,
};
#pragma pop

/* 80A0C544-80A0C61C 000020 00D8+00 1/2 0/0 0/0 .data            l_bckGetParamList */
SECTION_DATA static u8 l_bckGetParamList[216] = {
    0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0E,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x0B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0D,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x11, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10,
    0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00, 0x02,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x13, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x17, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x12,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x15, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09,
    0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00,
};

/* 80A0C61C-80A0C694 0000F8 0078+00 1/1 0/0 0/0 .data            l_btpGetParamList */
SECTION_DATA static u8 l_btpGetParamList[120] = {
    0x00, 0x00, 0x00, 0x23, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x29, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x25, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x24, 0x00, 0x00, 0x00, 0x02, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x26, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x27, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2A, 0x00, 0x00,
    0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2C, 0x00, 0x00, 0x00, 0x02, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2B, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00,
};

/* 80A0C694-80A0C6C4 000170 0030+00 1/2 0/0 0/0 .data            l_btkGetParamList */
SECTION_DATA static u8 l_btkGetParamList[48] = {
    0x00, 0x00, 0x00, 0x1D, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20,
    0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00,
};

/* 80A0C6C4-80A0C6C8 -00001 0004+00 6/7 0/0 0/0 .data            l_arcNames */
SECTION_DATA static void* l_arcNames = (void*)&d_a_npc_impal__stringBase0;

/* 80A0C6C8-80A0C6D8 -00001 0010+00 0/1 0/0 0/0 .data            l_evtNames */
#pragma push
#pragma force_active on
SECTION_DATA static void* l_evtNames[4] = {
    (void*)NULL,
    (void*)(((char*)&d_a_npc_impal__stringBase0) + 0x6),
    (void*)(((char*)&d_a_npc_impal__stringBase0) + 0x14),
    (void*)(((char*)&d_a_npc_impal__stringBase0) + 0x22),
};
#pragma pop

/* 80A0C6D8-80A0C6E4 0001B4 000C+00 2/2 0/0 0/0 .data            l_resetPos */
SECTION_DATA static u8 l_resetPos[12] = {
    0x45, 0x1E, 0x8C, 0x38, 0x42, 0xC7, 0xFB, 0xBB, 0xC4, 0x90, 0x47, 0x6B,
};

/* 80A0C6E4-80A0C6E8 -00001 0004+00 0/2 0/0 0/0 .data            l_myName */
#pragma push
#pragma force_active on
SECTION_DATA static void* l_myName = (void*)&d_a_npc_impal__stringBase0;
#pragma pop

/* 80A0C6E8-80A0C6F4 -00001 000C+00 0/1 0/0 0/0 .data            @3805 */
#pragma push
#pragma force_active on
SECTION_DATA static void* lit_3805[3] = {
    (void*)NULL,
    (void*)0xFFFFFFFF,
    (void*)EvCut_ImpalAppear1__12daNpcImpal_cFi,
};
#pragma pop

/* 80A0C6F4-80A0C700 -00001 000C+00 0/1 0/0 0/0 .data            @3806 */
#pragma push
#pragma force_active on
SECTION_DATA static void* lit_3806[3] = {
    (void*)NULL,
    (void*)0xFFFFFFFF,
    (void*)EvCut_ImpalAppear2__12daNpcImpal_cFi,
};
#pragma pop

/* 80A0C700-80A0C70C -00001 000C+00 0/1 0/0 0/0 .data            @3807 */
#pragma push
#pragma force_active on
SECTION_DATA static void* lit_3807[3] = {
    (void*)NULL,
    (void*)0xFFFFFFFF,
    (void*)EvCut_CopyRod__12daNpcImpal_cFi,
};
#pragma pop

/* 80A0C70C-80A0C73C 0001E8 0030+00 0/2 0/0 0/0 .data            mEvtSeqList__12daNpcImpal_c */
#pragma push
#pragma force_active on
SECTION_DATA u8 daNpcImpal_c::mEvtSeqList[48] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
#pragma pop

/* 80A0C73C-80A0C764 -00001 0028+00 1/1 0/0 0/0 .data            @4441 */
SECTION_DATA static void* lit_4441[10] = {
    (void*)(((char*)setExpressionAnm__12daNpcImpal_cFib) + 0xA0),
    (void*)(((char*)setExpressionAnm__12daNpcImpal_cFib) + 0xBC),
    (void*)(((char*)setExpressionAnm__12daNpcImpal_cFib) + 0xD8),
    (void*)(((char*)setExpressionAnm__12daNpcImpal_cFib) + 0xF4),
    (void*)(((char*)setExpressionAnm__12daNpcImpal_cFib) + 0x110),
    (void*)(((char*)setExpressionAnm__12daNpcImpal_cFib) + 0x12C),
    (void*)(((char*)setExpressionAnm__12daNpcImpal_cFib) + 0x148),
    (void*)(((char*)setExpressionAnm__12daNpcImpal_cFib) + 0x164),
    (void*)(((char*)setExpressionAnm__12daNpcImpal_cFib) + 0x180),
    (void*)(((char*)setExpressionAnm__12daNpcImpal_cFib) + 0x19C),
};

/* 80A0C764-80A0C770 -00001 000C+00 1/1 0/0 0/0 .data            @4498 */
SECTION_DATA static void* lit_4498[3] = {
    (void*)NULL,
    (void*)0xFFFFFFFF,
    (void*)wait__12daNpcImpal_cFPv,
};

/* 80A0C770-80A0C77C -00001 000C+00 0/1 0/0 0/0 .data            @4721 */
#pragma push
#pragma force_active on
SECTION_DATA static void* lit_4721[3] = {
    (void*)NULL,
    (void*)0xFFFFFFFF,
    (void*)talk__12daNpcImpal_cFPv,
};
#pragma pop

/* 80A0C77C-80A0C788 -00001 000C+00 0/1 0/0 0/0 .data            @4725 */
#pragma push
#pragma force_active on
SECTION_DATA static void* lit_4725[3] = {
    (void*)NULL,
    (void*)0xFFFFFFFF,
    (void*)talk__12daNpcImpal_cFPv,
};
#pragma pop

/* 80A0C788-80A0C794 -00001 000C+00 0/1 0/0 0/0 .data            @4730 */
#pragma push
#pragma force_active on
SECTION_DATA static void* lit_4730[3] = {
    (void*)NULL,
    (void*)0xFFFFFFFF,
    (void*)demo__12daNpcImpal_cFPv,
};
#pragma pop

/* 80A0C794-80A0C7A0 -00001 000C+00 1/1 0/0 0/0 .data            @4917 */
SECTION_DATA static void* lit_4917[3] = {
    (void*)NULL,
    (void*)0xFFFFFFFF,
    (void*)wait__12daNpcImpal_cFPv,
};

/* 80A0C7A0-80A0C7AC -00001 000C+00 0/1 0/0 0/0 .data            @5000 */
#pragma push
#pragma force_active on
SECTION_DATA static void* lit_5000[3] = {
    (void*)NULL,
    (void*)0xFFFFFFFF,
    (void*)wait__12daNpcImpal_cFPv,
};
#pragma pop

/* 80A0C7AC-80A0C7B8 -00001 000C+00 0/1 0/0 0/0 .data            @5003 */
#pragma push
#pragma force_active on
SECTION_DATA static void* lit_5003[3] = {
    (void*)NULL,
    (void*)0xFFFFFFFF,
    (void*)wait__12daNpcImpal_cFPv,
};
#pragma pop

/* 80A0C7B8-80A0C7D8 -00001 0020+00 1/0 0/0 0/0 .data            daNpcImpal_MethodTable */
static actor_method_class daNpcImpal_MethodTable = {
    (process_method_func)daNpcImpal_Create__FPv,
    (process_method_func)daNpcImpal_Delete__FPv,
    (process_method_func)daNpcImpal_Execute__FPv,
    (process_method_func)daNpcImpal_IsDelete__FPv,
    (process_method_func)daNpcImpal_Draw__FPv,
};

/* 80A0C7D8-80A0C808 -00001 0030+00 0/0 0/0 1/0 .data            g_profile_NPC_IMPAL */
extern actor_process_profile_definition g_profile_NPC_IMPAL = {
  fpcLy_CURRENT_e,         // mLayerID
  7,                       // mListID
  fpcPi_CURRENT_e,         // mListPrio
  PROC_NPC_IMPAL,          // mProcName
  &g_fpcLf_Method.base,   // sub_method
  sizeof(daNpcImpal_c),    // mSize
  0,                       // mSizeOther
  0,                       // mParameters
  &g_fopAc_Method.base,    // sub_method
  416,                     // mPriority
  &daNpcImpal_MethodTable, // sub_method
  0x00040100,              // mStatus
  fopAc_NPC_e,             // mActorType
  fopAc_CULLBOX_CUSTOM_e,  // cullType
};

/* 80A0C808-80A0C814 0002E4 000C+00 2/2 0/0 0/0 .data            __vt__11J3DTexNoAnm */
SECTION_DATA extern void* __vt__11J3DTexNoAnm[3] = {
    (void*)NULL /* RTTI */,
    (void*)NULL,
    (void*)calc__11J3DTexNoAnmCFPUs,
};

/* 80A0C814-80A0C85C 0002F0 0048+00 2/2 0/0 0/0 .data            __vt__12daNpcImpal_c */
SECTION_DATA extern void* __vt__12daNpcImpal_c[18] = {
    (void*)NULL /* RTTI */,
    (void*)NULL,
    (void*)__dt__12daNpcImpal_cFv,
    (void*)setParam__12daNpcImpal_cFv,
    (void*)main__12daNpcImpal_cFv,
    (void*)ctrlBtk__12daNpcImpal_cFv,
    (void*)adjustShapeAngle__8daNpcF_cFv,
    (void*)setMtx__8daNpcF_cFv,
    (void*)setMtx2__8daNpcF_cFv,
    (void*)setAttnPos__12daNpcImpal_cFv,
    (void*)setCollisions__8daNpcF_cFv,
    (void*)setExpressionAnm__12daNpcImpal_cFib,
    (void*)setExpressionBtp__12daNpcImpal_cFi,
    (void*)setExpression__12daNpcImpal_cFif,
    (void*)setMotionAnm__12daNpcImpal_cFif,
    (void*)setMotion__12daNpcImpal_cFifi,
    (void*)drawDbgInfo__12daNpcImpal_cFv,
    (void*)drawOtherMdls__8daNpcF_cFv,
};

/* 80A0C85C-80A0C868 000338 000C+00 3/3 0/0 0/0 .data            __vt__12J3DFrameCtrl */
SECTION_DATA extern void* __vt__12J3DFrameCtrl[3] = {
    (void*)NULL /* RTTI */,
    (void*)NULL,
    (void*)__dt__12J3DFrameCtrlFv,
};

/* 80A0C868-80A0C88C 000344 0024+00 3/3 0/0 0/0 .data            __vt__12dBgS_ObjAcch */
SECTION_DATA extern void* __vt__12dBgS_ObjAcch[9] = {
    (void*)NULL /* RTTI */,
    (void*)NULL,
    (void*)__dt__12dBgS_ObjAcchFv,
    (void*)NULL,
    (void*)NULL,
    (void*)func_80A0C254,
    (void*)NULL,
    (void*)NULL,
    (void*)func_80A0C24C,
};

/* 80A0C88C-80A0C898 000368 000C+00 3/3 0/0 0/0 .data            __vt__10cCcD_GStts */
SECTION_DATA extern void* __vt__10cCcD_GStts[3] = {
    (void*)NULL /* RTTI */,
    (void*)NULL,
    (void*)__dt__10cCcD_GSttsFv,
};

/* 80A0C898-80A0C8A4 000374 000C+00 2/2 0/0 0/0 .data            __vt__10dCcD_GStts */
SECTION_DATA extern void* __vt__10dCcD_GStts[3] = {
    (void*)NULL /* RTTI */,
    (void*)NULL,
    (void*)__dt__10dCcD_GSttsFv,
};

/* 80A0C8A4-80A0C8B0 000380 000C+00 2/2 0/0 0/0 .data            __vt__12dBgS_AcchCir */
SECTION_DATA extern void* __vt__12dBgS_AcchCir[3] = {
    (void*)NULL /* RTTI */,
    (void*)NULL,
    (void*)__dt__12dBgS_AcchCirFv,
};

/* 80A0C8B0-80A0C8BC 00038C 000C+00 4/4 0/0 0/0 .data            __vt__18daNpcF_ActorMngr_c */
SECTION_DATA extern void* __vt__18daNpcF_ActorMngr_c[3] = {
    (void*)NULL /* RTTI */,
    (void*)NULL,
    (void*)__dt__18daNpcF_ActorMngr_cFv,
};

/* 80A0C8BC-80A0C8C8 000398 000C+00 3/3 0/0 0/0 .data            __vt__8cM3dGCyl */
SECTION_DATA extern void* __vt__8cM3dGCyl[3] = {
    (void*)NULL /* RTTI */,
    (void*)NULL,
    (void*)__dt__8cM3dGCylFv,
};

/* 80A0C8C8-80A0C8D4 0003A4 000C+00 3/3 0/0 0/0 .data            __vt__8cM3dGAab */
SECTION_DATA extern void* __vt__8cM3dGAab[3] = {
    (void*)NULL /* RTTI */,
    (void*)NULL,
    (void*)__dt__8cM3dGAabFv,
};

/* 80A0C8D4-80A0C8E0 0003B0 000C+00 3/3 0/0 0/0 .data            __vt__15daNpcF_Lookat_c */
SECTION_DATA extern void* __vt__15daNpcF_Lookat_c[3] = {
    (void*)NULL /* RTTI */,
    (void*)NULL,
    (void*)__dt__15daNpcF_Lookat_cFv,
};

/* 80A079EC-80A07B70 0000EC 0184+00 1/1 0/0 0/0 .text            __ct__12daNpcImpal_cFv */
daNpcImpal_c::daNpcImpal_c() {
    // NONMATCHING
}

/* 80A07B70-80A07BB8 000270 0048+00 1/0 0/0 0/0 .text            __dt__8cM3dGCylFv */
// cM3dGCyl::~cM3dGCyl() {
extern "C" void __dt__8cM3dGCylFv() {
    // NONMATCHING
}

/* 80A07BB8-80A07C00 0002B8 0048+00 1/0 0/0 0/0 .text            __dt__8cM3dGAabFv */
// cM3dGAab::~cM3dGAab() {
extern "C" void __dt__8cM3dGAabFv() {
    // NONMATCHING
}

/* 80A07C00-80A07DC4 000300 01C4+00 1/0 0/0 0/0 .text            __dt__12daNpcImpal_cFv */
daNpcImpal_c::~daNpcImpal_c() {
    // NONMATCHING
}

/* ############################################################################################## */
/* 80A0C270-80A0C2E0 000000 0070+00 12/12 0/0 0/0 .rodata          m__18daNpcImpal_Param_c */
SECTION_RODATA u8 const daNpcImpal_Param_c::m[112] = {
    0x43, 0x07, 0x00, 0x00, 0xC0, 0x40, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x44, 0x0C, 0x00, 0x00,
    0x43, 0x7F, 0x00, 0x00, 0x43, 0x02, 0x00, 0x00, 0x42, 0x0C, 0x00, 0x00, 0x41, 0xF0, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x41, 0x20, 0x00, 0x00, 0xC1, 0x20, 0x00, 0x00,
    0x41, 0xF0, 0x00, 0x00, 0xC1, 0x20, 0x00, 0x00, 0x42, 0x34, 0x00, 0x00, 0xC2, 0x34, 0x00, 0x00,
    0x3F, 0x19, 0x99, 0x9A, 0x41, 0xA0, 0x00, 0x00, 0x00, 0x03, 0x00, 0x06, 0x00, 0x05, 0x00, 0x06,
    0x42, 0xA0, 0x00, 0x00, 0x43, 0xFA, 0x00, 0x00, 0x43, 0x96, 0x00, 0x00, 0xC3, 0x96, 0x00, 0x00,
    0x00, 0x3C, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x43, 0x96, 0x00, 0x00,
};
COMPILER_STRIP_GATE(0x80A0C270, &daNpcImpal_Param_c::m);

/* 80A0C2E0-80A0C2E4 000070 0004+00 0/1 0/0 0/0 .rodata          @4196 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_4196 = -160.0f;
COMPILER_STRIP_GATE(0x80A0C2E0, &lit_4196);
#pragma pop

/* 80A0C2E4-80A0C2E8 000074 0004+00 0/1 0/0 0/0 .rodata          @4197 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_4197 = -50.0f;
COMPILER_STRIP_GATE(0x80A0C2E4, &lit_4197);
#pragma pop

/* 80A0C2E8-80A0C2EC 000078 0004+00 0/1 0/0 0/0 .rodata          @4198 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_4198 = 160.0f;
COMPILER_STRIP_GATE(0x80A0C2E8, &lit_4198);
#pragma pop

/* 80A0C2EC-80A0C2F0 00007C 0004+00 0/1 0/0 0/0 .rodata          @4199 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_4199 = 220.0f;
COMPILER_STRIP_GATE(0x80A0C2EC, &lit_4199);
#pragma pop

/* 80A0C4C8-80A0C4C8 000258 0000+00 0/0 0/0 0/0 .rodata          @stringBase0 */
#pragma push
#pragma force_active on
SECTION_DEAD static char const* const stringBase_80A0C4F8 = "F_SP128";
SECTION_DEAD static char const* const stringBase_80A0C500 = "R_SP128";
#pragma pop

/* 80A07DC4-80A080F8 0004C4 0334+00 1/1 0/0 0/0 .text            Create__12daNpcImpal_cFv */
void daNpcImpal_c::Create() {
    // NONMATCHING
}

/* ############################################################################################## */
/* 80A0C2F0-80A0C2F4 000080 0004+00 4/4 0/0 0/0 .rodata          @4248 */
SECTION_RODATA static f32 const lit_4248 = 1.0f;
COMPILER_STRIP_GATE(0x80A0C2F0, &lit_4248);

/* 80A0C2F4-80A0C2F8 000084 0004+00 2/8 0/0 0/0 .rodata          @4249 */
SECTION_RODATA static u8 const lit_4249[4] = {
    0x00,
    0x00,
    0x00,
    0x00,
};
COMPILER_STRIP_GATE(0x80A0C2F4, &lit_4249);

/* 80A080F8-80A08368 0007F8 0270+00 1/1 0/0 0/0 .text            CreateHeap__12daNpcImpal_cFv */
void daNpcImpal_c::CreateHeap() {
    // NONMATCHING
}

/* 80A08368-80A083A4 000A68 003C+00 1/1 0/0 0/0 .text            __dt__15J3DTevKColorAnmFv */
// J3DTevKColorAnm::~J3DTevKColorAnm() {
extern "C" void __dt__15J3DTevKColorAnmFv() {
    // NONMATCHING
}

/* 80A083A4-80A083BC 000AA4 0018+00 1/1 0/0 0/0 .text            __ct__15J3DTevKColorAnmFv */
// J3DTevKColorAnm::J3DTevKColorAnm() {
extern "C" void __ct__15J3DTevKColorAnmFv() {
    // NONMATCHING
}

/* 80A083BC-80A083F8 000ABC 003C+00 1/1 0/0 0/0 .text            __dt__14J3DTevColorAnmFv */
// J3DTevColorAnm::~J3DTevColorAnm() {
extern "C" void __dt__14J3DTevColorAnmFv() {
    // NONMATCHING
}

/* 80A083F8-80A08410 000AF8 0018+00 1/1 0/0 0/0 .text            __ct__14J3DTevColorAnmFv */
// J3DTevColorAnm::J3DTevColorAnm() {
extern "C" void __ct__14J3DTevColorAnmFv() {
    // NONMATCHING
}

/* 80A08410-80A08458 000B10 0048+00 1/1 0/0 0/0 .text            __dt__11J3DTexNoAnmFv */
// J3DTexNoAnm::~J3DTexNoAnm() {
extern "C" void __dt__11J3DTexNoAnmFv() {
    // NONMATCHING
}

/* 80A08458-80A0847C 000B58 0024+00 1/1 0/0 0/0 .text            __ct__11J3DTexNoAnmFv */
// J3DTexNoAnm::J3DTexNoAnm() {
extern "C" void __ct__11J3DTexNoAnmFv() {
    // NONMATCHING
}

/* 80A0847C-80A084B8 000B7C 003C+00 1/1 0/0 0/0 .text            __dt__12J3DTexMtxAnmFv */
// J3DTexMtxAnm::~J3DTexMtxAnm() {
extern "C" void __dt__12J3DTexMtxAnmFv() {
    // NONMATCHING
}

/* 80A084B8-80A084D0 000BB8 0018+00 1/1 0/0 0/0 .text            __ct__12J3DTexMtxAnmFv */
// J3DTexMtxAnm::J3DTexMtxAnm() {
extern "C" void __ct__12J3DTexMtxAnmFv() {
    // NONMATCHING
}

/* 80A084D0-80A0850C 000BD0 003C+00 1/1 0/0 0/0 .text            __dt__14J3DMatColorAnmFv */
// J3DMatColorAnm::~J3DMatColorAnm() {
extern "C" void __dt__14J3DMatColorAnmFv() {
    // NONMATCHING
}

/* 80A0850C-80A08524 000C0C 0018+00 1/1 0/0 0/0 .text            __ct__14J3DMatColorAnmFv */
// J3DMatColorAnm::J3DMatColorAnm() {
extern "C" void __ct__14J3DMatColorAnmFv() {
    // NONMATCHING
}

/* 80A08524-80A08558 000C24 0034+00 1/1 0/0 0/0 .text            Delete__12daNpcImpal_cFv */
void daNpcImpal_c::Delete() {
    // NONMATCHING
}

/* 80A08558-80A0857C 000C58 0024+00 2/2 0/0 0/0 .text            Execute__12daNpcImpal_cFv */
void daNpcImpal_c::Execute() {
    // NONMATCHING
}

/* 80A0857C-80A085EC 000C7C 0070+00 1/1 0/0 0/0 .text            Draw__12daNpcImpal_cFv */
void daNpcImpal_c::Draw() {
    // NONMATCHING
}

/* ############################################################################################## */
/* 80A0C2F8-80A0C304 000088 000C+00 1/1 0/0 0/0 .rodata          @4299 */
SECTION_RODATA static u8 const lit_4299[12] = {
    0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x04,
};
COMPILER_STRIP_GATE(0x80A0C2F8, &lit_4299);

/* 80A085EC-80A087BC 000CEC 01D0+00 1/1 0/0 0/0 .text
 * ctrlJoint__12daNpcImpal_cFP8J3DJointP8J3DModel               */
void daNpcImpal_c::ctrlJoint(J3DJoint* param_0, J3DModel* param_1) {
    // NONMATCHING
}

/* 80A087BC-80A087DC 000EBC 0020+00 1/1 0/0 0/0 .text
 * createHeapCallBack__12daNpcImpal_cFP10fopAc_ac_c             */
void daNpcImpal_c::createHeapCallBack(fopAc_ac_c* param_0) {
    // NONMATCHING
}

/* 80A087DC-80A08828 000EDC 004C+00 1/1 0/0 0/0 .text
 * ctrlJointCallBack__12daNpcImpal_cFP8J3DJointi                */
void daNpcImpal_c::ctrlJointCallBack(J3DJoint* param_0, int param_1) {
    // NONMATCHING
}

/* 80A08828-80A08A68 000F28 0240+00 2/0 0/0 0/0 .text            setExpressionAnm__12daNpcImpal_cFib
 */
void daNpcImpal_c::setExpressionAnm(int param_0, bool param_1) {
    // NONMATCHING
}

/* 80A08A68-80A08B48 001168 00E0+00 1/0 0/0 0/0 .text            setExpressionBtp__12daNpcImpal_cFi
 */
void daNpcImpal_c::setExpressionBtp(int param_0) {
    // NONMATCHING
}

/* 80A08B48-80A08CBC 001248 0174+00 1/0 0/0 0/0 .text            setMotionAnm__12daNpcImpal_cFif */
bool daNpcImpal_c::setMotionAnm(int param_0, f32 param_1) {
    // NONMATCHING
}

/* 80A08CBC-80A08EB8 0013BC 01FC+00 1/1 0/0 0/0 .text            reset__12daNpcImpal_cFv */
void daNpcImpal_c::reset() {
    // NONMATCHING
}

/* 80A08EB8-80A08F60 0015B8 00A8+00 1/1 0/0 0/0 .text
 * setAction__12daNpcImpal_cFM12daNpcImpal_cFPCvPvPv_b          */
void daNpcImpal_c::setAction(bool (daNpcImpal_c::*param_0)(void*)) {
    // NONMATCHING
}

/* ############################################################################################## */
/* 80A0C304-80A0C310 000094 000C+00 0/1 0/0 0/0 .rodata          @4538 */
#pragma push
#pragma force_active on
SECTION_RODATA static u8 const lit_4538[12] = {
    0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
};
COMPILER_STRIP_GATE(0x80A0C304, &lit_4538);
#pragma pop

/* 80A0C310-80A0C314 0000A0 0004+00 0/1 0/0 0/0 .rodata          @4539 */
#pragma push
#pragma force_active on
SECTION_RODATA static u8 const lit_4539[4] = {
    0x00,
    0x00,
    0x00,
    0x00,
};
COMPILER_STRIP_GATE(0x80A0C310, &lit_4539);
#pragma pop

/* 80A0C314-80A0C320 0000A4 000C+00 0/1 0/0 0/0 .rodata          @4540 */
#pragma push
#pragma force_active on
SECTION_RODATA static u8 const lit_4540[12] = {
    0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
};
COMPILER_STRIP_GATE(0x80A0C314, &lit_4540);
#pragma pop

/* 80A0C320-80A0C324 0000B0 0004+00 0/1 0/0 0/0 .rodata          @4541 */
#pragma push
#pragma force_active on
SECTION_RODATA static u8 const lit_4541[4] = {
    0x00,
    0x00,
    0x00,
    0x00,
};
COMPILER_STRIP_GATE(0x80A0C320, &lit_4541);
#pragma pop

/* 80A0C324-80A0C330 0000B4 000C+00 0/1 0/0 0/0 .rodata          @4542 */
#pragma push
#pragma force_active on
SECTION_RODATA static u8 const lit_4542[12] = {
    0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
};
COMPILER_STRIP_GATE(0x80A0C324, &lit_4542);
#pragma pop

/* 80A0C330-80A0C334 0000C0 0004+00 0/1 0/0 0/0 .rodata          @4543 */
#pragma push
#pragma force_active on
SECTION_RODATA static u8 const lit_4543[4] = {
    0x00,
    0x00,
    0x00,
    0x00,
};
COMPILER_STRIP_GATE(0x80A0C330, &lit_4543);
#pragma pop

/* 80A0C334-80A0C340 0000C4 000C+00 0/1 0/0 0/0 .rodata          @4544 */
#pragma push
#pragma force_active on
SECTION_RODATA static u8 const lit_4544[12] = {
    0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
};
COMPILER_STRIP_GATE(0x80A0C334, &lit_4544);
#pragma pop

/* 80A0C340-80A0C344 0000D0 0004+00 0/1 0/0 0/0 .rodata          @4545 */
#pragma push
#pragma force_active on
SECTION_RODATA static u8 const lit_4545[4] = {
    0x00,
    0x00,
    0x00,
    0x00,
};
COMPILER_STRIP_GATE(0x80A0C340, &lit_4545);
#pragma pop

/* 80A0C344-80A0C350 0000D4 000C+00 0/1 0/0 0/0 .rodata          @4546 */
#pragma push
#pragma force_active on
SECTION_RODATA static u8 const lit_4546[12] = {
    0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
COMPILER_STRIP_GATE(0x80A0C344, &lit_4546);
#pragma pop

/* 80A0C350-80A0C354 0000E0 0004+00 0/1 0/0 0/0 .rodata          @4547 */
#pragma push
#pragma force_active on
SECTION_RODATA static u8 const lit_4547[4] = {
    0x00,
    0x00,
    0x00,
    0x00,
};
COMPILER_STRIP_GATE(0x80A0C350, &lit_4547);
#pragma pop

/* 80A0C354-80A0C360 0000E4 000C+00 0/1 0/0 0/0 .rodata          @4548 */
#pragma push
#pragma force_active on
SECTION_RODATA static u8 const lit_4548[12] = {
    0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
COMPILER_STRIP_GATE(0x80A0C354, &lit_4548);
#pragma pop

/* 80A0C360-80A0C364 0000F0 0004+00 0/1 0/0 0/0 .rodata          @4549 */
#pragma push
#pragma force_active on
SECTION_RODATA static u8 const lit_4549[4] = {
    0x00,
    0x00,
    0x00,
    0x00,
};
COMPILER_STRIP_GATE(0x80A0C360, &lit_4549);
#pragma pop

/* 80A0C364-80A0C370 0000F4 000C+00 0/1 0/0 0/0 .rodata          @4550 */
#pragma push
#pragma force_active on
SECTION_RODATA static u8 const lit_4550[12] = {
    0x00, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
COMPILER_STRIP_GATE(0x80A0C364, &lit_4550);
#pragma pop

/* 80A0C370-80A0C374 000100 0004+00 0/1 0/0 0/0 .rodata          @4551 */
#pragma push
#pragma force_active on
SECTION_RODATA static u8 const lit_4551[4] = {
    0x00,
    0x00,
    0x00,
    0x00,
};
COMPILER_STRIP_GATE(0x80A0C370, &lit_4551);
#pragma pop

/* 80A0C374-80A0C380 000104 000C+00 0/1 0/0 0/0 .rodata          @4552 */
#pragma push
#pragma force_active on
SECTION_RODATA static u8 const lit_4552[12] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
COMPILER_STRIP_GATE(0x80A0C374, &lit_4552);
#pragma pop

/* 80A0C380-80A0C384 000110 0004+00 0/1 0/0 0/0 .rodata          @4553 */
#pragma push
#pragma force_active on
SECTION_RODATA static u8 const lit_4553[4] = {
    0x00,
    0x00,
    0x00,
    0x00,
};
COMPILER_STRIP_GATE(0x80A0C380, &lit_4553);
#pragma pop

/* 80A0C384-80A0C3A4 000114 0020+00 0/0 0/0 0/0 .rodata          @4554 */
#pragma push
#pragma force_active on
SECTION_RODATA static u8 const lit_4554[32] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
COMPILER_STRIP_GATE(0x80A0C384, &lit_4554);
#pragma pop

/* 80A0C3A4-80A0C3B0 000134 000C+00 0/1 0/0 0/0 .rodata          @4558 */
#pragma push
#pragma force_active on
SECTION_RODATA static u8 const lit_4558[12] = {
    0x00, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
COMPILER_STRIP_GATE(0x80A0C3A4, &lit_4558);
#pragma pop

/* 80A0C3B0-80A0C3B4 000140 0004+00 0/1 0/0 0/0 .rodata          @4559 */
#pragma push
#pragma force_active on
SECTION_RODATA static u8 const lit_4559[4] = {
    0x00,
    0x00,
    0x00,
    0x00,
};
COMPILER_STRIP_GATE(0x80A0C3B0, &lit_4559);
#pragma pop

/* 80A0C3B4-80A0C3C0 000144 000C+00 0/1 0/0 0/0 .rodata          @4560 */
#pragma push
#pragma force_active on
SECTION_RODATA static u8 const lit_4560[12] = {
    0x00, 0x0D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
};
COMPILER_STRIP_GATE(0x80A0C3B4, &lit_4560);
#pragma pop

/* 80A0C3C0-80A0C3CC 000150 000C+00 0/1 0/0 0/0 .rodata          @4561 */
#pragma push
#pragma force_active on
SECTION_RODATA static u8 const lit_4561[12] = {
    0x00, 0x0B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
COMPILER_STRIP_GATE(0x80A0C3C0, &lit_4561);
#pragma pop

/* 80A0C3CC-80A0C3D4 00015C 0008+00 0/1 0/0 0/0 .rodata          @4562 */
#pragma push
#pragma force_active on
SECTION_RODATA static u8 const lit_4562[8] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
COMPILER_STRIP_GATE(0x80A0C3CC, &lit_4562);
#pragma pop

/* 80A0C3D4-80A0C3E0 000164 000C+00 0/1 0/0 0/0 .rodata          @4563 */
#pragma push
#pragma force_active on
SECTION_RODATA static u8 const lit_4563[12] = {
    0x00, 0x0B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
COMPILER_STRIP_GATE(0x80A0C3D4, &lit_4563);
#pragma pop

/* 80A0C3E0-80A0C3E4 000170 0004+00 0/1 0/0 0/0 .rodata          @4564 */
#pragma push
#pragma force_active on
SECTION_RODATA static u8 const lit_4564[4] = {
    0x00,
    0x00,
    0x00,
    0x00,
};
COMPILER_STRIP_GATE(0x80A0C3E0, &lit_4564);
#pragma pop

/* 80A0C3E4-80A0C3F0 000174 000C+00 0/1 0/0 0/0 .rodata          @4565 */
#pragma push
#pragma force_active on
SECTION_RODATA static u8 const lit_4565[12] = {
    0x00, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
COMPILER_STRIP_GATE(0x80A0C3E4, &lit_4565);
#pragma pop

/* 80A0C3F0-80A0C3F4 000180 0004+00 0/1 0/0 0/0 .rodata          @4566 */
#pragma push
#pragma force_active on
SECTION_RODATA static u8 const lit_4566[4] = {
    0x00,
    0x00,
    0x00,
    0x00,
};
COMPILER_STRIP_GATE(0x80A0C3F0, &lit_4566);
#pragma pop

/* 80A0C3F4-80A0C400 000184 000C+00 0/1 0/0 0/0 .rodata          @4567 */
#pragma push
#pragma force_active on
SECTION_RODATA static u8 const lit_4567[12] = {
    0x00, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
};
COMPILER_STRIP_GATE(0x80A0C3F4, &lit_4567);
#pragma pop

/* 80A0C400-80A0C40C 000190 000C+00 0/1 0/0 0/0 .rodata          @4568 */
#pragma push
#pragma force_active on
SECTION_RODATA static u8 const lit_4568[12] = {
    0x00, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
COMPILER_STRIP_GATE(0x80A0C400, &lit_4568);
#pragma pop

/* 80A0C40C-80A0C414 00019C 0008+00 0/1 0/0 0/0 .rodata          @4569 */
#pragma push
#pragma force_active on
SECTION_RODATA static u8 const lit_4569[8] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
COMPILER_STRIP_GATE(0x80A0C40C, &lit_4569);
#pragma pop

/* 80A0C414-80A0C420 0001A4 000C+00 0/1 0/0 0/0 .rodata          @4570 */
#pragma push
#pragma force_active on
SECTION_RODATA static u8 const lit_4570[12] = {
    0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
};
COMPILER_STRIP_GATE(0x80A0C414, &lit_4570);
#pragma pop

/* 80A0C420-80A0C42C 0001B0 000C+00 0/1 0/0 0/0 .rodata          @4571 */
#pragma push
#pragma force_active on
SECTION_RODATA static u8 const lit_4571[12] = {
    0x00, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
COMPILER_STRIP_GATE(0x80A0C420, &lit_4571);
#pragma pop

/* 80A0C42C-80A0C434 0001BC 0008+00 0/1 0/0 0/0 .rodata          @4572 */
#pragma push
#pragma force_active on
SECTION_RODATA static u8 const lit_4572[8] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
COMPILER_STRIP_GATE(0x80A0C42C, &lit_4572);
#pragma pop

/* 80A0C434-80A0C440 0001C4 000C+00 0/1 0/0 0/0 .rodata          @4573 */
#pragma push
#pragma force_active on
SECTION_RODATA static u8 const lit_4573[12] = {
    0x00, 0x0F, 0x00, 0x00, 0x40, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
COMPILER_STRIP_GATE(0x80A0C434, &lit_4573);
#pragma pop

/* 80A0C440-80A0C444 0001D0 0004+00 0/1 0/0 0/0 .rodata          @4574 */
#pragma push
#pragma force_active on
SECTION_RODATA static u8 const lit_4574[4] = {
    0x00,
    0x00,
    0x00,
    0x00,
};
COMPILER_STRIP_GATE(0x80A0C440, &lit_4574);
#pragma pop

/* 80A0C444-80A0C460 0001D4 001C+00 0/0 0/0 0/0 .rodata          @4575 */
#pragma push
#pragma force_active on
SECTION_RODATA static u8 const lit_4575[28] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
COMPILER_STRIP_GATE(0x80A0C444, &lit_4575);
#pragma pop

/* 80A0C460-80A0C470 0001F0 000C+04 0/1 0/0 0/0 .rodata          @4589 */
#pragma push
#pragma force_active on
SECTION_RODATA static u8 const lit_4589[12 + 4 /* padding */] = {
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    /* padding */
    0x00,
    0x00,
    0x00,
    0x00,
};
COMPILER_STRIP_GATE(0x80A0C460, &lit_4589);
#pragma pop

/* 80A0C470-80A0C478 000200 0008+00 0/3 0/0 0/0 .rodata          @4678 */
#pragma push
#pragma force_active on
SECTION_RODATA static u8 const lit_4678[8] = {
    0x3F, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
COMPILER_STRIP_GATE(0x80A0C470, &lit_4678);
#pragma pop

/* 80A0C478-80A0C480 000208 0008+00 0/3 0/0 0/0 .rodata          @4679 */
#pragma push
#pragma force_active on
SECTION_RODATA static u8 const lit_4679[8] = {
    0x40, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
COMPILER_STRIP_GATE(0x80A0C478, &lit_4679);
#pragma pop

/* 80A0C480-80A0C488 000210 0008+00 0/3 0/0 0/0 .rodata          @4680 */
#pragma push
#pragma force_active on
SECTION_RODATA static u8 const lit_4680[8] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
COMPILER_STRIP_GATE(0x80A0C480, &lit_4680);
#pragma pop

/* 80A0C488-80A0C48C 000218 0004+00 0/1 0/0 0/0 .rodata          @4681 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_4681 = 1000.0f;
COMPILER_STRIP_GATE(0x80A0C488, &lit_4681);
#pragma pop

/* 80A08F60-80A090E8 001660 0188+00 1/1 0/0 0/0 .text            s_sub1__FPvPv */
static void s_sub1(void* param_0, void* param_1) {
    // NONMATCHING
}

/* ############################################################################################## */
/* 80A0C48C-80A0C490 00021C 0004+00 3/7 0/0 0/0 .rodata          @4889 */
SECTION_RODATA static f32 const lit_4889 = -1.0f;
COMPILER_STRIP_GATE(0x80A0C48C, &lit_4889);

/* 80A0C490-80A0C494 000220 0004+00 0/2 0/0 0/0 .rodata          @4890 */
#pragma push
#pragma force_active on
SECTION_RODATA static u32 const lit_4890 = 0x3BB40000;
COMPILER_STRIP_GATE(0x80A0C490, &lit_4890);
#pragma pop

/* 80A0C494-80A0C498 000224 0004+00 0/2 0/0 0/0 .rodata          @4891 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_4891 = 15.0f;
COMPILER_STRIP_GATE(0x80A0C494, &lit_4891);
#pragma pop

/* 80A0C498-80A0C4A0 000228 0008+00 0/2 0/0 0/0 .rodata          @4893 */
#pragma push
#pragma force_active on
SECTION_RODATA static u8 const lit_4893[8] = {
    0x43, 0x30, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00,
};
COMPILER_STRIP_GATE(0x80A0C498, &lit_4893);
#pragma pop

/* 80A0C4C8-80A0C4C8 000258 0000+00 0/0 0/0 0/0 .rodata          @stringBase0 */
#pragma push
#pragma force_active on
SECTION_DEAD static char const* const stringBase_80A0C508 = "NO_RESPONSE";
#pragma pop

/* 80A090E8-80A099B4 0017E8 08CC+00 4/0 0/0 0/0 .text            wait__12daNpcImpal_cFPv */
void daNpcImpal_c::wait(void* param_0) {
    // NONMATCHING
}

/* 80A099B4-80A099F8 0020B4 0044+00 1/0 0/0 0/0 .text            setMotion__12daNpcImpal_cFifi */
void daNpcImpal_c::setMotion(int param_0, f32 param_1, int param_2) {
    // NONMATCHING
}

/* 80A099F8-80A09A24 0020F8 002C+00 1/0 0/0 0/0 .text            setExpression__12daNpcImpal_cFif */
void daNpcImpal_c::setExpression(int param_0, f32 param_1) {
    // NONMATCHING
}

/* ############################################################################################## */
/* 80A0C4C8-80A0C4C8 000258 0000+00 0/0 0/0 0/0 .rodata          @stringBase0 */
#pragma push
#pragma force_active on
SECTION_DEAD static char const* const stringBase_80A0C514 = "DEFAULT_GETITEM";
#pragma pop

/* 80A09A24-80A09F4C 002124 0528+00 2/0 0/0 0/0 .text            talk__12daNpcImpal_cFPv */
void daNpcImpal_c::talk(void* param_0) {
    // NONMATCHING
}

/* 80A09F4C-80A0A1E0 00264C 0294+00 1/0 0/0 0/0 .text            demo__12daNpcImpal_cFPv */
void daNpcImpal_c::demo(void* param_0) {
    // NONMATCHING
}

/* ############################################################################################## */
/* 80A0C4A0-80A0C4A4 000230 0004+00 0/1 0/0 0/0 .rodata          @5095 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_5095 = 2360.0f;
COMPILER_STRIP_GATE(0x80A0C4A0, &lit_5095);
#pragma pop

/* 80A0C4A4-80A0C4A8 000234 0004+00 0/1 0/0 0/0 .rodata          @5096 */
#pragma push
#pragma force_active on
SECTION_RODATA static u32 const lit_5096 = 0x42C7FC73;
COMPILER_STRIP_GATE(0x80A0C4A4, &lit_5096);
#pragma pop

/* 80A0C4A8-80A0C4AC 000238 0004+00 0/1 0/0 0/0 .rodata          @5097 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_5097 = -1150.0f;
COMPILER_STRIP_GATE(0x80A0C4A8, &lit_5097);
#pragma pop

/* 80A0A1E0-80A0A680 0028E0 04A0+00 1/0 0/0 0/0 .text EvCut_ImpalAppear1__12daNpcImpal_cFi */
void daNpcImpal_c::EvCut_ImpalAppear1(int param_0) {
    // NONMATCHING
}

/* 80A0A680-80A0A950 002D80 02D0+00 1/0 0/0 0/0 .text EvCut_ImpalAppear2__12daNpcImpal_cFi */
void daNpcImpal_c::EvCut_ImpalAppear2(int param_0) {
    // NONMATCHING
}

/* ############################################################################################## */
/* 80A0C4AC-80A0C4B0 00023C 0004+00 0/1 0/0 0/0 .rodata          @5195 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_5195 = 150.0f;
COMPILER_STRIP_GATE(0x80A0C4AC, &lit_5195);
#pragma pop

/* 80A0C4B0-80A0C4B4 000240 0004+00 0/1 0/0 0/0 .rodata          @5196 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_5196 = 500.0f;
COMPILER_STRIP_GATE(0x80A0C4B0, &lit_5196);
#pragma pop

/* 80A0A950-80A0AD40 003050 03F0+00 1/0 0/0 0/0 .text            EvCut_CopyRod__12daNpcImpal_cFi */
void daNpcImpal_c::EvCut_CopyRod(int param_0) {
    // NONMATCHING
}

/* 80A0AD40-80A0AD60 003440 0020+00 1/0 0/0 0/0 .text            daNpcImpal_Create__FPv */
static void daNpcImpal_Create(void* param_0) {
    // NONMATCHING
}

/* 80A0AD60-80A0AD80 003460 0020+00 1/0 0/0 0/0 .text            daNpcImpal_Delete__FPv */
static void daNpcImpal_Delete(void* param_0) {
    // NONMATCHING
}

/* 80A0AD80-80A0ADA0 003480 0020+00 1/0 0/0 0/0 .text            daNpcImpal_Execute__FPv */
static void daNpcImpal_Execute(void* param_0) {
    // NONMATCHING
}

/* 80A0ADA0-80A0ADC0 0034A0 0020+00 1/0 0/0 0/0 .text            daNpcImpal_Draw__FPv */
static void daNpcImpal_Draw(void* param_0) {
    // NONMATCHING
}

/* 80A0ADC0-80A0ADC8 0034C0 0008+00 1/0 0/0 0/0 .text            daNpcImpal_IsDelete__FPv */
static bool daNpcImpal_IsDelete(void* param_0) {
    return true;
}

/* 80A0ADC8-80A0ADF8 0034C8 0030+00 1/0 0/0 0/0 .text            calc__11J3DTexNoAnmCFPUs */
// void J3DTexNoAnm::calc(u16* param_0) const {
extern "C" void calc__11J3DTexNoAnmCFPUs() {
    // NONMATCHING
}

/* 80A0ADF8-80A0AEA8 0034F8 00B0+00 1/0 0/0 0/0 .text            setParam__12daNpcImpal_cFv */
void daNpcImpal_c::setParam() {
    // NONMATCHING
}

/* 80A0AEA8-80A0B380 0035A8 04D8+00 1/0 0/0 0/0 .text            main__12daNpcImpal_cFv */
void daNpcImpal_c::main() {
    // NONMATCHING
}

/* ############################################################################################## */
/* 80A0C4B4-80A0C4B8 000244 0004+00 1/1 0/0 0/0 .rodata          @5328 */
SECTION_RODATA static f32 const lit_5328 = 1.0f / 5.0f;
COMPILER_STRIP_GATE(0x80A0C4B4, &lit_5328);

/* 80A0B380-80A0B45C 003A80 00DC+00 1/0 0/0 0/0 .text            ctrlBtk__12daNpcImpal_cFv */
void daNpcImpal_c::ctrlBtk() {
    // NONMATCHING
}

/* ############################################################################################## */
/* 80A0C4B8-80A0C4BC 000248 0004+00 0/1 0/0 0/0 .rodata          @5401 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_5401 = 10.0f;
COMPILER_STRIP_GATE(0x80A0C4B8, &lit_5401);
#pragma pop

/* 80A0B45C-80A0B76C 003B5C 0310+00 1/0 0/0 0/0 .text            setAttnPos__12daNpcImpal_cFv */
void daNpcImpal_c::setAttnPos() {
    // NONMATCHING
}

/* ############################################################################################## */
/* 80A0C4BC-80A0C4C0 00024C 0004+00 0/1 0/0 0/0 .rodata          @5442 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_5442 = -80.0f;
COMPILER_STRIP_GATE(0x80A0C4BC, &lit_5442);
#pragma pop

/* 80A0C4C0-80A0C4C4 000250 0004+00 0/1 0/0 0/0 .rodata          @5443 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_5443 = 80.0f;
COMPILER_STRIP_GATE(0x80A0C4C0, &lit_5443);
#pragma pop

/* 80A0C4C4-80A0C4C8 000254 0004+00 0/1 0/0 0/0 .rodata          @5444 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_5444 = 40.0f;
COMPILER_STRIP_GATE(0x80A0C4C4, &lit_5444);
#pragma pop

/* 80A0B76C-80A0B94C 003E6C 01E0+00 1/1 0/0 0/0 .text            lookat__12daNpcImpal_cFv */
void daNpcImpal_c::lookat() {
    // NONMATCHING
}

/* 80A0B94C-80A0B954 00404C 0008+00 1/0 0/0 0/0 .text            drawDbgInfo__12daNpcImpal_cFv */
bool daNpcImpal_c::drawDbgInfo() {
    return false;
}

/* 80A0B954-80A0B960 004054 000C+00 1/1 0/0 0/0 .text sinShort__Q25JMath18TSinCosTable<13,f>CFs */
extern "C" void func_80A0B954(void* _this, s16 param_0) /* const */ {
    // NONMATCHING
}

/* ############################################################################################## */
/* 80A0C8E0-80A0C8EC 0003BC 000C+00 2/2 0/0 0/0 .data            __vt__18daNpcImpal_Param_c */
SECTION_DATA extern void* __vt__18daNpcImpal_Param_c[3] = {
    (void*)NULL /* RTTI */,
    (void*)NULL,
    (void*)__dt__18daNpcImpal_Param_cFv,
};

/* 80A0C8F8-80A0C904 000008 000C+00 1/1 0/0 0/0 .bss             @3804 */
static u8 lit_3804[12];

/* 80A0C904-80A0C908 000014 0004+00 1/1 0/0 0/0 .bss             l_HIO */
static u8 l_HIO[4];

/* 80A0B960-80A0BA1C 004060 00BC+00 0/0 1/0 0/0 .text            __sinit_d_a_npc_impal_cpp */
void __sinit_d_a_npc_impal_cpp() {
    // NONMATCHING
}

#pragma push
#pragma force_active on
REGISTER_CTORS(0x80A0B960, __sinit_d_a_npc_impal_cpp);
#pragma pop

/* 80A0BA1C-80A0BA64 00411C 0048+00 5/4 0/0 0/0 .text            __dt__18daNpcF_ActorMngr_cFv */
// daNpcF_ActorMngr_c::~daNpcF_ActorMngr_c() {
extern "C" void __dt__18daNpcF_ActorMngr_cFv() {
    // NONMATCHING
}

/* 80A0BA64-80A0BAA0 004164 003C+00 2/2 0/0 0/0 .text            __ct__18daNpcF_ActorMngr_cFv */
// daNpcF_ActorMngr_c::daNpcF_ActorMngr_c() {
extern "C" void __ct__18daNpcF_ActorMngr_cFv() {
    // NONMATCHING
}

/* 80A0BAA0-80A0BB70 0041A0 00D0+00 1/0 0/0 0/0 .text            __dt__15daNpcF_Lookat_cFv */
// daNpcF_Lookat_c::~daNpcF_Lookat_c() {
extern "C" void __dt__15daNpcF_Lookat_cFv() {
    // NONMATCHING
}

/* 80A0BB70-80A0BBAC 004270 003C+00 5/5 0/0 0/0 .text            __dt__5csXyzFv */
// csXyz::~csXyz() {
extern "C" void __dt__5csXyzFv() {
    // NONMATCHING
}

/* 80A0BBAC-80A0BBB0 0042AC 0004+00 2/2 0/0 0/0 .text            __ct__5csXyzFv */
// csXyz::csXyz() {
extern "C" void __ct__5csXyzFv() {
    /* empty function */
}

/* 80A0BBB0-80A0BBEC 0042B0 003C+00 5/5 0/0 0/0 .text            __dt__4cXyzFv */
// cXyz::~cXyz() {
extern "C" void __dt__4cXyzFv() {
    // NONMATCHING
}

/* 80A0BBEC-80A0BBF0 0042EC 0004+00 2/2 0/0 0/0 .text            __ct__4cXyzFv */
// cXyz::cXyz() {
extern "C" void __ct__4cXyzFv() {
    /* empty function */
}

/* 80A0BBF0-80A0BE3C 0042F0 024C+00 1/1 0/0 0/0 .text            __dt__8daNpcF_cFv */
// daNpcF_c::~daNpcF_c() {
extern "C" void __dt__8daNpcF_cFv() {
    // NONMATCHING
}

/* 80A0BE3C-80A0C02C 00453C 01F0+00 1/1 0/0 0/0 .text            __ct__8daNpcF_cFv */
// daNpcF_c::daNpcF_c() {
extern "C" void __ct__8daNpcF_cFv() {
    // NONMATCHING
}

/* 80A0C02C-80A0C09C 00472C 0070+00 1/0 0/0 0/0 .text            __dt__12dBgS_AcchCirFv */
// dBgS_AcchCir::~dBgS_AcchCir() {
extern "C" void __dt__12dBgS_AcchCirFv() {
    // NONMATCHING
}

/* 80A0C09C-80A0C0F8 00479C 005C+00 1/0 0/0 0/0 .text            __dt__10dCcD_GSttsFv */
// dCcD_GStts::~dCcD_GStts() {
extern "C" void __dt__10dCcD_GSttsFv() {
    // NONMATCHING
}

/* 80A0C0F8-80A0C168 0047F8 0070+00 3/2 0/0 0/0 .text            __dt__12dBgS_ObjAcchFv */
// dBgS_ObjAcch::~dBgS_ObjAcch() {
extern "C" void __dt__12dBgS_ObjAcchFv() {
    // NONMATCHING
}

/* 80A0C168-80A0C1B0 004868 0048+00 1/0 0/0 0/0 .text            __dt__12J3DFrameCtrlFv */
// J3DFrameCtrl::~J3DFrameCtrl() {
extern "C" void __dt__12J3DFrameCtrlFv() {
    // NONMATCHING
}

/* 80A0C1B0-80A0C1B4 0048B0 0004+00 1/0 0/0 0/0 .text            adjustShapeAngle__8daNpcF_cFv */
// void daNpcF_c::adjustShapeAngle() {
extern "C" void adjustShapeAngle__8daNpcF_cFv() {
    /* empty function */
}

/* 80A0C1B4-80A0C1B8 0048B4 0004+00 1/0 0/0 0/0 .text            setCollisions__8daNpcF_cFv */
// void daNpcF_c::setCollisions() {
extern "C" void setCollisions__8daNpcF_cFv() {
    /* empty function */
}

/* 80A0C1B8-80A0C1BC 0048B8 0004+00 1/0 0/0 0/0 .text            drawOtherMdls__8daNpcF_cFv */
// void daNpcF_c::drawOtherMdls() {
extern "C" void drawOtherMdls__8daNpcF_cFv() {
    /* empty function */
}

/* 80A0C1BC-80A0C204 0048BC 0048+00 1/0 0/0 0/0 .text            __dt__10cCcD_GSttsFv */
// cCcD_GStts::~cCcD_GStts() {
extern "C" void __dt__10cCcD_GSttsFv() {
    // NONMATCHING
}

/* 80A0C204-80A0C24C 004904 0048+00 2/1 0/0 0/0 .text            __dt__18daNpcImpal_Param_cFv */
daNpcImpal_Param_c::~daNpcImpal_Param_c() {
    // NONMATCHING
}

/* 80A0C24C-80A0C254 00494C 0008+00 1/0 0/0 0/0 .text            @36@__dt__12dBgS_ObjAcchFv */
static void func_80A0C24C() {
    // NONMATCHING
}

/* 80A0C254-80A0C25C 004954 0008+00 1/0 0/0 0/0 .text            @20@__dt__12dBgS_ObjAcchFv */
static void func_80A0C254() {
    // NONMATCHING
}

/* 80A0C4C8-80A0C4C8 000258 0000+00 0/0 0/0 0/0 .rodata          @stringBase0 */
