#ifndef WEAVE_CORE_H
#define WEAVE_CORE_H

namespace Weave {
    void init_core();
    void shutdown_core();
}

#define BIT(x) (1u << x)

#endif
