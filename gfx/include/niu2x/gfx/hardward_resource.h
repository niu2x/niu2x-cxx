#ifndef NIU2X_GFX_VERTEX_BUFFER_H
#define NIU2X_GFX_VERTEX_BUFFER_H

#include <niu2x/noncopyable.h>
#include <niu2x/type/convention.h>
#include <niu2x/gfx/vertex.h>

namespace niu2x::gfx {

class VertexBuffer {
public:
    virtual ~VertexBuffer() = 0;
    virtual void resize(NR vertex_count) = 0;
    virtual void set_vertex(NR offset, NR count, const Vertex*) = 0;
};

class RenderProgram {
public:
    enum class Stage {
        VERTEX,
        FRAGMENT,
    };

    struct RenderProgramOptions {
        HashMap<Stage, String> source_code;
    };

    virtual ~RenderProgram() = 0;
};

} // namespace niu2x::gfx

#endif