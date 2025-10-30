/**
 * @file d_a_npc_bans.cpp
 * 
*/

#include "d/dolzel_rel.h" // IWYU pragma: keep

#include "d/actor/d_a_npc_bans.h"
#include "JSystem/JHostIO/JORFile.h"
#include "d/d_debug_viewer.h"
#include "d/actor/d_a_tag_evtarea.h"
#include "d/actor/d_a_tag_kmsg.h"
#include "d/actor/d_a_npc_len.h"

enum Bans_RES_File_ID {
    /* BCK */
    /* 0x06 */ BCK_BANS_F_TALK_A = 0x6,
    /* 0x07 */ BCK_BANS_F_TALK_B,
    /* 0x08 */ BCK_BANS_FH_TALK_B,
    /* 0x09 */ BCK_BANS_WAIT_A,

    /* BMDE */
    /* 0x0C */ BMDE_BANS = 0xC,

    /* BTK */
    /* 0x0F */ BTK_BANS = 0xF,

    /* BTP */
    /* 0x12 */ BTP_BANS = 0x12,
};

enum Bans_TW_RES_File_ID {
    /* BCK */
    /* 0x4 */ BCK_BANS_WAIT_TW = 0x4,

    /* BMDR */
    /* 0x7 */ BMDR_BANS_TW = 0x7,
};

enum Bans1_RES_File_ID {
    /* BCK */
    /* 0x04 */ BCK_BANS_ANGRY_A = 0x4,
    /* 0x05 */ BCK_BANS_ANGRY_B,
    /* 0x06 */ BCK_BANS_MASKDOWN,
    /* 0x07 */ BCK_BANS_MASKUP,
    /* 0x08 */ BCK_BANS_SIDESTEPL,
    /* 0x09 */ BCK_BANS_SIDESTEPR,
    /* 0x0A */ BCK_BANS_TALK_A,
    /* 0x0B */ BCK_BANS_TALK_B,
    /* 0x0C */ BCK_BANS_TALK_C,
    /* 0x0D */ BCK_BANS_TALK_D,
    /* 0x0E */ BCK_BANS_WAIT_B,
    /* 0x0F */ BCK_BANS_WAIT_C,
    /* 0x10 */ BCK_BANS_WAIT_D,

    /* EVT */
    /* 0x13 */ EVT_BANS1_EVENT_LIST = 0x13,
};

enum Bans2_RES_File_ID {
    /* BCK */
    /* 0x05 */ BCK_BANS_ANGRY_C = 0x5,
    /* 0x06 */ BCK_BANS_FAINT,
    /* 0x07 */ BCK_BANS_REST,
    /* 0x08 */ BCK_BANS_SAD,
    /* 0x09 */ BCK_BANS_SCOOP_A,
    /* 0x0A */ BCK_BANS_SCOOP_B,
    /* 0x0B */ BCK_BANS_WORK,

    /* BMDR */
    /* 0x0E */ BMDR_BANS_SCOOP = 0xE,
    /* 0x0F */ BMDR_BANS_TUB,

    /* EVT */
    /* 0x12 */ EVT_BANS2_EVENT_LIST = 0x12,
};

enum RES_Name {
    /* 0x0 */ NONE,
    /* 0x1 */ BANS,
    /* 0x2 */ BANS_TW,
    /* 0x3 */ BANS1,
    /* 0x4 */ BANS2,
    /* 0x5 */ LEN1,
};

enum Face_Motion {
    /* 0x0 */ FACE_TALK_A,
    /* 0x1 */ FACE_TALK_B,
    /* 0x2 */ FACE_H_TALK_B,
    /* 0x3 */ FACE_BLINK,
    /* 0x4 */ FACE_NONE,
};

enum Motion {
    /* 0x00 */ MOT_WAIT_A,
    /* 0x01 */ MOT_WAIT_B,
    /* 0x02 */ MOT_MASKDOWN,
    /* 0x03 */ MOT_MASKUP,
    /* 0x04 */ MOT_ANGRY_B,
    /* 0x05 */ MOT_TALK_A,
    /* 0x06 */ MOT_TALK_B,
    /* 0x07 */ MOT_WAIT_C,
    /* 0x08 */ MOT_WAIT_D,
    /* 0x09 */ MOT_TALK_C,
    /* 0x0A */ MOT_TALK_D,
    /* 0x0B */ MOT_WORK,
    /* 0x0C */ MOT_SAD,
    /* 0x0D */ MOT_FAINT,
    /* 0x0E */ MOT_TALK_D_C,
    /* 0x0F */ MOT_REST,
    /* 0x10 */ MOT_WAIT_TW,
    /* 0x11 */ MOT_ANGRY_A,
    /* 0x12 */ MOT_SIDESTEPL,
    /* 0x13 */ MOT_SIDESTEPR,
    /* 0x14 */ MOT_ANGRY_C,
};

enum Event {
    /* 0x0 */ EVT_NONE,
    /* 0x1 */ EVT_DEFAULT_GETITEM,
    /* 0x2 */ EVT_NO_RESPONSE,
    /* 0x3 */ EVT_DEMO13_STB,
    /* 0x4 */ EVT_ANGER,
    /* 0x5 */ EVT_ANGER2,
    /* 0x6 */ EVT_ANGER_NEAR,
    /* 0x7 */ EVT_ANGER_NEAR2,
    /* 0x8 */ EVT_GOBACK,
};

enum Type {
    /* 0x0 */ TYPE_POST_TWILIGHT,
    /* 0x1 */ TYPE_TWILIGHT,
    /* 0x2 */ TYPE_COLIN_KIDNAPPED,
    /* 0x3 */ TYPE_MAKING_BOMBS,
    /* 0x4 */ TYPE_SHOP,
    /* 0x5 */ TYPE_DEFAULT,
};

#if DEBUG
daNpc_Bans_HIO_c::daNpc_Bans_HIO_c() {
    m = daNpc_Bans_Param_c::m;
}

void daNpc_Bans_HIO_c::listenPropertyEvent(const JORPropertyEvent* event) {
    char buffer[2000];
    JORReflexible::listenPropertyEvent(event);
    JORFile jorFile;
    int len;

    switch (reinterpret_cast<u32>(event->id)) {
        case 0x40000002:
            if (jorFile.open(6, "", NULL, NULL, NULL)) {
                memset(buffer, 0, sizeof(buffer));
                len = 0;
                daNpcT_cmnListenPropertyEvent(buffer, &len, &m.common);
                sprintf(&buffer[len], "%.3ff,\t//  走り速度\n", m.run_spd);
                len = strlen(buffer);
                jorFile.writeData(buffer, len);
                jorFile.close();
                OS_REPORT("write append success!::%6d\n", len);
            } else {
                OS_REPORT("write append failure!\n");
            }
            break;
    }
}

void daNpc_Bans_HIO_c::genMessage(JORMContext* ctx) {
    daNpcT_cmnGenMessage(ctx, &m.common);
    ctx->genSlider("走り速度        ", &m.run_spd, 0.0f, 32.0f, 0, NULL, 0xFFFF, 0xFFFF, 0x200, 0x18);
    ctx->genButton("ファイル書き出し", 0x40000002, 0, NULL, 0xFFFF, 0xFFFF, 0x200, 0x18);
}
#endif

/* 80968020-80968040 000020 0020+00 1/1 0/0 0/0 .data            l_bmdData */
static int l_bmdData[4][2] = {
    {BMDE_BANS, BANS},
    {BMDR_BANS_TW, BANS_TW},
    {BMDR_BANS_SCOOP, BANS2},
    {BMDR_BANS_TUB, BANS2},
};

/* 80968040-80968088 -00001 0048+00 0/1 0/0 0/0 .data            l_evtList */
static daNpcT_evtData_c l_evtList[9] = {
    {"", 0},
    {"DEFAULT_GETITEM", 0},
    {"NO_RESPONSE", 0},
    {"DEMO13_STB", 0},
    {"ANGER", 3},
    {"ANGER2", 4},
    {"ANGER_NEAR", 3},
    {"ANGER_NEAR2", 4},
    {"GOBACK", 3},
};

/* 80968088-809680A0 -00001 0018+00 3/4 0/0 0/0 .data            l_resNameList */
static char* l_resNameList[6] = {
    "",
    "Bans",
    "Bans_TW",
    "Bans1",
    "Bans2",
    "Len1",
};

/* 809680A0-809680A4 0000A0 0003+01 1/0 0/0 0/0 .data            l_loadResPtrn0 */
static s8 l_loadResPtrn0[3] = {
    BANS, BANS1, -1,
};

/* 809680A4-809680A8 0000A4 0003+01 1/0 0/0 0/0 .data            l_loadResPtrn1 */
static s8 l_loadResPtrn1[3] = {
    BANS, BANS2, -1,
};

/* 809680A8-809680AC 0000A8 0002+02 1/0 0/0 0/0 .data            l_loadResPtrn2 */
static s8 l_loadResPtrn2[2] = {
    BANS_TW, -1,
};

/* 809680AC-809680B0 0000AC 0004+00 1/0 0/0 0/0 .data            l_loadResPtrn3 */
static s8 l_loadResPtrn3[4] = {
    BANS, BANS1, BANS2, -1,
};

/* 809680B0-809680B8 0000B0 0005+03 1/0 0/0 0/0 .data            l_loadResPtrn4 */
static s8 l_loadResPtrn4[5] = {
    BANS, BANS_TW, BANS1, BANS2, -1,
};

/* 809680B8-809680D0 -00001 0018+00 1/2 0/0 0/0 .data            l_loadResPtrnList */
static s8* l_loadResPtrnList[6] = {
    l_loadResPtrn3, l_loadResPtrn2, l_loadResPtrn1,
    l_loadResPtrn1, l_loadResPtrn0, l_loadResPtrn4,
};

/* 809680D0-8096815C 0000D0 008C+00 0/1 0/0 0/0 .data            l_faceMotionAnmData */
static daNpcT_faceMotionAnmData_c l_faceMotionAnmData[5] = {
    {-1, J3DFrameCtrl::EMode_NONE, NONE, BTP_BANS, J3DFrameCtrl::EMode_LOOP, BANS, TRUE},
    {-1, J3DFrameCtrl::EMode_NONE, NONE, -1, J3DFrameCtrl::EMode_NONE, NONE, FALSE},
    {BCK_BANS_F_TALK_A, J3DFrameCtrl::EMode_NONE, BANS, BTP_BANS, J3DFrameCtrl::EMode_LOOP, BANS, TRUE},
    {BCK_BANS_F_TALK_B, J3DFrameCtrl::EMode_NONE, BANS, BTP_BANS, J3DFrameCtrl::EMode_LOOP, BANS, TRUE},
    {BCK_BANS_FH_TALK_B, J3DFrameCtrl::EMode_LOOP, BANS, BTP_BANS, J3DFrameCtrl::EMode_LOOP, BANS, TRUE},
};

