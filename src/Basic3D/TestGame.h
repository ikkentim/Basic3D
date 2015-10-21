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

#include "Engine.h"
#include "Vector3.h"
#include "Mesh.h"

class TestGame : public Engine {
private:
    Mesh meshes_[64];
    int meshes_count_ = 0;
    Vector3 camera_;

public:
    TestGame();
    void engine_update() override;
    void engine_render() override;

private:
    void scan_line(int y, Vertex * va, Vertex * vb, Vertex * vc, Vertex * vd,
        Texture * texture);
    void draw_triangle(Vertex v1, Vertex v2, Vertex v3, Texture * texture);
};