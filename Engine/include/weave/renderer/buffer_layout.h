#ifndef WEAVE_BUFFER_LAYOUT_H
#define WEAVE_BUFFER_LAYOUT_H

#include "weave/PCH.h"
#include "weave/renderer/buffer_element.h"

namespace Weave {
    class BufferLayout {
    public:
        BufferLayout() {}

        BufferLayout(const std::initializer_list<BufferElement>& elements) {
            this->elements = elements;
            this->calculate_offsets_and_stride();
        }

        [[nodiscard]] inline const std::vector<BufferElement>& get_elements() const { return this->elements; }
        inline uint32_t get_stride() const { return this->stride; }

        std::vector<BufferElement>::iterator begin() { return elements.begin(); }
        std::vector<BufferElement>::iterator end() { return elements.end(); }
        std::vector<BufferElement>::const_iterator begin() const { return elements.begin(); }
        std::vector<BufferElement>::const_iterator end() const { return elements.end(); }

    private:
        void calculate_offsets_and_stride() {
            this->stride = 0;
            uint32_t offset = 0;

            for (BufferElement& element : elements) {
                element.offset = offset;
                offset += element.size;
                this->stride += element.size;
            }
        }

    private:
        std::vector<BufferElement> elements;
        uint32_t stride;
    };
}

#endif
