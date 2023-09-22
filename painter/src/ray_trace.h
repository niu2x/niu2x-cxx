#include <niu2x/painter.h>
#include <niu2x/math.h>

namespace niu2x::painter {

using Vec3 = math::Vec3;

class RayTracePainter : public Painter {
public:
    struct Camera {
        DoubleSize size;
        Vec3 pos;
        Vec3 look;
        Vec3 up;
        double focal_length;
    };

    RayTracePainter();
    virtual ~RayTracePainter();

    virtual void paint(Image* image) override;

private:
    Camera camera_;
};

} // namespace niu2x::painter