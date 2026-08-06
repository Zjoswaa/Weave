#ifndef WEAVE_OPENGL_CONTEXT_H
#define  WEAVE_OPENGL_CONTEXT_H

#include "weave/renderer/graphics_context.h"
#include "weave/core/window.h"

namespace Weave {
    class OpenGlContext : public GraphicsContext {
    public:
        OpenGlContext(const Weave::Window* window);
        virtual ~OpenGlContext();

        void init() override;

    private:
        virtual void shutdown();

    private:
        const Weave::Window* window;
    };
}

#endif
