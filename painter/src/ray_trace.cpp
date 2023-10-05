#include "ray_trace.h"
#include "ray_trace/lambertian.h"
#include "ray_trace/metal.h"
#include "ray_trace/dielectric.h"
#include "ray_trace/math.h"

namespace niu2x::painter {

using math::Interval;
using math::random;
using math::to_color;

RayTracePainter::RayTracePainter()
: camera_(16 / 9.0, 20, 10, 3.4)
, samples_per_pixel_(100)
, max_depth_(50)
{
    auto material_ground
        = make_shared<ray_trace::Lambertian>(Vec3(0.8, 0.8, 0.0));
    auto material_center
        = make_shared<ray_trace::Lambertian>(Vec3(0.1, 0.2, 0.5));
    auto material_left = make_shared<ray_trace::Dielectric>(1.5);
    auto material_right
        = make_shared<ray_trace::Metal>(Vec3(0.8, 0.6, 0.2), 1.0);

    hittable_objects_.insert(
        make_shared<Sphere>(Vec3(0.0, -100.5, -1.0), 100.0, material_ground));
    hittable_objects_.insert(
        make_shared<Sphere>(Vec3(0.0, 0.0, -1.0), 0.5, material_center));
    hittable_objects_.insert(
        make_shared<Sphere>(Vec3(-1.0, 0.0, -1.0), 0.5, material_left));
    hittable_objects_.insert(
        make_shared<Sphere>(Vec3(1.0, 0.0, -1.0), 0.5, material_right));
    hittable_objects_.insert(
        make_shared<Sphere>(Vec3(-1.0, 0.0, -1.0), -0.4, material_left));

    camera_.look_at(Vec3(-2, 2, 1), Vec3(0, 0, -1), Vec3(0, 1, 0));
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
        return Vec3(0, 0, 0);
    }
    auto a = 0.5 * (ray.direction().z + 1.0);
    return Vec3(1.0, 1.0, 1.0) * (1.0 - a) + Vec3(0.4, 0.4, 1.0) * a;
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

                Vec2 defocus_unit
                    // = ray_trace::random_unit_vec2() * camera_.defocus_radius;
                    = ray_trace::random_unit_vec2()
                    * math::random<double>(0, camera_.defocus_radius);
                Vec3 defocus_ray_origin = ray_origin
                    + defocus_unit.x * camera_.side
                    + defocus_unit.y * camera_.up;

                double px
                    = (pixel_x + random(-0.5, 0.5)) / image_size.width - 0.5;
                double py
                    = 0.5 - (pixel_y + random(-0.5, 0.5)) / image_size.height;

                px *= camera_.size.width;
                py *= camera_.size.height;
                auto pixel_pos
                    = screen_center + px * camera_.side + py * camera_.up;

                auto ray_dir = normalize(pixel_pos - defocus_ray_origin);
                auto ray = math::Ray(defocus_ray_origin, ray_dir);
                color += ray_color(ray, max_depth_);
            }

            color /= samples_per_pixel_;
            color = linear_to_gamma(color);
            image->set_pixel(row, col, to_color(color));
        }
    }
}

} // namespace niu2x::painter
