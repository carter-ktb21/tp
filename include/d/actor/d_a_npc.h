#ifndef D_A_D_A_NPC_H
#define D_A_D_A_NPC_H

#include "JSystem/J3DGraphAnimator/J3DMaterialAnm.h"
#include "SSystem/SComponent/c_counter.h"
#include "SSystem/SComponent/c_math.h"
#include "Z2AudioLib/Z2Creature.h"
#include "d/actor/d_a_player.h"
#include "d/d_bg_s_movebg_actor.h"
#include "d/d_path.h"
#include "d/d_msg_flow.h"
#include "d/d_particle_copoly.h"
#include "global.h"

struct daNpc_GetParam1 {  // name unknown
    /* 0x0 */ int fileIdx;
    /* 0x4 */ int arcIdx;
};

struct daNpc_GetParam2 {  // name unknown
    /* 0x0 */ int fileIdx;
    /* 0x4 */ int attr;
    /* 0x8 */ int arcIdx;
};

class daNpcT_ActorMngr_c {
private:
    /* 0x0 */ fpc_ProcID mActorID;

public:
    /* 801456D4 */ void initialize();
    /* 801456E0 */ void entry(fopAc_ac_c*);
    /* 801456FC */ void remove();
    /* 80145708 */ fopAc_ac_c* getActorP();

    daNpcT_ActorMngr_c() { initialize(); };

    /* 8014D108 */ virtual ~daNpcT_ActorMngr_c() {}
};

class daNpcT_MatAnm_c : public J3DMaterialAnm {
private:
    /* 0x0F4 */ mutable f32 field_0xF4;
    /* 0x0F8 */ mutable f32 field_0xF8;
    /* 0x0FC */ f32 mNowOffsetX;
    /* 0x100 */ f32 mNowOffsetY;
    /* 0x104 */ u8 mEyeMoveFlg;
    /* 0x105 */ u8 mMorfFrm;

public:
    daNpcT_MatAnm_c() { initialize(); }

    /* 80145764 */ void initialize();
    /* 8014D24C */ virtual ~daNpcT_MatAnm_c() {}
    /* 80145788 */ virtual void calc(J3DMaterial*) const;

    void setNowOffsetX(f32 i_value) { mNowOffsetX = i_value; }
    void setNowOffsetY(f32 i_value) { mNowOffsetY = i_value; }
    void onEyeMoveFlag() { mEyeMoveFlg = 1; }
    void offEyeMoveFlag() { mEyeMoveFlg = 0; }
    void setMorfFrm(u8 i_value) { mMorfFrm = i_value; }
};

class daNpcT_MotionSeqMngr_c {
public:
    class sequenceStepData_c {
    public:
        /* 0x0 */ s16 mAnmIdx;
        /* 0x2 */ s8 mMorf;
        /* 0x3 */ s8 mLoopCount;
    };  // Size: 0x4?

    /* 80145898 */ void initialize();
    /* 801458C0 */ int play(u16, int*, f32*);
    /* 80145A24 */ s32 checkEndSequence();

    daNpcT_MotionSeqMngr_c(sequenceStepData_c const* param_1,int param_2) :
    mpSeqData(param_1), mStepNum(param_2) {
        initialize();
    }

    bool checkEntryNewMotion() { return mStepNo == 0 && mPrevStepNo == -1; }
    int getNo() { return mNo; }
    int getOffset() { return mOffset; }
    int getStepNo() { return mStepNo; }
    void setNo(int i_index, f32 i_morf, BOOL i_reset, int i_offset) {
        if (i_index >= 0) {
            int newNo = i_index + i_offset;
            if (i_reset || newNo != mNo) {
                int offset = mOffset;
                initialize();
                mOffset = offset;
                mNo = newNo;
                mInitialMorf = i_morf;
            }
        }
    }

private:
    /* 0x00 */ sequenceStepData_c const* mpSeqData;
    /* 0x04 */ int mStepNum;
    /* 0x08 */ int mNo;
    /* 0x0C */ int mOffset;
    /* 0x10 */ int mStepNo;
    /* 0x14 */ int mPrevStepNo;
    /* 0x18 */ f32 mInitialMorf;
    /* 0x1C */ bool mEndSequence;

public:
    /* 8014D0C0 */ virtual ~daNpcT_MotionSeqMngr_c() {}
};

class daNpcT_JntAnm_c {
private:
    /* 0x000 */ daNpcT_ActorMngr_c mActrMngr;
    /* 0x008 */ cXyz mPos;
    /* 0x014 */ cXyz mAttnPos;
    /* 0x020 */ cXyz* mAttnPosP;
    /* 0x024 */ cXyz field_0x24;
    /* 0x030 */ cXyz mJntPos[3];
    /* 0x054 */ cXyz field_0x54[3];
    /* 0x078 */ cXyz mMinRad[3];
    /* 0x09C */ cXyz mMaxRad[3];
    /* 0x0C0 */ cXyz mRad[3];
    /* 0x0E4 */ cXyz field_0xe4[3];
    /* 0x108 */ cXyz mEyePos;
    /* 0x114 */ cXyz mHeadPos;
    /* 0x120 */ cXyz field_0x120;
    /* 0x12C */ csXyz mEyeAngle;
    /* 0x132 */ csXyz field_0x132;
    /* 0x138 */ int mMode;
    /* 0x13C */ int field_0x13c;
    /* 0x140 */ int mBaseTimer;
    /* 0x144 */ int mTimer;
    /* 0x148 */ f32 field_0x148;
    /* 0x14C */ f32 field_0x14c;
    /* 0x150 */ csXyz field_0x150;
    /* 0x156 */ u8 field_0x156;
    /* 0x157 */ u8 mDirectFlag;
    /* 0x158 */ u8 field_0x158;

public:
    /* 80146C98 */ void initialize();
    /* 80146CD8 */ void setParam(fopAc_ac_c*, J3DModel*, cXyz*, int, int, int, f32, f32, f32, f32,
                                 f32, f32, f32, f32, f32, f32, cXyz*);
    /* 80147858 */ void calc(f32);
    /* 80147C38 */ void calcJntRad(f32, f32, f32);

    void setEyeAngleX(cXyz param_1, f32 param_2, s16 param_3) {
        cXyz cStack_50;
        s16 sVar3 = 0;
        if (mAttnPosP != NULL) {
            cStack_50 = *mAttnPosP - param_1;
            sVar3 = -cM_atan2s(cStack_50.y,  cStack_50.absXZ());
            sVar3 += param_3;
        }
        sVar3 += field_0x150.x;
        mEyeAngle.x = field_0x132.x * (1.0f - 1.0f / param_2) +
                      sVar3 * (1.0f / param_2);
    }

    void setEyeAngleY(cXyz param_1, s16 param_2, BOOL param_3, f32 param_4, s16 param_5) {
        cXyz cStack_50;
        s16 sVar3 = 0;
        if (mAttnPosP != NULL) {
            cStack_50 = *mAttnPosP - param_1;
            sVar3 = cM_atan2s(cStack_50.x,  cStack_50.z);
            sVar3 -= param_2;
            s16 diff = field_0x150.y - param_2;
            sVar3 -= diff;
            sVar3 += param_5;
        }
        if (param_3) {
            sVar3 = -sVar3;
        }
        mEyeAngle.y = field_0x132.y * (1.0f - 1.0f / param_4) +
                      sVar3 * (1.0f / param_4);
    }

    s16 getEyeAngleX() { return mEyeAngle.x; }
    s16 getEyeAngleY() { return mEyeAngle.y; }

    f32 getJntRadX(int param_0) {
        f32 ret = field_0xe4[2].x;
        if (param_0 == 0) {
            ret += field_0xe4[0].x * (1.0f - field_0x148);
        } else if (param_0 == 1) {
            ret += field_0xe4[0].x * field_0x148;
        }
        return ret;
    }

    f32 getJntRadY(int param_0) {
        f32 ret = field_0xe4[2].y;
        if (param_0 == 0) {
            ret += field_0xe4[0].y * (1.0f - field_0x148);
        } else if (param_0 == 1) {
            ret += field_0xe4[0].y * field_0x148;
        }
        return ret;
    }

    s16 getJntRadX2S(int param_0) {
        return cM_rad2s(getJntRadX(param_0));
    }

    s16 getJntRadY2S(int param_0) {
        return cM_rad2s(getJntRadY(param_0));
    }

    void clrRad() {
        for (int i = 0; i < 3; i++) {
            mRad[i].setall(0.0f);
        }
    }

    int getTime() {
        return cLib_getRndValue(mBaseTimer / 2, mBaseTimer);
    }

    daNpcT_JntAnm_c() {
        initialize();
    }
    /* 8014D150 */ virtual ~daNpcT_JntAnm_c() {}

    void clrDirectFlag() { mDirectFlag = 0; }
    int getMode() { return mMode; }

