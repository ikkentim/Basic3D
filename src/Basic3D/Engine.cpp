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

#include "Engine.h"
#include <cstring>

#define RATE_RENDER     (24)
#define RATE_UPDATE     (30)

#define MAX_DEPTH       (9112383.0f)


Engine::Engine() {
    for (int i = 0; i < buffer_size(); i++) {
        depthBuffer_[i] = MAX_DEPTH;
        dDepthBuffer_[i] = MAX_DEPTH;
    }
}

//static int renders = 0;

void Engine::tick(double timeElapsed) {
    timeSinceRender_ += timeElapsed;
    timeSinceUpdate_ += timeElapsed;

    if (timeSinceRender_ > 1.0f / RATE_RENDER) {
        timeSinceRender_ -= 0;
        awaitRender_ = true;
    }

    // debugging / fps:
    //renders++;
    //awaitRender_ = true;
    //if (timeSinceRender_ > 1.0f) {
    //    renders = 0;
    //    timeSinceRender_ = 0;
    //}

    if (timeSinceUpdate_ > 1.0f / RATE_UPDATE) {
        timeSinceUpdate_ -= 0;
        awaitUpdate_ = true;
    }
}

bool Engine::update() {
    if (awaitUpdate_) {
        awaitUpdate_ = false;
        engine_update();
    }

    if (awaitRender_) {
        awaitRender_ = false;
        engine_render();
        return true;
    }

    return false;
}

const Color * Engine::buffer() {
    return buffer_;
}

const int Engine::buffer_size() {
    return ENGINE_WIDTH * ENGINE_HEIGHT;
}

void Engine::buffer_clear() {
    memcpy(buffer_, dBuffer_, buffer_size() * sizeof(Color));
    memcpy(depthBuffer_, dDepthBuffer_, buffer_size() * sizeof(float));
}

void Engine::buffer_set_color(Color color) {
    for (int i = 0; i < buffer_size(); i++)
        dBuffer_[i] = color;
}

bool Engine::buffer_check(int x, int y, float depth) {
    return !(x < 0 || y < 0 || x >= ENGINE_WIDTH || y >= ENGINE_HEIGHT) &&
        (depth < depthBuffer_[x + y * ENGINE_WIDTH]);
}

void Engine::buffer_set(int x, int y, float depth, Color color) {
    if (!buffer_check(x, y, depth)) return;

    buffer_[x + y * ENGINE_WIDTH] = color;
    depthBuffer_[x + y * ENGINE_WIDTH] = depth;
}