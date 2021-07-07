#include <iostream>
#include <windows.h>
#include "Controller.h"
#include "setInterval.cpp"
#include "Sender.h"
#include "Util.h"

#pragma comment(lib, "Xinput.lib")
#pragma comment(lib, "User32.lib")

void handleTick(Controller *);

std::atomic_bool b;
bool running = true;

int main() {
    auto controller = Controller(.1f, .1f);
    Util::setPrevWBtns(controller.getState()->wButtons);
    running = true;
    controller.refresh();
    controller.refresh();
    controller.refresh();
    controller.refresh();
    controller.refresh();
    controller.refresh();
    controller.refresh();
    controller.refresh();
    controller.refresh();
    controller.refresh();

    setInterval(b, 5, handleTick, &controller);
}

void handleTick(Controller *controller) {
    controller->refresh();
    if (running) {
        //move
        int leftTriggerMul = 18.5 * controller->leftTrigger;
        int defaultMul = 5;
        int mul = defaultMul + leftTriggerMul;
        Sender::moveMouse(controller->leftStickX * mul, -controller->leftStickY * mul);

        //scroll
        Sender::scrollMouse(controller->rightStickX * 121, controller->rightStickY * 121);

        //buttons
        Util::checkBtnMouse(controller, XINPUT_GAMEPAD_A, MOUSEEVENTF_LEFTDOWN, MOUSEEVENTF_LEFTUP);
        Util::checkBtnMouse(controller, XINPUT_GAMEPAD_RIGHT_THUMB, MOUSEEVENTF_RIGHTDOWN, MOUSEEVENTF_RIGHTUP);
        Util::checkBtnMouse(controller, XINPUT_GAMEPAD_LEFT_THUMB, MOUSEEVENTF_MIDDLEDOWN, MOUSEEVENTF_MIDDLEUP);
        Util::checkBtnKeyboard(controller, XINPUT_GAMEPAD_DPAD_LEFT, VK_BACK);
        Util::checkBtnKeyboard(controller, XINPUT_GAMEPAD_DPAD_DOWN, VK_MEDIA_PLAY_PAUSE);

        if (Util::checkBtnCombination(controller, XINPUT_GAMEPAD_BACK, XINPUT_GAMEPAD_START)) {
            b.store(false);
            exit(0);
        }

    }
    if (Util::hasBtnChanged(controller, XINPUT_GAMEPAD_BACK) && controller->isPressed(XINPUT_GAMEPAD_BACK)) {
        running = !running;
        std::cout << "switch: " << running << endl;
    }
    Util::setPrevWBtns(controller->getState()->wButtons);
}