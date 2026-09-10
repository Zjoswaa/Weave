#ifndef WEAVE_RENDERER_API_H
#define WEAVE_RENDERER_API_H

#include "weave/PCH.h"
#include "weave/renderer/vertex_array.h"

namespace Weave {
    class RendererAPI {
    public:
        enum class API {
            None = 0,
            OpenGL = 1
        };

        virtual ~RendererAPI() = default;

        virtual void init() = 0;
        virtual void shutdown() = 0;

        virtual void begin_frame() = 0;
        virtual void end_frame() = 0;
        virtual void clear() = 0;

        virtual void set_clear_color(const float r, const float g, const float b, const float a) = 0;
        virtual void draw_indexed(const std::shared_ptr<VertexArray>& vertex_array) = 0;

        inline static API current() { return current_renderer_api; }
    private:
        inline static API current_renderer_api = API::OpenGL;
    };
}

#endif