/* 8096815C-8096838C 00015C 0230+00 0/1 0/0 0/0 .data            l_motionAnmData */
static daNpcT_motionAnmData_c l_motionAnmData[20] = {
    {BCK_BANS_WAIT_A, J3DFrameCtrl::EMode_LOOP, BANS, BTK_BANS, J3DFrameCtrl::EMode_NONE, BANS, 1, 0},
    {BCK_BANS_WAIT_B, J3DFrameCtrl::EMode_LOOP, BANS1, BTK_BANS, J3DFrameCtrl::EMode_NONE, BANS, 1, 0},
    {BCK_BANS_WAIT_C, J3DFrameCtrl::EMode_LOOP, BANS1, BTK_BANS, J3DFrameCtrl::EMode_NONE, BANS, 1, 0},
    {BCK_BANS_WAIT_D, J3DFrameCtrl::EMode_LOOP, BANS1, BTK_BANS, J3DFrameCtrl::EMode_NONE, BANS, 1, 0},
    {BCK_BANS_WAIT_TW, J3DFrameCtrl::EMode_LOOP, BANS_TW, -1, J3DFrameCtrl::EMode_NONE, NONE, 0, 0},
    {BCK_BANS_MASKDOWN, J3DFrameCtrl::EMode_NONE, BANS1, BTK_BANS, J3DFrameCtrl::EMode_NONE, BANS, 0, 0},
    {BCK_BANS_MASKUP, J3DFrameCtrl::EMode_NONE, BANS1, BTK_BANS, J3DFrameCtrl::EMode_NONE, BANS, 0, 0},
    {BCK_BANS_ANGRY_A, J3DFrameCtrl::EMode_NONE, BANS1, BTK_BANS, J3DFrameCtrl::EMode_NONE, BANS, 0, 0},
    {BCK_BANS_ANGRY_B, J3DFrameCtrl::EMode_NONE, BANS1, BTK_BANS, J3DFrameCtrl::EMode_NONE, BANS, 0, 0},
    {BCK_BANS_ANGRY_C, J3DFrameCtrl::EMode_NONE, BANS2, BTK_BANS, J3DFrameCtrl::EMode_NONE, BANS, 0, 0},
    {BCK_BANS_TALK_A, J3DFrameCtrl::EMode_NONE, BANS1, BTK_BANS, J3DFrameCtrl::EMode_NONE, BANS, 0, 0},
    {BCK_BANS_TALK_B, J3DFrameCtrl::EMode_NONE, BANS1, BTK_BANS, J3DFrameCtrl::EMode_NONE, BANS, 0, 0},
    {BCK_BANS_TALK_C, J3DFrameCtrl::EMode_NONE, BANS1, BTK_BANS, J3DFrameCtrl::EMode_NONE, BANS, 0, 0},
    {BCK_BANS_TALK_D, J3DFrameCtrl::EMode_NONE, BANS1, BTK_BANS, J3DFrameCtrl::EMode_NONE, BANS, 0, 0},
    {BCK_BANS_SIDESTEPL, J3DFrameCtrl::EMode_NONE, BANS1, BTK_BANS, J3DFrameCtrl::EMode_NONE, BANS, 0, 0},
    {BCK_BANS_SIDESTEPR, J3DFrameCtrl::EMode_NONE, BANS1, BTK_BANS, J3DFrameCtrl::EMode_NONE, BANS, 0, 0},
    {BCK_BANS_WORK, J3DFrameCtrl::EMode_LOOP, BANS2, BTK_BANS, J3DFrameCtrl::EMode_NONE, BANS, 0, 0},
    {BCK_BANS_REST, J3DFrameCtrl::EMode_LOOP, BANS2, BTK_BANS, J3DFrameCtrl::EMode_NONE, BANS, 0, 0},
    {BCK_BANS_SAD, J3DFrameCtrl::EMode_LOOP, BANS2, BTK_BANS, J3DFrameCtrl::EMode_NONE, BANS, 0, 0},
    {BCK_BANS_FAINT, J3DFrameCtrl::EMode_LOOP, BANS2, BTK_BANS, J3DFrameCtrl::EMode_NONE, BANS, 0, 0},
};

/* 8096838C-809683DC 00038C 0050+00 0/1 0/0 0/0 .data            l_faceMotionSequenceData */
static daNpcT_MotionSeqMngr_c::sequenceStepData_c l_faceMotionSequenceData[20] = {
    {2, -1, 1}, {-1, 0, 0}, {-1, 0, 0}, {-1, 0, 0},
    {3, -1, 1}, {4, 0, 0}, {-1, 0, 0}, {-1, 0, 0},
    {4, -1, 0}, {-1, 0, 0}, {-1, 0, 0}, {-1, 0, 0},
    {0, -1, 0}, {-1, 0, 0}, {-1, 0, 0}, {-1, 0, 0},
    {1, -1, 0}, {-1, 0, 0}, {-1, 0, 0}, {-1, 0, 0},
};

/* 809683DC-8096852C 0003DC 0150+00 0/1 0/0 0/0 .data            l_motionSequenceData */
static daNpcT_MotionSeqMngr_c::sequenceStepData_c l_motionSequenceData[84] = {
    {0, 0xF7, 0}, {-1, 0, 0}, {-1, 0, 0}, {-1, 0, 0},
    {1, 0xF7, 0}, {-1, 0, 0}, {-1, 0, 0}, {-1, 0, 0},
    {5, 0, 1}, {1, 0, 0}, {-1, 0, 0}, {-1, 0, 0},
    {6, 0, 1}, {0, 0, 0}, {-1, 0, 0}, {-1, 0, 0},
    {8, 0, 1}, {0, 0, 0}, {-1, 0, 0}, {-1, 0, 0},
    {0xA, 0, 1}, {2, 0, 0}, {-1, 0, 0}, {-1, 0, 0},
    {0xB, -1, 1}, {2, 0, 0}, {-1, 0, 0}, {-1, 0, 0},
    {2, 0xF7, 0}, {-1, 0, 0}, {-1, 0, 0}, {-1, 0, 0},
    {3, 0xF7, 0}, {-1, 0, 0}, {-1, 0, 0}, {-1, 0, 0},
    {0xC, -1, 1}, {3, 0, 0}, {-1, 0, 0}, {-1, 0, 0},
    {0xD, -1, 1}, {3, 0, 0}, {-1, 0, 0}, {-1, 0, 0},
    {0x10, 0xF7, 0}, {-1, 0, 0}, {-1, 0, 0}, {-1, 0, 0},
    {0x12, 0xF7, 0}, {-1, 0, 0}, {-1, 0, 0}, {-1, 0, 0},
    {0x13, 0xF7, 0}, {-1, 0, 0}, {-1, 0, 0}, {-1, 0, 0},
    {0xD, -1, 1}, {0xC, 0, 1}, {3, 0, 0}, {-1, 0, 0},
    {0x11, 0xF7, 0}, {-1, 0, 0}, {-1, 0, 0}, {-1, 0, 0},
    {4, 0xF7, 0}, {-1, 0, 0}, {-1, 0, 0}, {-1, 0, 0},
    {7, 0, 1}, {-1, 0, 0}, {-1, 0, 0}, {-1, 0, 0},
    {0xE, 0, 1}, {-1, 0, 0}, {-1, 0, 0}, {-1, 0, 0},
    {0xF, 0, 1}, {-1, 0, 0}, {-1, 0, 0}, {-1, 0, 0},
    {9, 0, 1}, {-1, 0, 0}, {-1, 0, 0}, {-1, 0, 0},
};

/* 8096852C-8096853C -00001 0010+00 1/1 0/0 0/0 .data            mCutNameList__12daNpc_Bans_c */
char* daNpc_Bans_c::mCutNameList[4] = {
    "",
    "ANGER",
    "PURCHASE",
    "GO_BACK",
};

/* 80968560-80968590 000560 0030+00 1/2 0/0 0/0 .data            mCutList__12daNpc_Bans_c */
daNpc_Bans_c::cutFunc daNpc_Bans_c::mCutList[4] = {
    NULL,
    &daNpc_Bans_c::cutAnger,
    &daNpc_Bans_c::cutPurchase,
    &daNpc_Bans_c::cutPurchase,
};

/* 809628CC-80962AA0 0000EC 01D4+00 1/0 0/0 0/0 .text            __dt__12daNpc_Bans_cFv */
daNpc_Bans_c::~daNpc_Bans_c() {
    OS_REPORT("|%06d:%x|daNpc_Bans_c(%d) -> デストラクト\n", g_Counter.mCounter0, this, mType);

    deleteObject();

    if (mpMorf[0] != NULL) {
        mpMorf[0]->stopZelAnime();
    }

    if (mpScoopMorf != NULL) {
        mpScoopMorf->stopZelAnime();
    }

    #if DEBUG
    if (mHIO != NULL) {
        mHIO->removeHIO();
    }
    #endif

    deleteRes(l_loadResPtrnList[mType], (const char**)l_resNameList);
}

/* 80967E20-80967EB0 000000 0090+00 12/12 0/0 0/0 .rodata          m__18daNpc_Bans_Param_c */
daNpc_Bans_HIOParam const daNpc_Bans_Param_c::m = {
    200.0f,
    -3.0f,
    1.0f,
    400.0f,
    255.0f,
    190.0f,
    35.0f,
    30.0f,
    0.0f,
    0.0f,
    10.0f,
    -10.0f,
    30.0f,
    -10.0f,
    45.0f,
    -45.0f,
    0.6f,
    12.0f,
    3,
    6,
    5,
    6,
    110.0f,
    0.0f,
    0.0f,
    0.0f,
    60,
    8,
    0,
    0,
    0,
    false,
    false,
    4.0f,
    -20.0f,
    0.0f,
    -20.0f,
    20.0f,
    40.0f,
    20.0f,
    110.0f,
    10.0f,
};

/* 80968864-80968868 000014 0004+00 1/1 0/0 0/0 .bss             l_HIO */
static NPC_BANS_HIO_CLASS l_HIO;

