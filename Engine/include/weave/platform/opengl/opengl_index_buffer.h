#ifndef WEAVE_OPENGL_INDEX_BUFFER_H
#define WEAVE_OPENGL_INDEX_BUFFER_H

#include "weave/PCH.h"
#include "weave/renderer/index_buffer.h"

namespace Weave::OpenGL {
    class IndexBuffer : public Weave::IndexBuffer {
    public:
        IndexBuffer(uint32_t* indices, uint32_t count);
        ~IndexBuffer() override;

        void bind() const override;
        void unbind() const override;

        inline uint32_t get_count() const override { return this->count; }

    private:
        uint32_t id;
        uint32_t count;
    };
}

#endif
