#ifndef WEAVE_RENDERER_H
#define WEAVE_RENDERER_H

#include "weave/PCH.h"
#include "weave/renderer/renderer_api.h"
#include "weave/renderer/vertex_array.h"

namespace Weave {
    class Renderer {
    public:
        static void init();
        static void shutdown();

        static void begin_frame();
        static void end_frame();
        static void clear();

        static void set_clear_color(const float r, const float g, const float b, const float a);
        static void draw_indexed(const std::shared_ptr<VertexArray>& vertex_array);

    private:
        static RendererAPI* renderer_api;
    };
}

#endif