/* 80962AA0-80962D6C 0002C0 02CC+00 1/1 0/0 0/0 .text            create__12daNpc_Bans_cFv */
cPhs__Step daNpc_Bans_c::create() {
    fopAcM_SetupActor2(this, daNpc_Bans_c, l_faceMotionAnmData, l_motionAnmData,
                       l_faceMotionSequenceData, 4, l_motionSequenceData, 4,
                       l_evtList, l_resNameList);
    mType = getType();
    mFlowNodeNo = getFlowNodeNo();
    mTwilight = dKy_darkworld_check();

    cPhs__Step phase = (cPhs__Step)loadRes(l_loadResPtrnList[mType], (const char**)l_resNameList);
    if (phase == cPhs_COMPLEATE_e) {
        OS_REPORT("\t(%s:%d) flowNo:%d, PathID:%02x, MaxItem:%d, group:%d<%08x> ", fopAcM_getProcNameString(this), mType, mFlowNodeNo,
                  getPathID(), getMaxNumItem(), getGroupId(), fopAcM_GetParam(this));

        if (isDelete()) {
            OS_REPORT("===>isDelete:TRUE\n");
            return cPhs_ERROR_e;
        }

        OS_REPORT("\n");

        static u32 const heapSize[6] = {
            0x6C50, 0x4B40, 0x6C50,
            0x7580, 0x6460, 0x0000,
        };

        if (!fopAcM_entrySolidHeap(this, createHeapCallBack, heapSize[mType])) {
            return cPhs_ERROR_e;
        }

        J3DModelData* modelData = mpMorf[0]->getModel()->getModelData();
        fopAcM_SetMtx(this, mpMorf[0]->getModel()->getBaseTRMtx());
        fopAcM_setCullSizeBox(this, -200.0f, -100.0f, -200.0f, 200.0f, 300.0f, 200.0f);
        mSound.init(&current.pos, &eyePos, 3, 1);

        #if DEBUG
        mHIO = &l_HIO;
        mHIO->entryHIO("バ−ンズ"); // Barnes
        #endif

        reset();

        mAcch.Set(fopAcM_GetPosition_p(this), fopAcM_GetOldPosition_p(this), this, 1, &mAcchCir,
                  fopAcM_GetSpeed_p(this), fopAcM_GetAngle_p(this), fopAcM_GetShapeAngle_p(this));
        mCcStts.Init(mHIO->m.common.weight, 0, this);
        mCyl2.Set(mCcDCyl);
        mCyl2.SetStts(&mCcStts);
        mCyl2.SetTgHitCallback(tgHitCallBack);
        mCyl1.Set(mCcDCyl);
        mCyl1.SetStts(&mCcStts);
        mAcch.CrrPos(dComIfG_Bgsp());
        mGndChk = mAcch.m_gnd;
        mGroundH = mAcch.GetGroundH();

        if (mGroundH != -G_CM3D_F_INF) {
            setEnvTevColor();
            setRoomNo();
        }

        mCreating = true;
        Execute();
        mCreating = false;
    }

    return phase;
}

enum unk_ModelFlags_e {
    unk_flag_1 = 0,
    unk_flag_2 = 0x80000,
};

/* 80962D6C-8096317C 00058C 0410+00 1/1 0/0 0/0 .text            CreateHeap__12daNpc_Bans_cFv */
int daNpc_Bans_c::CreateHeap() {
    J3DModelData* modelData;
    int bmdIdx;
    int resIdx;
    u32 idx = 0;
    idx = mTwilight == true ? TRUE : FALSE;
    resIdx = l_bmdData[idx][1];
    bmdIdx = l_bmdData[idx][0];
    modelData = (J3DModelData*)dComIfG_getObjectRes(l_resNameList[resIdx], bmdIdx);
    if (modelData == NULL) {
        return 0;
    }

    u32 uVar2 = 0x11020284;
    mpMorf[0] = new mDoExt_McaMorfSO(modelData, NULL, NULL, NULL, -1, 1.0f, 0, -1, &mSound, (int)idx == 1 ? unk_flag_2 : unk_flag_1, uVar2);
    if (mpMorf[0] == NULL || mpMorf[0]->getModel() == NULL) {
        return 0;
    }

    J3DModel* model = mpMorf[0]->getModel();
    for (u16 i = 0; i < modelData->getJointNum(); i++) {
        modelData->getJointNodePointer(i)->setCallBack(ctrlJointCallBack);
    }
    model->setUserArea((uintptr_t)this);

    mpMatAnm[0] = new daNpcT_MatAnm_c();
    if (mpMatAnm[0] == NULL) {
        return 0;
    }

    if (mType == TYPE_MAKING_BOMBS) {
        idx = 2;
        resIdx = l_bmdData[idx][1];
        bmdIdx = l_bmdData[idx][0];
        modelData = (J3DModelData*)dComIfG_getObjectRes(l_resNameList[resIdx], bmdIdx);
        if (modelData == NULL) {
            return 1;
        }

        u32 uVar3 = 0x11000084;
        mpScoopMorf = new mDoExt_McaMorfSO(modelData, NULL, NULL, NULL, -1, 1.0f, 0, -1, NULL, 0x80000, uVar3);
        if (mpScoopMorf == NULL || mpScoopMorf->getModel() == NULL) {
            return 0;
        }
    }

    if (mType == TYPE_MAKING_BOMBS) {
        if (l_bmdData[3][0] >= 0) {
            modelData = (J3DModelData*)dComIfG_getObjectRes(l_resNameList[l_bmdData[3][1]], l_bmdData[3][0]);
        } else {
            modelData = NULL;
        }

        if (modelData != NULL) {
            mTubModel[0] = mDoExt_J3DModel__create(modelData, 0x80000, 0x11000084);
        }

        if (mTubModel[0] == NULL) {
            return 0;
        }
    }

    if (mTwilight) {
        if (setMotionAnm(4, 0, FALSE)) {
            return 1;
        }

        return 0;
    }

    if (setFaceMotionAnm(2, false) && setMotionAnm(0, 0.0f, FALSE)) {
        return 1;
    }

    return 0;
}

/* 80963338-8096336C 000B58 0034+00 1/1 0/0 0/0 .text            Delete__12daNpc_Bans_cFv */
int daNpc_Bans_c::Delete() {
    OS_REPORT("|%06d:%x|daNpc_Bans_c -> Delete\n", g_Counter.mCounter0, this);
    fpc_ProcID id = fopAcM_GetID(this);
    this->~daNpc_Bans_c();
    return 1;
}

/* 8096336C-80963444 000B8C 00D8+00 2/2 0/0 0/0 .text            Execute__12daNpc_Bans_cFv */
int daNpc_Bans_c::Execute() {
    if (!mCreating && !checkShopOpen() && mType == TYPE_SHOP && mShopFlag == 0) {
        initShopSystem();
        setSellItemMax(getMaxNumItem());
        field_0xf60 = -1;
        mShopCamAction.setCamDataIdx(0);
        mShopCamAction.setCamAction(NULL);
        mShopFlag = 1;
    }

    execute();

    if (mShopFlag != 0 && searchItemActor()) {
        mShopCamAction.move();
    }

    return 1;
}

/* 80963444-809634E0 000C64 009C+00 1/1 0/0 0/0 .text            Draw__12daNpc_Bans_cFv */
int daNpc_Bans_c::Draw() {
    if (mpMatAnm[0] != NULL) {
        J3DModelData* modelData = mpMorf[0]->getModel()->getModelData();
        modelData->getMaterialNodePointer(getEyeballMaterialNo())->setMaterialAnm(mpMatAnm[0]);
    }

    #if DEBUG
    return draw(chkAction(&daNpc_Bans_c::test), !(mTwilight & 0xFF), mRealShadowSize, NULL, 100.0f, FALSE, FALSE, FALSE);
    #else
    return draw(FALSE, !(mTwilight & 0xFF), mRealShadowSize, NULL, 100.0f, FALSE, FALSE, FALSE);
    #endif
}

/* 809634E0-80963500 000D00 0020+00 1/1 0/0 0/0 .text            createHeapCallBack__12daNpc_Bans_cFP10fopAc_ac_c */
int daNpc_Bans_c::createHeapCallBack(fopAc_ac_c* a_this) {
    daNpc_Bans_c* i_this = (daNpc_Bans_c*)a_this;
    return i_this->CreateHeap();
}

/* 80963500-80963558 000D20 0058+00 1/1 0/0 0/0 .text            ctrlJointCallBack__12daNpc_Bans_cFP8J3DJointi */
int daNpc_Bans_c::ctrlJointCallBack(J3DJoint* i_joint, int param_2) {
    if (param_2 == 0) {
        J3DModel* model = j3dSys.getModel();
        daNpc_Bans_c* i_this = (daNpc_Bans_c*)model->getUserArea();
        if (i_this != NULL) {
            i_this->ctrlJoint(i_joint, model);
        }
    }

    return 1;
}

/* 80963558-809635BC 000D78 0064+00 1/1 0/0 0/0 .text            getType__12daNpc_Bans_cFv */
u8 daNpc_Bans_c::getType() {
    u8 param = fopAcM_GetParam(this) & 0xFF;
    switch (param) {
        case 0:
            return TYPE_POST_TWILIGHT; // After Eldin Twilight cleared but before Colin kidnapped

        case 1:
            return TYPE_TWILIGHT; // Eldin Twilight
        
        case 2:
            return TYPE_COLIN_KIDNAPPED; // After Colin kidnapped but before horseback battle cleared

        case 3:
            return TYPE_MAKING_BOMBS; // After horseback battle cleared but before Goron Mines cleared

        case 4:
            return TYPE_SHOP; // After Goron Mines cleared

        default:
            return TYPE_DEFAULT;
    }
}

