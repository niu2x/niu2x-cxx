#include "gl_render_program.h"
#include "glad/glad.h"
#include <niu2x/type/exception.h>

namespace niu2x::gfx {

class GL_Shader : private Noncopyable {
public:
    GL_Shader(GLuint shader_type, const char* source_code)
    {
        native_id_ = glCreateShader(shader_type);
        glShaderSource(native_id_, 1, &source_code, nullptr);
        glCompileShader(native_id_);

        GLint success;
        GLchar log[512];
        glGetShaderiv(native_id_, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(native_id_, 512, nullptr, log);
            glDeleteShader(native_id_);
            throw_runtime_err(log);
        }
    }

    ~GL_Shader() { glDeleteShader(native_id_); }

    inline GLuint native_id() const { return native_id_; }

private:
    GLuint native_id_;
};

GLuint GL_RenderProgram::current_binding_id_ = 0;

void GL_RenderProgram::bind()
{
    if (current_binding_id_ != native_id_) {
        current_binding_id_ = native_id_;

        glUseProgram(native_id_);
    }
}

using Uniform = RenderProgram::Uniform;

static Uniform uniform_from_str(const String& name)
{
    static const HashMap<String, Uniform> map {
        { "texture0", Uniform::TEX_0 },
        { "model", Uniform::MODEL },
        { "view", Uniform::VIEW },
        { "projection", Uniform::PROJECTION },
    };

    auto iter = map.find(name);
    if (iter != map.end()) {
        return iter->second;
    }

    return Uniform::UNKNOWN;
}

GL_RenderProgram::GL_RenderProgram(const Options& options)
{
    UniquePtr<GL_Shader> vertex_shader;
    UniquePtr<GL_Shader> fragment_shader;

    if (options.source_code.contains(Stage::VERTEX)) {
        const char* source = options.source_code.at(Stage::VERTEX).c_str();
        vertex_shader = make_unique<GL_Shader>(GL_VERTEX_SHADER, source);
    }

    if (options.source_code.contains(Stage::FRAGMENT)) {
        const char* source = options.source_code.at(Stage::FRAGMENT).c_str();
        fragment_shader = make_unique<GL_Shader>(GL_FRAGMENT_SHADER, source);
    }

    native_id_ = glCreateProgram();
    glAttachShader(native_id_, vertex_shader->native_id());
    glAttachShader(native_id_, fragment_shader->native_id());
    glLinkProgram(native_id_);

    GLint success;
    glGetProgramiv(native_id_, GL_LINK_STATUS, &success);
    if (!success) {
        GLchar log[512];
        glGetProgramInfoLog(native_id_, 512, NULL, log);
        glDeleteProgram(native_id_);
        throw_runtime_err(log);
    }

    GLint total = -1;
    glGetProgramiv(native_id_, GL_ACTIVE_UNIFORMS, &total);

    for (GLint i = 0; i < total; ++i) {
        GLint name_len = -1, num = -1;
        GLenum type = GL_ZERO;
        char name[100];
        glGetActiveUniform(native_id_, GLuint(i), sizeof(name) - 1, &name_len,
            &num, &type, name);
        name[name_len] = 0;

        auto uniform_key = uniform_from_str(name);
        if (uniform_key != Uniform::UNKNOWN) {
            GLuint location = glGetUniformLocation(native_id_, name);
            uniform_locations_[uniform_key] = location;
        }
    }
}

GL_RenderProgram::~GL_RenderProgram() { glDeleteProgram(native_id_); }

void GL_RenderProgram::set_uniform_integer(Uniform p_uniform, int n)
{
    auto loc = uniform_locations_[p_uniform];
    glUniform1i(loc, n);
}

void GL_RenderProgram::set_uniform_mat4(Uniform p_uniform, const Mat4& m)
{
    auto loc = uniform_locations_[p_uniform];
    glUniformMatrix4fv(loc, 1, GL_FALSE, reinterpret_cast<const float*>(&m));
}

} // namespace niu2x::gfx