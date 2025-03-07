/**
 * c_bg_w.cpp
 *
 */

#include "SSystem/SComponent/c_bg_w.h"

/* 802681C0-802681C8 262B00 0008+00 0/0 1/1 0/0 .text            Regist__9cBgW_BgIdFi */
void cBgW_BgId::Regist(int id) {
    m_id = id;
}

/* 802681C8-802681D4 262B08 000C+00 0/0 2/2 0/0 .text            Release__9cBgW_BgIdFv */
void cBgW_BgId::Release() {
    m_id = 0x100;
}

/* 802681D4-802681E4 262B14 0010+00 0/0 7/7 121/121 .text            ChkUsed__9cBgW_BgIdCFv */
bool cBgW_BgId::ChkUsed() const {
    if (m_id < 0x100) {
        return true;
    }

    return false;
}

/* 802681E4-802681FC 262B24 0018+00 1/1 22/22 8/8 .text            cBgW_CheckBGround__Ff */
bool cBgW_CheckBGround(float y) {
    if (y >= 0.5f) {
        return true;
    } else {
        return false;
    }
}

/* 802681FC-80268210 262B3C 0014+00 1/1 6/6 0/0 .text            cBgW_CheckBRoof__Ff */
bool cBgW_CheckBRoof(float y) {
    if (y < (-4.0f / 5.0f)) {
        return true;
    } else {
        return false;
    }
}

/* 80268210-80268260 262B50 0050+00 0/0 16/16 4/4 .text            cBgW_CheckBWall__Ff */
bool cBgW_CheckBWall(float y) {
    if (!cBgW_CheckBGround(y) && !cBgW_CheckBRoof(y))
        return true;

    return false;
}
