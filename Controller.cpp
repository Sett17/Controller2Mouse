//
// Created by sett on 04-Jul-21.
//

#include <cstdlib>
#include <cstdio>
#include <xstring>
#include "Controller.h"

int Controller::getPort() {
    return cId + 1;
}

XINPUT_GAMEPAD *Controller::getState() {
    return &state.Gamepad;
}

bool Controller::checkConnection() {
    int controllerId = -1;

    for (DWORD i = 0; i < XUSER_MAX_COUNT && controllerId == -1; i++) {
        XINPUT_STATE xinputState;
        ZeroMemory(&xinputState, sizeof(XINPUT_STATE));

        if (XInputGetState(i, &xinputState) == ERROR_SUCCESS)
            controllerId = i;
    }

    cId = controllerId;

    return controllerId != -1;
}

bool Controller::refresh() {
    if (cId == -1) {
        checkConnection();
    }

    if (cId != -1) {
        ZeroMemory(&state, sizeof(XINPUT_STATE));
        if (XInputGetState(cId, &state) != ERROR_SUCCESS) {
            cId = -1;
            return false;
        }

        float normLX = fmaxf(-1, (float) state.Gamepad.sThumbLX / 32767);
        float normLY = fmaxf(-1, (float) state.Gamepad.sThumbLY / 32767);

        leftStickX = (abs(normLX) < deadZoneX ? 0 : (abs(normLX) - deadZoneX) * (normLX / abs(normLX)));
        leftStickY = (abs(normLY) < deadZoneY ? 0 : (abs(normLY) - deadZoneY) * (normLY / abs(normLY)));

        if (deadZoneX > 0) leftStickX *= 1 / (1 - deadZoneX);
        if (deadZoneY > 0) leftStickY *= 1 / (1 - deadZoneY);

        float normRX = fmaxf(-1, (float) state.Gamepad.sThumbRX / 32767);
        float normRY = fmaxf(-1, (float) state.Gamepad.sThumbRY / 32767);

        rightStickX = (abs(normRX) < deadZoneX ? 0 : (abs(normRX) - deadZoneX) * (normRX / abs(normRX)));
        rightStickY = (abs(normRY) < deadZoneY ? 0 : (abs(normRY) - deadZoneY) * (normRY / abs(normRY)));

        if (deadZoneX > 0) rightStickX *= 1 / (1 - deadZoneX);
        if (deadZoneY > 0) rightStickY *= 1 / (1 - deadZoneY);

        leftTrigger = (float) state.Gamepad.bLeftTrigger / 255;
        rightTrigger = (float) state.Gamepad.bRightTrigger / 255;

        return true;
    }
    return false;
}

bool Controller::isPressed(WORD btn) {
    return (state.Gamepad.wButtons & btn) != 0;
}

void Controller::printThis() {
    printf("|LStick: %05d, %05d | RStick: %05d, %05d|\n|LTrigger: %03d | RTrigger: %03d", leftStickX, leftStickY, rightStickX, rightStickY, leftTrigger, rightTrigger);
}