    int setMode(int mode, BOOL param_2) {
        if (mode >= 0 && (param_2 || mode != mMode)) {
            mActrMngr.remove();
            mAttnPosP = NULL;
            field_0x14c = 0.0f;
            mDirectFlag = 0;
            mMode = mode;
            return 1;
        }
        return 0;
    }

    void setDirect(u8 isDirect) {
        if (isDirect != 0) {
            mEyeAngle.x = 0;
            mEyeAngle.y = 0;
        }
        mDirectFlag = isDirect;
    }

    enum LookMode {
        /* 0 */ LOOK_NONE,
        /* 1 */ LOOK_PLAYER,
        /* 2 */ LOOK_ACTOR,
        /* 3 */ LOOK_POS,
        /* 4 */ LOOK_CAMERA,
        /* 5 */ LOOK_MODE_5,
        /* 6 */ LOOK_MODE_6,
        /* 7 */ LOOK_MODE_7,
        /* 8 */ LOOK_MODE_8,
    };

    void lookNone(u8 isDirect) {
        setMode(LOOK_NONE, FALSE);
        setDirect(isDirect);
    }

    void lookPlayer(u8 isDirect) {
        setMode(LOOK_PLAYER, FALSE);
        setDirect(isDirect);
    }

    void lookCamera(u8 isDirect) {
        setMode(LOOK_CAMERA, FALSE);
        setDirect(isDirect);
    }

    void lookActor(fopAc_ac_c* param_1, f32 param_2, u8 isDirect) {
        if (setMode(LOOK_ACTOR, mActrMngr.getActorP() != param_1) && fopAcM_IsActor(param_1)) {
            mActrMngr.entry(param_1);
            field_0x14c = param_2;
        }
        setDirect(isDirect);
    }

    void lookPos(cXyz* i_pos, u8 i_direct) {
        BOOL tmp = mAttnPosP != i_pos;
        if (setMode(LOOK_POS, tmp)) {
            mAttnPosP = i_pos;
        }
        setDirect(i_direct);
    }

    void sorasu1(cXyz *arg0, u8 arg1) {
        BOOL diff_ptrs = mAttnPosP != arg0;
        if (setMode(5, diff_ptrs) != 0) {
            mAttnPosP = arg0;
        }

        setDirect(arg1);
    }

    void sorasu2(cXyz *arg0, u8 arg1) {
        BOOL diff_ptrs = mAttnPosP != arg0;
        if (setMode(6, diff_ptrs) != 0) {
            mAttnPosP = arg0;
        }

        setDirect(arg1);
    }
};

class daNpcT_DmgStagger_c {
public:
    /* 80147DCC */ void setParam(fopAc_ac_c*, fopAc_ac_c*, s16);
    /* 80147E3C */ void calc(BOOL);

    void initialize() {
        u8 zero = 0;
        for (int i = 0; i < 2; i++) {
            mAngle[i].setall(zero);
            mPower[i] = 0.0f;
        }
        mStagger = 0;
        field_0x16 = 0;
        mRebirth = 0;
    }

    int checkStagger() { return mStagger != 0; }

    s16 getAngleX(int idx) { return mAngle[idx].x; }
    s16 getAngleZ(int idx) { return mAngle[idx].z; }
    int checkRebirth() { return mRebirth; }
    void setPower(f32 power) {
        for (int i = 0; i < 2; i++) {
            mPower[i] = power;
        }
    }

    /* 0x00 */ csXyz mAngle[2];
    /* 0x0C */ f32 mPower[2];
    /* 0x14 */ s16 mStagger;
    /* 0x16 */ s16 field_0x16;
    /* 0x18 */ bool mRebirth;
};

struct daNpcT_evtData_c {
    /* 0x0 */ const char* eventName;
    /* 0x4 */ int num;
};

struct daNpcT_faceMotionAnmData_c {
    /* 0x00 */ int mBckFileIdx;
    /* 0x04 */ int mBckAttr;
    /* 0x08 */ int mBckArcIdx;
    /* 0x0C */ int mBtpFileIdx;
    /* 0x10 */ int mBtpAttr;
    /* 0x14 */ int mBtpArcIdx;
    /* 0x18 */ BOOL field_0x18;
};

struct daNpcT_pntData_c {
    /* 0x0 */ int field_0x0;
    /* 0x4 */ int field_0x4;
};

struct daNpcT_motionAnmData_c {
    /* 0x00 */ int mBckFileIdx;
    /* 0x04 */ int mBckAttr;
    /* 0x08 */ int mBckArcIdx;
    /* 0x0C */ int mBtkFileIdx;
    /* 0x10 */ int mBtkAttr;
    /* 0x14 */ int mBtkArcIdx;
    /* 0x18 */ s16 field_0x18;
    /* 0x1A */ s16 field_0x1a;
};

class daNpcT_Hermite_c {
public:
    /* 0x00 */ f32 field_0x00;
    /* 0x04 */ f32 H00;
    /* 0x08 */ f32 H01;
    /* 0x0C */ f32 H10;
    /* 0x10 */ f32 H11;

    /* 8014CBAC */ virtual ~daNpcT_Hermite_c() {}

    f32 GetH00() { return H00; }
    f32 GetH01() { return H01; }
    f32 GetH10() { return H10; }
    f32 GetH11() { return H11; }

    // constants might be wrong, regalloc
    void Set(f32 param_1) {
        field_0x00 = param_1;
        f32 sqr = param_1 * param_1;
        f32 cubed = param_1 * sqr;

        H00 = 1.0f + (2.0f * cubed - 3.0f * sqr);
        H01 = -2.0f * cubed + 3.0f * sqr;
        H10 = param_1 + (cubed - 2.0f * sqr);
        H11 = cubed - sqr;
    }
};

class daNpcT_Path_c {
public:
    /* 0x00 */ dPath* mPathInfo;
    /* 0x04 */ cXyz mPosition;
    /* 0x10 */ f32 field_0x10;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 field_0x18;
    /* 0x1C */ u16 mIdx;
    /* 0x1E */ u16 field_0x1E;
    /* 0x20 */ u8 mDirection;
    /* 0x21 */ u8 mIsClosed;

    /* 80145B7C */ void hermite(cXyz&, cXyz&, cXyz&, cXyz&, daNpcT_Hermite_c&, cXyz&);
    /* 80145C40 */ void initialize();
    /* 80145C74 */ int setPathInfo(u8, s8, u8);
    /* 80145D2C */ int setNextPathInfo(s8, u8);
    /* 80145DA0 */ void reverse();
    /* 80145DD0 */ int setNextIdx(int);
    /* 80145E38 */ int getDstPos(cXyz, cXyz*, int);
    /* 80145FB4 */ int getDstPosH(cXyz, cXyz*, int, int);
    /* 80146188 */ int chkPassed1(cXyz, int);
    /* 801464D8 */ int chkPassed2(cXyz, cXyz*, int, int);

    daNpcT_Path_c() {
        initialize();
    }

    virtual ~daNpcT_Path_c() {}

    Vec getPntPos(int i_idx) { return mPathInfo->m_points[i_idx].m_position; }

    int chkClose() {
        BOOL rt = dPath_ChkClose(mPathInfo);
        return rt;
    }

    bool chkReverse() { return mDirection == 1; }

    int getNumPnts() { return mPathInfo->m_num; }

    void setIdx(int i_idx) { mIdx = i_idx; }

    const u16 getIdx() { return mIdx; }

    dPath* getPathInfo() { return mPathInfo; }

    void onReverse() {
        mDirection = 1;
        field_0x1E = 1;
    }

    void offReverse() {
        mDirection = 0;
        field_0x1E = 1;
    }
};

class mDoExt_McaMorfSO;

