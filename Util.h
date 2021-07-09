//
// Created by sett on 07-Jul-21.
//

#ifndef CONTROLLER2MOUSE_UTIL_H
#define CONTROLLER2MOUSE_UTIL_H

#include <windows.h>
#include "Controller.h"
#include "Sender.h"

class Util {
    static WORD prevWBtns;
    static bool isFirst;
public:
    static void checkBtnMouse(Controller *controller, WORD btn, DWORD eventDown, DWORD eventUp);

    static void checkBtnKeyboard(Controller *controller, WORD btn, WORD keyCode);

    static void checkBtnKeyboardCombination(Controller *controller, WORD btn, WORD keyCode1, WORD keyCode2);

    static bool checkBtnCombination(Controller *controller, WORD btn1, WORD btn2);

    static bool checkBtnCombination(Controller *controller, WORD btn1, WORD btn2, WORD btn3);

    static bool hasBtnChanged(Controller *controller, WORD btn);

    static void setPrevWBtns(WORD btnState) {
        prevWBtns = btnState;
    }
};


#endif //CONTROLLER2MOUSE_UTIL_H