/* 809635BC-809636C0 000DDC 0104+00 1/1 0/0 0/0 .text            isDelete__12daNpc_Bans_cFv */
BOOL daNpc_Bans_c::isDelete() {
    switch (mType) {
        case TYPE_POST_TWILIGHT:
            /*
                Delete if TYPE_POST_TWILIGHT and:
                Eldin Twilight Not Cleared or Colin Kidnapped
            */
            return !daNpcT_chkEvtBit(61) || // dSv_event_flag_c::M_028 - Cutscene - [cutscene: 14] restore mountain spirit - Reuinion with Colin et al.
                    daNpcT_chkEvtBit(53); // dSv_event_flag_c::M_020 - Cutscene - [cutscene: ] Colin kidnapped : ON once watched

        case TYPE_TWILIGHT:
            /*
                Do not delete if TYPE_TWILIGHT
            */
            return FALSE;
        
        case TYPE_COLIN_KIDNAPPED:
            /*
                Delete if TYPE_COLIN_KIDNAPPED and:
                Colin Not Kidnapped or Horseback Battle Cleared
            */
            return !daNpcT_chkEvtBit(53) || // dSv_event_flag_c::M_020 - Cutscene - [cutscene: ] Colin kidnapped : ON once watched
                    daNpcT_chkEvtBit(85); // dSv_event_flag_c::M_052 - Main Event - Horseback battle clear

        case TYPE_MAKING_BOMBS:
            /*
                Delete if TYPE_MAKING_BOMBS and:
                Horseback Battle Not Cleared or Goron Mines Cleared
            */
            return !daNpcT_chkEvtBit(85) || // dSv_event_flag_c::M_052 - Main Event - Horseback battle clear
                    daNpcT_chkEvtBit(64); // dSv_event_flag_c::M_031 - Goron Mines - Goron Mines clear

        case TYPE_SHOP:
            /*
                Delete if TYPE_SHOP and:
                Goron Mines Cleared
            */
            return !daNpcT_chkEvtBit(64); // dSv_event_flag_c::M_031 - Goron Mines - Goron Mines clear

        default:
            return FALSE;
    }
}

/* 809636C0-80963840 000EE0 0180+00 1/1 0/0 0/0 .text            reset__12daNpc_Bans_cFv */
void daNpc_Bans_c::reset() {
    csXyz angle;
    int size = (u8*)&field_0x126c - (u8*)&mNextAction;
    if (mpMatAnm[0] != NULL) {
        mpMatAnm[0]->initialize();
    }
    
    initialize();

    for (int i = 0; i < 8; i++) {
        mActorMngrs[i].initialize();
    }

    memset(&mNextAction, 0, size);

    angle.setall(0);
    angle.y = home.angle.y;

    switch (mType) {
        case TYPE_POST_TWILIGHT:
        case TYPE_TWILIGHT:
        case TYPE_COLIN_KIDNAPPED:
        case TYPE_MAKING_BOMBS:
        case TYPE_SHOP:
        default:
            daNpcT_offTmpBit(57); // dSv_event_tmp_flag_c::T_0057 - Kakariko Village (inside) - Barnes bomb shop <purchase>
            setAngle(angle);
    }
}

/* 80963840-809638CC 001060 008C+00 1/0 0/0 0/0 .text            afterJntAnm__12daNpc_Bans_cFi */
void daNpc_Bans_c::afterJntAnm(int param_1) {
    if (param_1 == 1) {
        mDoMtx_stack_c::YrotM(-mStagger.getAngleZ(1));
        mDoMtx_stack_c::ZrotM(mStagger.getAngleX(1));
    } else if (param_1 == 6) {
        mDoMtx_stack_c::YrotM(-mStagger.getAngleZ(0));
        mDoMtx_stack_c::ZrotM(mStagger.getAngleX(0));
    }
}

/* 809638CC-80963A7C 0010EC 01B0+00 1/0 0/0 0/0 .text            setParam__12daNpc_Bans_cFv */
void daNpc_Bans_c::setParam() {
    if (mSetParamFlag) {
        if (mShopProcess == 2) {
            mShopCamAction.Reset();
        } else {
            mShopCamAction.EventRecoverNotime();
        }

        mSetParamFlag = 0;
    }

    selectAction();
    srchActors();

    #if DEBUG
    u32 flags = 0x42;
    #else
    u32 flags = 10;
    #endif
    s16 talk_distance = mHIO->m.common.talk_distance;
    s16 talk_angle = mHIO->m.common.talk_angle;
    s16 attention_distance = mHIO->m.common.attention_distance;
    s16 attention_angle = mHIO->m.common.attention_angle;

    switch (mType) {
        case TYPE_POST_TWILIGHT:
            talk_distance = 5;
            attention_distance = 5;
            break;

        case TYPE_TWILIGHT:
            talk_distance = 8;
            break;

        case TYPE_COLIN_KIDNAPPED:
            break;

        case TYPE_MAKING_BOMBS:
            talk_distance = 4;
            attention_distance = 5;
            break;

        case TYPE_SHOP:
            talk_distance = 5;
            attention_distance = 5;

            if (daPy_py_c::checkNowWolf()) {
                flags = 0;
            }
            break;
    }

    attention_info.distances[fopAc_attn_LOCK_e] = daNpcT_getDistTableIdx(attention_distance, attention_angle);
    attention_info.distances[fopAc_attn_TALK_e] = attention_info.distances[fopAc_attn_LOCK_e];
    attention_info.distances[fopAc_attn_SPEAK_e] = daNpcT_getDistTableIdx(talk_distance, talk_angle);
    attention_info.flags = flags;

    scale.set(mHIO->m.common.scale, mHIO->m.common.scale, mHIO->m.common.scale);
    mCcStts.SetWeight(mHIO->m.common.weight);
    mCylH = mHIO->m.common.height;
    mWallR = mHIO->m.common.width;
    mAttnFovY = mHIO->m.common.fov;
    mAcchCir.SetWallR(mWallR);
    mAcchCir.SetWallH(mHIO->m.common.knee_length);
    mRealShadowSize = mHIO->m.common.real_shadow_size;
    mExpressionMorfFrame = mHIO->m.common.expression_morf_frame;
    mMorfFrames = mHIO->m.common.morf_frame;
    gravity = mHIO->m.common.gravity;
}

/* 80963A7C-80963B30 00129C 00B4+00 1/0 0/0 0/0 .text            checkChangeEvt__12daNpc_Bans_cFv */
BOOL daNpc_Bans_c::checkChangeEvt() {
    if (!chkAction(&daNpc_Bans_c::talk)) {
        mPreItemNo = 0;

        if (dComIfGp_event_chkTalkXY()) {
            if (dComIfGp_evmng_ChkPresentEnd()) {
                mEvtNo = EVT_NO_RESPONSE;
                evtChange();
            }

            return TRUE;
        }

        switch (mType) {
            default:
                break;
        }
    }

    return FALSE;
}

/* 80963B30-80963BA8 001350 0078+00 1/0 0/0 0/0 .text setAfterTalkMotion__12daNpc_Bans_cFv */
void daNpc_Bans_c::setAfterTalkMotion() {
    int motion = MOT_MASKUP;

    switch (mFaceMotionSeqMngr.getNo()) {
        case FACE_TALK_B:
            motion = MOT_MASKDOWN;
            break;
    }

    mFaceMotionSeqMngr.setNo(motion, -1.0f, FALSE, 0);
}

/* 80963BA8-80963DB0 0013C8 0208+00 1/1 0/0 0/0 .text            srchActors__12daNpc_Bans_cFv */
void daNpc_Bans_c::srchActors() {
    switch (mType) {
        case TYPE_POST_TWILIGHT:
            for (int i = 0; i < 2; i++) {
                if (mActorMngrs[i + 5].getActorP() == NULL) {
                    mActorMngrs[i + 5].entry(getEvtAreaTagP(3, i));
                }
            }
            break;
        
        case TYPE_TWILIGHT:
            for (int i = 0; i < 2; i++) {
                if (mActorMngrs[i + 5].getActorP() == NULL) {
                    mActorMngrs[i + 5].entry(getEvtAreaTagP(3, i));
                }
            }

            if (mActorMngrs[3].getActorP() == NULL) {
                mActorMngrs[3].entry(getNearestActorP(PROC_NPC_LEN));
            }
            break;

        case TYPE_COLIN_KIDNAPPED:
        case TYPE_MAKING_BOMBS:
            for (int i = 0; i < 2; i++) {
                if (mActorMngrs[i + 5].getActorP() == NULL) {
                    mActorMngrs[i + 5].entry(getEvtAreaTagP(3, i));
                }
            }
            break;

        case TYPE_SHOP:
            for (int i = 0; i < 2; i++) {
                if (mActorMngrs[i + 5].getActorP() == NULL) {
                    mActorMngrs[i + 5].entry(getEvtAreaTagP(3, i));
                }
            }

            if (mActorMngrs[7].getActorP() == NULL) {
                mActorMngrs[7].entry(getKMsgTagP());
            }

            if (mActorMngrs[4].getActorP() == NULL) {
                mActorMngrs[4].entry(getShopItemTagP());
            }
            break;
    }
}

/* 80963DB0-80963EDC 0015D0 012C+00 1/0 0/0 0/0 .text            evtTalk__12daNpc_Bans_cFv */
BOOL daNpc_Bans_c::evtTalk() {
    if (mShopFlag) {
        if (chkAction(&daNpc_Bans_c::shop)) {
            (this->*mAction)(NULL);
        } else {
            if (!daNpcT_chkTmpBit(57)) { // dSv_event_flag_c::M_024 - Cutscene - [cutscene: 16] take back Colin
                mShopCamAction.shop_cam_action_init();
            }

            setAction(&daNpc_Bans_c::shop);
        }
    } else if (chkAction(&daNpc_Bans_c::talk)) {
        (this->*mAction)(NULL);
    } else {
        setAction(&daNpc_Bans_c::talk);
    }

    return TRUE;
}

/* 80963EDC-80963FA4 0016FC 00C8+00 1/0 0/0 0/0 .text            evtCutProc__12daNpc_Bans_cFv */
BOOL daNpc_Bans_c::evtCutProc() {
    s32 staffId = dComIfGp_getEventManager().getMyStaffId("Bans", this, -1);
    if (staffId != -1) {
        mStaffId = staffId;
        int actIdx = dComIfGp_getEventManager().getMyActIdx(mStaffId, mCutNameList, 4, FALSE, FALSE);
        if ((this->*mCutList[actIdx])(mStaffId)) {
            dComIfGp_getEventManager().cutEnd(mStaffId);
        }

        return TRUE;
    }

    return FALSE;
}

/* 80963FA4-80964148 0017C4 01A4+00 1/0 0/0 0/0 .text            action__12daNpc_Bans_cFv */
void daNpc_Bans_c::action() {
    fopAc_ac_c* actor = NULL;
    if (!mTwilight) {
        actor = hitChk(&mCyl2, 0xFFFFFFFF);
    }

    if (actor != NULL) {
        if (mCyl2.GetTgHitObj()->ChkAtType(AT_TYPE_THROW_OBJ)) {
            mStagger.setParam(this, actor, mCurAngle.y);
            setDamage(0, 3, 0);
            mDamageTimerStart = 0;
            mJntAnm.lookNone(1);
        }
    }

    if (mStagger.checkRebirth()) {
        mStagger.initialize();
        mMode = 1;
    }

    if (mNextAction) {
        if (mAction == mNextAction) {
            (this->*mAction)(NULL);
        } else {
            setAction(mNextAction);
        }
    }
}

