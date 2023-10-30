#ifndef NIU2X_GFX_VERTEX_H
#define NIU2X_GFX_VERTEX_H

namespace niu2x::gfx {

struct Vertex {
    float x, y, z;
    float r, g, b, a;
    float u, v;
};

} // namespace niu2x::gfx

#endif