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

#include "Vector2.h"
#include "Vector3.h"
#include "Face.h"

struct Vertex {
    Vector3 coordinates;
    Vector2 texture_coordinates;

    Vertex() {

    }

    Vertex(float x, float y, float z, float u,
        float v) {
        coordinates = { x, y, z };
        texture_coordinates = Vector2(u, v);
    }

    Vertex(Vector3 p, Vector2 t) {
        coordinates = p;
        texture_coordinates = t;
    }

    Vertex(Vector3 p) {
        coordinates = p;
    }
};