class daNpcT_c : public fopAc_ac_c {
public:
    /* 0x568 */ daNpcT_faceMotionAnmData_c const* mpFaceMotionAnmData;
    /* 0x56C */ daNpcT_motionAnmData_c const* mpMotionAnmData;
    /* 0x570 */ daNpcT_evtData_c const* mpEvtData;
    /* 0x574 */ char** mpArcNames;
    /* 0x578 */ mDoExt_McaMorfSO* mpMorf[2];
    /* 0x580 */ Z2Creature mSound;
    /* 0x610 */ mDoExt_bckAnm mBckAnm;
    /* 0x62C */ mDoExt_btpAnm mBtpAnm;
    /* 0x644 */ mDoExt_btkAnm mBtkAnm;
    /* 0x65C */ mDoExt_brkAnm mBrkAnm;
    /* 0x674 */ mDoExt_bpkAnm mBpkAnm;
    /* 0x68C */ dBgS_ObjAcch mAcch;
    /* 0x864 */ dCcD_Stts mCcStts;
    /* 0x8A0 */ dBgS_AcchCir mAcchCir;
    /* 0x8E0 */ request_of_phase_process_class mPhase[10];
    /* 0x930 */ cBgS_GndChk mGndChk;
    /* 0x96C */ daNpcT_MatAnm_c* mpMatAnm[2];
    /* 0x974 */ dMsgFlow_c mFlow;
    /* 0x9C0 */ dPaPoT_c field_0x9c0;
    /* 0xA40 */ dCcD_Stts field_0xa40;
    /* 0xA7C */ u32 mFlowNodeNo;
    /* 0xA80 */ f32 mExpressionMorfFrame;
    /* 0xA84 */ f32 mMorfFrames;
    /* 0xA88 */ bool mCreating;
    /* 0xA89 */ bool mTwilight;
    /* 0xA8C */ dBgS_GndChk field_0xa8c;
    /* 0xAE0 */ dBgS_LinChk mLinChk;
    /* 0xB50 */ daNpcT_MotionSeqMngr_c mFaceMotionSeqMngr;
    /* 0xB74 */ daNpcT_MotionSeqMngr_c mMotionSeqMngr;
    /* 0xB98 */ daNpcT_ActorMngr_c mPlayerActorMngr;
    /* 0xBA0 */ daNpcT_ActorMngr_c field_0xba0;
    /* 0xBA8 */ daNpcT_JntAnm_c mJntAnm;
    /* 0xD08 */ daNpcT_DmgStagger_c mStagger;
    /* 0xD24 */ cXyz mFootLPos;
    /* 0xD30 */ cXyz mFootRPos;
    /* 0xD3C */ cXyz mFootLOffset;
    /* 0xD48 */ cXyz mFootROffset;
    /* 0xD54 */ cXyz mOldFootLOffset;
    /* 0xD60 */ cXyz mOldFootROffset;
    /* 0xD6C */ cXyz field_0xd6c;
    /* 0xD78 */ csXyz mCurAngle;
    /* 0xD7E */ csXyz field_0xd7e;
    /* 0xD84 */ csXyz field_0xd84;
    /* 0xD8A */ csXyz field_0xd8a;
    /* 0xD90 */ fpc_ProcID mItemPartnerId;
    /* 0xD94 */ u32 mShadowKey;
    /* 0xD98 */ u32 mAnmFlags;
    /* 0xD9C */ fpc_ProcID mMsgId;
    /* 0xDA0 */ u32 mHitodamaPrtclKey[2];
    /* 0xDA8 */ u32 mPolSound;
    /* 0xDAC */ int mStaffId;
    /* 0xDB0 */ int mCutType;
    /* 0xDB4 */ int field_0xdb4;
    /* 0xDB8 */ int mDamageTimerStart;
    /* 0xDBC */ int mDamageTimer;
    /* 0xDC0 */ int mBtpPauseTimer;
    /* 0xDC4 */ int mEventTimer;
    /* 0xDC8 */ s16 mPlayerAngle;
    /* 0xDCA */ s16 mGroundAngle;
    /* 0xDCC */ u8 field_0xdcc[2];
    /* 0xDCE */ s16 mFootLPolyAngle;
    /* 0xDD0 */ u8 field_0xdd0[2];
    /* 0xDD2 */ s16 mFootRPolyAngle;
    /* 0xDD4 */ s16 mStartAngle;
    /* 0xDD6 */ s16 mTargetAngle;
    /* 0xDD8 */ s16 mStepMode;
    /* 0xDDA */ s16 mTurnAmount;
    /* 0xDDC */ f32 mTurnCount;
    /* 0xDE0 */ f32 field_0xde0;
    /* 0xDE4 */ f32 field_0xde4;
    /* 0xDE8 */ f32 mRealShadowSize;
    /* 0xDEC */ f32 mCylH;
    /* 0xDF0 */ f32 mWallR;
    /* 0xDF4 */ f32 mGroundH;
    /* 0xDF8 */ f32 mAttnFovY;
    /* 0xDFC */ f32 field_0xdfc;
    /* 0xE00 */ cXyz field_0xe00;
    /* 0xE0C */ cXyz field_0xe0c;
    /* 0xE18 */ s16 field_0xe18;
    /* 0xE1A */ s16 field_0xe1a;
    /* 0xE1C */ s16 mEvtId;
    /* 0xE1E */ u16 mMorfLoops;
    /* 0xE20 */ u16 mBckLoops;
    /* 0xE22 */ u16 mMode;
    /* 0xE24 */ s8 mReverb;
    /* 0xE25 */ u8 mHide;
    /* 0xE26 */ bool field_0xe26;
    /* 0xE27 */ u8 mFootLOnGround;
    /* 0xE28 */ u8 mFootROnGround;
    /* 0xE29 */ u8 field_0xe29;
    /* 0xE2A */ u8 field_0xe2a;
    /* 0xE2B */ bool mNoDraw;
    /* 0xE2C */ u8 field_0xe2c;
    /* 0xE2D */ bool field_0xe2d;
    /* 0xE2E */ u8 mPreItemNo;
    /* 0xE30 */ u16 mEvtNo;
    /* 0xE32 */ bool mSpeakEvent;
    /* 0xE33 */ bool field_0xe33;
    /* 0xE34 */ u8 field_0xe34;
    /* 0xE35 */ u8 field_0xe35;
    /* 0xE36 */ u8 field_0xe36;
    /* 0xE37 */ u8 field_0xe37;
    /* 0xE38 */ u8 field_0xe38;
    /* 0xE3C vtable */

public:
    daNpcT_c(daNpcT_faceMotionAnmData_c const* i_faceMotionAnmData,
             daNpcT_motionAnmData_c const* i_motionAnmData,
             daNpcT_MotionSeqMngr_c::sequenceStepData_c const* i_faceMotionSequenceData,
             int i_faceMotionStepNum,
             daNpcT_MotionSeqMngr_c::sequenceStepData_c const* i_motionSequenceData,
             int i_motionStepNum, daNpcT_evtData_c const* i_evtData, char** i_arcNames) :
        mpFaceMotionAnmData(i_faceMotionAnmData),
        mpMotionAnmData(i_motionAnmData),
        mpEvtData(i_evtData),
        mpArcNames(i_arcNames),
        mFaceMotionSeqMngr(i_faceMotionSequenceData, i_faceMotionStepNum),
        mMotionSeqMngr(i_motionSequenceData, i_motionStepNum) {
        OS_REPORT("|%06d:%x|daNpcT_c -> コンストラクト\n", g_Counter.mCounter0, this);
        initialize();
    }

    /* 80147FA4 */ static void tgHitCallBack(fopAc_ac_c*, dCcD_GObjInf*, fopAc_ac_c*, dCcD_GObjInf*);
    /* 80147FD4 */ static void* srchActor(void*, void*);
    /* 80148058 */ J3DAnmTransform* getTrnsfrmAnmP(char const*, int);
    /* 80148094 */ J3DAnmTransformKey* getTrnsfrmKeyAnmP(char const*, int);
    /* 801480D0 */ J3DAnmTexPattern* getTexPtrnAnmP(char const*, int);
    /* 8014810C */ J3DAnmTextureSRTKey* getTexSRTKeyAnmP(char const*, int);
    /* 80148148 */ J3DAnmTevRegKey* getTevRegKeyAnmP(char const*, int);
    /* 80148184 */ J3DAnmColor* getColorAnmP(char const*, int);
    /* 801481C0 */ int setBckAnm(J3DAnmTransform*, f32, int, int, int, bool);
    /* 80148204 */ int setMcaMorfAnm(J3DAnmTransformKey*, f32, f32, int, int, int);
    /* 801482F8 */ int setBtpAnm(J3DAnmTexPattern*, J3DModelData*, f32, int);
    /* 80148338 */ int setBtkAnm(J3DAnmTextureSRTKey*, J3DModelData*, f32, int);
    /* 80148378 */ int setBrkAnm(J3DAnmTevRegKey*, J3DModelData*, f32, int);
    /* 801483B8 */ int setBpkAnm(J3DAnmColor*, J3DModelData*, f32, int);
    /* 801483F8 */ int loadRes(s8 const*, char const**);
    /* 801484AC */ void deleteRes(s8 const*, char const**);
    /* 8014852C */ int execute();
    /* 8014886C */ int draw(BOOL, BOOL, f32, _GXColorS10*, f32, BOOL, BOOL, BOOL);
    /* 80148C70 */ void setEnvTevColor();
    /* 80148CCC */ void setRoomNo();
    /* 80148D10 */ int checkEndAnm(f32);
    /* 80148DD0 */ int checkEndAnm(J3DFrameCtrl*, f32);
    /* 80148E4C */ void playAllAnm();
    /* 80149190 */ void setMtx();
    /* 8014924C */ void ctrlFaceMotion();
    /* 80149300 */ void ctrlMotion();
    /* 801493B8 */ int ctrlMsgAnm(int*, int*, fopAc_ac_c*, int);
    /* 8014A224 */ void evtChange();
    /* 8014A388 */ bool setFaceMotionAnm(int, bool);
    /* 8014A908 */ void setPos(cXyz);
    /* 8014AA18 */ void setAngle(s16);
    /* 8014A99C */ void setAngle(csXyz);
    /* 8014AA40 */ fopAc_ac_c* hitChk(dCcD_GObjInf*, u32);
    /* 8014AAD0 */ void setDamage(int, int, int);
    /* 8014ABD0 */ BOOL chkActorInSight(fopAc_ac_c*, f32, s16);
    /* 8014ACF0 */ BOOL chkPointInArea(cXyz, cXyz, f32, f32, f32, s16);
    /* 8014ADA0 */ BOOL chkPointInArea(cXyz, cXyz, cXyz, s16);
    /* 8014AE1C */ BOOL chkFindActor(fopAc_ac_c*, BOOL, s16);
    /* 8014B024 */ BOOL chkWolfAction();
    /* 8014B0C8 */ BOOL chkFindWolf(s16, int, int, f32, f32, f32, f32, BOOL);
    /* 8014B338 */ BOOL srchPlayerActor();
    /* 8014B3EC */ cXyz getAttnPos(fopAc_ac_c*);
    /* 8014B4A4 */ BOOL turn(s16, int, int);
    /* 8014B648 */ BOOL step(s16, int, int, int, int);
    /* 8014B808 */ void calcSpeedAndAngle(cXyz, BOOL, s16, s16);
    /* 8014BB00 */ int getActorDistance(fopAc_ac_c*, int, int);
    /* 8014BBF0 */ BOOL initTalk(int, fopAc_ac_c**);
    /* 8014BC78 */ BOOL talkProc(int*, BOOL, fopAc_ac_c**, BOOL);
    /* 8014BE2C */ fopAc_ac_c* getNearestActorP(s16);
    /* 8014BEE4 */ fopAc_ac_c* getEvtAreaTagP(int, int);
    /* 8014BFB0 */ fopAc_ac_c* getShopItemTagP();
    /* 8014C030 */ void setHitodamaPrtcl();

