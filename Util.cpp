//
// Created by sett on 07-Jul-21.
//

#include <iostream>
#include "Util.h"

WORD Util::prevWBtns{0};
bool Util::isFirst{true};

void Util::checkBtnMouse(Controller *controller, WORD btn, DWORD eventDown, DWORD eventUp) {
    if (hasBtnChanged(controller, btn) && controller->isPressed(btn)) {
        Sender::sendMouseKey(eventDown);
    }
    if (hasBtnChanged(controller, btn) && !controller->isPressed(btn)) {
        Sender::sendMouseKey(eventUp);
    }
}

void Util::checkBtnKeyboard(Controller *controller, WORD btn, WORD keyCode) {
    if (hasBtnChanged(controller, btn) && controller->isPressed(btn)) {
        Sender::sendKeyboardKey(keyCode, false);
    }
    if (hasBtnChanged(controller, btn)) {
        Sender::sendKeyboardKey(keyCode, true);
    }
}

bool Util::hasBtnChanged(Controller *controller, WORD btn) {
    if (isFirst) {
        isFirst = false;
        return false;
    }
    return ((prevWBtns & btn) != (controller->getState()->wButtons & btn));
}

bool Util::checkBtnCombination(Controller *controller, WORD btn1, WORD btn2) {
    return ((prevWBtns & (btn1 | btn2)) != (controller->getState()->wButtons & (btn1 | btn2)) && controller->isPressed(btn1) && controller->isPressed(btn2));
}

bool Util::checkBtnCombination(Controller *controller, WORD btn1, WORD btn2, WORD btn3) {
    return (checkBtnCombination(controller, btn1, btn2) && checkBtnCombination(controller, btn2, btn3));
}