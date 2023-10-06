#include <niu2x/painter/ray_trace/camera.h>

namespace niu2x::painter::ray_trace {

Camera::Camera(const Options& opt)
: size_({
    opt.aspect_ratio,
    1.0,
})
, focal_length_(size_.height / 2 / tan(math::deg2rad(opt.fov / 2)))
, defocus_radius_(opt.focus_dist * tan(math::deg2rad(opt.defocus_angle / 2)))
{
    double scale = opt.focus_dist / focal_length_;
    focal_length_ = opt.focus_dist;
    size_.width *= scale;
    size_.height *= scale;
}

void Camera::look(const Vec3& eye, const Vec3& target, const Vec3& p_up)
{
    pos_ = eye;
    look_ = normalize(target - eye);
    side_ = normalize(cross(look_, p_up));
    up_ = cross(side_, look_);
}

} // namespace niu2x::painter::ray_trace