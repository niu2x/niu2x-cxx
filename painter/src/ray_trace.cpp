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
: camera_(16 / 9.0, 20, 0.6, 10)
, samples_per_pixel_(500)
, max_depth_(50)
{

    auto ground_material
        = make_shared<ray_trace::Lambertian>(Vec3(0.5, 0.5, 0.5));
    hittable_objects_.insert(
        make_shared<Sphere>(Vec3(0, -1000, 0), 1000, ground_material));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = math::random<double>();
            Vec3 center(a + 0.9 * math::random<double>(), 0.2,
                b + 0.9 * math::random<double>());

            if (length(center - Vec3(4, 0.2, 0)) > 0.9) {
                SharedPtr<ray_trace::Material> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo
                        = math::random<Vec3>(Vec3(0, 0, 0), Vec3(1, 1, 1))
                        * math::random<Vec3>(Vec3(0, 0, 0), Vec3(1, 1, 1));
                    sphere_material
                        = make_shared<ray_trace::Lambertian>(albedo);
                    hittable_objects_.insert(
                        make_shared<Sphere>(center, 0.2, sphere_material));
                } else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = math::random<Vec3>(
                        Vec3(0.5, 0.5, 0.5), Vec3(1, 1, 1));
                    auto fuzz = math::random<double>(0, 0.5);
                    sphere_material
                        = make_shared<ray_trace::Metal>(albedo, fuzz);
                    hittable_objects_.insert(
                        make_shared<Sphere>(center, 0.2, sphere_material));
                } else {
                    // glass
                    sphere_material = make_shared<ray_trace::Dielectric>(1.5);
                    hittable_objects_.insert(
                        make_shared<Sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1 = make_shared<ray_trace::Dielectric>(1.5);
    hittable_objects_.insert(
        make_shared<Sphere>(Vec3(0, 1, 0), 1.0, material1));

    auto material2 = make_shared<ray_trace::Lambertian>(Vec3(0.4, 0.2, 0.1));
    hittable_objects_.insert(
        make_shared<Sphere>(Vec3(-4, 1, 0), 1.0, material2));

    auto material3 = make_shared<ray_trace::Metal>(Vec3(0.7, 0.6, 0.5), 0.0);
    hittable_objects_.insert(
        make_shared<Sphere>(Vec3(4, 1, 0), 1.0, material3));

    camera_.look_at(Vec3(13, 2, 3), Vec3(0, 0, 0), Vec3(0, 1, 0));
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

    double total = image_size.height * image_size.width;
    double current = 0;

    for (int row = 0; row < image_size.height; row++) {
        current += image_size.width;
        for (int col = 0; col < image_size.width; col++) {

            double pixel_x = col + 0.5;
            double pixel_y = row + 0.5;

            Vec3 color;

            for (int n = 0; n < samples_per_pixel_; n++) {

                Vec2 defocus_unit = ray_trace::random_unit_vec2()
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
        printf("progress: %.2lf%%\n", current / total * 100);
    }
}

} // namespace niu2x::painter