/* 80964148-80964228 001968 00E0+00 1/0 0/0 0/0 .text            beforeMove__12daNpc_Bans_cFv */
void daNpc_Bans_c::beforeMove() {
    fopAcM_OffStatus(this, fopAcM_STATUS_UNK_0x8000000);

    if (checkHide()) {
        fopAcM_OnStatus(this, fopAcM_STATUS_UNK_0x8000000);
    }

    if (checkPlayerIn2ndFloorOfBombShop()) {
        attention_info.flags = 0;
    } else if (checkHide() || mNoDraw) {
        attention_info.flags = 0;
    }
}

/* 80964228-809646E0 001A48 04B8+00 1/0 0/0 0/0 .text            setAttnPos__12daNpc_Bans_cFv */
void daNpc_Bans_c::setAttnPos() {
    cXyz sp70(15.0f, 30.0f, 0.0f);
    cXyz sp7c(15.0f, 0.0f, 0.0f);

    if (mDemo13Flag) {
        daPy_getPlayerActorClass()->onWolfEyeKeep();
    }

    mStagger.calc(FALSE);
    f32 rad = cM_s2rad((s16)(mCurAngle.y - field_0xd7e.y));

    if (mType == TYPE_POST_TWILIGHT) {
        mJntAnm.setParam(this, mpMorf[0]->getModel(), &sp70, getBackboneJointNo(), getNeckJointNo(), getHeadJointNo(), 0.0f, 0.0f, 0.0f, 0.0f,
                         mHIO->m.common.head_angleX_min, mHIO->m.common.head_angleX_max, mHIO->m.common.head_angleY_min, mHIO->m.common.head_angleY_max,
                         mHIO->m.common.neck_rotation_ratio, rad, &sp7c);
    } else {
        mJntAnm.setParam(this, mpMorf[0]->getModel(), &sp70, getBackboneJointNo(), getNeckJointNo(), getHeadJointNo(),
                         mHIO->m.common.body_angleX_min, mHIO->m.common.body_angleX_max, mHIO->m.common.body_angleY_min, mHIO->m.common.body_angleY_max,
                         mHIO->m.common.head_angleX_min, mHIO->m.common.head_angleX_max, mHIO->m.common.head_angleY_min, mHIO->m.common.head_angleY_max,
                         mHIO->m.common.neck_rotation_ratio, rad, &sp7c);
    }

    mJntAnm.calcJntRad(0.2f, 1.0f, rad);
    setMtx();

    if (mpScoopMorf != NULL) {
        if (mMotionSeqMngr.getNo() == MOT_WORK) {
            if (mpMorf[0]->checkFrame(8.0f)) {
                mDoAud_seStart(Z2SE_BANS_SHOVEL, &current.pos, 0, 0);
            }

            if (mpMorf[0]->checkFrame(34.0f)) {
                mDoAud_seStart(Z2SE_BANS_SHOVEL2, &current.pos, 0, 0);
            }
        }

        mpScoopMorf->play(0, 0);

        mDoMtx_stack_c::copy(mpMorf[0]->getModel()->getAnmMtx(0x15));
        Mtx mtx;

        #if DEBUG
        cMtx_copy(mDoMtx_stack_c::get(), mtx);
        #else
        MTXCopy(mDoMtx_stack_c::get(), mtx);
        #endif

        mpScoopMorf->getModel()->setBaseTRMtx(mtx);
        mpScoopMorf->modelCalc();
    }

    mDoMtx_stack_c::copy(mpMorf[0]->getModel()->getAnmMtx(getHeadJointNo()));
    mDoMtx_stack_c::multVec(&sp70, &eyePos);
    mJntAnm.setEyeAngleX(eyePos, 1.0f, 0);
    mJntAnm.setEyeAngleY(eyePos, mCurAngle.y, FALSE, 1.0f, 0);

    sp70.set(0.0f, 0.0f, 0.0f);
    sp70.y = mHIO->m.common.attention_offset;

    if (mType == TYPE_TWILIGHT) {
        sp70.set(30.0f, 180.0f, 10.0f);
    } else if (mMotionSeqMngr.getNo() == MOT_SAD) {
        sp70.set(0.0f, 180.0f, 70.0f);
    }

    mDoMtx_stack_c::YrotS(mCurAngle.y);
    mDoMtx_stack_c::multVec(&sp70, &sp70);
    attention_info.position = sp70 + current.pos;
}

/* 809646E0-80964994 001F00 02B4+00 1/0 0/0 0/0 .text            setCollision__12daNpc_Bans_cFv */
void daNpc_Bans_c::setCollision() {
    cXyz pos;

    if (!mHide) {
        u32 coSPrm = 0x79;
        u32 tgType = 0xD8FBFDFF;
        u32 tgSPrm = 0x1F;

        if (mTwilight) {
            tgType = 0;
            tgSPrm = 0;
        } else {
            if (mStagger.checkStagger()) {
                tgType = 0;
                tgSPrm = 0;
            }
        }

        f32 height, width;
        if (mType != TYPE_POST_TWILIGHT && mType != TYPE_SHOP) {
            mCyl2.SetCoSPrm(coSPrm);
            mCyl2.SetTgType(tgType);
            mCyl2.SetTgSPrm(tgSPrm);
            mCyl2.OnTgNoHitMark();
            pos.set(0.0f, 0.0f, 10.0f);
            height = mCylH;
            width = mWallR;

            if (mType == TYPE_TWILIGHT) {
                pos.set(0.0f, 0.0f, 0.0f);
                height = mCylH;
                width = 50.0f;
            }

            mDoMtx_stack_c::YrotS(mCurAngle.y);
            mDoMtx_stack_c::multVec(&pos, &pos);
            pos += current.pos;
            mCyl2.SetH(height);
            mCyl2.SetR(width);
            mCyl2.SetC(pos);
            dComIfG_Ccsp()->Set(&mCyl2);
        }

        if (mType == TYPE_COLIN_KIDNAPPED) {
            pos.set(0.0f, 0.0f, -60.0f);
            height = mCylH;
            width = 100.0f;
            mDoMtx_stack_c::YrotS(mCurAngle.y);
            mDoMtx_stack_c::multVec(&pos, &pos);
            pos += current.pos;
            mCyl1.SetH(height);
            mCyl1.SetR(width);
            mCyl1.SetC(pos);
            dComIfG_Ccsp()->Set(&mCyl1);
        }

        if (mType == TYPE_MAKING_BOMBS) {
            pos.set(0.0f, 0.0f, 50.0f);
            height = 40.0f;
            width = 110.0f;
            mDoMtx_stack_c::YrotS(mCurAngle.y);
            mDoMtx_stack_c::multVec(&pos, &pos);
            pos += current.pos;
            mCyl1.SetH(height);
            mCyl1.SetR(width);
            mCyl1.SetC(pos);
            dComIfG_Ccsp()->Set(&mCyl1);
        }
    }

    mCyl2.ClrCoHit();
    mCyl2.ClrTgHit();
}

/* 80964994-8096499C 0021B4 0008+00 1/0 0/0 0/0 .text            drawDbgInfo__12daNpc_Bans_cFv */
int daNpc_Bans_c::drawDbgInfo() {
    #if DEBUG
    if (mHIO->m.common.debug_info_ON) {
        f32 dist_max_speak = dComIfGp_getAttention()->getDistTable(attention_info.distances[fopAc_attn_SPEAK_e]).mDistMax;
        f32 dist_max_talk = dComIfGp_getAttention()->getDistTable(attention_info.distances[fopAc_attn_TALK_e]).mDistMax;
        dDbVw_drawCircleOpa(attention_info.position, dist_max_speak, (GXColor){0x00, 0xC8, 0x00, 0xFF}, 1, 12);
        dDbVw_drawCircleOpa(attention_info.position, dist_max_talk, (GXColor){0xC8, 0x00, 0x00, 0xFF}, 1, 12);
        dDbVw_drawSphereXlu(eyePos, 18.0f, (GXColor){0x80, 0x80, 0x80, 0xA0}, 1);
        dDbVw_drawSphereXlu(eyePos, 9.0f, (GXColor){0x80, 0x80, 0x80, 0xA0}, 1);
    }
    #endif
    
    return 0;
}

/* 8096499C-80964AD8 0021BC 013C+00 1/0 0/0 0/0 .text            drawOtherMdl__12daNpc_Bans_cFv */
void daNpc_Bans_c::drawOtherMdl() {
    for (int i = 0; i < 1; i++) {
        if (mTubModel[i] != NULL && i == 0 && mType == TYPE_MAKING_BOMBS) {
            g_env_light.setLightTevColorType_MAJI(mTubModel[i], &tevStr);
            mDoMtx_stack_c::transS(current.pos);
            mDoMtx_stack_c::YrotM(home.angle.y);
            mDoMtx_stack_c::scaleM(scale);
            mTubModel[i]->setBaseTRMtx(mDoMtx_stack_c::get());
            mDoExt_modelUpdateDL(mTubModel[i]);
            dComIfGd_addRealShadow(mShadowKey, mTubModel[i]);
        }
    }

    if (mpScoopMorf != NULL) {
        g_env_light.setLightTevColorType_MAJI(mpScoopMorf->getModel(), &tevStr);
        mpScoopMorf->entryDL();dComIfGd_addRealShadow(mShadowKey, mpScoopMorf->getModel());
    }

    if (mShopFlag) {
        cXyz pos;
        itemRotate();
        pos.set(0.0f, 0.0f, 0.0f);
        itemZoom(&pos);
        drawCursor();
    }
}

