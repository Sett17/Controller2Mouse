#include <iostream>
#include <windows.h>
#include "Controller.h"
#include "setInterval.cpp"
#include "Sender.h"

#pragma comment(lib, "Xinput.lib")
#pragma comment(lib, "User32.lib")

void handleTick(Controller *);

void checkBtnMouse(Controller *controller, WORD btn, DWORD eventDown, DWORD eventUp);

void checkBtnKeyboard(Controller *controller, WORD btn, WORD keyCode);

std::atomic_bool b;
WORD prevwButtons;

int main() {
    auto controller = Controller(.1f, .1f);
    prevwButtons = controller.getState()->wButtons;

    setInterval(b, 5, handleTick, &controller);
}

void handleTick(Controller *controller) {
    controller->refresh();

    //move
    int leftTriggerMul = 17 * controller->leftTrigger;
    int defaultMul = 5;
    int mul = defaultMul + leftTriggerMul;
    Sender::moveMouse(controller->leftStickX * mul, -controller->leftStickY * mul);

    //scroll
    Sender::scrollMouse(controller->rightStickX * 120, controller->rightStickY * 120);

    //buttons
    checkBtnMouse(controller, XINPUT_GAMEPAD_A, MOUSEEVENTF_LEFTDOWN, MOUSEEVENTF_LEFTUP);
    checkBtnMouse(controller, XINPUT_GAMEPAD_RIGHT_THUMB, MOUSEEVENTF_RIGHTDOWN, MOUSEEVENTF_RIGHTUP);
    checkBtnMouse(controller, XINPUT_GAMEPAD_LEFT_THUMB, MOUSEEVENTF_MIDDLEDOWN, MOUSEEVENTF_MIDDLEUP);

    checkBtnKeyboard(controller, XINPUT_GAMEPAD_DPAD_LEFT, VK_BACK);

    prevwButtons = controller->getState()->wButtons;
}

void checkBtnMouse(Controller *controller, WORD btn, DWORD eventDown, DWORD eventUp) {
    if (((prevwButtons & btn) != 0) != controller->isPressed(btn) && controller->isPressed(btn)) {
        Sender::sendMouseKey(eventDown);
    }
    if (((prevwButtons & btn) != 0) != controller->isPressed(btn) && !controller->isPressed(btn)) {
        Sender::sendMouseKey(eventUp);
    }
}

void checkBtnKeyboard(Controller *controller, WORD btn, WORD keyCode) {
    if (((prevwButtons & btn) != 0) != controller->isPressed(btn) && controller->isPressed(btn)) {
        Sender::sendKeyboardKey(keyCode, false);
    }
    if (((prevwButtons & btn) != 0) != controller->isPressed(btn) && !controller->isPressed(btn)) {
        Sender::sendKeyboardKey(keyCode, true);
    }
}