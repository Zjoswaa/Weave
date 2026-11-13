#ifndef WEAVE_OPENGL_CONTEXT_H
#define WEAVE_OPENGL_CONTEXT_H
#ifdef WEAVE_HAS_OPENGL

#include "weave/core/window.h"
#include "weave/renderer/graphics_context.h"

namespace Weave::OpenGL {
    class Context : public Weave::GraphicsContext {
    public:
        Context(const Weave::Window& window);
        virtual ~Context();

        bool init() override;

    private:
        void shutdown();

    private:
        const Weave::Window& window;
    };
}

#endif // WEAVE_HAS_OPENGL
#endif // WEAVE_OPENGL_CONTEXT_H
