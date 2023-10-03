#include "ray_trace.h"
#include "ray_trace/lambertian.h"

namespace niu2x::painter {

using math::Interval;
using math::random;
using math::to_color;

RayTracePainter::RayTracePainter()
: camera_({ 4, 3 }, 4)
, samples_per_pixel_(16)
, max_depth_(4)
{
    auto lambertian = make_shared<ray_trace::Lambertian>(Vec3(0.1, 0.1, 0.3));

    hittable_objects_.insert(make_shared<Sphere>(Vec3(0, 8, 1), 1, lambertian));
    hittable_objects_.insert(
        make_shared<Sphere>(Vec3(0, 8, -40), 40, lambertian));
    camera_.look_at(Vec3(0, 0, 2), Vec3(0, 1, -0.2), Vec3(0, 0, 1));
}

RayTracePainter::~RayTracePainter() { }

static inline Vec3 linear_to_gamma(const Vec3& c)
{
    return Vec3(sqrt(c[0]), sqrt(c[1]), sqrt(c[2]));
}

Vec3 RayTracePainter::ray_color(const Ray& ray, int depth)
{
    if (depth <= 0)
        return Vec3(0, 0, 0);
    auto hit
        = hittable_objects_.hit(ray, math::Interval(0.001, math::infinity));
    if (hit) {
        auto& record = hit.value();
        Vec3 attenuation;
        Ray scattered;
        if (record.material->scatter(ray, record, attenuation, scattered)) {
            return attenuation * ray_color(scattered, depth - 1);
        }
    }
    auto a = 0.5 * (ray.direction().y + 1.0);
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
            color = linear_to_gamma(color);
            image->set_pixel(row, col, to_color(color));
        }
    }
}

} // namespace niu2x::painter