    /* 8014CD20 */ virtual ~daNpcT_c() {}
    /* 801490D4 */ virtual BOOL ctrlBtk();
    /* 8014CC14 */ virtual void ctrlSubFaceMotion(int) {}
    /* 8014CC40 */ virtual BOOL checkChangeJoint(int) { return FALSE; }
    /* 8014CC38 */ virtual BOOL checkRemoveJoint(int) { return FALSE; }
    /* 8014CC5C */ virtual s32 getBackboneJointNo() { return -1; }
    /* 8014CC54 */ virtual s32 getNeckJointNo() { return -1; }
    /* 8014CC4C */ virtual s32 getHeadJointNo() { return -1; }
    /* 8014CC90 */ virtual s32 getFootLJointNo() { return -1; }
    /* 8014CC88 */ virtual s32 getFootRJointNo() { return -1; }
    /* 8014D0A8 */ virtual u16 getEyeballLMaterialNo() { return 0; }
    /* 8014D0B0 */ virtual u16 getEyeballRMaterialNo() { return 0; }
    /* 8014D0B8 */ virtual u16 getEyeballMaterialNo() { return 0; }
    /* 8014951C */ virtual int ctrlJoint(J3DJoint*, J3DModel*);
    /* 8014CC48 */ virtual void afterJntAnm(int) {}
    /* 8014CC24 */ virtual void setParam() {}
    /* 8014CC80 */ virtual BOOL checkChangeEvt() { return FALSE; }
    /* 8014CC78 */ virtual BOOL evtTalk() { return TRUE; }
    /* 8014CC70 */ virtual BOOL evtEndProc() { return TRUE; }
    /* 8014CC68 */ virtual BOOL evtCutProc() { return FALSE; }
    /* 8014CC64 */ virtual void setAfterTalkMotion() {}
    /* 8014997C */ virtual BOOL evtProc();
    /* 8014CC20 */ virtual void action() {}
    /* 8014CC1C */ virtual void beforeMove() {}
    /* 8014CC18 */ virtual void afterMoved() {}
    /* 8014CC10 */ virtual void setAttnPos() {}
    /* 80149BB4 */ virtual void setFootPos();
    /* 8014CC0C */ virtual void setCollision() {}
    /* 80149D7C */ virtual void setFootPrtcl(cXyz*, f32, f32);
    /* 8014A05C */ virtual bool checkCullDraw();
    /* 8014A064 */ virtual void twilight();
    /* 8014CC98 */ virtual BOOL chkXYItems() { return FALSE; }
    /* 8014A0B0 */ virtual void evtOrder();
    /* 8014CBF4 */ virtual void decTmr() {
        if (mDamageTimer != 0) {
            mDamageTimer--;
        }
    }
    /* 8014A324 */ virtual void clrParam();
    /* 8014CC30 */ virtual int drawDbgInfo() { return 0; }
    /* 8014CC28 */ virtual void drawOtherMdl() {}
    /* 8014CC2C */ virtual void drawGhost() {}
    /* 8014CCA0 */ virtual bool afterSetFaceMotionAnm(int, int, f32, int) { return true; }
    /* 8014CCE0 */ virtual bool afterSetMotionAnm(int, int, f32, int) { return true; }
    /* 8014CCB0 */ virtual daNpcT_faceMotionAnmData_c getFaceMotionAnm(daNpcT_faceMotionAnmData_c param_1) { return param_1; }
    /* 8014CCF0 */ virtual daNpcT_motionAnmData_c getMotionAnm(daNpcT_motionAnmData_c param_1) { return param_1; }
    /* 8014CCEC */ virtual void changeAnm(int*, int*) {}
    /* 8014CCAC */ virtual void changeBck(int*, int*) {}
    /* 8014CCA8 */ virtual void changeBtp(int*, int*) {}
    /* 8014CCE8 */ virtual void changeBtk(int*, int*) {}
    /* 8014A628 */ virtual bool setMotionAnm(int, f32, BOOL);

    bool checkHide() { return mHide || (!dComIfGs_wolfeye_effect_check() && mTwilight); }
    BOOL checkStep() { return mStepMode == 1; }
    void setCommander(fopAc_ac_c* param_0) { field_0xba0.entry(param_0); }
    void setCutType(int i_cutType) { mCutType = i_cutType; }
    void onHide() { mHide = true; }
    void offHide() { mHide = false; }
    void hide() { onHide(); }
    void show() { offHide(); }

    void initialize() {
        memset(&mFootLPos, 0, (u8*)&field_0xe38 - (u8*)&mFootLPos);
        mFaceMotionSeqMngr.initialize();
        mMotionSeqMngr.initialize();
        mPlayerActorMngr.initialize();
        field_0xba0.initialize();
        mJntAnm.initialize();
        mStagger.initialize();
        mItemPartnerId = fpcM_ERROR_PROCESS_ID_e;
        field_0xe26 = true;
        field_0xe1a = cM_rndF(65536.0f);
        field_0xde0 = 0.2f;
        field_0xde4 = 0.2f;
    }

    static dCcD_SrcGObjInf const mCcDObjData;
    static dCcD_SrcCyl mCcDCyl;
    static dCcD_SrcSph mCcDSph;
    static fopAc_ac_c* mFindActorPtrs[50];
    static s16 mSrchName;
    static s32 mFindCount;

    enum Mode {
        /*  0 */ MODE_ENTER,
        /*  1 */ MODE_INIT,
        /*  2 */ MODE_RUN,
        /*  3 */ MODE_EXIT,
        /*  4 */ MODE_4,
        /* -1 */ MODE_INVALID = -1,
    };

    enum AnmFlags {
        ANM_PAUSE_MORF = 0x1,
        ANM_PAUSE_BTK = 0x2,
        ANM_PAUSE_BRK = 0x4,
        ANM_PAUSE_BPK = 0x8,
        ANM_PAUSE_BCK = 0x10,
        ANM_PAUSE_BTP = 0x20,
        ANM_PLAY_MORF = 0x40,
        ANM_PLAY_BTK = 0x80,
        ANM_PLAY_BRK = 0x100,
        ANM_PLAY_BPK = 0x200,
        ANM_PLAY_BCK = 0x400,
        ANM_PLAY_BTP = 0x800,
        ANM_FLAG_1000 = 0x1000,
        ANM_PAUSE_TIMER_BTP = 0x2000,
        ANM_FLAG_4000 = 0x4000,
    };
};

STATIC_ASSERT(sizeof(daNpcT_c) == 0xE40);

BOOL daNpcT_chkEvtBit(u32 i_idx);
BOOL daNpcT_chkPointInArea(cXyz param_0, cXyz param_1, cXyz param_2, s16 param_3, BOOL param_4);
u8 daNpcT_getDistTableIdx(int param_0, int param_1);
BOOL daNpcT_chkDoBtnIsSpeak(fopAc_ac_c* i_ActorP);
void daNpcT_offTmpBit(u32 i_idx);
void daNpcT_onTmpBit(u32 i_idx);
BOOL daNpcT_chkTmpBit(u32 i_idx);
void daNpcT_onEvtBit(u32 i_idx);
BOOL daNpcT_chkTmpBit(u32 i_idx);
BOOL daNpcT_getPlayerInfoFromPlayerList(int param_0, int i_roomNo, cXyz* o_spawnPos,
                                        csXyz* o_angle);

