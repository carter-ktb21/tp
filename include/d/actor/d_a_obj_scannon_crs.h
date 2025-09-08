#ifndef D_A_OBJ_SCANNON_CRS_H
#define D_A_OBJ_SCANNON_CRS_H

#include "f_op/f_op_actor_mng.h"
#include "d/actor/d_a_midna.h"

/**
 * @ingroup actors-objects
 * @class daSCannonCrs_c
 * @brief Sky Cannon (Broken)
 *
 * @details
 *
 */
class daSCannonCrs_c : public fopAc_ac_c, public request_of_phase_process_class {
public:
    enum daSCannonCrs_exeMode {
        MODE_WAIT,
        MODE_PRE_WAIT,
        MODE_ORDER_EVT,
        MODE_TALK_EVT,
        MODE_WARP_EVT,
        MODE_END,
    };

    /* 80CC973C */ daSCannonCrs_c();
    /* 80CC983C */ virtual ~daSCannonCrs_c();
    /* 80CC9910 */ int create();
    /* 80CC9B10 */ int Delete();
    /* 80CC9B80 */ int draw();
    /* 80CC9C64 */ int execute();
    /* 80CC9CA4 */ void middleExe(daMidna_c*);
    /* 80CC9D60 */ void exeModeWait(daMidna_c*);
    /* 80CC9F34 */ void exeModePreWait(daMidna_c*);
    /* 80CC9F80 */ void exeModeOrderEvt(daMidna_c*);
    /* 80CCA240 */ void exeModeTalkEvt(daMidna_c*);
    /* 80CCA2CC */ void exeModeWarpEvt(daMidna_c*);
    /* 80CCA344 */ void exeModeEnd(daMidna_c*);
    /* 80CCA348 */ void demoExe();
    /* 80CCA74C */ void init();
    /* 80CCA848 */ void setModelMtx();
    /* 80CCA8CC */ int createHeap();
    /* 80CCAAC4 */ bool chkInTalkRange();
    /* 80CCAB24 */ void initEmtRt(u16, int, u16 const*, JPABaseEmitter**);
    /* 80CCAC48 */ void exeEmtRt(u16, int, JPABaseEmitter**);
    /* 80CCACD0 */ void callMidnaBeamEmt();

    int getTalkRange() { return fopAcM_GetParamBit(this, 0, 8); }
    int getWarpId() { return fopAcM_GetParamBit(this, 8, 8); }
    u16 getMsgId() { return home.angle.x; }

    static void (daSCannonCrs_c::*s_exeProc[])(daMidna_c*);

private:
    /* 0x574 */ cXyz mPortalWaitPos;
    /* 0x580 */ dMsgFlow_c mMsgFlow;
    /* 0x5CC */ mDoExt_bckAnm mBck;
    /* 0x5E8 */ mDoExt_btkAnm mBtk;
    /* 0x600 */ J3DModel* mpModel;
    /* 0x604 */ dBgW* mpBgW;
    /* 0x608 */ Mtx mBgMtx;
    /* 0x638 */ f32 mTalkRangeSqDist;
    /* 0x63C */ int mStaffId;
    /* 0x640 */ int mWarpQuakeTimer;
    /* 0x644 */ int mVoiceTimer;
    /* 0x648 */ u16 mEffectJointNo;
    /* 0x64A */ u16 mCenterJointNo;
    /* 0x64C */ s16 mEvtIdx;
    /* 0x64E */ u8 mMode;
    /* 0x64F */ u8 field_0x64F[0x651 - 0x64F];
    /* 0x651 */ u8 field_0x651;
    /* 0x652 */ u8 field_0x652;
    /* 0x654 */ JPABaseEmitter* mpDisapEmt[4];
    /* 0x664 */ JPABaseEmitter* mpBeamEmt[4];
};

STATIC_ASSERT(sizeof(daSCannonCrs_c) == 0x674);

#endif /* D_A_OBJ_SCANNON_CRS_H */
