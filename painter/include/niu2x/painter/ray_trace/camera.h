#ifndef NIU2X_PAINTER_RAY_TRACE_CAMERA_H
#define NIU2X_PAINTER_RAY_TRACE_CAMERA_H

#include <niu2x/math.h>

namespace niu2x::painter::ray_trace {

using math::DoubleSize;
using math::Vec3;

/**
 * @brief      This class describes a camera.
 */
class Camera {
public:
    /**
     * @brief      This is Camera Options.
     */
    struct Options {
        /**
         * @brief      ratio = width / height
         */
        double aspect_ratio;
        /**
         * @brief      fov
         */
        double fov;
        /**
         * @brief      焦距
         */
        double focus_dist;
        /**
         * @brief      defocus
         */
        double defocus_angle;

        Vec3 background;
    };

    /**
     * @brief      Constructs a new Camera instance.
     *
     * @param[in]  options  The options
     */
    Camera(const Options& options);

    /**
     * @brief      pose a camera.
     *
     * @param[in]  eye     The eye pos
     * @param[in]  target  The target pos
     * @param[in]  p_up    The up direction
     */
    void look(const Vec3& eye, const Vec3& target, const Vec3& up);

    inline const Vec3& eye() const { return pos_; }

    inline const Vec3& look() const { return look_; }

    inline const Vec3& up() const { return up_; }

    inline const Vec3& side() const { return side_; }

    inline const DoubleSize& size() const { return size_; }

    inline double focal_dist() const { return focal_length_; }

    inline double defocus_radius() const { return defocus_radius_; }

    const Vec3& background() const { return background_; }

private:
    DoubleSize size_;
    double focal_length_;
    double defocus_radius_;

    Vec3 pos_;
    Vec3 look_;
    Vec3 up_;
    Vec3 side_;

    Vec3 background_;
};

} // namespace niu2x::painter::ray_trace

namespace niu2x::painter {
using RayTraceCamera = ray_trace::Camera;
}

#endif