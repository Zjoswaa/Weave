#include "weave/PCH.h"
#include "weave/core/log.h"
#include "weave/platform/opengl/opengl_renderer_api.h"
#include "weave/renderer/renderer.h"
#include "weave/renderer/renderer_api.h"

namespace Weave {
    RendererAPI* Renderer::renderer_api = nullptr;

    void Renderer::init() {
        WEAVE_LOG_CORE_INFO_TAG("Renderer", "Initializing");
        switch (RendererAPI::current()) {
            case RendererAPI::API::OpenGL:
                Renderer::renderer_api = new OpenGlRendererAPI();
                break;
            default:
                WEAVE_LOG_CORE_CRITICAL_TAG("Renderer", "Failed to initialize, no API selected");
                break;
        }

        if (Renderer::renderer_api) {
            Renderer::renderer_api->init();
            WEAVE_LOG_CORE_INFO_TAG("Renderer", "Initialized");
        }
    }

    void Renderer::shutdown() {
        WEAVE_LOG_CORE_INFO_TAG("Renderer", "Shutting down");
        Renderer::renderer_api->shutdown();
        delete Renderer::renderer_api;
        Renderer::renderer_api = nullptr;
        WEAVE_LOG_CORE_INFO_TAG("Renderer", "Shut down");
    }

    void Renderer::begin_frame() {
        Renderer::renderer_api->begin_frame();
    }

    void Renderer::end_frame() {
        Renderer::renderer_api->end_frame();
    }

    void Renderer::clear() {
        Renderer::renderer_api->clear();
    }

    void Renderer::set_clear_color(const float r, const float g, const float b, const float a) {
        Renderer::renderer_api->set_clear_color(r, g, b, a);
    }

    void Renderer::draw_indexed(const std::shared_ptr<VertexArray>& vertex_array) {
        Renderer::renderer_api->draw_indexed(vertex_array);
    }
}
