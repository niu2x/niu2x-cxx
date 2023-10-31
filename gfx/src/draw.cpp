#include <niu2x/gfx/draw.h>
#include "glad/glad.h"

namespace niu2x::gfx {

void Draw::draw_triangles(Index index, NR count)
{
    glDrawArrays(GL_TRIANGLES, index, count);
}

void Draw::clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

} // namespace niu2x::gfx