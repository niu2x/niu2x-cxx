#include <niu2x/painter/ray_trace/painter.h>

namespace niu2x::painter::ray_trace {

using math::random;
using math::random_unit_vec2;
using math::to_color;

static inline Vec3 linear_to_gamma(const Vec3& c)
{
    return Vec3(sqrt(c[0]), sqrt(c[1]), sqrt(c[2]));
}

Painter::Painter(int max_depth, int samples)
: max_depth_(max_depth)
, samples_per_pixel_(samples)
{
}

Painter::~Painter() { }

void Painter::paint(Image* image, const Camera* camera, const Hittable* obj)
{

    auto& eye = camera->eye();
    auto& camera_size = camera->size();
    auto& camera_side = camera->side();
    auto& camera_up = camera->up();
    Vec3 screen_center = eye + camera->look() * camera->focal_dist();
    auto& image_size = image->size();

    double task_total = image_size.height * image_size.width;
    double task_current = 0;
    double defocus_radius = camera->defocus_radius();

    for (int row = 0; row < image_size.height; row++) {
        task_current += image_size.width;
        for (int col = 0; col < image_size.width; col++) {

            double pixel_x = col + 0.5;
            double pixel_y = row + 0.5;

            Vec3 color;

            for (int n = 0; n < samples_per_pixel_; n++) {
                Vec2 defocus_v = random_unit_vec2();
                defocus_v *= random(0.0, defocus_radius);

                Vec3 defocus_eye = eye;
                defocus_eye += defocus_v.x * camera_side;
                defocus_eye += defocus_v.y * camera_up;

                double px = pixel_x + random(-0.5, 0.5);
                px /= image_size.width;
                px -= 0.5;

                double py = pixel_y + random(-0.5, 0.5);
                py /= image_size.height;
                py = 0.5 - py;

                px *= camera_size.width;
                py *= camera_size.height;
                auto pixel_pos = screen_center;
                pixel_pos += px * camera_side;
                pixel_pos += py * camera_up;

                auto ray_dir = normalize(pixel_pos - defocus_eye);
                auto ray = math::Ray(defocus_eye, ray_dir, random(0.0, 1.0));
                color += ray_color(ray, max_depth_, obj, camera);
            }

            color /= samples_per_pixel_;
            color = linear_to_gamma(color);
            image->set_pixel(row, col, to_color(color));
        }
        printf("progress: %.2lf%%\n", task_current / task_total * 100);
    }
}

Vec3 RayTracePainter::ray_color(
    const Ray& ray, int depth, const Hittable* obj, const Camera* camera)
{
    if (depth <= 0)
        return Vec3(0, 0, 0);

    auto hit = obj->hit(ray, math::Interval(0.001, math::infinity));
    if (hit) {
        auto& record = hit.value();
        Vec3 attenuation;
        Vec3 color_from_scatter { 0, 0, 0 };
        Ray scattered;
        if (record.material->scatter(ray, record, attenuation, scattered)) {
            color_from_scatter
                = attenuation * ray_color(scattered, depth - 1, obj, camera);
        }
        Vec3 color_from_emission
            = record.material->emitted(record.u, record.v, record.p);
        return color_from_emission + color_from_scatter;
    }
    return camera->background();
}

} // namespace niu2x::painter::ray_trace