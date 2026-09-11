#include "weave/PCH.h"
#include "weave/platform/opengl/opengl_framebuffer.h"
#include "weave/renderer/framebuffer.h"

namespace Weave {
    std::shared_ptr<Framebuffer> Framebuffer::create(const FramebufferSpecification& spec) {
        return std::make_shared<OpenGlFramebuffer>(spec);
    }
}
