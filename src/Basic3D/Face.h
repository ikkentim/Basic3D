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

struct Face {
    unsigned char a;
    unsigned char b;
    unsigned char c;

    Face() :
        a(0),
        b(0),
        c(0)
    {
    }

    Face(unsigned char aa, unsigned char bb, unsigned char cc) :
        a(aa),
        b(bb),
        c(cc)
    {
    }
};
