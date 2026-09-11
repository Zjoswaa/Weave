#ifndef WEAVE_CAMERA_H
#define WEAVE_CAMERA_H

#include "weave/PCH.h"

#include <glm/glm.hpp>

namespace Weave {
    class Camera {
    public:
        enum class ProjectionType {
            Perspective = 0,
            Orthographic = 1
        };

        Camera();

        void set_viewport_size(uint32_t width, uint32_t height);
        ProjectionType get_projection_type() const {
            return this->projection_type;
        }
        void set_projection_type(ProjectionType projection_type);

        void set_perspective(float vertical_fov, float near_clip, float far_clip);
        float get_perspective_vertical_fov() const {
            return this->perspective_fov;
        }
        void set_perspective_vertical_fov(float vertical_fov) {
            this->perspective_fov = vertical_fov;
            this->recalculate_projection();
        }

        void set_orthographic(float size, float near_clip, float far_clip);
        float get_orthographic_size() const {
            return this->orthographic_size;
        }
        void set_orthographic_size(float size) {
            this->orthographic_size = size;
            this->recalculate_projection();
        }

        const glm::vec3& get_position() const { return this->position; }
        void set_position(const glm::vec3& position) {
            this->position = position;
            this->recalculate_view();
        }

        float get_rotation() const { return this->rotation; }
        void set_rotation(float rotation) {
            this->rotation = rotation;
            this->recalculate_view();
        }

        const glm::mat4& get_projection_matrix() const {
            return this->projection_matrix;
        }
        const glm::mat4& get_view_matrix() const {
            return this->view_matrix;
        }
        const glm::mat4& get_view_projection_matrix() const {
            return this->view_projection_matrix;
        }

    private:
        void recalculate_projection();
        void recalculate_view();

    private:
        ProjectionType projection_type = ProjectionType::Perspective;
        float aspect_ratio = 16.f / 9.f;

        float perspective_fov = 90.0f;
        float perspective_near = 0.01f;
        float perspective_far = 1000.0f;

        float orthographic_size = 5.0f;
        float orthographic_near = -1.0f;
        float orthographic_far = 1.0f;

        glm::mat4 projection_matrix { 1.0f };
        glm::mat4 view_matrix { 1.0f };
        glm::mat4 view_projection_matrix { 1.0f };

        glm::vec3 position { 0.0f, 0.0f, 0.0f };
        float rotation = 0.0f;
    };
}

#endif
