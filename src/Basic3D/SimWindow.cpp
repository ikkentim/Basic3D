/* Copyright (C) 2015 Tim Potze
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

/**
* GameWindow.cpp
* Defines the GameWindow class.
*/

#include "SimWindow.h"
#include <string>

#define WINDOW_WIDTH    (ENGINE_WIDTH)
#define WINDOW_HEIGHT   (ENGINE_HEIGHT)

static SimWindow *window_ = NULL;
HINSTANCE SimWindow::instance_ = GetModuleHandle(NULL);

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    return window_->msg_proc(hWnd, uMsg, wParam, lParam);
}

SimWindow::SimWindow(Engine *engine) {
    window_ = this;
    engine_ = engine;
    hWnd_ = NULL;
}

int SimWindow::run() {
    MSG msg = { 0 };
    INT64 frequency;
    INT64 lastTick;

    ::QueryPerformanceCounter((LARGE_INTEGER*)&lastTick);
    ::QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);

    while (msg.message != WM_QUIT) {
        if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else {
            INT64 tick;
            QueryPerformanceCounter((LARGE_INTEGER*)&tick);
            QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);

            if (//GetFocus() == hWnd_ &&
                game_loop((double)(tick - lastTick) / frequency)) {

                BitBlt(dc_, 0, 0,
                    WINDOW_WIDTH,
                    WINDOW_HEIGHT, graphics_, 0, 0, SRCCOPY);

            }

            lastTick = tick;
        }
    }

    SelectObject(graphics_, oldHandle_);
    DeleteObject(bitmap_);
    DeleteDC(graphics_);

    return msg.wParam;
}

HRESULT SimWindow::create() {
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_VREDRAW | CS_HREDRAW;
    wcex.lpfnWndProc = (WNDPROC)WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = instance_;
    wcex.hIcon = LoadIcon(instance_, (LPCTSTR)IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = NULL;
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = L"Skeleton";
    wcex.hIconSm = NULL;

    ::RegisterClassEx(&wcex);

    int window_width = WINDOW_WIDTH;
    int window_height = WINDOW_HEIGHT;

    RECT winSz = { 0, 0, window_width, window_height };
    AdjustWindowRect(&winSz, WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME, false);

    hWnd_ = ::CreateWindowEx(0, L"Skeleton", L"Window",
        WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME ^ WS_MAXIMIZEBOX ^ WS_MINIMIZEBOX,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        winSz.right - winSz.left,
        winSz.bottom - winSz.top,
        NULL, NULL, instance_, NULL);

    if (!hWnd_) return false;

    dc_ = ::GetDC(hWnd_);

    graphics_ = CreateCompatibleDC(dc_);
    bitmap_ = CreateCompatibleBitmap(dc_, WINDOW_WIDTH, WINDOW_HEIGHT);
    oldHandle_ = SelectObject(graphics_, bitmap_);

    ShowWindow(hWnd_, SW_SHOW);
    UpdateWindow(hWnd_);

    return true;
}

LRESULT SimWindow::msg_proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    if (!hWnd_)
        hWnd_ = hWnd;

    switch (uMsg) {
    case WM_DESTROY:
        exit(0);
        break;
    default:
        return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
    return 0;
}

bool SimWindow::game_loop(double delta) {
    engine_->tick(delta);
    if (engine_->update()) {
        for (int i = 0; i < engine_->buffer_size(); i++) {
            Color pixel = engine_->buffer()[i];
            SetPixel(graphics_, i % ENGINE_WIDTH, i / ENGINE_WIDTH,
                ((pixel.dat & 0xff0000) >> 16) | (pixel.dat & 0x00ff00) | 
                ((pixel.dat & 0x0000ff) << 16));
        }
        return true;
    }

    if (GetAsyncKeyState(VK_ESCAPE) &&
        !GetAsyncKeyState(VK_LSHIFT) &&
        !GetAsyncKeyState(VK_LCONTROL)) {
        exit(0);
    }

    return false;
}
