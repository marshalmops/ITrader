#ifndef TRENDSOLVERCONTEXT_H
#define TRENDSOLVERCONTEXT_H

#include <cstdint>

namespace TrendSolverContext {
    static float S_ACCEPTABLE_DOT_CROSSING_DEVIATION_PERCENT = 0.05;
    
    enum class Trend : uint8_t {
        T_UNDEFINED = 0,
        T_UP,
        T_DOWN
    };
}

#endif // TRENDSOLVERCONTEXT_H
