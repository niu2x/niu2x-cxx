#ifndef NIU2X_GFX_IMAGE_SHEET_H
#define NIU2X_GFX_IMAGE_SHEET_H

#include <niu2x/noncopyable.h>
#include <niu2x/type/std_alias.h>
#include <niu2x/fs/path.h>
#include <niu2x/gfx/hardward_resource.h>

namespace niu2x::gfx {

class ImageSheet {
public:
    class Frame {
    public:
        Frame(Texture2D* tex, const IntRect& region)
        : tex_(tex)
        , region_(region)
        {
        }

        Frame()
        : tex_(nullptr)
        {
        }

        Texture2D* texture() const { return tex_; }
        const IntRect& region() const { return region_; }

    private:
        Texture2D* tex_;
        IntRect region_;
    };

    ImageSheet();

    void add_page(UniquePtr<Texture2D> tex, CR<fs::Path>& sub_config);

    Frame* get_frame(const String& name) const
    {
        return const_cast<Frame*>(&frames_.at(name));
    }

private:
    Vector<UPtr<Texture2D>> textures_;
    HashMap<String, Frame> frames_;
};

} // namespace niu2x::gfx

#endif