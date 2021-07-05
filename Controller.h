//
// Created by sett on 04-Jul-21.
//

#ifndef CONTROLLER2MOUSE_CONTROLLER_H
#define CONTROLLER2MOUSE_CONTROLLER_H

#include <Windows.h>
#include <xinput.h>

class Controller {
    int cId;
    XINPUT_STATE state;

    float deadZoneX, deadZoneY;

public:
    Controller() : deadZoneX(.05f), deadZoneY(.02f) {}

    Controller(float dzX, float dzY) : deadZoneX(dzX), deadZoneY(dzY) {}

    float leftStickX, leftStickY;
    float rightStickX, rightStickY;
    float leftTrigger, rightTrigger;

    int getPort();

    XINPUT_GAMEPAD *getState();

    bool checkConnection();

    bool refresh();

    bool isPressed(WORD);

    void printThis();
};


#endif //CONTROLLER2MOUSE_CONTROLLER_H
