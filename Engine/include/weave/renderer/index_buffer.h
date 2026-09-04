#ifndef WEAVE_INDEX_BUFFER_H
#define WEAVE_INDEX_BUFFER_H

#include "weave/PCH.h"

namespace Weave {
    class IndexBuffer {
    public:
        virtual ~IndexBuffer() = default;

        virtual void bind() const = 0;
        virtual void unbind() const = 0;
        virtual uint32_t get_count() const = 0;

        static IndexBuffer* create(const uint32_t* indices, const uint32_t count);
    };
}

#endif
