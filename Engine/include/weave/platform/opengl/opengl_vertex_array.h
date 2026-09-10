#ifndef WEAVE_OPENGL_VERTEX_ARRAY_H
#define WEAVE_OPENGL_VERTEX_ARRAY_H

#include "weave/PCH.h"
#include "weave/renderer/vertex_array.h"

#include <glad/glad.h>

namespace Weave {
    class OpenGlVertexArray : public VertexArray {
    public:
        OpenGlVertexArray();
        ~OpenGlVertexArray() override;

        void bind() const override;
        void unbind() const override;

        void add_vertex_buffer(const std::shared_ptr<VertexBuffer>& vertex_buffer) override;
        void set_index_buffer(const std::shared_ptr<IndexBuffer>& index_buffer) override;

        const std::vector<std::shared_ptr<VertexBuffer>>& get_vertex_buffers() const override {
            return this->vertex_buffers;
        }
        const std::shared_ptr<IndexBuffer>& get_index_buffer() const override {
            return this->index_buffer;
        }

    private:
        GLuint id;
        std::vector<std::shared_ptr<VertexBuffer>> vertex_buffers;
        std::shared_ptr<IndexBuffer> index_buffer;
    };
}

#endif
