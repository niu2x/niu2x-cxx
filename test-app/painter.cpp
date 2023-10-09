#include <niu2x/painter.h>
#include <niu2x/fs.h>
#include <niu2x/stream.h>
#include <niu2x/image.h>
#include <niu2x/math.h>

using namespace niu2x;

int main()
{
    using Vec3 = math::Vec3;

    image::Image canvas;
    canvas.reset(400, 225, Color::WHITE);

    painter::RayTraceCamera::Options camera_options
        = { .aspect_ratio = 16 / 9.0,
              .fov = 20,
              .focus_dist = 10,
              .defocus_angle = 0.6 };
    painter::RayTraceCamera camera(camera_options);

    painter::RayTraceObjects objs;

    auto ground_material
        = make_shared<painter::RayTraceLambertian>(Vec3(0.5, 0.5, 0.5));
    objs.insert(make_shared<painter::RayTraceSphere>(
        Vec3(0, -1000, 0), 1000, ground_material));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = math::random<double>();
            Vec3 center(a + 0.9 * math::random<double>(), 0.2,
                b + 0.9 * math::random<double>());

            if (length(center - Vec3(4, 0.2, 0)) > 0.9) {
                SharedPtr<painter::RayTraceMaterial> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo
                        = math::random<Vec3>(Vec3(0, 0, 0), Vec3(1, 1, 1))
                        * math::random<Vec3>(Vec3(0, 0, 0), Vec3(1, 1, 1));
                    sphere_material
                        = make_shared<painter::RayTraceLambertian>(albedo);
                    objs.insert(make_shared<painter::RayTraceSphere>(
                        center, 0.2, sphere_material));
                } else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = math::random<Vec3>(
                        Vec3(0.5, 0.5, 0.5), Vec3(1, 1, 1));
                    auto fuzz = math::random<double>(0, 0.5);
                    sphere_material
                        = make_shared<painter::RayTraceMetal>(albedo, fuzz);
                    auto center2 = center + Vec3(0, math::random(.0, .5), 0);
                    objs.insert(make_shared<painter::RayTraceSphere>(
                        center, center2, 0.2, sphere_material));
                } else {
                    // glass
                    sphere_material
                        = make_shared<painter::RayTraceDielectric>(1.5);
                    objs.insert(make_shared<painter::RayTraceSphere>(
                        center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1 = make_shared<painter::RayTraceDielectric>(1.5);
    objs.insert(
        make_shared<painter::RayTraceSphere>(Vec3(0, 1, 0), 1.0, material1));

    auto material2
        = make_shared<painter::RayTraceLambertian>(Vec3(0.4, 0.2, 0.1));
    objs.insert(
        make_shared<painter::RayTraceSphere>(Vec3(-4, 1, 0), 1.0, material2));

    auto material3
        = make_shared<painter::RayTraceMetal>(Vec3(0.7, 0.6, 0.5), 0.0);
    objs.insert(
        make_shared<painter::RayTraceSphere>(Vec3(4, 1, 0), 1.0, material3));

    camera.look(Vec3(13, 2, 3), Vec3(0, 0, 0), Vec3(0, 1, 0));

    painter::RayTracePainter painter(50, 100);
    painter.paint(&canvas, &camera, &objs);

    fs::File canvas_file("test.png");
    stream::FileWriteStream canvas_file_writer(canvas_file);
    canvas.store_to(&canvas_file_writer);

    return 0;
}