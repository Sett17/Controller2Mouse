//
// Created by sett on 05-Jul-21.
//

#include <Windows.h>
#include "Sender.h"

void Sender::moveMouse(int x, int y) {
    INPUT inp;
    inp.type = INPUT_MOUSE;
    inp.mi.mouseData = 0;
    inp.mi.time = 0;
    inp.mi.dx = x;
    inp.mi.dy = y;
    inp.mi.dwFlags = MOUSEEVENTF_MOVE;
    SendInput(1, &inp, sizeof(inp));
}

void Sender::scrollMouse(int x, int y) {
    if (x != 0) {
        INPUT inp;
        inp.type = INPUT_MOUSE;
        inp.mi.mouseData = x;
        inp.mi.time = 0;
        inp.mi.dwFlags = MOUSEEVENTF_HWHEEL;
        SendInput(1, &inp, sizeof(inp));
    }
    if (y != 0) {
        INPUT inp;
        inp.type = INPUT_MOUSE;
        inp.mi.mouseData = y;
        inp.mi.time = 0;
        inp.mi.dwFlags = MOUSEEVENTF_WHEEL;
        SendInput(1, &inp, sizeof(inp));
    }
}

void Sender::sendMouseKey(int flags) {
    INPUT inp;
    inp.type = INPUT_MOUSE;
    inp.mi.mouseData = 0;
    inp.mi.time = 0;
    inp.mi.dwFlags = flags;

    SendInput(1, &inp, sizeof(inp));
}

void Sender::sendKeyboardKey(int keyCode, bool doUp) {
    INPUT inp;
    inp.type = INPUT_KEYBOARD;
    inp.ki.wVk = keyCode;
    inp.ki.wScan = 0;
    inp.ki.time = 0;
    inp.ki.dwFlags = 0;
    if (doUp) {
        inp.ki.dwFlags = KEYEVENTF_KEYUP;
    }

    SendInput(1, &inp, sizeof(inp));
}