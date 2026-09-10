#include "weave/PCH.h"
#include "weave/renderer/vertex_array.h"
#include "weave/platform/opengl/opengl_vertex_array.h"

namespace Weave {
    VertexArray* VertexArray::create() {
        return new OpenGlVertexArray();
    }
}
