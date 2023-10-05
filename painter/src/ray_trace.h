#ifndef NIU2X_PAINTER_RAY_TRACE_H
#define NIU2X_PAINTER_RAY_TRACE_H

#include <niu2x/painter.h>
#include <niu2x/math.h>
#include "ray_trace/sphere.h"
#include "ray_trace/math.h"

namespace niu2x::painter {

using math::DoubleSize;
using math::Ray;
using math::Vec2;
using math::Vec3;

class RayTracePainter : public Painter {
public:
    using Sphere = ray_trace::Sphere;
    struct Camera {
        Camera(double aspect_ratio, double fov, double defocus_angle,
            double focus_dist)
        : size({
            aspect_ratio,
            1.0,
        })
        , focal_length(size.height / 2 / tan(math::deg2rad(fov / 2)))
        , defocus_radius(focus_dist * tan(math::deg2rad(defocus_angle / 2)))
        {
            double scale = focus_dist / focal_length;
            focal_length = focus_dist;

            size.width *= scale;
            size.height *= scale;
        }

        DoubleSize size;
        double focal_length;
        double defocus_radius;

        void look_at(const Vec3& p_pos, const Vec3& target, const Vec3& p_up)
        {
            this->pos = p_pos;
            this->look = normalize(target - p_pos);
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
    ray_trace::HittableGroup hittable_objects_;
    int samples_per_pixel_;
    int max_depth_;

    Vec3 ray_color(const Ray& ray, int depth);
};

} // namespace niu2x::painter

#endif