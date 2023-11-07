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
using Vec3 = math::Vec<float, 3>;

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

class IndexBuffer {
public:
    virtual ~IndexBuffer() = 0;

    virtual void resize(NR index_count) = 0;

    virtual void set(NR offset, NR count, const uint16_t*) = 0;

    inline void set(Index index, uint16_t i) { set(index, 1, &i); }

    virtual NR size() const = 0;

    virtual void bind() = 0;
};

enum class RenderProgramID {
    COLOR,
    TEXTURE_COLOR,
};

struct Color {
    float r, g, b, a;
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
        MASK_COLOR,
    };

    using UniformPacket
        = HashMap<Uniform, Variant<int, Mat4, Color, Array<float, 4>>>;

    struct Options {
        HashMap<Stage, String> source_code;
    };

    virtual ~RenderProgram() = 0;
    virtual void bind() = 0;
    virtual void set_uniform_integer(Uniform uniform, int n) = 0;
    virtual void set_uniform_mat4(Uniform uniform, const Mat4& m) = 0;
    virtual void set_uniform_4f(Uniform uniform, const float* array) = 0;

    void set_uniforms(const UniformPacket&);
};

enum class PixelFormat {
    RGBA_8888,
    RGB_888,
    R8,
};

using PixelFmt = PixelFormat;

using IntSize = math::IntSize;
using IntRect = math::IntRect;

class Texture2D {
public:
    virtual ~Texture2D() = 0;
    virtual void resize(IntSize size, PixelFormat format) = 0;
    virtual void bind(Index slot) = 0;
    virtual void set_data(const IntRect& region, const void* pixel_data) = 0;
    virtual IntSize size() const = 0;
    void load(ReadStream* in, PixelFormat format);
};

} // namespace niu2x::gfx

#endif