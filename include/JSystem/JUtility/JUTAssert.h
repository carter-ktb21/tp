#ifndef JUTASSERT_H
#define JUTASSERT_H

#include "dolphin/os.h"

#ifdef DEBUG
#define JUT_ASSERT(LINE, COND) \
    (COND) ? (void)0 : (JUTAssertion::showAssert(JUTAssertion::getSDevice(), __FILE__, LINE, #COND), OSPanic(__FILE__, LINE, "Halt"));

#define JUT_ASSERT_MSG(LINE, COND, MSG) \
    (COND) ? (void)0 : (JUTAssertion::showAssert(JUTAssertion::getSDevice(), __FILE__, LINE, MSG), OSPanic(__FILE__, LINE, "Halt"));

#define JUT_ASSERT_MSG_F(LINE, COND, MSG, ...) \
    (COND) ? (void)0 : (JUTAssertion::showAssert_f(JUTAssertion::getSDevice(), __FILE__, LINE, MSG, __VA_ARGS__), OSPanic(__FILE__, LINE, "Halt"));

#define J3D_ASSERT(LINE, COND, MSG) JUT_ASSERT_MSG(LINE, (COND) != 0, MSG)
#define J3D_PANIC(LINE, COND, MSG) ((COND) != 0 || (OSPanic(__FILE__, LINE, MSG), 0));

#define JUT_PANIC(LINE, TEXT)                                                                      \
    JUTAssertion::showAssert(JUTAssertion::getSDevice(), __FILE__, LINE, TEXT);                    \
    OSPanic(__FILE__, LINE, "Halt");

#define JUT_WARN_DEVICE(LINE, DEVICE, ...)                                                                        \
    JUTAssertion::setWarningMessage_f(DEVICE, __FILE__, LINE, __VA_ARGS__);    \

#define JUT_WARN(LINE, ...)                                                                        \
    JUT_WARN_DEVICE(LINE, JUTAssertion::getSDevice(), __VA_ARGS__)

#define JUT_LOG(LINE, ...)                                                                         \
    JUTAssertion::setLogMessage_f(JUTAssertion::getSDevice(), __FILE__, LINE, __VA_ARGS__)

#define JUT_CONFIRM(LINE, COND)                                                                    \
    JUTAssertion::setConfirmMessage(JUTAssertion::getSDevice(), __FILE__, LINE, COND, #COND)

#else
#define JUT_ASSERT(...) (void)0;
#define JUT_ASSERT_MSG(...) (void)0;
#define JUT_ASSERT_MSG_F(...) (void)0;
#define J3D_ASSERT(...) (void)0;
#define J3D_PANIC(...) (void)0;
#define JUT_PANIC(...)
#define JUT_WARN(...)
#define JUT_WARN_DEVICE(...)
#define JUT_LOG(...)
#define JUT_CONFIRM(...)
#endif

namespace JUTAssertion {
    /* 802E495C */ void create();
    /* 802E4960 */ u32 flush_subroutine();
    /* 802E499C */ void flushMessage();
    /* 802E4A54 */ void flushMessage_dbPrint();
    /* 802E4C34 */ void setVisible(bool);
    /* 802E4C3C */ void setMessageCount(int);

    u32 getSDevice();
    void showAssert(u32 device, const char * file, int line, const char * assertion);
    void showAssert_f(u32 device, const char* file, int line, const char* msg, ...);
    void setWarningMessage_f(u32 device, char * file, int line, const char * fmt, ...);
    void setLogMessage_f(u32 device, char* file, int line, const char* fmt, ...);
    void setConfirmMessage(u32 param_1, char* file, int line, bool param_4, const char* msg);
};

extern bool sAssertVisible;

#endif /* JUTASSERT_H */
