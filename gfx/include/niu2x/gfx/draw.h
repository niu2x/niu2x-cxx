#ifndef NIU2X_GFX_DRAW_H
#define NIU2X_GFX_DRAW_H

#include <niu2x/singleton.h>
#include <niu2x/type/std_alias.h>
#include <niu2x/gfx/hardward_resource.h>

namespace niu2x::gfx {

struct Draw {
    static void draw_arrays(Index index, NR count);
    static void draw_elements(Index index, NR count);

    static void clear();
};

} // namespace niu2x::gfx

#endif