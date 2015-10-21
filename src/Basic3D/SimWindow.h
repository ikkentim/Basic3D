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

#include <windows.h>
#include "Engine.h"

#pragma once

class SimWindow {
public:
    SimWindow(Engine *engine);
    HRESULT create();
    int run();
    LRESULT msg_proc(HWND, UINT, WPARAM, LPARAM);
private:
    bool game_loop(double);
    static HINSTANCE instance_;
    HWND  hWnd_;
    HDC graphics_;
    HDC dc_;
    HBITMAP bitmap_;
    HANDLE oldHandle_;
    Engine *engine_;
};