/* 80964AD8-80964B9C 0022F8 00C4+00 1/1 0/0 0/0 .text            setScoopAnm__12daNpc_Bans_cFiif */
bool daNpc_Bans_c::setScoopAnm(int i_idx, int i_attr, f32 i_morf) {
    static int scoopAnmData[20][2] = {
        {-1, 0},
        {-1, 0},
        {-1, 0},
        {-1, 0},
        {-1, 0},
        {-1, 0},
        {-1, 0},
        {-1, 0},
        {-1, 0},
        {0xA, 0x4},
        {-1, 0},
        {-1, 0},
        {-1, 0},
        {-1, 0},
        {-1, 0},
        {-1, 0},
        {9, 4},
        {0xA, 4},
        {-1, 0},
        {-1, 0},
    };

    J3DAnmTransform* anm = NULL;

    if (mpScoopMorf != NULL) {
        if (scoopAnmData[i_idx][0] > 0) {
            anm = getTrnsfrmKeyAnmP(l_resNameList[scoopAnmData[i_idx][1]], scoopAnmData[i_idx][0]);
        }

        if (anm != NULL) {
            mpScoopMorf->setAnm(anm, i_attr, i_morf, 1.0f, 0.0f, -1.0f);
        }
    }

    return 1;
}

/* 80964B9C-80964BD0 0023BC 0034+00 1/0 0/0 0/0 .text afterSetMotionAnm__12daNpc_Bans_cFiifi */
bool daNpc_Bans_c::afterSetMotionAnm(int i_idx, int i_attr, f32 i_morf, int param_4) {
    if (mCreating == true) {
        i_morf = 0.0f;
    }

    return setScoopAnm(i_idx, i_attr, i_morf);
}

/* 80964BD0-80964C4C 0023F0 007C+00 1/1 0/0 0/0 .text            selectAction__12daNpc_Bans_cFv */
BOOL daNpc_Bans_c::selectAction() {
    mNextAction = NULL;

    #if DEBUG
    if (mHIO->m.common.debug_mode_ON) {
        mNextAction = &daNpc_Bans_c::test;
        return TRUE;
    }
    #endif
    
    switch (mType) {
        case TYPE_SHOP:
            mNextAction = &daNpc_Bans_c::tend;
            break;
        
        default:
            mNextAction = &daNpc_Bans_c::wait;
            break;
    }

    return TRUE;
}

/* 80964C4C-80964C78 00246C 002C+00 2/2 0/0 0/0 .text            chkAction__12daNpc_Bans_cFM12daNpc_Bans_cFPCvPvPv_i */
BOOL daNpc_Bans_c::chkAction(actionFunc action) {
    return mAction == action;
}

/* 80964C78-80964D20 002498 00A8+00 2/2 0/0 0/0 .text            setAction__12daNpc_Bans_cFM12daNpc_Bans_cFPCvPvPv_i */
BOOL daNpc_Bans_c::setAction(actionFunc action) {
    mMode = MODE_EXIT;
    if (mAction != NULL) {
        (this->*(mAction))(NULL);
    }

    mMode = MODE_ENTER;
    mAction = action;
    if (mAction != NULL) {
        (this->*(mAction))(NULL);
    }

    return 1;
}

/* 80964D20-80964DD0 002540 00B0+00 1/1 0/0 0/0 .text            checkPlayerIn2ndFloorOfBombShop__12daNpc_Bans_cFv */
BOOL daNpc_Bans_c::checkPlayerIn2ndFloorOfBombShop() {
    /* NONMATCHING */
    bool rv = false;
    bool bVar1 = false;

    if (strcmp("R_SP109", dComIfGp_getStartStageName()) == 0 && dComIfGp_roomControl_getStayNo() == 1) {
        bVar1 = true;
    }

    if (bVar1) {
        if (300.0f < fabsf(daPy_getPlayerActorClass()->current.pos.y - current.pos.y)) {
            rv = true;
        }
    }

    return rv;
}

/* 80964DD0-80964EB0 0025F0 00E0+00 2/2 0/0 0/0 .text            orderAngerEvt__12daNpc_Bans_cFv */
void daNpc_Bans_c::orderAngerEvt() {
    daPy_py_c* player = daPy_getPlayerActorClass();

    if (player->checkUseKandelaar(0) && player->getKandelaarFlamePos() != NULL) {
        mEvtNo = EVT_ANGER;

        for (int i = 0; i < 2; i++) {
            daTag_EvtArea_c* actor = (daTag_EvtArea_c*)mActorMngrs[i + 5].getActorP();
            bool bVar1 = false;
            bool bVar2 = false;

            if (actor != NULL) {
                cXyz& pos(player->current.pos);
                bVar1 = true;
                if (actor->chkPointInArea(pos)) {
                    mEvtNo = EVT_ANGER_NEAR;
                    break;
                }
            }
        }
    }
}

/* 80964EB0-80964F48 0026D0 0098+00 1/1 0/0 0/0 .text            getKMsgTagP__12daNpc_Bans_cFv */
fopAc_ac_c* daNpc_Bans_c::getKMsgTagP() {
    f32 fVar1 = 1000000000.0f;
    mFindCount = 0;
    mSrchName = PROC_TAG_KMSG;
    fopAcM_Search(srchActor, this);
    int i = 0;

    for (; i < mFindCount; i++) {
        if (((daTag_KMsg_c*)mFindActorPtrs[i])->getType() == 1) {
            return mFindActorPtrs[i];
        }
    }

    return NULL;
}

/* 80964F48-80964FEC 002768 00A4+00 1/1 0/0 0/0 .text            setPrtcls__12daNpc_Bans_cFv */
void daNpc_Bans_c::setPrtcls() {
    static u16 const id[4] = {
        0x862C, 0x86A3, 0x862D, 0x862E,
    };

    for (int i = 0; i < 4; i++) {
        dComIfGp_particle_set(id[i], &daPy_getPlayerActorClass()->current.pos, NULL, NULL);
    }
}

/* 80964FEC-809658F8 00280C 090C+00 1/0 0/0 0/0 .text            cutAnger__12daNpc_Bans_cFi */
int daNpc_Bans_c::cutAnger(int i_staffId) {
    int rv = 0;
    int* piVar1 = NULL;
    int prm = -1;
    int timer = 0;

    piVar1 = dComIfGp_evmng_getMyIntegerP(i_staffId, "prm");
    if (piVar1 != NULL) {
        prm = *piVar1;
    }

    piVar1 = dComIfGp_evmng_getMyIntegerP(i_staffId, "timer");
    if (piVar1 != NULL) {
        timer = *piVar1;
    }

    if (dComIfGp_getEventManager().getIsAddvance(i_staffId)) {
        switch (prm) {
            case 0:
            case 1:
                if (mType == TYPE_MAKING_BOMBS) {
                    mFaceMotionSeqMngr.setNo(FACE_BLINK, -1.0f, FALSE, 0);
                    mMotionSeqMngr.setNo(MOT_REST, -1.0f, FALSE, 0);
                }

                initTalk(12, NULL);
                break;
            
            case 2:
                if (mType == TYPE_MAKING_BOMBS) {
                    mFaceMotionSeqMngr.setNo(FACE_BLINK, -1.0f, FALSE, 0);
                    mMotionSeqMngr.setNo(MOT_ANGRY_C, -1.0f, FALSE, 0);
                } else {
                    mFaceMotionSeqMngr.setNo(FACE_BLINK, -1.0f, FALSE, 0);
                    mMotionSeqMngr.setNo(MOT_ANGRY_A, -1.0f, FALSE, 0);
                }

                mJntAnm.lookNone(1);
                setAngle(home.angle.y);
                break;

            case 3:
                mEventTimer = timer;
                mDropWaterTimer = 20;
                break;
            
            case 4:
                mEventTimer = timer;
                break;

            case 5:
                mFaceMotionSeqMngr.setNo(FACE_BLINK, -1.0f, FALSE, 0);
                mMotionSeqMngr.setNo(MOT_ANGRY_C, -1.0f, FALSE, 0);
                break;
                
            case 6:
                mFaceMotionSeqMngr.setNo(FACE_TALK_A, -1.0f, FALSE, 0);
                mMotionSeqMngr.setNo(MOT_REST, -1.0f, FALSE, 0);
                initTalk(12, NULL);
                break;
        }
    }

    switch (prm) {
        case 0:
        case 1:
            mJntAnm.lookPlayer(0);

            if (mType == TYPE_POST_TWILIGHT || mType == TYPE_MAKING_BOMBS || mPlayerAngle == mCurAngle.y) {
                if (talkProc(NULL, FALSE, NULL, FALSE) && mFlow.checkEndFlow()) {
                    rv = 1;
                }
            } else {
                step(mPlayerAngle, -1, -1, 15, 0);
            }
            break;
        
        case 2:
            if (mMotionSeqMngr.getNo() == MOT_ANGRY_A || mMotionSeqMngr.getNo() == MOT_ANGRY_C) {
                if (mMotionSeqMngr.checkEndSequence()) {
                    cXyz pos(daPy_getPlayerActorClass()->current.pos);
                    pos.y += 450.0f;
                    mDoAud_seStart(Z2SE_LINK_COVER_WATER, &pos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(this)));
                    setPrtcls();

                    if (mType == TYPE_SHOP) {
                        if (daNpcT_chkTmpBit(57)) { // dSv_event_tmp_flag_c::T_0057 - Kakariko Village (inside) - Barnes bomb shop <purchase>
                            mFaceMotionSeqMngr.setNo(FACE_H_TALK_B, -1.0f, FALSE, 0);
                            mMotionSeqMngr.setNo(MOT_WAIT_D, -1.0f, FALSE, 0);
                        } else {
                            mFaceMotionSeqMngr.setNo(FACE_BLINK, -1.0f, FALSE, 0);
                            mMotionSeqMngr.setNo(MOT_WAIT_C, -1.0f, FALSE, 0);
                        }
                    } else if (mType == TYPE_MAKING_BOMBS) {
                        mFaceMotionSeqMngr.setNo(FACE_BLINK, -1.0f, FALSE, 0);
                        mMotionSeqMngr.setNo(MOT_WORK, -1.0f, FALSE, 0);
                    } else {
                        mFaceMotionSeqMngr.setNo(FACE_BLINK, -1.0f, FALSE, 0);
                        mMotionSeqMngr.setNo(MOT_WAIT_A, -1.0f, FALSE, 0);
                    }
                } else if ((mMotionSeqMngr.getNo() == MOT_ANGRY_A && mpMorf[0]->checkFrame(16.0f)) || (mMotionSeqMngr.getNo() == MOT_ANGRY_C && mpMorf[0]->checkFrame(8.0f))) {
                    dComIfGp_getVibration().StartShock(VIBMODE_S_POWER5, 15, cXyz(0.0f, 1.0f, 0.0f));
                }
            } else {
                rv = 1;
            }
            break;

        case 3:
            if (mDropWaterTimer != 0 || dComIfGp_getEventManager().getIsAddvance(i_staffId) != 0) {
                if (cLib_calcTimer(&mDropWaterTimer) == 0) {
                    daPy_getPlayerActorClass()->onWaterDrop();
                    daPy_getPlayerActorClass()->forceKandelaarLightOff();
                }
            }

            if (cLib_calcTimer(&mEventTimer) == 0) {
                rv = 1;
            }
            break;
        
        case 4:
            action();
            if (cLib_calcTimer(&mEventTimer) == 0) {
                rv = 1;
            }
            break;

        case 5:
            if (mMotionSeqMngr.getNo() == MOT_ANGRY_C) {
                mJntAnm.lookNone(0);
                if (mMotionSeqMngr.checkEndSequence()) {
                    mFaceMotionSeqMngr.setNo(FACE_BLINK, -1.0f, FALSE, 0);
                    mMotionSeqMngr.setNo(MOT_REST, -1.0f, FALSE, 0);
                    rv = 1;
                }
            } else {
                rv = 1;
            }
            break;

        case 6:
            mJntAnm.lookPlayer(0);
            field_0xe26 = 0;

            if (talkProc(NULL, FALSE, NULL, FALSE) && mFlow.checkEndFlow()) {
                rv = 1;
            }
            break;
    }

    if (mMotionSeqMngr.getNo() == MOT_ANGRY_C && mpMorf[0]->checkFrame(9.0f)) {
        mDoAud_seStart(Z2SE_BANS_KICK, &current.pos, 0, 0);
    }

    return rv;
}

