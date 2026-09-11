#include "weave/PCH.h"
#include "weave/renderer/camera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Weave {
    Camera::Camera() {
        this->recalculate_projection();
        this->recalculate_view();
    }

    void Camera::set_viewport_size(uint32_t width, uint32_t height) {
        if (width == 0 || height == 0) {
            return;
        }

        this->aspect_ratio = (float)width / (float)height;
        this->recalculate_projection();
    }

    void Camera::set_projection_type(ProjectionType projection_type) {
        this->projection_type = projection_type;
        recalculate_projection();
    }

    void Camera::set_perspective(float vertical_fov, float near_clip, float far_clip) {
        this->perspective_fov = vertical_fov;
        this->perspective_near = near_clip;
        this->perspective_far = far_clip;
        this->recalculate_projection();
    }

    void Camera::set_orthographic(float size, float near_clip, float far_clip) {
        this->orthographic_size = size;
        this->orthographic_near = near_clip;
        this->orthographic_far = far_clip;
        recalculate_projection();
    }

    void Camera::recalculate_projection() {
        if (this->projection_type == ProjectionType::Perspective) {
            this->projection_matrix = glm::perspective(glm::radians(this->perspective_fov), this->aspect_ratio, this->perspective_near, this->perspective_far);
        }
        else {
            float ortho_left = -this->orthographic_size * this->aspect_ratio * 0.5f;
            float ortho_right = this->orthographic_size * this->aspect_ratio * 0.5f;
            float ortho_bottom = -this->orthographic_size * 0.5f;
            float ortho_top = this->orthographic_size * 0.5f;

            this->projection_matrix = glm::ortho(ortho_left, ortho_right, ortho_bottom, ortho_top, this->orthographic_near, this->orthographic_far);
        }
        this->view_projection_matrix = this->projection_matrix * this->view_matrix;
    }

    void Camera::recalculate_view() {
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), this->position) * glm::rotate(glm::mat4(1.0f), glm::radians(this->rotation), glm::vec3(0, 0, 1));

        this->view_matrix = glm::inverse(transform);
        this->view_projection_matrix = this->projection_matrix * this->view_matrix;
    }
}
