#ifndef NIU2X_GFX_GUI_H
#define NIU2X_GFX_GUI_H

#include <niu2x/gfx/window.h>
#include <niu2x/gfx/hardward_resource.h>

#include <niu2x/gfx/gui/node.h>
#include <niu2x/gfx/gui/panel.h>
#include <niu2x/lua.h>

namespace niu2x::gfx::gui {

extern Mat4 ui_view_mat4;
extern Mat4 ui_projection_mat4;

void update_view_projection(IntSize window_size);
UniquePtr<Node> build_ui(lua::LuaEngine* lua);
} // namespace niu2x::gfx::gui

#endif
