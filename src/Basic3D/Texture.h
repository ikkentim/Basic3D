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

#pragma once

#include "Color.h"

struct Texture {
    const Color * dat;
    int width;
    int height;
    Texture(const Color * d, int w, int h) : dat(d), width(w), height(h) {

    }

    Color map(float tu, float tv)
    {
        int u = abs((int)(tu*width) % width);
        int v = abs((int)(tv*height) % height);
        return dat[u + v * width];
    }
};