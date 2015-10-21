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

struct Color {
    int dat;
    Color() :
        dat(0)
    {
    }

    Color(const int&d) :
        dat(d)
    {
    }

    Color operator*(float scalar) const {
        int r = (dat >> 16) & 0xff;
        int g = (dat >> 8) & 0xff;
        int b = (dat)& 0xff;

        r = (int)(r * scalar);
        g = (int)(g * scalar);
        b = (int)(b * scalar);

        if (r > 0xff) r = 0xff;
        if (g > 0xff) g = 0xff;
        if (b > 0xff) b = 0xff;

        return (r << 16) | (g << 8) | b;
    }
};