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

#define ENGINE_WIDTH    (160)
#define ENGINE_HEIGHT   (128)

class Engine {
public:
    Engine();
    void tick(double timeElapsed);
    bool update();
    const Color * buffer();
    const inline int buffer_size();
protected:
    virtual void engine_update() = 0;
    virtual void engine_render() = 0;
    void buffer_clear();
    void buffer_set_color(Color color);
    void buffer_set(int x, int y, float depth, Color color);
    bool buffer_check(int x, int y, float depth);
private:
    Color buffer_[ENGINE_WIDTH * ENGINE_HEIGHT];
    float depthBuffer_[ENGINE_WIDTH * ENGINE_HEIGHT];
    Color dBuffer_[ENGINE_WIDTH * ENGINE_HEIGHT];
    float dDepthBuffer_[ENGINE_WIDTH * ENGINE_HEIGHT];
    
    bool awaitRender_ = false;
    bool awaitUpdate_ = false;
    double timeSinceRender_ = 0;
    double timeSinceUpdate_ = 0;
};