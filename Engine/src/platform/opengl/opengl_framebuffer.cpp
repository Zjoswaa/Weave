#include "weave/PCH.h"
#include "weave/core/log.h"
#include "weave/platform/opengl/opengl_framebuffer.h"

#include <glad/glad.h>

namespace Weave {
    OpenGlFramebuffer::OpenGlFramebuffer(const FramebufferSpecification& spec) {
        this->spec = spec;
        invalidate();
    }

    OpenGlFramebuffer::~OpenGlFramebuffer() {
        glDeleteFramebuffers(1, &this->id);
        glDeleteTextures(1, &this->color_attachment);
        glDeleteTextures(1, &this->depth_attachment);
    }

    void OpenGlFramebuffer::invalidate() {
        if (this->id) {
            glDeleteFramebuffers(1, &this->id);
            glDeleteTextures(1, &this->color_attachment);
            glDeleteTextures(1, &this->depth_attachment);
        }

        glGenFramebuffers(1, &this->id);
        glBindFramebuffer(GL_FRAMEBUFFER, this->id);

        glGenTextures(1, &this->color_attachment);
        glBindTexture(GL_TEXTURE_2D, this->color_attachment);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, this->spec.width, this->spec.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->color_attachment, 0);

        glGenTextures(1, &this->depth_attachment);
        glBindTexture(GL_TEXTURE_2D, this->depth_attachment);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, this->spec.width, this->spec.height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, nullptr);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, this->depth_attachment, 0);

        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
            WEAVE_LOG_CORE_ERROR("Framebuffer is incomplete");
        }

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void OpenGlFramebuffer::bind() {
        glBindFramebuffer(GL_FRAMEBUFFER, this->id);
        glViewport(0, 0, this->spec.width, this->spec.height);
    }

    void OpenGlFramebuffer::unbind() {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void OpenGlFramebuffer::resize(uint32_t width, uint32_t height) {
        if (width == 0 || height == 0) {
            return;
        }

        this->spec.width = width;
        this->spec.height = height;

        this->invalidate();
    }
}
