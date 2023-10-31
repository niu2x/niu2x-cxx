#include <niu2x/gfx/resource_manager.h>
#include <niu2x/unused.h>

namespace niu2x::gfx {

ResourceManager::ResourceManager() { }

void ResourceManager::load_texture2d(const String& path, PixelFormat format)
{
    unused(path);
    unused(format);
}

} // namespace niu2x::gfx