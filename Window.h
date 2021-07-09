//
// Created by sett on 07-Jul-21.
//

#ifndef CONTROLLER2MOUSE_WINDOW_H
#define CONTROLLER2MOUSE_WINDOW_H

#include <Windows.h>


class Window {
    HWND mHwnd;
public:
    Window(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    HWND getHwnd();
};


#endif //CONTROLLER2MOUSE_WINDOW_H