class daBaseNpc_matAnm_c : public J3DMaterialAnm {
public:
    /* 80150444 */ virtual ~daBaseNpc_matAnm_c() {}
    /* 8014D884 */ virtual void calc(J3DMaterial*) const;

    /* 0x0F4 */ mutable f32 field_0xF4;
    /* 0x0F8 */ mutable f32 field_0xF8;
    /* 0x0FC */ f32 mNowOffsetX;
    /* 0x100 */ f32 mNowOffsetY;
    /* 0x104 */ u8 mEyeMoveFlg;
    /* 0x105 */ u8 mMorfFrm;
};

class daBaseNpc_acMngr_c {
public:
    /* 8014D804 */ daBaseNpc_acMngr_c();
    /* 8014D81C */ void entry(fopAc_ac_c*);
    /* 8014D838 */ fopAc_ac_c* getActor();
    /* 80150524 */ virtual ~daBaseNpc_acMngr_c() {}

private:
    /* 0x04 */ fpc_ProcID mActorId;
};

class daBaseNpc_path_c {
public:
    /* 8014D998 */ daBaseNpc_path_c();
    /* 8014D9A8 */ BOOL isPath();
    /* 8014D9BC */ int setPathInfo(u8, s8, s8);
    /* 8014DA48 */ void reverseDir();
    /* 8014DA64 */ s32 chkPnt(cXyz);
    /* 8014DAC4 */ BOOL setNextPnt();
    /* 8014DB04 */ u16 getIdx();
    /* 8014DB0C */ void setIdx(u16);
    /* 8014DB14 */ Vec getPntPos(u16);
    /* 801503FC */ virtual ~daBaseNpc_path_c() {}

    static const int MAXNUMCONTROLPNT_e = 64;

public:
    /* 0x004 */ dPath* mPathInfo;
    /* 0x008 */ f32 field_0x8;
    /* 0x00C */ dPnt mCurvePnts[160];
    /* 0xA0C */ u8 field_0xa0c[0xA0E - 0xA0C];
    /* 0xA0E */ u16 mCurvePntNum;
    /* 0xA10 */ u16 mIdx;
    /* 0xA12 */ s8 mDirection;
    /* 0xA13 */ u8 field_0xa13;
    /* 0xA14 */ s16 field_0xa14;
    /* 0xA16 */ u8 field_0xa16[2];
    /* 0xA18 */ int field_0xa18;
    /* 0xA1C */ u8 field_0xa1c[8];
};

class daBaseNpc_lookat_c {
public:
    /* 8014DB40 */ void limitter(s16, s16*, s16, s16);
    /* 8014DBB4 */ void calc(fopAc_ac_c*, f32 (*)[4], s16);
    /* 8014E634 */ void setMaxJntLmt(csXyz, int);
    /* 8014E658 */ void setMinJntLmt(csXyz, int);
    /* 8014E67C */ void setJntPos(cXyz, int);
    /* 8014E6A0 */ int setAttnPos(cXyz*);
    /* 8014E6AC */ csXyz getRot(int);
    /* 801502EC */ virtual ~daBaseNpc_lookat_c() {}

    /* 0x04 */ csXyz mMaxJntLmt[4];
    /* 0x1C */ csXyz mMinJntLmt[4];
    /* 0x34 */ cXyz mJntPos[4];
    /* 0x64 */ csXyz field_0x64[4];
    /* 0x7C */ csXyz mRot[4];
    /* 0x94 */ u8 field_0x94[4];
    /* 0x98 */ cXyz* mpAttnPos;
};

class daBaseNpc_c : public fopAc_ac_c {
public:
    /* 8014E6C8 */ daBaseNpc_c();
    /* 8014EE44 */ J3DAnmTransform* getTrnsfrmKeyAnmP(char*, int);
    /* 8014EE80 */ int setMcaMorfAnm(J3DAnmTransformKey*, f32, f32, int, int, int);
    /* 8014EEE4 */ int setBckAnm(J3DAnmTransform*, f32, int, int, int, bool);
    /* 8014EF28 */ J3DAnmTransform* getTexPtrnAnmP(char*, int);
    /* 8014EF64 */ int setBtpAnm(J3DAnmTexPattern*, J3DModelData*, f32, int);
    /* 8014EFF4 */ void orderEvent(int, char*);
    /* 8014F0A0 */ void setEnvTevColor();
    /* 8014F0FC */ void setRoomNo();
    /* 8014F148 */ int checkEndAnm(f32);
    /* 8014F1C8 */ int checkEndAnm(J3DFrameCtrl*);

    /* 8014E89C */ virtual ~daBaseNpc_c();
    /* 8014EAD0 */ virtual int execute();
    /* 8014EC50 */ virtual int draw(f32);
    /* 8014EE3C */ virtual const char* getResName();
    /* 8014EFA4 */ virtual void attnSttsOn(int, int);
    /* 8014EFF0 */ virtual void setParam();
    /* 8014F09C */ virtual void mainProc();
    /* 8014F140 */ virtual BOOL btkCtrl();
    /* 8014F228 */ virtual void allAnmPlay();
    /* 8014F38C */ virtual void adjustShapeAngle();
    /* 8014F390 */ virtual void setMtx(int);
    /* 8014F4A0 */ virtual void setCollisions();
    /* 8014F4A4 */ virtual void setAttnPos();
    /* 8014F4A8 */ virtual void drawOtherMdls();
    /* 8014F4AC */ virtual bool dbgDraw();

    static dCcD_SrcGObjInf const mCcDObj;
    static dCcD_SrcCyl mCcDCyl;
    static dCcD_SrcSph mCcDSph;

public:
    /* 0x56C */ dBgS_ObjAcch mAcch;
    /* 0x744 */ char field_0x744;
    /* 0x745 */ u8 field_0x745[0x74c - 0x745];
    /* 0x74C */ request_of_phase_process_class mPhase;
    /* 0x754 */ mDoExt_McaMorfSO* mpModelMorf;
    /* 0x758 */ Z2Creature mSound;
    /* 0x7E8 */ u32 mShadowId;
    /* 0x7EC */ mDoExt_bckAnm mBck;
    /* 0x808 */ mDoExt_btpAnm mBtp;
    /* 0x820 */ mDoExt_btkAnm mBtk;
    /* 0x838 */ s16 field_0x838;
    /* 0x83C */ u16* field_0x83c;
    /* 0x840 */ u16 field_0x840;
    /* 0x842 */ u16 field_0x842;
    /* 0x844 */ bool field_0x844;
    /* 0x845 */ u8 field_0x845[0x848 - 0x845];
    /* 0x848 */ s32 field_0x848;
    /* 0x84C */ dMsgFlow_c mMsgFlow;
    /* 0x898 */ u8 field_0x898[0x89A - 0x898];
    /* 0x89A */ s16 mEvtIdx;
    /* 0x89C */ dCcD_Stts mCcStts;
    /* 0x8D8 */ dBgS_AcchCir mAcchCir;
    /* 0x918 */ s16 field_0x918;
    /* 0x91A */ csXyz field_0x91a;
    /* 0x920 */ daBaseNpc_lookat_c mLookat;
    /* 0x9BC */ csXyz field_0x9bc;
    /* 0x9C2 */ csXyz field_0x9c2;
    /* 0x9C8 */ csXyz field_0x9c8;
    /* 0x9CE */ csXyz field_0x9ce;
    /* 0x9D4 */ cBgS_GndChk field_0x9d4;
    /* 0xA10 */ f32 mGroundY;
};

STATIC_ASSERT(sizeof(daBaseNpc_c) == 0xA14);

class daBaseNpc_moveBgActor_c : public daBaseNpc_c {
public:
    /* 8014F4B4 */ daBaseNpc_moveBgActor_c();
    /* 8014F518 */ int MoveBGCreateHeap();
    /* 8014F60C */ int MoveBGCreate(char const*, int, MoveBGActor_SetFunc, u32);
    /* 8014F6FC */ int MoveBGDelete();
    /* 8014F770 */ int MoveBGExecute();

    /* 80155FB0 */ virtual ~daBaseNpc_moveBgActor_c() {}
    /* 801503BC */ virtual int CreateHeap() { return 1; }
    /* 801503C4 */ virtual int Create() { return 1; }
    /* 801503D4 */ virtual int Execute(Mtx**) { return 1; }
    /* 801503DC */ virtual int Draw() { return 1; }
    /* 801503CC */ virtual int Delete() { return 1; }
    /* 801503E4 */ virtual int IsDelete() { return 1; }
    /* 801503EC */ virtual int ToFore() { return 1; }
    /* 801503F4 */ virtual int ToBack() { return 1; }

    static const char* m_name;
    static int m_dzb_id;
    static MoveBGActor_SetFunc m_set_func;

public:
    /* 0xA14 */ dBgW* mpBgw;
    /* 0xA18 */ Mtx mBgMtx;
};

class daNpcF_ActorMngr_c {
private:
    /* 0x0 */ fpc_ProcID mActorID;

public:
    daNpcF_ActorMngr_c() { initialize(); }

