#include "rpsc_gl.h"

namespace niu2x::gfx::rpsc::gl {

const char* color_vertex = R"RAW(
#version 450 core

layout (location = 0) in vec3 in_position; // x, y, z
layout (location = 1) in vec4 in_color;    // r, g, b, a
layout (location = 2) in vec2 in_tex_coord; // u, v

out vec4 frag_color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec4 mask_color;

void main()
{
    gl_Position = projection * view * model * vec4(in_position, 1.0);
    frag_color = in_color * mask_color;
}

)RAW";
const char* color_fragment = R"RAW(
#version 450 core

in vec4 frag_color;
out vec4 color;

void main()
{
    color = frag_color;
}
)RAW";

const char* texture_color_vertex = R"RAW(
#version 450 core

layout (location = 0) in vec3 in_position; // x, y, z
layout (location = 1) in vec4 in_color;    // r, g, b, a
layout (location = 2) in vec2 in_tex_coord; // u, v

out vec4 frag_color;
out vec2 tex_coord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec4 mask_color;

void main()
{
    gl_Position = projection * view * model * vec4(in_position, 1.0);
    frag_color = in_color * mask_color;
    tex_coord = in_tex_coord;
}

)RAW";
const char* texture_color_fragment = R"RAW(
#version 450 core

in vec4 frag_color;
in vec2 tex_coord;

out vec4 color;

uniform sampler2D texture0;

void main()
{
    color = texture(texture0, tex_coord) * frag_color;
}
)RAW";

} // namespace niu2x::gfx::rpsc::gl