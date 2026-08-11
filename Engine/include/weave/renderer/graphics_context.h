#ifndef WEAVE_GRAPHICS_CONTEXT_H
#define WEAVE_GRAPHICS_CONTEXT_H

#include "weave/PCH.h"
#include "weave/core/window.h"

namespace Weave {
    /**
     * \brief The context that stores graphics data per-window.
     *
     * The context is created with a factory method that accepts a reference to the window that the context will bind to.
     */
    class GraphicsContext {
    public:
        virtual ~GraphicsContext() = default;

        virtual void init() = 0;
        virtual void swap_buffers() = 0;

        static std::unique_ptr<GraphicsContext> create(Weave::Window* window);
    };
}

#endif
