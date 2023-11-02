#ifndef NIU2X_GFX_VERTEX_BUFFER_H
#define NIU2X_GFX_VERTEX_BUFFER_H

#include <niu2x/noncopyable.h>
#include <niu2x/type/convention.h>
#include <niu2x/type/stream.h>
#include <niu2x/gfx/vertex.h>
#include <niu2x/math/geometry.h>
#include <niu2x/stream/data.h>
#include <niu2x/math/linalg_alias.h>

namespace niu2x::gfx {

using Mat4 = math::Mat<float, 4, 4>;

class VertexBuffer {
public:
    virtual ~VertexBuffer() = 0;

    virtual void resize(NR vertex_count) = 0;

    virtual void set_vertexs(NR offset, NR count, const Vertex*) = 0;

    inline void set_vertex(Index index, const Vertex& vertex)
    {
        set_vertexs(index, 1, &vertex);
    }

    virtual NR size() const = 0;

    virtual void bind() = 0;
};

enum class RenderProgramID {
    COLOR,
    TEXTURE_COLOR,
};

class RenderProgram {
public:
    enum class Stage {
        VERTEX,
        FRAGMENT,
    };

    enum class Uniform {
        UNKNOWN,
        TEX_0,
        MODEL,
        VIEW,
        PROJECTION,
    };

    using UniformPacket = HashMap<Uniform, Variant<int, Mat4>>;

    struct Options {
        HashMap<Stage, String> source_code;
    };

    virtual ~RenderProgram() = 0;
    virtual void bind() = 0;
    virtual void set_uniform_integer(Uniform uniform, int n) = 0;
    virtual void set_uniform_mat4(Uniform uniform, const Mat4& m) = 0;
    void set_uniforms(const UniformPacket&);
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