#include <niu2x/painter.h>
#include <niu2x/fs.h>
#include <niu2x/stream.h>
#include <niu2x/image.h>
#include <niu2x/math.h>

using namespace niu2x;

static void random_sphere()
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

    auto checker = make_shared<painter::ray_trace::CheckerTexture>(0.32,
        math::to_color(Vec3(.2, .3, .1)), math::to_color(Vec3(.9, .9, .9)));

    auto ground_material = make_shared<painter::RayTraceLambertian>(checker);
    objs.insert(make_shared<painter::RayTraceSphere>(
        Vec3(0, -1000, 0), 1000, ground_material));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = math::random();
            Vec3 center(
                a + 0.9 * math::random(), 0.2, b + 0.9 * math::random());

            if (length(center - Vec3(4, 0.2, 0)) > 0.9) {
                SharedPtr<painter::RayTraceMaterial> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo
                        = math::random<Vec3>(Vec3(0, 0, 0), Vec3(1, 1, 1))
                        * math::random<Vec3>(Vec3(0, 0, 0), Vec3(1, 1, 1));
                    sphere_material
                        = make_shared<painter::RayTraceLambertian>(albedo);
                    auto center2 = center + Vec3(0, math::random(.0, .5), 0);
                    objs.insert(make_shared<painter::RayTraceSphere>(
                        center, center2, 0.2, sphere_material));
                } else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = math::random<Vec3>(
                        Vec3(0.5, 0.5, 0.5), Vec3(1, 1, 1));
                    auto fuzz = math::random(0.0, 0.5);
                    sphere_material
                        = make_shared<painter::RayTraceMetal>(albedo, fuzz);
                    objs.insert(make_shared<painter::RayTraceSphere>(
                        center, 0.2, sphere_material));
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

    painter::RayTraceBVH world(objs);

    camera.look(Vec3(13, 2, 3), Vec3(0, 0, 0), Vec3(0, 1, 0));

    painter::RayTracePainter painter(50, 100);
    painter.paint(&canvas, &camera, &world);
    // painter.paint(&canvas, &camera, &objs);

    fs::File canvas_file("test.png");
    stream::FileWriteStream canvas_file_writer(canvas_file);
    canvas.store_to(&canvas_file_writer);
}

static void two_spheres()
{

    using Vec3 = math::Vec3;

    image::Image canvas;
    canvas.reset(400, 225, Color::WHITE);

    painter::RayTraceCamera::Options camera_options
        = { .aspect_ratio = 16 / 9.0,
              .fov = 20,
              .focus_dist = 10,
              .defocus_angle = 0 };
    painter::RayTraceCamera camera(camera_options);

    painter::RayTraceObjects objs;

    auto checker = make_shared<painter::ray_trace::CheckerTexture>(0.8,
        math::to_color(Vec3(.2, .3, .1)), math::to_color(Vec3(.9, .9, .9)));

    objs.insert(make_shared<painter::RayTraceSphere>(Vec3(0, -10, 0), 10,
        make_shared<painter::RayTraceLambertian>(checker)));
    objs.insert(make_shared<painter::RayTraceSphere>(
        Vec3(0, 10, 0), 10, make_shared<painter::RayTraceLambertian>(checker)));

    painter::RayTraceBVH world(objs);

    camera.look(Vec3(13, 2, 3), Vec3(0, 0, 0), Vec3(0, 1, 0));

    painter::RayTracePainter painter(50, 100);
    painter.paint(&canvas, &camera, &world);

    fs::File canvas_file("test.png");
    stream::FileWriteStream canvas_file_writer(canvas_file);
    canvas.store_to(&canvas_file_writer);
}

static void earth()
{
    using Vec3 = math::Vec3;
    const fs::Path earth_map = "/home/niu2x/Downloads/earthmap.jpg";

    auto earth_texture
        = make_shared<painter::ray_trace::ImageTexture>(earth_map);
    auto earth_surface
        = make_shared<painter::RayTraceLambertian>(earth_texture);
    auto globe
        = make_shared<painter::RayTraceSphere>(Vec3(0, 0, 0), 2, earth_surface);

    image::Image canvas;
    canvas.reset(400, 225, Color::WHITE);

    painter::RayTraceCamera::Options camera_options
        = { .aspect_ratio = 16 / 9.0,
              .fov = 20,
              .focus_dist = 10,
              .defocus_angle = 0 };
    painter::RayTraceCamera camera(camera_options);
    painter::RayTraceObjects objs;
    objs.insert(globe);

    camera.look(Vec3(13, 2, 3), Vec3(0, 0, 0), Vec3(0, 1, 0));

    painter::RayTracePainter painter(50, 100);
    painter.paint(&canvas, &camera, &objs);

    fs::File canvas_file("test.png");
    stream::FileWriteStream canvas_file_writer(canvas_file);
    canvas.store_to(&canvas_file_writer);
}