    /* 801506B0 */ void initialize();
    /* 801506D8 */ void entry(unsigned int);
    /* 801506BC */ void entry(fopAc_ac_c*);
    /* 801506E0 */ void remove();
    /* 801506EC */ fopAc_ac_c* getActorP();

    fpc_ProcID getPId() { return mActorID; }

    /* 80155E40 */ virtual ~daNpcF_ActorMngr_c() {}
};

class daNpcF_c : public fopAc_ac_c {
protected:
    /* 0x568 */ mDoExt_McaMorfSO* mpMorf;
    /* 0x56C */ mDoExt_bckAnm mBckAnm;
    /* 0x588 */ mDoExt_btpAnm mBtpAnm;
    /* 0x5A0 */ mDoExt_btkAnm mBtkAnm;
    /* 0x5B8 */ mDoExt_brkAnm mBrkAnm;
    /* 0x5D0 */ dBgS_ObjAcch mAcch;
    /* 0x7A8 */ dCcD_Stts mCcStts;
    /* 0x7E4 */ dBgS_AcchCir mAcchCir;
    /* 0x824 */ daNpcF_ActorMngr_c field_0x824;
    /* 0x82C */ daNpcF_ActorMngr_c mAttnActor[5];
    /* 0x854 */ cXyz mLookatPos[3];
    /* 0x878 */ cXyz mLookPos;
    /* 0x884 */ cXyz field_0x884;
    /* 0x890 */ cXyz field_0x890;
    /* 0x89C */ cXyz field_0x89c;
    /* 0x8A8 */ cXyz field_0x8a8;
    /* 0x8B4 */ cXyz field_0x8b4;
    /* 0x8C0 */ cXyz field_0x8c0;
    /* 0x8CC */ cXyz field_0x8cc;
    /* 0x8D8 */ cXyz field_0x8d8;
    /* 0x8E4 */ cXyz mHeadPos;
    /* 0x8F0 */ csXyz mCurAngle;
    /* 0x8F6 */ csXyz mOldAngle;
    /* 0x8FC */ csXyz mEyeAngle;
    /* 0x902 */ csXyz mHeadAngle;
    /* 0x908 */ csXyz field_0x908[3];
    /* 0x91A */ csXyz mLookatAngle[3];
    /* 0x92C */ int mStaffID;
    /* 0x930 */ int mCutType;
    /* 0x934 */ int mAttnIdx;
    /* 0x938 */ int mAttnChangeTimer;
    /* 0x93C */ int mAttnActorTimer[5];
    /* 0x950 */ int mMsgTimer;
    /* 0x954 */ int mDamageTimer;
    /* 0x958 */ int mTotalDamageTimer;
    /* 0x95C */ int field_0x95c;
    /* 0x960 */ int mEventTimer;
    /* 0x964 */ int mBtpTimer;
    /* 0x968 */ int mTurnAmount;
    /* 0x96C */ int mTurnMode;
    /* 0x970 */ f32 mTurnStepNum;
    /* 0x974 */ f32 mExpressionMorfOverride;
    /* 0x978 */ f32 mExpressionMorf;
    /* 0x97C */ f32 mMotionMorfOverride;
    /* 0x980 */ f32 mGroundH;
    /* 0x984 */ f32 field_0x984[3];
    /* 0x990 */ s16 field_0x990;
    /* 0x992 */ s16 field_0x992;
    /* 0x994 */ s16 mTurnStartAngle;
    /* 0x996 */ s16 mTurnTargetAngle;
    /* 0x998 */ u16 field_0x998;
    /* 0x99C */ u32 mAnmFlags;
    /* 0x9A0 */ u32 mShadowKey;
    /* 0x9A4 */ u32 field_0x9a4;
    /* 0x9A8 */ u32 mHitodamaParticleKey[2];
    /* 0x9B0 */ u32 mPolySound;
    /* 0x9B4 */ int mFlowNodeNo;
    /* 0x9B8 */ cXyz field_0x9b8;
    /* 0x9C4 */ cXyz field_0x9c4;
    /* 0x9D0 */ s16 field_0x9d0;
    /* 0x9D2 */ s16 field_0x9d2;
    /* 0x9D4 */ s16 mEventIdx;
    /* 0x9D6 */ s16 mExpressionPhase;
    /* 0x9D8 */ s16 mExpressionPrevPhase;
    /* 0x9DA */ s16 mMotionPhase;
    /* 0x9DC */ s16 mMotionPrevPhase;
    /* 0x9DE */ s16 mExpression;
    /* 0x9E0 */ s16 mMotion;
    /* 0x9E2 */ u16 mMotionLoops;
    /* 0x9E4 */ u16 mExpressionLoops;
    /* 0x9E6 */ u16 mOrderEvtNo;
    /* 0x9E8 */ s8 mReverb;
    /* 0x9E9 */ bool mOrderSpeakEvt;
    /* 0x9EA */ bool field_0x9ea;
    /* 0x9EB */ bool field_0x9eb;
    /* 0x9EC */ bool field_0x9ec;
    /* 0x9ED */ bool mOrderNewEvt;
    /* 0x9EE */ bool field_0x9ee;
    /* 0x9EF */ u8 field_0x9ef;
    /* 0x9F0 */ bool mIsDamaged;
    /* 0x9F1 */ u8 field_0x9f1;
    /* 0x9F2 */ bool mHide;
    /* 0x9F3 */ u8 field_0x9f3;
    /* 0x9F4 */ bool mTwilight;
    /* 0x9F5 */ u8 field_0x9f5;
    /* 0x9F6 */ u8 field_0x9f6;
    /* 0x9F8 */ dMsgFlow_c mFlow;
    /* 0xA44 */ cBgS_GndChk mGndChk;
    /* 0xA80 */ dBgS_GndChk field_0xa80;
    /* 0xAD4 */ dBgS_LinChk field_0xad4;

public:
    struct daNpcF_anmPlayData {
        u16 idx;
        f32 morf;
        s32 numLoops;
    };

    enum AnmFlags {
        ANM_PAUSE_MORF = 0x0001,
        ANM_PAUSE_BTK = 0x0002,
        ANM_PAUSE_BRK = 0x0004,
        ANM_PLAY_MORF = 0x0008,
        ANM_PLAY_BTK = 0x0010,
        ANM_PLAY_BRK = 0x0020,
        ANM_PAUSE_BCK = 0x0040,
        ANM_PAUSE_BTP = 0x0080,
        ANM_PLAY_BCK = 0x0100,
        ANM_PLAY_BTP = 0x0200,
        ANM_FLAG_400 = 0x0400,
        ANM_FLAG_800 = 0x0800,
        ANM_PAUSE_EXPRESSION = 0x1000,
        ANM_PAUSE_BPK = 0x2000,
        ANM_PLAY_BPK = 0x4000,
        ANM_MOTION_FLAGS = ANM_PAUSE_MORF | ANM_PAUSE_BTK | ANM_PAUSE_BRK | ANM_PLAY_MORF |
                           ANM_PLAY_BTK | ANM_PLAY_BRK,
        ANM_EXPRESSION_FLAGS = ANM_PAUSE_BCK | ANM_PAUSE_BTP | ANM_PLAY_BCK | ANM_PLAY_BTP |
                               ANM_FLAG_400 | ANM_FLAG_800 | ANM_PAUSE_EXPRESSION,
        ANM_PAUSE_ALL = ANM_PAUSE_MORF | ANM_PAUSE_BTK | ANM_PAUSE_BRK | ANM_PAUSE_BCK |
                        ANM_PAUSE_BTP | ANM_PAUSE_EXPRESSION,
    };

    enum LookMode {
        /* 0 */ LOOK_NONE,
        /* 1 */ LOOK_RESET,
        /* 2 */ LOOK_PLAYER,
        /* 3 */ LOOK_PLAYER_TALK,
        /* 4 */ LOOK_ACTOR,
        /* 5 */ LOOK_ATTN,
    };

    daNpcF_c() { initialize(); }
    /* 80152014 */ BOOL execute();
    /* 801522AC */ int draw(BOOL, BOOL, f32, _GXColorS10*, BOOL);
    /* 80152614 */ static void tgHitCallBack(fopAc_ac_c*, dCcD_GObjInf*, fopAc_ac_c*,
                                             dCcD_GObjInf*);
    /* 80152654 */ static void* srchAttnActor1(void*, void*);
    /* 801526E8 */ static void* srchActor(void*, void*);