/* 809658F8-80965CCC 003118 03D4+00 2/0 0/0 0/0 .text            cutPurchase__12daNpc_Bans_cFi */
int daNpc_Bans_c::cutPurchase(int i_staffId) {
    fopAc_ac_c* actor_p = NULL;
    int rv = 0;
    int* piVar1 = NULL;
    int prm = -1;
    int timer = 0;

    piVar1 = dComIfGp_evmng_getMyIntegerP(i_staffId, "prm");
    if (piVar1 != NULL) {
        prm = *piVar1;
    }

    piVar1 = dComIfGp_evmng_getMyIntegerP(i_staffId, "timer");
    if (piVar1 != NULL) {
        timer = *piVar1;
    }

    if (dComIfGp_getEventManager().getIsAddvance(i_staffId)) {
        switch (prm) {
            case 1:
                mFaceMotionSeqMngr.setNo(FACE_BLINK, 0.0f, FALSE, 0);
                mMotionSeqMngr.setNo(MOT_SIDESTEPL, -1.0f, FALSE, 0);
                speedF = 0.0f;
                speed.setall(0.0f);
                daNpcT_onTmpBit(57); // dSv_event_tmp_flag_c::T_0057 - Kakariko Village (inside) - Barnes bomb shop <purchase>
                break;

            case 2:
                break;

            case 3:
                mFaceMotionSeqMngr.setNo(FACE_BLINK, 0.0f, FALSE, 0);
                mMotionSeqMngr.setNo(MOT_SIDESTEPR, -1.0f, FALSE, 0);
                speedF = 0.0f;
                speed.setall(0.0f);
                field_0x1266 = 0;
                daNpcT_offTmpBit(57); // dSv_event_tmp_flag_c::T_0057 - Kakariko Village (inside) - Barnes bomb shop <purchase>
                break;
        }
    }

    switch (prm) {
        case 1:
            mJntAnm.lookNone(0);
            actor_p = mActorMngrs[7].getActorP();
            JUT_ASSERT(2427, NULL != actor_p);

            if (mMotionSeqMngr.getNo() == MOT_SIDESTEPL) {
                current.angle.y = cLib_targetAngleY(&home.pos, &actor_p->current.pos);
                speedF = mHIO->m.run_spd;

                if (mMotionSeqMngr.checkEndSequence()) {
                    mFaceMotionSeqMngr.setNo(FACE_H_TALK_B, 0.0f, FALSE, 0);
                    mMotionSeqMngr.setNo(MOT_WAIT_D, 0.0f, FALSE, 0);
                    setAngle(shape_angle.y);
                    speedF = 0.0f;
                    speed.setall(0.0f);
                }
            } else {
                rv = 1;
            }
            break;

        case 3:
            mJntAnm.lookNone(0);
            actor_p = mActorMngrs[7].getActorP();
            JUT_ASSERT(2448, NULL != actor_p);

            if (mMotionSeqMngr.getNo() == MOT_SIDESTEPR) {
                current.angle.y = cLib_targetAngleY(&actor_p->current.pos, &home.pos);
                speedF = mHIO->m.run_spd;

                if (mMotionSeqMngr.checkEndSequence()) {
                    mFaceMotionSeqMngr.setNo(FACE_BLINK, 0.0f, FALSE, 0);
                    mMotionSeqMngr.setNo(MOT_WAIT_C, 0.0f, FALSE, 0);
                    setAngle(shape_angle.y);
                    speedF = 0.0f;
                    speed.setall(0.0f);
                }
            } else {
                rv = 1;
            }
            break;
    }

    return rv;
}

/* 80965CCC-809661F0 0034EC 0524+00 1/0 0/0 0/0 .text            wait__12daNpc_Bans_cFPv */
int daNpc_Bans_c::wait(void* param_1) {
    daNpc_Len_c* actor_p = NULL;

    switch (mMode) {
        case 0:
        case 1:
            if (!mStagger.checkStagger()) {
                switch (mType) {
                    case TYPE_POST_TWILIGHT:
                        mFaceMotionSeqMngr.setNo(FACE_BLINK, -1.0f, FALSE, 0);
                        mMotionSeqMngr.setNo(MOT_SAD, -1.0f, FALSE, 0);
                        break;

                    case TYPE_TWILIGHT:
                        mFaceMotionSeqMngr.setNo(FACE_NONE, -1.0f, FALSE, 0);
                        mMotionSeqMngr.setNo(MOT_WAIT_TW, -1.0f, FALSE, 0);
                        break;
                    
                    case TYPE_COLIN_KIDNAPPED:
                        mFaceMotionSeqMngr.setNo(FACE_BLINK, -1.0f, FALSE, 0);
                        mMotionSeqMngr.setNo(MOT_FAINT, -1.0f, FALSE, 0);
                        break;

                    case TYPE_MAKING_BOMBS:
                        mFaceMotionSeqMngr.setNo(FACE_BLINK, -1.0f, FALSE, 0);
                        mMotionSeqMngr.setNo(MOT_WORK, -1.0f, FALSE, 0);
                        break;

                    default:
                        mFaceMotionSeqMngr.setNo(FACE_BLINK, -1.0f, FALSE, 0);
                        mMotionSeqMngr.setNo(MOT_WAIT_A, -1.0f, FALSE, 0);
                        break;
                }

                mMode = 2;
            }
            // fallthrough
        case 2:
            if (mType == TYPE_TWILIGHT) {
                actor_p = (daNpc_Len_c*)mActorMngrs[3].getActorP();
                if (actor_p != NULL && actor_p->checkStartDemo13StbEvt(this, mHIO->m.common.box_min_x, mHIO->m.common.box_min_y, mHIO->m.common.box_min_z,
                                                                       mHIO->m.common.box_max_x, mHIO->m.common.box_max_y, mHIO->m.common.box_max_z, mHIO->m.common.box_offset)) {
                    mEvtNo = EVT_DEMO13_STB;
                    mDemo13Flag = 1;
                }

                if (mDemo13Flag != 0 &&
                    daNpcT_chkEvtBit(60) && // dSv_event_flag_c::M_027 - Cutscene - [cutscene: 13] kids in the church (beast eyes)
                    !dComIfGp_event_runCheck()
                ) {
                   mDemo13Flag = 0; 
                }
            }

            if (mType != TYPE_TWILIGHT && mType != TYPE_COLIN_KIDNAPPED) {
                orderAngerEvt();
                if (mType == 3) {
                    if (mEvtNo == EVT_ANGER) {
                        mEvtNo = EVT_ANGER2;
                    }

                    if (mEvtNo == EVT_ANGER_NEAR) {
                        mEvtNo = EVT_ANGER_NEAR2;
                    }
                }
            }

            if (!mStagger.checkStagger()) {
                if (mType == TYPE_POST_TWILIGHT || mType == TYPE_COLIN_KIDNAPPED || mType == TYPE_MAKING_BOMBS) {
                    mPlayerActorMngr.remove();
                }

                if (mPlayerActorMngr.getActorP() != NULL && !mTwilight && mType != TYPE_COLIN_KIDNAPPED) {
                    mJntAnm.lookPlayer(0);
                    if (!chkActorInSight(mPlayerActorMngr.getActorP(), mAttnFovY, mCurAngle.y)) {
                        mJntAnm.lookNone(0);
                    }

                    if (!srchPlayerActor() && home.angle.y == mCurAngle.y) {
                        mMode = 1;
                    }
                } else {
                    mJntAnm.lookNone(0);

                    if (home.angle.y != mCurAngle.y) {
                        if (field_0xe34 != 0) {
                            if (step(home.angle.y, -1, -1, 15, 0)) {
                                mMode = 1;
                            }
                        } else {
                            setAngle(home.angle.y);
                            mMode = 1;
                        }

                        attention_info.flags = 0;
                    } else if (!mTwilight && mType != TYPE_POST_TWILIGHT && mType != TYPE_COLIN_KIDNAPPED && mType == TYPE_MAKING_BOMBS) {
                        srchPlayerActor();
                    }
                }

                switch (mJntAnm.getMode()) {
                    case 0:
                        break;
                }
            }
            break;

        case 3:
            break;
    }

    return 1;
}

