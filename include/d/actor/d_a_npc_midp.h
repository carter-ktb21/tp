#ifndef D_A_NPC_MIDP_H
#define D_A_NPC_MIDP_H

#include "d/actor/d_a_npc.h"

/**
 * @ingroup actors-npcs
 * @class daNpc_midP_c
 * @brief Midna (True Form)
 *
 * @details
 *
*/

struct daNpc_midP_HIOParam {
    /* 0x0 */ daNpcT_HIOParam common;
};

class daNpc_midP_HIO_c : public mDoHIO_entry_c {
    /* 0x8 */ daNpc_midP_HIOParam param;
};

class daNpc_midP_Param_c {
public:
    /* 80A73954 */ virtual ~daNpc_midP_Param_c() {}

    static const daNpc_midP_HIOParam m;
};

class daNpc_midP_c : public daNpcT_c {
public:
    enum Joint {
        /* 0x00 */ JNT_CENTER,
        /* 0x01 */ JNT_BACKBONE1,
        /* 0x02 */ JNT_BACKBONE2,
        /* 0x03 */ JNT_NECK,
        /* 0x04 */ JNT_HEAD,
        /* 0x05 */ JNT_CHIN,
        /* 0x06 */ JNT_MAYUL,
        /* 0x07 */ JNT_MAYUR,
        /* 0x08 */ JNT_MOUTH,
        /* 0x09 */ JNT_SHOULDERL,
        /* 0x0A */ JNT_ARML1,
        /* 0x0B */ JNT_ARML2,
        /* 0x0C */ JNT_HANDL,
        /* 0x0D */ JNT_FINGERL1,
        /* 0x0E */ JNT_FINGERL2,
        /* 0x0F */ JNT_THAMBL,
        /* 0x10 */ JNT_MANTL1,
        /* 0x11 */ JNT_MANTL2,
        /* 0x12 */ JNT_MANT_ANIMEL1,
        /* 0x13 */ JNT_SHOULDERR,
        /* 0x14 */ JNT_ARMR1,
        /* 0x15 */ JNT_ARMR2,
        /* 0x16 */ JNT_HANDR,
        /* 0x17 */ JNT_FINGERR1,
        /* 0x18 */ JNT_FINGERR2,
        /* 0x19 */ JNT_THAMBR,
        /* 0x1A */ JNT_MANTR1,
        /* 0x1B */ JNT_MANTR2,
        /* 0x1C */ JNT_MANT_ANIMER1,
        /* 0x1D */ JNT_WAIST,
        /* 0x1E */ JNT_LEGL1,
        /* 0x1F */ JNT_LEGL2,
        /* 0x20 */ JNT_FOOTL,
        /* 0x21 */ JNT_TOEL,
        /* 0x22 */ JNT_LEGR1,
        /* 0x23 */ JNT_LEGR2,
        /* 0x24 */ JNT_FOOTR,
        /* 0x25 */ JNT_TOER,
        /* 0x26 */ JNT_MANTC1,
        /* 0x27 */ JNT_MANTC2,
        /* 0x28 */ JNT_MANT_ANIMEL2,
        /* 0x29 */ JNT_MANT_ANIMER2,
        /* 0x2A */ JNT_SKIRTB1,
        /* 0x2B */ JNT_SKIRTB2,
        /* 0x2C */ JNT_SKIRTF1,
        /* 0x2D */ JNT_SKIRTF2,
    };

    typedef int (daNpc_midP_c::*cutFunc)(int);
    typedef int (daNpc_midP_c::*actionFunc)(void*);

    enum Type {
        TYPE_0,
        TYPE_1,
    };
    /* 80A70C6C */ ~daNpc_midP_c();
    /* 80A70D90 */ int create();
    /* 80A71074 */ int CreateHeap();
    /* 80A714BC */ int Delete();
    /* 80A714F0 */ int Execute();
    /* 80A71510 */ int Draw();
    /* 80A715D4 */ static int createHeapCallBack(fopAc_ac_c*);
    /* 80A715F4 */ static int ctrlJointCallBack(J3DJoint*, int);
    /* 80A7164C */ u8 getType();
    /* 80A7166C */ int isDelete();
    /* 80A7168C */ void reset();
    /* 80A717D4 */ void afterJntAnm(int);
    /* 80A71860 */ BOOL ctrlBtk();
    /* 80A7199C */ void setParam();
    /* 80A71A98 */ void setAfterTalkMotion();
    /* 80A71AF8 */ void srchActors();
    /* 80A71AFC */ BOOL evtTalk();
    /* 80A71BFC */ BOOL evtCutProc();
    /* 80A71CC4 */ void action();
    /* 80A71DB0 */ void beforeMove();
    /* 80A71E28 */ void setAttnPos();
    /* 80A72064 */ void setCollision();
    /* 80A7216C */ int drawDbgInfo();
    /* 80A72174 */ void drawGhost();
    /* 80A721E0 */ int selectAction();
    /* 80A72228 */ int chkAction(int (daNpc_midP_c::*)(void*));
    /* 80A72254 */ int setAction(int (daNpc_midP_c::*)(void*));
    /* 80A722FC */ int wait(void*);
    /* 80A72548 */ int talk(void*);
    /* 80A737D0 */ daNpc_midP_c(daNpcT_faceMotionAnmData_c const* param_1, daNpcT_motionAnmData_c const* param_2,
                                daNpcT_MotionSeqMngr_c::sequenceStepData_c const* param_3, int param_4,
                                daNpcT_MotionSeqMngr_c::sequenceStepData_c const* param_5, int param_6,
                                daNpcT_evtData_c const* param_7, char** param_8) :
                                daNpcT_c(param_1, param_2, param_3, param_4, param_5, param_6, param_7, param_8) {}
    /* 80A7390C */ u16 getEyeballRMaterialNo() { return 3; }
    /* 80A73914 */ u16 getEyeballLMaterialNo() { return 2; }
    /* 80A7391C */ s32 getHeadJointNo() { return JNT_HEAD; }
    /* 80A73924 */ s32 getNeckJointNo() { return JNT_NECK; }
    /* 80A7392C */ s32 getBackboneJointNo() { return JNT_BACKBONE2; }
    /* 80A73934 */ BOOL checkChangeJoint(int i_joint) { return i_joint == JNT_HEAD; }
    /* 80A73944 */ BOOL checkRemoveJoint(int i_joint) { return i_joint == JNT_MOUTH; }

    int getFlowNodeNo() {
        u16 nodeNo = home.angle.x;
        if (nodeNo == 0xffff) {
            return -1;
        }
        return nodeNo;
    }

    static char* mCutNameList;
    static cutFunc mCutList[1];

private:
    /* 0xE40 */ u8 field_0xE40[0xe44 - 0xe40];
    /* 0xE44 */ dCcD_Cyl mCyl;
    /* 0xF80 */ u8 mType;
    /* 0xF81 */ u8 field_0xf81[0xf84-0xf81];
    /* 0xF84 */ actionFunc field_0xf84;
    /* 0xF90 */ actionFunc field_0xf90;
    /* 0xF9C */ int field_0xf9c;
};

STATIC_ASSERT(sizeof(daNpc_midP_c) == 0xfa0);

#endif /* D_A_NPC_MIDP_H */
