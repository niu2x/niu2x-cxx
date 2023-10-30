#ifndef NIU2X_GFX_GFX_FACTORY_H
#define NIU2X_GFX_GFX_FACTORY_H

#include <niu2x/singleton.h>
#include <niu2x/type/std_alias.h>
#include <niu2x/gfx/hardward_resource.h>

namespace niu2x::gfx {

class GFX_Factory : public Singleton<GFX_Factory> {
public:
    UniquePtr<VertexBuffer> create_vertex_buffer();
    UniquePtr<RenderProgram> create_render_program();
};

} // namespace niu2x::gfx

#endif