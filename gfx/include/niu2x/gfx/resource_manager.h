#ifndef NIU2X_GFX_RESOURCE_MANAGER_H
#define NIU2X_GFX_RESOURCE_MANAGER_H

#include <niu2x/singleton.h>
#include <niu2x/gfx/hardward_resource.h>
#include <niu2x/fs/path.h>

namespace niu2x::gfx {

using Path = fs::Path;

class ResourceManager : public Singleton<ResourceManager> {
public:
    using ResId = String;
    ResourceManager();

    void load_texture2d(const Path& path);
    void load_texture2d(const ResId& id, const Path& path, PixelFormat format);

    inline Texture2D* get_texture2d(const ResId& id) const
    {
        return texture2ds_.at(id).get();
    }

    void clear();

private:
    HashMap<ResId, UniquePtr<Texture2D>> texture2ds_;
};

} // namespace niu2x::gfx

#endif