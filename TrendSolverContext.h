#ifndef TRENDSOLVERCONTEXT_H
#define TRENDSOLVERCONTEXT_H

#include <cstdint>

namespace TrendSolverContext {
    static float S_ACCEPTABLE_DOT_CROSSING_DEVIATION_PERCENT = 0.05;
    
    using TrendType = uint8_t;
    
    enum class Trend : TrendType {
        T_UNDEFINED = 0,
        T_UP,
        T_DOWN,
        T_COUNT
    };
    
    inline Trend getTrendByValue(const TrendType trendValue) {
        if (trendValue <= static_cast<TrendType>(Trend::T_UNDEFINED)
         || trendValue >= static_cast<TrendType>(Trend::T_COUNT))
        {
            return Trend::T_UNDEFINED;
        }
        
        return static_cast<Trend>(trendValue);
    }
}

#endif // TRENDSOLVERCONTEXT_H
