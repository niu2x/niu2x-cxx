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

void GL_RenderProgram::bind() { glUseProgram(native_id_); }

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
}

GL_RenderProgram::~GL_RenderProgram() { glDeleteProgram(native_id_); }

} // namespace niu2x::gfx