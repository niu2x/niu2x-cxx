#include "ray_trace.h"

namespace niu2x::painter {

using math::Interval;
using math::random;
using math::to_color;

RayTracePainter::RayTracePainter()
: camera_({ 4, 3 }, 4)
, samples_per_pixel_(16)
, max_depth_(4)
{
    // for (int i = 0; i < 10; i++) {
    //     hittable_objects_.insert(make_shared<Sphere>(Vec3(i, 8, 4), 0.5));
    //     hittable_objects_.insert(make_shared<Sphere>(Vec3(i, 8, 1), 0.5));
    //     hittable_objects_.insert(make_shared<Sphere>(Vec3(i, 8, 2), 0.5));
    // }

    hittable_objects_.insert(make_shared<Sphere>(Vec3(0, 8, 1), 2));
    hittable_objects_.insert(make_shared<Sphere>(Vec3(0, 8, -40), 40));
    camera_.look_at(Vec3(0, 0, 0), Vec3(0, 1, -0.2), Vec3(0, 0, 1));
}

RayTracePainter::~RayTracePainter() { }

inline Vec3 random_on_hemisphere(const Vec3& normal)
{
    Vec3 on_unit_sphere = random<Vec3>();
    if (dot(on_unit_sphere, normal) > 0.0) {
        // In the same hemisphere as the normal
        return on_unit_sphere;
    } else
        return -on_unit_sphere;
}

Vec3 RayTracePainter::ray_color(const Ray& ray, int depth)
{
    if (depth <= 0)
        return Vec3(0, 0, 0);
    auto hit = hittable_objects_.hit(ray, math::Interval(0.1, math::infinity));
    if (hit) {
        Vec3 direction = random_on_hemisphere(hit.value().normal);
        return 0.5 * ray_color(Ray(hit.value().p, direction), depth);
    }
    auto a = 0.5 * (ray.direction().z + 1.0);
    return Vec3(1.0, 1.0, 1.0) * (1.0 - a) + Vec3(0.5, 0.7, 1.0) * a;
}

void RayTracePainter::paint(Image* image)
{
    auto ray_origin = camera_.pos;
    auto screen_center = ray_origin + camera_.look * camera_.focal_length;
    auto image_size = image->size();

    for (int row = 0; row < image_size.height; row++) {
        for (int col = 0; col < image_size.width; col++) {

            double pixel_x = col + 0.5;
            double pixel_y = row + 0.5;

            Vec3 color;

            for (int n = 0; n < samples_per_pixel_; n++) {

                double px
                    = (pixel_x + random(-0.5, 0.5)) / image_size.width - 0.5;
                double py
                    = 0.5 - (pixel_y + random(-0.5, 0.5)) / image_size.height;

                px *= camera_.size.width;
                py *= camera_.size.height;
                auto pixel_pos
                    = screen_center + px * camera_.side + py * camera_.up;

                auto ray_dir = normalize(pixel_pos - ray_origin);
                auto ray = math::Ray(ray_origin, ray_dir);
                color += ray_color(ray, max_depth_);
            }

            color /= samples_per_pixel_;
            image->set_pixel(row, col, to_color(color));
        }
    }
}

} // namespace niu2x::painter