/* 809661F0-80966874 003A10 0684+00 1/0 0/0 0/0 .text            tend__12daNpc_Bans_cFPv */
int daNpc_Bans_c::tend(void* param_1) {
    /* NONMATCHING */
    BOOL bVar1 = FALSE;

    switch (mMode) {
        case 0:
        case 1:
            if (!mStagger.checkStagger()) {
                if (field_0x126a != 0) {
                    mFaceMotionSeqMngr.setNo(FACE_H_TALK_B, -1.0f, FALSE, 0);
                    mMotionSeqMngr.setNo(MOT_WAIT_B, -1.0f, FALSE, 0);
                } else {
                    if (daNpcT_chkTmpBit(57)) { // dSv_event_tmp_flag_c::T_0057 - Kakariko Village (inside) - Barnes bomb shop <purchase>
                        mFaceMotionSeqMngr.setNo(FACE_H_TALK_B, -1.0f, FALSE, 0);
                        mMotionSeqMngr.setNo(MOT_WAIT_D, -1.0f, FALSE, 0);
                    } else {
                        mFaceMotionSeqMngr.setNo(FACE_BLINK, -1.0f, FALSE, 0);
                        mMotionSeqMngr.setNo(MOT_WAIT_C, -1.0f, FALSE, 0);
                    }

                    mTimer = 20;
                }

                mMode = 2;
            }
            // fallthrough
        case 2:
            if (mShopFlag) {
                if (field_0x1266) {
                    mEvtNo = EVT_GOBACK;
                    field_0xe33 = true;
                } else if (daNpcT_chkTmpBit(57)) { // dSv_event_tmp_flag_c::T_0057 - Kakariko Village (inside) - Barnes bomb shop <purchase>
                    mSpeakEvent = true;
                    field_0xe33 = true;
                } else if (mShopProcess == 2) {
                    mSpeakEvent = true;
                    field_0xe33 = true;
                } else {
                    orderAngerEvt();
                }
            } else {
                orderAngerEvt();
            }

            if (field_0x126a) {
                mJntAnm.lookNone(0);
                attention_info.flags = 0;
            } else if (!mStagger.checkStagger()) {
                mJntAnm.lookNone(0);

                if (home.angle.y != mCurAngle.y) {
                    if (field_0xe34) {
                        if (step(home.angle.y, -1, -1, 15, 0)) {
                            mMode = 1;
                        }
                    } else {
                        setAngle(home.angle.y);
                        mMode = 1;
                    }

                    attention_info.flags = 0;
                } else {
                    bVar1 = FALSE;
                    fopAc_ac_c* actor_p = mActorMngrs[7].getActorP();

                    if (actor_p != NULL) {
                        cXyz attnPos = getAttnPos(daPy_getPlayerActorClass());
                        BOOL bVar2 = NULL != mPlayerActorMngr.getActorP();
                        
                        int i_no = attention_info.distances[fopAc_attn_SPEAK_e];
                        f32 dist_max = dComIfGp_getAttention()->getDistTable(i_no).mDistMax;
                        f32 neg_lower_y = dComIfGp_getAttention()->getDistTable(i_no).mLowerY * -1.0f;
                        f32 neg_upper_y = dComIfGp_getAttention()->getDistTable(i_no).mUpperY * -1.0f;

                        if (bVar2) {
                            i_no = attention_info.distances[fopAc_attn_TALK_e];
                            dist_max = dComIfGp_getAttention()->getDistTable(i_no).mDistMaxRelease;
                        }

                        if (chkPointInArea(attnPos, actor_p->attention_info.position, dist_max, neg_lower_y, neg_upper_y, 0)) {
                            mJntAnm.lookPlayer(0);
                            bVar1 = true;
                        }
                    }

                    if (!bVar1) {
                        if (mPlayerActorMngr.getActorP() != NULL) {
                            mJntAnm.lookPlayer(0);

                            if (!chkActorInSight(mPlayerActorMngr.getActorP(), mAttnFovY, mCurAngle.y)) {
                                mJntAnm.lookNone(0);
                            }

                            if (!srchPlayerActor()) {
                                mMode = 1;
                            }
                        } else {
                            mJntAnm.lookNone(0);

                            if (!mTwilight && mType != TYPE_POST_TWILIGHT && mType != TYPE_COLIN_KIDNAPPED) {
                                srchPlayerActor();
                            }
                        }
                    }
                }

                switch (mJntAnm.getMode()) {
                    case 0:
                        break;

                    case 1:
                        if (daPy_py_c::checkNowWolf()) {
                            if (field_0x126a) {
                                mJntAnm.lookNone(0);
                            } else if (cLib_calcTimer(&mTimer) == 0) {
                                mMotionSeqMngr.setNo(MOT_MASKDOWN, -1.0f, FALSE, 0);
                                field_0x126a = 1;
                            }

                            attention_info.flags = 0;
                        }
                        break;
                }
            }
            break;

        case 3:
            break;
    }

    return 1;
}

/* 80966888-80966B24 0040A8 029C+00 3/0 0/0 0/0 .text            talk__12daNpc_Bans_cFPv */
int daNpc_Bans_c::talk(void* param_1) {
    switch (mMode) {
        case 0:
        case 1:
            if (!mStagger.checkStagger()) {
                initTalk(mFlowNodeNo, NULL);
                mMakingBombsFlag = 0;

                if (mType == TYPE_MAKING_BOMBS) {
                    if (daNpcT_chkEvtBit(240)) { // dSv_event_flag_c::F_0240 - Kakariko Village - Speak with Barnes while heas making bombs
                        mMakingBombsFlag = 1;
                    } else {
                        mFaceMotionSeqMngr.setNo(FACE_BLINK, -1.0f, FALSE, 0);
                        mMotionSeqMngr.setNo(MOT_REST, -1.0f, FALSE, 0);
                    }
                }

                mMode = 2;
            }
            // fallthrough
        case 2:
            if (!mStagger.checkStagger()) {
                if (mTwilight || mPlayerAngle == mCurAngle.y || mType == TYPE_POST_TWILIGHT || mType == TYPE_COLIN_KIDNAPPED || mType == TYPE_MAKING_BOMBS) {
                    if (talkProc(NULL, FALSE, NULL, FALSE) && mFlow.checkEndFlow()) {
                        mPlayerActorMngr.entry(daPy_getPlayerActorClass());
                        dComIfGp_event_reset();
                        mMode = 3;
                    }

                    mJntAnm.lookPlayer(0);

                    if (mTwilight || mType == TYPE_POST_TWILIGHT || mType == TYPE_COLIN_KIDNAPPED || mMakingBombsFlag) {
                        mJntAnm.lookNone(0);
                    }
                } else {
                    mJntAnm.lookPlayer(0);
                    step(mPlayerAngle, -1, -1, 15, 0);
                }
            }
            break;

        case 3:
            break;
    }

    return 0;
}

/* 80966B24-80966C88 004344 0164+00 2/0 0/0 0/0 .text            shop__12daNpc_Bans_cFPv */
int daNpc_Bans_c::shop(void* param_1) {
    switch (mMode) {
        case 0:
        case 1:
            if (!mStagger.checkStagger()) {
                if (mShopProcess == 2) {
                    shop_init(true);
                } else {
                    mShopCamAction.Save();
                    initTalk(mFlowNodeNo, NULL);
                    setAngle(home.angle.y);
                    shop_init(false);
                }

                mJntAnm.lookNone(1);
                mMode = 2;
            }
            // fallthrough
        case 2:
            if (!mStagger.checkStagger()) {
                mShopProcess = shop_process(this, &mFlow);
                if (mShopProcess != 0) {
                    if (daNpcT_chkTmpBit(57)) { // dSv_event_tmp_flag_c::T_0057 - Kakariko Village (inside) - Barnes bomb shop <purchase>
                        field_0x1266 = 1;
                    }

                    mPlayerActorMngr.entry(daPy_getPlayerActorClass());
                    dComIfGp_event_reset();
                    mMode = 3;
                    mSetParamFlag = 1;
                }
            }
            break;

        case 3:
            break;
    }

    return 0;
}

#if DEBUG
/* 80DA60D0 - 80DA61AF */
int daNpc_Bans_c::test(void* param_1) {
    int rv = 0;
    
    switch (mMode) {
        case 0:
        case 1:
            speedF = 0.0f;
            speed.setall(0.0f);
            mMode = 2;
            // fallthrough
        case 2:
            mFaceMotionSeqMngr.setNo(mHIO->m.common.face_expression, -1.0f, FALSE, 0);
            mMotionSeqMngr.setNo(mHIO->m.common.motion, -1.0f, FALSE, 0);
            mJntAnm.lookNone(0);
            attention_info.flags = 0;
            break;

        case 3:
            break;
    }

    return rv;
}
#endif

/* 80966C88-80966CA8 0044A8 0020+00 1/0 0/0 0/0 .text            daNpc_Bans_Create__FPv */
static int daNpc_Bans_Create(void* a_this) {
    return static_cast<daNpc_Bans_c*>(a_this)->create();
}

/* 80966CA8-80966CC8 0044C8 0020+00 1/0 0/0 0/0 .text            daNpc_Bans_Delete__FPv */
static int daNpc_Bans_Delete(void* a_this) {
    return static_cast<daNpc_Bans_c*>(a_this)->Delete();
}

/* 80966CC8-80966CE8 0044E8 0020+00 1/0 0/0 0/0 .text            daNpc_Bans_Execute__FPv */
static int daNpc_Bans_Execute(void* a_this) {
    return static_cast<daNpc_Bans_c*>(a_this)->Execute();
}

/* 80966CE8-80966D08 004508 0020+00 1/0 0/0 0/0 .text            daNpc_Bans_Draw__FPv */
static int daNpc_Bans_Draw(void* a_this) {
    return static_cast<daNpc_Bans_c*>(a_this)->Draw();
}

/* 80966D08-80966D10 004528 0008+00 1/0 0/0 0/0 .text            daNpc_Bans_IsDelete__FPv */
static int daNpc_Bans_IsDelete(void* a_this) {
    return 1;
}

/* 80968684-809686A4 -00001 0020+00 1/0 0/0 0/0 .data            daNpc_Bans_MethodTable */
static actor_method_class daNpc_Bans_MethodTable = {
    (process_method_func)daNpc_Bans_Create,
    (process_method_func)daNpc_Bans_Delete,
    (process_method_func)daNpc_Bans_Execute,
    (process_method_func)daNpc_Bans_IsDelete,
    (process_method_func)daNpc_Bans_Draw,
};

/* 809686A4-809686D4 -00001 0030+00 0/0 0/0 1/0 .data            g_profile_NPC_BANS */
extern actor_process_profile_definition g_profile_NPC_BANS = {
  fpcLy_CURRENT_e,          // mLayerID
  7,                        // mListID
  fpcPi_CURRENT_e,          // mListPrio
  PROC_NPC_BANS,            // mProcName
  &g_fpcLf_Method.base,    // sub_method
  sizeof(daNpc_Bans_c),     // mSize
  0,                        // mSizeOther
  0,                        // mParameters
  &g_fopAc_Method.base,     // sub_method
  322,                      // mPriority
  &daNpc_Bans_MethodTable,  // sub_method
  0x00040107,               // mStatus
  fopAc_NPC_e,              // mActorType
  fopAc_CULLBOX_CUSTOM_e,   // cullType
};