static void two_perlin_spheres()
{
    using Vec3 = math::Vec3;

    image::Image canvas;
    canvas.reset(400, 225, Color::WHITE);

    painter::RayTraceCamera::Options camera_options
        = { .aspect_ratio = 16 / 9.0,
              .fov = 20,
              .focus_dist = 10,
              .defocus_angle = 0 };
    painter::RayTraceCamera camera(camera_options);

    painter::RayTraceObjects objs;

    auto pertext = make_shared<painter::ray_trace::NoiseTexture>(4);

    objs.insert(make_shared<painter::RayTraceSphere>(Vec3(0, -1000, 0), 1000,
        make_shared<painter::RayTraceLambertian>(pertext)));
    objs.insert(make_shared<painter::RayTraceSphere>(
        Vec3(0, 2, 0), 2, make_shared<painter::RayTraceLambertian>(pertext)));

    painter::RayTraceBVH world(objs);

    camera.look(Vec3(13, 2, 3), Vec3(0, 0, 0), Vec3(0, 1, 0));

    painter::RayTracePainter painter(50, 100);
    painter.paint(&canvas, &camera, &world);

    fs::File canvas_file("test.png");
    stream::FileWriteStream canvas_file_writer(canvas_file);
    canvas.store_to(&canvas_file_writer);
}

static void quads()
{
    using Vec3 = math::Vec3;
    image::Image canvas;
    canvas.reset(400, 225, Color::WHITE);

    painter::RayTraceCamera::Options camera_options
        = { .aspect_ratio = 16 / 9.0,
              .fov = 80,
              .focus_dist = 10,
              .defocus_angle = 0 };
    painter::RayTraceCamera camera(camera_options);

    painter::RayTraceObjects objs;

    // Materials
    auto left_red
        = make_shared<painter::RayTraceLambertian>((Vec3(1.0, 0.2, 0.2)));
    auto back_green
        = make_shared<painter::RayTraceLambertian>((Vec3(0.2, 1.0, 0.2)));
    auto right_blue
        = make_shared<painter::RayTraceLambertian>((Vec3(0.2, 0.2, 1.0)));
    auto upper_orange
        = make_shared<painter::RayTraceLambertian>((Vec3(1.0, 0.5, 0.0)));
    auto lower_teal
        = make_shared<painter::RayTraceLambertian>((Vec3(0.2, 0.8, 0.8)));

    // Quads
    objs.insert(make_shared<painter::ray_trace::Quad>(
        Vec3(-3, -2, 5), Vec3(0, 0, -4), Vec3(0, 4, 0), left_red));
    objs.insert(make_shared<painter::ray_trace::Quad>(
        Vec3(-2, -2, 0), Vec3(4, 0, 0), Vec3(0, 4, 0), back_green));
    objs.insert(make_shared<painter::ray_trace::Quad>(
        Vec3(3, -2, 1), Vec3(0, 0, 4), Vec3(0, 4, 0), right_blue));
    objs.insert(make_shared<painter::ray_trace::Quad>(
        Vec3(-2, 3, 1), Vec3(4, 0, 0), Vec3(0, 0, 4), upper_orange));
    objs.insert(make_shared<painter::ray_trace::Quad>(
        Vec3(-2, -3, 5), Vec3(4, 0, 0), Vec3(0, 0, -4), lower_teal));

    painter::RayTraceBVH world(objs);

    camera.look(Vec3(0, 0, 9), Vec3(0, 0, 0), Vec3(0, 1, 0));

    painter::RayTracePainter painter(50, 100);
    painter.paint(&canvas, &camera, &world);

    fs::File canvas_file("test.png");
    stream::FileWriteStream canvas_file_writer(canvas_file);
    canvas.store_to(&canvas_file_writer);
}

int main()
{
    quads();
    return 0;
}