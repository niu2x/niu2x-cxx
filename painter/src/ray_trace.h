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

        void look_at(const Vec3& p_pos, const Vec3& p_look, const Vec3& p_up)
        {
            this->pos = p_pos;
            this->look = normalize(p_look);
            this->side = normalize(cross(this->look, p_up));
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
    int samples_per_pixel_;
    int max_depth_;

    Vec3 ray_color(const Ray& ray, int depth);
};

} // namespace niu2x::painter