#ifndef NIU2X_GFX_RESOURCE_MANAGER_H
#define NIU2X_GFX_RESOURCE_MANAGER_H

#include <niu2x/gfx/hardward_resource.h>

namespace niu2x::gfx {

class ResourceManager {
public:
    using ResId = String;
    ResourceManager();
    void load_texture2d(const String& path, PixelFormat format);
    // Texture2D* get<Texture2D>();

private:
    HashMap<ResId, UniquePtr<Texture2D>> texture2ds_;
};

} // namespace niu2x::gfx

#endif