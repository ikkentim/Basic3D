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

#include "math3d.h"

Vector3 vector_up() {
    return Vector3(0, 1, 0);
}

Matrix4 matrix_look_at(Vector3 position, Vector3 target, Vector3 up) {
    Vector3 vector = (position - target).normalized();
    Vector3 vector2 = up.cross(vector).normalized();
    Vector3 vector3 = vector.cross(vector2);

    return
    {
        vector2.x, vector3.x, vector.x, 0.0f,
        vector2.y, vector3.y, vector.y, 0.0f,
        vector2.z, vector3.z, vector.z, 0.0f,
        -vector2.dot(position), -vector3.dot(position),
        -vector.dot(position), 1.0f
    };
}

Matrix4 matrix_perspective(float fieldOfView, float aspectRatio, float nearPlaneDistance, float farPlaneDistance) {
    Matrix4 result;
    if ((fieldOfView <= 0) || (fieldOfView >= PI) ||
        nearPlaneDistance <= 0 || farPlaneDistance <= 0 ||
        nearPlaneDistance >= farPlaneDistance) {
        return Matrix4();
    }
    float num = 1.0f / (tanf((fieldOfView * 0.5f)));
    float num9 = num / aspectRatio;
    result.m11 = num9;
    result.m12 = result.m13 = result.m14 = 0;
    result.m22 = num;
    result.m21 = result.m23 = result.m24 = 0;
    result.m31 = result.m32 = 0.0f;
    result.m33 = farPlaneDistance / (nearPlaneDistance - farPlaneDistance);
    result.m34 = -1;
    result.m41 = result.m42 = result.m44 = 0;
    result.m43 = (nearPlaneDistance * farPlaneDistance) / (nearPlaneDistance - farPlaneDistance);

    return result;
}

Matrix4 matrix_scale(float x, float y, float z) {
    return
    {
        x, 0, 0, 0,
        0, y, 0, 0,
        0, 0, z, 0,
        0, 0, 0, 1
    };
}
Matrix4 matrix_translation(float x, float y, float z) {
    return
    {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        x, y, z, 1
    };
}

Matrix4 matrix_rotation_y(float radians) {
    Matrix4 result;

    float val1 = cosf(radians);
    float val2 = sinf(radians);

    result.m11 = val1;
    result.m13 = -val2;
    result.m31 = val2;
    result.m33 = val1;

    return result;
}
Matrix4 matrix_rotation_z(float radians) {
    Matrix4 result;

    float val1 = cosf(radians);
    float val2 = sinf(radians);

    result.m11 = val1;
    result.m12 = val2;
    result.m21 = -val2;
    result.m22 = val1;

    return result;
}
Matrix4 matrix_rotation_x(float radians) {
    Matrix4 result;

    float val1 = cosf(radians);
    float val2 = sinf(radians);

    result.m22 = val1;
    result.m23 = val2;
    result.m32 = -val2;
    result.m33 = val1;

    return result;
}

float clamp(float value, float min, float max) {
    return value < min ? min : (value > max ? max : value);
}

float interpolate(float min, float max, float gradient) {
    return min + (max - min) * clamp(gradient);
}

float lineside2d(Vector3 point, Vector3 from, Vector3 to) {
    return Vector2(point.x - from.x, point.y - from.y)
        .cross(Vector2(to.x - from.x, to.y - from.y));
}

Vertex project(Vertex vertex, Matrix4 matrix) {
    Vector3 point2d = vertex.coordinates.transform(matrix);
    return{ Vector3(point2d.x + ENGINE_WIDTH / 2.0f, point2d.y + ENGINE_HEIGHT / 2.0f, point2d.z),
        vertex.texture_coordinates };
}