    /* 801528C8 */ void initialize();
    /* 80152B2C */ J3DAnmTransformKey* getTrnsfrmKeyAnmP(char*, int);
    /* 80152B68 */ J3DAnmTexPattern* getTexPtrnAnmP(char*, int);
    /* 80152BA4 */ J3DAnmTextureSRTKey* getTexSRTKeyAnmP(char*, int);
    /* 80152BE0 */ J3DAnmTevRegKey* getTevRegKeyAnmP(char*, int);
    /* 80152C1C */ BOOL setMcaMorfAnm(J3DAnmTransformKey* i_anm, f32 i_rate, f32 i_morf, int i_attr,
                                      int i_start, int i_end);
    /* 80152C80 */ BOOL setBckAnm(J3DAnmTransform* i_bck, f32 i_rate, int i_attr, int i_start,
                                  int i_end, bool i_modify);
    /* 80152CC4 */ BOOL setBtpAnm(J3DAnmTexPattern* i_btp, J3DModelData* i_modelData, f32 i_rate,
                                  int i_attr);
    /* 80152D04 */ BOOL setBtkAnm(J3DAnmTextureSRTKey* i_btk, J3DModelData* i_modelData, f32 i_rate,
                                  int i_attr);
    /* 80152D44 */ BOOL setBrkAnm(J3DAnmTevRegKey* i_brk, J3DModelData* i_modelData, f32 i_rate,
                                  int i_attr);
    /* 80152D84 */ void setEnvTevColor();
    /* 80152DE0 */ void setRoomNo();
    /* 80152E24 */ BOOL chkEndAnm(f32);
    /* 80152EC4 */ BOOL chkEndAnm(J3DFrameCtrl*, f32);
    /* 80152F40 */ BOOL playAllAnm();
    /* 80153150 */ void playExpressionAnm(daNpcF_c::daNpcF_anmPlayData***);
    /* 80153264 */ void playMotionAnm(daNpcF_c::daNpcF_anmPlayData***);
    /* 8015337C */ void setLookatMtx(int, int*, f32);
    /* 80153578 */ BOOL hitChk2(dCcD_Cyl*, BOOL, BOOL);
    /* 80153658 */ void setDamage(int, int, int);
    /* 80153718 */ int ctrlMsgAnm(int&, int&, fopAc_ac_c*, BOOL);
    /* 8015387C */ void orderEvent(int, char*, u16, u16, u8, u16);
    /* 80153954 */ void changeEvent(char*, char*, u16, u16);
    /* 801539F0 */ BOOL chkActorInSight(fopAc_ac_c*, f32);
    /* 80153A78 */ BOOL chkActorInArea(fopAc_ac_c*, cXyz, cXyz, s16);
    /* 80153BDC */ BOOL chkActorInAttnArea(fopAc_ac_c*, fopAc_ac_c*, int);
    /* 80153D1C */ BOOL initTalk(int, fopAc_ac_c**);
    /* 80153D84 */ BOOL talkProc(int*, BOOL, fopAc_ac_c**);
    /* 80153EF4 */ BOOL turn(s16, f32, int);
    /* 801540A4 */ BOOL step(s16, int, int, int);
    /* 80154250 */ void setAngle(s16);
    /* 80154278 */ u8 getDistTableIdx(int, int);
    /* 801542A0 */ fopAc_ac_c* getEvtAreaTagP(int, int);
    /* 8015436C */ fopAc_ac_c* getAttnActorP(BOOL, fpcLyIt_JudgeFunc, f32, f32, f32, f32, s16,
                                             int, BOOL);
    /* 80154730 */ BOOL chkActorInSight2(fopAc_ac_c*, f32, s16);
    /* 80154834 */ BOOL chkPointInArea(cXyz, cXyz, f32, f32, f32, s16);
    /* 801548F4 */ BOOL chkPointInArea(cXyz, cXyz, cXyz, s16);
    /* 8015496C */ cXyz getAttentionPos(fopAc_ac_c*);
    /* 801549E0 */ BOOL chkFindPlayer2(BOOL, s16);
    /* 80154BD8 */ void setHitodamaPrtcl();

    /* 80155BF4 */ virtual ~daNpcF_c() {}
    /* 80155BC8 */ virtual void setParam() {}
    /* 80155BC0 */ virtual BOOL main() { return TRUE; }
    /* 80155BD8 */ virtual BOOL ctrlBtk() { return FALSE; }
    /* 80155BBC */ virtual void adjustShapeAngle() {}
    /* 8015276C */ virtual void setMtx();
    /* 801527FC */ virtual void setMtx2();
    /* 80155BB8 */ virtual void setAttnPos() {}
    /* 80155BB4 */ virtual void setCollisions() {}
    /* 80155BE0 */ virtual bool setExpressionAnm(int i_idx, bool i_modify) { return true; }
    /* 80155EC8 */ virtual bool setExpressionBtp(int i_idx) { return true; }
    /* 80155BF0 */ virtual void setExpression(int i_expression, f32 i_morf) {}
    /* 80155BE8 */ virtual void setMotionAnm(int i_idx, f32 i_morf) {}
    /* 80155BEC */ virtual void setMotion(int i_motion, f32 i_morf, int i_restart) {}
    /* 80155BD0 */ virtual BOOL drawDbgInfo() { return TRUE; }
    /* 80155BCC */ virtual void drawOtherMdls() {}

    BOOL chkActorInSpeakArea(fopAc_ac_c* i_actorCheck, fopAc_ac_c* i_actorArea) {
        return chkActorInAttnArea(i_actorCheck, i_actorArea, attention_info.distances[fopAc_attn_SPEAK_e]);
    }
    BOOL chkPlayerInSpeakArea(fopAc_ac_c* i_actor) {
        return chkActorInSpeakArea(daPy_getPlayerActorClass(), i_actor);
    }
    BOOL chkActorInTalkArea(fopAc_ac_c* i_actorCheck, fopAc_ac_c* i_actorArea) {
        return chkActorInAttnArea(i_actorCheck, i_actorArea, attention_info.distances[fopAc_attn_TALK_e]);
    }
    BOOL chkPlayerInTalkArea(fopAc_ac_c* i_actor) {
        return chkActorInTalkArea(daPy_getPlayerActorClass(), i_actor);
    }
    BOOL checkHide() { return mHide || (mTwilight && !dComIfGs_wolfeye_effect_check()); }
    void setIntDemander(fopAc_ac_c* i_actor) { field_0x824.entry(i_actor); }
    void setIntFlowNodeNo(int i_flowNodeNo) { mFlowNodeNo = i_flowNodeNo; }
    void setCutType(int i_cutType) { mCutType = i_cutType; }
    void onInterrupt(u8 param_0) { field_0x9ef = param_0; }

    static dCcD_SrcGObjInf const mCcDObjInfo;
    static dCcD_SrcCyl mCcDCyl;
    static dCcD_SrcSph mCcDSph;
    static fopAc_ac_c* mFindActorPList[100];
    static s32 mFindCount;
    static s16 mSrchActorName;
};

STATIC_ASSERT(sizeof(daNpcF_c) == 0xB48);

BOOL daNpcF_chkEvtBit(u32 i_idx);
void daNpcF_onEvtBit(u32 i_idx);
BOOL daNpcF_chkTmpBit(u32 i_idx);
void daNpcF_onTmpBit(u32 i_idx);
void daNpcF_offTmpBit(u32 i_idx);
u8 daNpcF_getDistTableIdx(int param_0, int param_1);
void daNpcF_clearMessageTmpBit();
BOOL daNpcF_chkPointInArea(cXyz, cXyz, cXyz, s16);
int daNpcF_getPlayerInfoFromPlayerList(int param_0, int i_roomNo, cXyz& param_2, csXyz& param_3);
s16 daNpcF_getGroundAngle(cBgS_PolyInfo*, s16);
BOOL daNpcF_pntVsLineSegmentLengthSquare2D(f32 i_pntX, f32 i_pntZ, f32 i_startX, f32 i_startZ,
                                           f32 i_endX, f32 i_endZ, f32* o_projX, f32* o_projZ,
                                           f32* o_dist2);
BOOL daNpcF_chkPassed(cXyz i_pos, dPnt* i_points, u16 i_idx, u16 i_num, BOOL i_isClosed,
                      BOOL i_isReversed);

class daNpcF_MatAnm_c : public J3DMaterialAnm {
private:
    /* 0x0F4 */ mutable f32 field_0xF4;
    /* 0x0F8 */ mutable f32 field_0xF8;
    /* 0x0FC */ f32 mNowOffsetX;
    /* 0x100 */ f32 mNowOffsetY;
    /* 0x104 */ u8 mEyeMoveFlag;
    /* 0x105 */ u8 mMorfFrm;

public:
    daNpcF_MatAnm_c() { initialize(); }
    /* 80150738 */ void initialize();
    /* 8015075C */ void calc(J3DMaterial*) const;
    /* 80155ED0 */ ~daNpcF_MatAnm_c() {}
    void setNowOffsetX(float i_nowOffsetX) { mNowOffsetX = i_nowOffsetX; }
    void setNowOffsetY(float i_nowOffsetY) { mNowOffsetY = i_nowOffsetY; }
    void onEyeMoveFlag() { mEyeMoveFlag = 1; }
    void offEyeMoveFlag() { mEyeMoveFlag = 0; }
};

