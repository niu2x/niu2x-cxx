#ifndef NIU2X_GFX_VERTEX_BUFFER_H
#define NIU2X_GFX_VERTEX_BUFFER_H

#include <niu2x/noncopyable.h>
#include <niu2x/type/convention.h>
#include <niu2x/type/stream.h>
#include <niu2x/gfx/vertex.h>
#include <niu2x/math/geometry.h>
#include <niu2x/stream/data.h>

namespace niu2x::gfx {

class VertexBuffer {
public:
    virtual ~VertexBuffer() = 0;

    virtual void resize(NR vertex_count) = 0;

    virtual void set_vertexs(NR offset, NR count, const Vertex*) = 0;

    inline void set_vertex(Index index, const Vertex& vertex)
    {
        set_vertexs(index, 1, &vertex);
    }

    virtual void bind() = 0;
};

enum class RenderProgramID {
    COLOR,
};

class RenderProgram {
public:
    enum class Stage {
        VERTEX,
        FRAGMENT,
    };

    struct Options {
        HashMap<Stage, String> source_code;
    };

    virtual ~RenderProgram() = 0;
    virtual void bind() = 0;
};

enum class PixelFormat {
    RGBA_8888,
    RGB_888,
    R8,
};

using DataIn = stream::DataIn;
using IntSize = math::IntSize;
using IntRect = math::IntRect;

class Texture2D {
public:
    virtual ~Texture2D() = 0;
    virtual void resize(IntSize size, PixelFormat format) = 0;
    virtual void bind(Index slot) = 0;
    virtual void set_data(const IntRect& region, const void* pixel_data) = 0;
    void load(ReadStream* in, PixelFormat format);
};

} // namespace niu2x::gfx

#endif