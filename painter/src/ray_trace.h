#include <niu2x/painter.h>
#include <niu2x/math.h>
#include "ray_trace/sphere.h"

namespace niu2x::painter {

using math::DoubleSize;
using math::Ray;
using math::Vec3;

class RayTracePainter : public Painter {
public:
    using Sphere = ray_trace::Sphere;
    struct Camera {
        Camera(const DoubleSize& size, double focal_length)
        : size(size)
        , focal_length(focal_length)
        {
        }

        const DoubleSize size;
        const double focal_length;

        void look_at(const Vec3& pos, const Vec3& look, const Vec3& up)
        {
            this->pos = pos;
            this->look = normalize(look);
            this->side = normalize(cross(this->look, up));
            this->up = cross(this->side, this->look);
        }

        Vec3 pos;
        Vec3 look;
        Vec3 up;
        Vec3 side;
    };

    RayTracePainter();
    virtual ~RayTracePainter();

    virtual void paint(Image* image) override;

private:
    Camera camera_;
    math::HittableGroup hittable_objects_;

    Color ray_color(const Ray& ray);
};

} // namespace niu2x::painter