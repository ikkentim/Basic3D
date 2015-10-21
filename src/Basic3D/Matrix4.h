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

struct Matrix4 {
    float m11, m12, m13, m14;
    float m21, m22, m23, m24;
    float m31, m32, m33, m34;
    float m41, m42, m43, m44;

    Matrix4() : Matrix4(
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
        ) {
    }

    Matrix4(float v11, float v12, float v13, float v14,
        float v21, float v22, float v23, float v24,
        float v31, float v32, float v33, float v34,
        float v41, float v42, float v43, float v44) :
        m11(v11), m12(v12), m13(v13), m14(v14),
        m21(v21), m22(v22), m23(v23), m24(v24),
        m31(v31), m32(v32), m33(v33), m34(v34),
        m41(v41), m42(v42), m43(v43), m44(v44) {
    }

    Matrix4 operator*(Matrix4 &b) {
        return
        {
            (m11 * b.m11) + (m12*b.m21) + (m13*b.m31) + (m14*b.m41),
            (m11 * b.m12) + (m12*b.m22) + (m13*b.m32) + (m14*b.m42),
            (m11 * b.m13) + (m12*b.m23) + (m13*b.m33) + (m14*b.m43),
            (m11 * b.m14) + (m12*b.m24) + (m13*b.m34) + (m14*b.m44),

            (m21 * b.m11) + (m22*b.m21) + (m23*b.m31) + (m24*b.m41),
            (m21 * b.m12) + (m22*b.m22) + (m23*b.m32) + (m24*b.m42),
            (m21 * b.m13) + (m22*b.m23) + (m23*b.m33) + (m24*b.m43),
            (m21 * b.m14) + (m22*b.m24) + (m23*b.m34) + (m24*b.m44),

            (m31 * b.m11) + (m32*b.m21) + (m33*b.m31) + (m34*b.m41),
            (m31 * b.m12) + (m32*b.m22) + (m33*b.m32) + (m34*b.m42),
            (m31 * b.m13) + (m32*b.m23) + (m33*b.m33) + (m34*b.m43),
            (m31 * b.m14) + (m32*b.m24) + (m33*b.m34) + (m34*b.m44),

            (m41 * b.m11) + (m42*b.m21) + (m43*b.m31) + (m44*b.m41),
            (m41 * b.m12) + (m42*b.m22) + (m43*b.m32) + (m44*b.m42),
            (m41 * b.m13) + (m42*b.m23) + (m43*b.m33) + (m44*b.m43),
            (m41 * b.m14) + (m42*b.m24) + (m43*b.m34) + (m44*b.m44)
        };
    }
};