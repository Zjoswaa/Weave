#ifndef WEAVE_OPENGL_FRAMEBUFFER_H
#define WEAVE_OPENGL_FRAMEBUFFER_H

#include "weave/PCH.h"
#include "weave/renderer/framebuffer.h"

#include <glad/glad.h>

namespace Weave {

    class OpenGlFramebuffer : public Framebuffer {
    public:
        OpenGlFramebuffer(const FramebufferSpecification& spec);
        ~OpenGlFramebuffer() override;

        void invalidate();

        void bind() override;
        void unbind() override;

        void resize(uint32_t width, uint32_t height) override;
        uint32_t get_color_attachment_renderer_id() const override { return this->color_attachment; }
        const FramebufferSpecification& get_specification() const override { return this->spec; }

    private:
        GLuint id = 0;
        GLuint color_attachment = 0;
        GLuint depth_attachment = 0;
        FramebufferSpecification spec;
    };

} // namespace Weave

#endif
