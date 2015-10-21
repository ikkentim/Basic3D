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

#include "Vector3.h"
#include "Vertex.h"
#include "Engine.h"
#include "Matrix4.h"

#define PI (3.141593f)

float clamp(float value, float min = 0, float max = 1);
float interpolate(float min, float max, float gradient);

Vector3 vector_up();
float lineside2d(Vector3 point, Vector3 from, Vector3 to);

Matrix4 matrix_look_at(Vector3 position, Vector3 target, Vector3 up);
Matrix4 matrix_perspective(float fov, float aspectRatio, float near, float far);
Matrix4 matrix_scale(float x, float y, float z);
Matrix4 matrix_translation(float x, float y, float z);
Matrix4 matrix_rotation_x(float radians);
Matrix4 matrix_rotation_y(float radians);
Matrix4 matrix_rotation_z(float radians);

Vertex project(Vertex vertex, Matrix4 matrix);