#include <niu2x/gfx/gui.h>

namespace niu2x::gfx::gui {

Mat4 ui_view_mat4;
Mat4 ui_projection_mat4;

void update_view_projection(IntSize window_size)
{
    float half_width = window_size.width * 0.5;
    float half_height = window_size.height * 0.5;

    auto eye = Vec3(half_width, -half_height, 10);
    auto target = Vec3(half_width, -half_height, 0);

    ui_view_mat4 = math::lookat_matrix(eye, target, Vec3(0, 1, 0));

    ui_projection_mat4 = math::frustum_matrix(
        -half_width, half_width, -half_height, half_height, -100.0f, 100.0f);
}

} // namespace niu2x::gfx::gui