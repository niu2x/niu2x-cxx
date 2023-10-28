#ifndef NIU2X_PAINTER_RAY_TRACE_PAINTER_H
#define NIU2X_PAINTER_RAY_TRACE_PAINTER_H

#include <niu2x/image.h>
#include <niu2x/painter/ray_trace/camera.h>
#include <niu2x/painter/ray_trace/hittable.h>

namespace niu2x::painter::ray_trace {

using image::Image;
using math::DoubleSize;
using math::Ray;
using math::Vec2;
using math::Vec3;

class Painter {
public:
    using Camera = niu2x::painter::ray_trace::Camera;

    Painter(int max_depth, int samples_per_pixel);
    ~Painter();
    void paint(Image* image, const Camera* camera, const Hittable* obj);

    void set_max_depth(int d) { max_depth_ = d; }
    void set_samples(int samples) { samples_per_pixel_ = samples; }

private:
    int max_depth_;
    int samples_per_pixel_;
    Vec3 ray_color(
        const Ray& ray, int depth, const Hittable* obj, const Camera* camera);
};

} // namespace niu2x::painter::ray_trace

namespace niu2x::painter {

using RayTracePainter = ray_trace::Painter;

};

#endif