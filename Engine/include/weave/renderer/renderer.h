#ifndef WEAVE_RENDERER_H
#define WEAVE_RENDERER_H

namespace Weave {
    enum class RendererAPI {
        None = 0,
        OpenGL = 1
    };

    class Renderer {
    public:
        inline static RendererAPI get_renderer_api() { return renderer_api; }

    private:
        static RendererAPI renderer_api;
    };
}

#endif
