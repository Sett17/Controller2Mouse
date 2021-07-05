//
// Created by sett on 05-Jul-21.
//

#ifndef CONTROLLER2MOUSE_SENDER_H
#define CONTROLLER2MOUSE_SENDER_H


class Sender {
public:
    static void moveMouse(int x, int y);

    static void scrollMouse(int x, int y);

    static void sendMouseKey(int flags);

    static void sendKeyboardKey(int keyCode, bool doUp);
};


#endif //CONTROLLER2MOUSE_SENDER_H
