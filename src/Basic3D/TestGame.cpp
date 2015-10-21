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

#include "TestGame.h"
#include "Mesh.h"
#include "math3d.h"
#include "algorithm.h"
#include "Texture.h"

Mesh cmesh(float x, float y, Texture * texture) {
    static Vertex * wallVertices = 0;
    static Face * wallFaces = 0;

    if (!wallVertices) {
        wallVertices = new Vertex[8];
        wallVertices[0] = { -1, -1,  1, 1, 0 };
        wallVertices[1] = { 1, -1,  1, 0, 0 };
        wallVertices[2] = { 1,  1,  1, 0, 1 };
        wallVertices[3] = { -1,  1,  1, 1, 1 };
        wallVertices[4] = { -1, -1, -1, 0, 0 };
        wallVertices[5] = { 1, -1, -1, 1, 0 };
        wallVertices[6] = { 1,  1, -1, 1, 1 };
        wallVertices[7] = { -1,  1, -1, 0, 1 };
    }
    if (!wallFaces) {
        wallFaces = new Face[8];
        wallFaces[0] = { 0,1,2 };
        wallFaces[1] = { 2,3,0 };

        wallFaces[2] = { 7,6,5 };
        wallFaces[3] = { 5,4,7 };

        wallFaces[4] = { 4,0,3 };
        wallFaces[5] = { 3,7,4 };

        wallFaces[6] = { 1,5,6 };
        wallFaces[7] = { 6,2,1 };
    }

    Mesh cMesh;
    cMesh.world = matrix_translation(x, 0, y);
    cMesh.texture = texture;
    cMesh.vertices = wallVertices;
    cMesh.faces = wallFaces;
    cMesh.face_count = 8;

    return cMesh;
}

TestGame::TestGame() {

    static const Color k[16 * 16] = {
      0xbc9862,0x9f844d,0x9f844d,0x9f844d,0x9f844d,0xbc9862,0xbc9862,0xb4905a,
      0x9f844d,0xbc9862,0xbc9862,0xbc9862,0xbc9862,0xbc9862,0xbc9862,0x9f844d,
      0xbc9862,0xbc9862,0xb4905a,0x735e39,0xb4905a,0xb4905a,0x9f844d,0x9f844d,
      0x9f844d,0x9f844d,0x9f844d,0xb4905a,0x9f844d,0xb4905a,0xbc9862,0x9f844d,
      0xbc9862,0xbc9862,0x9f844d,0x9f844d,0x9f844d,0x9f844d,0xb4905a,0xb4905a,
      0xbc9862,0xbc9862,0xbc9862,0xb4905a,0x735e39,0xbc9862,0xbc9862,0x9f844d,
      0x695433,0x695433,0x695433,0x735e39,0x735e39,0x735e39,0x735e39,0x735e39,
      0x735e39,0x735e39,0x695433,0x695433,0x695433,0x695433,0x735e39,0x735e39,
      0xbc9862,0x9f844d,0x9f844d,0x9f844d,0x9f844d,0xbc9862,0xbc9862,0x9f844d,
      0xbc9862,0x9f844d,0x9f844d,0x735e39,0xb4905a,0xb4905a,0xb4905a,0xbc9862,
      0x9f844d,0x9f844d,0x735e39,0xb4905a,0xb4905a,0xb4905a,0xbc9862,0x9f844d,
      0xb4905a,0xb4905a,0xb4905a,0xb4905a,0x9f844d,0x9f844d,0x9f844d,0x9f844d,
      0xbc9862,0xbc9862,0xbc9862,0xb4905a,0xbc9862,0xbc9862,0xbc9862,0x9f844d,
      0x9f844d,0x9f844d,0x735e39,0xbc9862,0xbc9862,0xbc9862,0xbc9862,0xbc9862,
      0x735e39,0x735e39,0x695433,0x695433,0x695433,0x695433,0x695433,0x735e39,
      0x735e39,0x735e39,0x695433,0x695433,0x695433,0x695433,0x735e39,0x735e39,
      0xbc9862,0xbc9862,0xbc9862,0xbc9862,0xbc9862,0x735e39,0x9f844d,0xbc9862,
      0xbc9862,0xb4905a,0xb4905a,0xb4905a,0xbc9862,0xbc9862,0xbc9862,0x9f844d,
      0x9f844d,0x9f844d,0x9f844d,0x9f844d,0x9f844d,0xbc9862,0xb4905a,0xb4905a,
      0x9f844d,0x9f844d,0x9f844d,0x735e39,0xbc9862,0x9f844d,0x9f844d,0x9f844d,
      0xbc9862,0xb4905a,0xb4905a,0xb4905a,0xbc9862,0xbc9862,0x9f844d,0x9f844d,
      0x9f844d,0x9f844d,0xb4905a,0xb4905a,0xb4905a,0xb4905a,0xb4905a,0x9f844d,
      0x735e39,0x695433,0x735e39,0x735e39,0x695433,0x695433,0x695433,0x735e39,
      0x735e39,0x735e39,0x735e39,0x735e39,0x695433,0x695433,0x695433,0x735e39,
      0xbc9862,0xbc9862,0xbc9862,0xbc9862,0xbc9862,0x9f844d,0xbc9862,0x9f844d,
      0x9f844d,0x9f844d,0x9f844d,0x9f844d,0xb4905a,0x735e39,0xbc9862,0xbc9862,
      0xb4905a,0x9f844d,0x735e39,0xbc9862,0xbc9862,0xbc9862,0xbc9862,0x9f844d,
      0xbc9862,0xb4905a,0xb4905a,0x9f844d,0x9f844d,0x9f844d,0x9f844d,0xb4905a,
      0xbc9862,0xbc9862,0x9f844d,0x9f844d,0x9f844d,0xbc9862,0xbc9862,0x9f844d,
      0xbc9862,0xbc9862,0x9f844d,0xb4905a,0xbc9862,0xbc9862,0xbc9862,0xbc9862,
      0x735e39,0x735e39,0x735e39,0x7c623e,0x695433,0x695433,0x7c623e,0x695433,
      0x735e39,0x735e39,0x735e39,0x695433,0x4c3d26,0x695433,0x695433,0x735e39 };

    static Texture t = Texture(k, 16, 16);

    meshes_[meshes_count_++] = cmesh(0, 0, &t);
    meshes_[meshes_count_++] = cmesh(0, 2, &t);
    meshes_[meshes_count_++] = cmesh(0, 4, &t);
    meshes_[meshes_count_++] = cmesh(0, 6, &t);
}

