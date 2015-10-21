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

#include <math.h>
#include "Matrix4.h"

struct Vector3 {
    float x;
    float y;
    float z;

    Vector3() : x(0), y(0), z(0) {

    }

    Vector3(float xx, float yy, float zz) : x(xx), y(yy), z(zz) {

    }

    inline void zero() {
        x = 0;
        y = 0;
        z = 0;
    }

    inline bool is_zero() const {
        return x == 0 && y == 0 && z == 0;
    }

    inline float length() {
        return (float)sqrt(length_sq());
    }

    inline float length_sq() {
        return x * x + y * y + z * z;
    }

    inline void normalize() {
        float len = length();
        x /= len;
        y /= len;
        z /= len;
    }

    inline Vector3 normalized() {
        Vector3 r = *this;
        r.normalize();
        return r;
    }

    inline float dot(const Vector3 &v3) const {
        return x*v3.x + y*v3.y + z * v3.z;
    }

    inline Vector3 cross(const Vector3 &v3) const {
        auto xx = y * v3.z - v3.y * z;
        auto yy = -(x * v3.z - v3.x * z);
        auto zz = x * v3.y - v3.x * y;
        return Vector3(xx, yy, zz);
    }

    inline Vector3 transform(Matrix4 matrix) const {
        float xx = (x * matrix.m11) + (y * matrix.m21) + (z * matrix.m31) + matrix.m41;
        float yy = (x * matrix.m12) + (y * matrix.m22) + (z * matrix.m32) + matrix.m42;
        float zz = (x * matrix.m13) + (y * matrix.m23) + (z * matrix.m33) + matrix.m43;
        return Vector3(xx, yy, zz);
    }

    inline Vector3 operator=(Vector3 a) {
        x = a.x;
        y = a.y;
        z = a.z;
        return a;
    }

    inline Vector3 operator+(Vector3 a) {
        return Vector3(x + a.x, y + a.y, z + a.z);
    }

    inline Vector3 operator-(Vector3 a) {
        return Vector3(x - a.x, y - a.y, z - a.z);
    }

    inline Vector3 operator/(float scalar) {
        return Vector3(x / scalar, y / scalar, z / scalar);
    }

    inline bool operator==(Vector3 a) {
        return a.x == x && a.y == y && a.z == z;
    }

    inline bool operator!=(Vector3 a) {
        return a.x != x || a.y != y || a.z != z;
    }
};
