#include "weave/PCH.h"
#include "weave/core/log.h"
#include "weave/platform/opengl/opengl_renderer_api.h"

#include <glad/glad.h>

namespace Weave {
    void OpenGlRendererAPI::init() {
        WEAVE_LOG_CORE_INFO_TAG("Renderer", "Initializing OpenGL Renderer");
    }

    void OpenGlRendererAPI::shutdown() {
        WEAVE_LOG_CORE_INFO_TAG("Renderer", "Shutting down OpenGL Renderer");
    }

    void OpenGlRendererAPI::set_clear_color(const float r, const float g, const float b, const float a) {
        glClearColor(r, g, b, a);
    }

    void OpenGlRendererAPI::clear() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void OpenGlRendererAPI::set_viewport(const int32_t x, const int32_t y, const int32_t width, const int32_t height) {
        glViewport(x, y, width, height);
    }

    void OpenGlRendererAPI::draw_indexed(const std::shared_ptr<VertexArray>& vertex_array) {
        vertex_array->bind();
        glDrawElements(GL_TRIANGLES, vertex_array->get_index_buffer()->get_count(), GL_UNSIGNED_INT, nullptr);
    }
}
