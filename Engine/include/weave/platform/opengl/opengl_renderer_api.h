#ifndef WEAVE_OPENGL_RENDERER_API_H
#define WEAVE_OPENGL_RENDERER_API_H

#include "weave/PCH.h"
#include "weave/renderer/renderer_api.h"

namespace Weave {
    class OpenGlRendererAPI : public RendererAPI {
    public:
        void init() override;
        void shutdown() override;

        void begin_frame() override {};
        void end_frame() override {};
        void clear() override;

        void set_clear_color(const float r, const float g, const float b, const float a) override;
        void draw_indexed(const std::shared_ptr<VertexArray>& vertex_array) override;
    };
}

#endif