class daNpcF_SPCurve_c {
private:
    /* 0x00 */ u16 mNurbs;
    /* 0x02 */ u16 field_0x02;
    /* 0x04 */ u8 mIsReversed;
    /* 0x05 */ u8 mIsClosed;
    /* 0x08 */ dPnt mPoints[96];

public:
    /* 80150870 */ void initialize(dPath*, int);

    daNpcF_SPCurve_c() {
        initialize(NULL, 0);
    }

    virtual ~daNpcF_SPCurve_c() {}
};  // Size: 0x60C

class daNpcF_Path_c {
protected:
    /* 0x00 */ u16 mIdx;
    /* 0x02 */ u8 mIsReversed;
    /* 0x03 */ bool mIsClosed;
    /* 0x04 */ dPath* mPathInfo;
    /* 0x08 */ f32 mRange;
    /* 0x0C */ f32 mPosDst;
    /* 0x10 */ f32 field_0x10;
    /* 0x14 */ cXyz mPosition;
    /* 0x20 */ daNpcF_SPCurve_c mSPCurve;

public:
    /* 80150900 */ void initialize();
    /* 8015095C */ int setPathInfo(u8, s8, u8);
    /* 80150A24 */ BOOL chkPassed(cXyz);
    /* 80150A7C */ BOOL chkPassedDst(cXyz);
    /* 80150BBC */ void reverse();
    /* 80150BE0 */ BOOL setNextIdx();
    /* 80150C18 */ int getNextIdx();
    /* 80150C60 */ int getBeforeIdx();
    /* 80150CA8 */ BOOL getBeforePos(cXyz&);
    /* 80150D44 */ BOOL getNextPos(cXyz&);
    /* 80150DE0 */ BOOL getDstPos(cXyz, cXyz&);
    /* 80150EB4 */ void setNextIdxDst(cXyz);

    daNpcF_Path_c() {
        initialize();
    }

    virtual ~daNpcF_Path_c() {}

    int getIdx() { return mIdx; };
    void setIdx(int i_idx) { mIdx = i_idx; }
    int getArg0() { return mPathInfo->m_points[mIdx].mArg0; }
    u8 getArg0(int i_idx) { return mPathInfo->m_points[i_idx].mArg0; }
    Vec getPntPos(int i_idx) { return mPathInfo->m_points[i_idx].m_position; }
    BOOL chkClose() { return dPath_ChkClose(mPathInfo); }
    BOOL chkReverse() { return mIsReversed == true; }
    void onReverse() { mIsReversed = true; }
    void offReverse() { mIsReversed = false; }
    dPath* getPathInfo() { return mPathInfo; }
    void setRange(f32 i_range) { mRange = i_range; }
};  // Size: 0x630

class daNpcF_Lookat_c {
private:
    /* 0x00 */ cXyz mJointPos[4];
    /* 0x30 */ cXyz* mAttnPos_p;
    /* 0x34 */ csXyz mAngularMoveDis[4];
    /* 0x4C */ csXyz mMinAngle[4];
    /* 0x64 */ csXyz mMaxAngle[4];
    /* 0x7C */ csXyz mRotAngle[4];
    /* 0x94 */ bool field_0x94[4];
    /* 0x98 vtable */

public:
    /* 80151038 */ void initialize();
    /* 801510B8 */ void setParam(f32, f32, f32, f32, f32, f32, f32, f32, f32, f32, f32, f32, s16,
                                 cXyz*);
    /* 80151350 */ void calc(fopAc_ac_c*, Mtx, csXyz**, BOOL, int, BOOL);
    /* 801515D4 */ void adjustMoveDisAngle(s16&, s16, s16, s16);
    /* 80151648 */ void initCalc(fopAc_ac_c*, Mtx, cXyz*, csXyz*, f32*, cXyz&, BOOL);
    /* 80151A54 */ void update(cXyz*, csXyz*, f32*);
    /* 80151B68 */ void calcMoveDisAngle(int, cXyz*, csXyz*, cXyz, int, BOOL);
    /* 80151F54 */ void setRotAngle();
    /* 80151FE0 */ void clrRotAngle();

    daNpcF_Lookat_c() { initialize(); }
    virtual ~daNpcF_Lookat_c() {}

    cXyz* getAttnPos() { return mAttnPos_p; }
    void setAttnPos(cXyz* i_attnPos) { mAttnPos_p = i_attnPos; }
};

class daNpcF_MoveBgActor_c : public daNpcF_c {
private:
public:
    /* 80155B54 */ ~daNpcF_MoveBgActor_c() {}
    /* 80155E88 */ virtual bool CreateHeap() { return true; }
    /* 80155E90 */ virtual bool Create() { return true; }
    /* 80155EA0 */ virtual bool Execute(f32 (**)[3][4]) { return true; }
    /* 80155EA8 */ virtual bool Draw() { return true; }
    /* 80155E98 */ virtual bool Delete() { return true; }
    /* 80155EB0 */ virtual bool IsDelete() { return true; }
    /* 80155EB8 */ virtual bool ToFore() { return true; }
    /* 80155EC0 */ virtual bool ToBack() { return true; }
};

struct daNpcT_HIOParam {
    /* 0x00 */ f32 attention_offset;
    /* 0x04 */ f32 gravity;
    /* 0x08 */ f32 scale;
    /* 0x0C */ f32 real_shadow_size;
    /* 0x10 */ f32 weight;
    /* 0x14 */ f32 height;
    /* 0x18 */ f32 knee_length;
    /* 0x1C */ f32 width;
    /* 0x20 */ f32 body_angleX_max;
    /* 0x24 */ f32 body_angleX_min;
    /* 0x28 */ f32 body_angleY_max;
    /* 0x2C */ f32 body_angleY_min;
    /* 0x30 */ f32 head_angleX_max;
    /* 0x34 */ f32 head_angleX_min;
    /* 0x38 */ f32 head_angleY_max;
    /* 0x3C */ f32 head_angleY_min;
    /* 0x40 */ f32 neck_rotation_ratio;
    /* 0x44 */ f32 morf_frame;
    /* 0x48 */ s16 talk_distance;
    /* 0x4A */ s16 talk_angle;
    /* 0x4C */ s16 attention_distance;
    /* 0x4E */ s16 attention_angle;
    /* 0x50 */ f32 fov;
    /* 0x54 */ f32 search_distance;
    /* 0x58 */ f32 search_height;
    /* 0x5C */ f32 search_depth;
    /* 0x60 */ s16 attention_time;
    /* 0x62 */ s16 damage_time;
    /* 0x64 */ s16 face_expression;
    /* 0x66 */ s16 motion;
    /* 0x68 */ s16 look_mode;
    /* 0x6A */ u8 debug_mode_ON;
    /* 0x6B */ u8 debug_info_ON;
    /* 0x6C */ f32 expression_morf_frame;
    /* 0x70 */ f32 box_min_x;
    /* 0x74 */ f32 box_min_y;
    /* 0x78 */ f32 box_min_z;
    /* 0x7C */ f32 box_max_x;
    /* 0x80 */ f32 box_max_y;
    /* 0x84 */ f32 box_max_z;
    /* 0x88 */ f32 box_offset;
};

void daNpcT_cmnGenMessage(JORMContext*, daNpcT_HIOParam* param_1);

void daNpcT_cmnListenPropertyEvent(char*, int*, daNpcT_HIOParam*);

struct daNpcF_HIOParam {
    /* 0x00 */ f32 attention_offset;
    /* 0x04 */ f32 gravity;
    /* 0x08 */ f32 scale;
    /* 0x0C */ f32 real_shadow_size;
    /* 0x10 */ f32 weight;
    /* 0x14 */ f32 height;
    /* 0x18 */ f32 knee_length;
    /* 0x1C */ f32 width;
    /* 0x20 */ f32 body_angleX_max;
    /* 0x24 */ f32 body_angleX_min;
    /* 0x28 */ f32 body_angleY_max;
    /* 0x2C */ f32 body_angleY_min;
    /* 0x30 */ f32 head_angleX_max;
    /* 0x34 */ f32 head_angleX_min;
    /* 0x38 */ f32 head_angleY_max;
    /* 0x3C */ f32 head_angleY_min;
    /* 0x40 */ f32 neck_rotation_ratio;
    /* 0x44 */ f32 morf_frame;
    /* 0x48 */ s16 talk_distance;
    /* 0x4A */ s16 talk_angle;
    /* 0x4C */ s16 attention_distance;
    /* 0x4E */ s16 attention_angle;
    /* 0x50 */ f32 fov;
    /* 0x54 */ f32 search_distance;
    /* 0x58 */ f32 search_height;
    /* 0x5C */ f32 search_depth;
    /* 0x60 */ s16 attention_time;
    /* 0x62 */ s16 damage_time;
    /* 0x64 */ s16 face_expression;
    /* 0x66 */ s16 motion;
    /* 0x68 */ s16 look_mode;
    /* 0x6A */ u8 debug_mode_ON;
    /* 0x6B */ u8 debug_info_ON;
};

#endif /* D_A_D_A_NPC_H */