void TestGame::engine_update() {

}

void TestGame::scan_line(int y, Vertex * va, Vertex * vb, Vertex * vc, 
    Vertex * vd, Texture * texture) {
    float gradient1 = va->coordinates.y != vb->coordinates.y ?
        (y - va->coordinates.y) / (vb->coordinates.y - va->coordinates.y) : 1,
        gradient2 = vc->coordinates.y != vd->coordinates.y ?
        (y - vc->coordinates.y) / (vd->coordinates.y - vc->coordinates.y) : 1;

    int sx = (int)interpolate(va->coordinates.x, vb->coordinates.x, gradient1),
        ex = (int)interpolate(vc->coordinates.x, vd->coordinates.x, gradient2);

    float z1 = interpolate(va->coordinates.z, vb->coordinates.z, gradient1),
        z2 = interpolate(vc->coordinates.z, vd->coordinates.z, gradient2),

        su = interpolate(va->texture_coordinates.x, vb->texture_coordinates.x, 
            gradient1),
        eu = interpolate(vc->texture_coordinates.x, vd->texture_coordinates.x, 
            gradient2),

        sv = interpolate(va->texture_coordinates.y, vb->texture_coordinates.y, 
            gradient1),
        ev = interpolate(vc->texture_coordinates.y, vd->texture_coordinates.y, 
            gradient2);

    for (int x = sx; x < ex; x++) {
        float gradient = (float)(x - sx) / (ex - sx);
        float z = interpolate(z1, z2, gradient);

        if (!buffer_check(x, y, z)) continue;

        buffer_set(x, y, z, texture->map(
            interpolate(su, eu, gradient),
            interpolate(sv, ev, gradient)));
    }
}

void TestGame::draw_triangle(Vertex v1, Vertex v2, Vertex v3,
    Texture * texture) {
    if (v1.coordinates.y > v2.coordinates.y)
        swap(v1, v2);
    if (v2.coordinates.y > v3.coordinates.y)
        swap(v2, v3);
    if (v1.coordinates.y > v2.coordinates.y)
        swap(v1, v2);

    if (lineside2d(v2.coordinates, v1.coordinates, v3.coordinates) > 0) {
        for (int y = max((int)v1.coordinates.y, 0);
        y <= min((int)v3.coordinates.y, ENGINE_HEIGHT - 1); y++) {
            if (y < v2.coordinates.y)
                scan_line(y, &v1, &v3, &v1, &v2, texture);
            else
                scan_line(y, &v1, &v3, &v2, &v3, texture);
        }
    }
    else {
        for (int y = max((int)v1.coordinates.y, 0);
        y <= min((int)v3.coordinates.y, ENGINE_HEIGHT - 1); y++) {
            if (y < v2.coordinates.y)
                scan_line(y, &v1, &v2, &v1, &v3, texture);
            else
                scan_line(y, &v2, &v3, &v1, &v3, texture);
        }
    }
}

void TestGame::engine_render() {
    buffer_clear(0x353535);

    static float rot = 0;
    rot += PI / 80;
    if (rot > 4 * PI)
        rot -= 4 * PI;

    camera_.x = (float)sin(rot);
    camera_.y = -0.8f;
    camera_.z = (float)cos(rot);
    Matrix4 viewMatrix = matrix_look_at(camera_, Vector3(0, 0, 0), vector_up());
    Matrix4 projectionMatrix = matrix_perspective(0.05f, 
        ((float)ENGINE_WIDTH) / ENGINE_HEIGHT, 0.01f, 1.0f);

    for (int i = 0; i < meshes_count_; i++) {
        Matrix4 transform = meshes_[i].world * viewMatrix * projectionMatrix;

        for (int j = 0; j < meshes_[i].face_count; j++)
            draw_triangle(
                project(meshes_[i].vertices[meshes_[i].faces[j].a], transform),
                project(meshes_[i].vertices[meshes_[i].faces[j].b], transform),
                project(meshes_[i].vertices[meshes_[i].faces[j].c], transform),
                meshes_[i].texture);
    }
}