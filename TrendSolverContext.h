#ifndef TRENDSOLVERCONTEXT_H
#define TRENDSOLVERCONTEXT_H

#include <cstdint>

namespace TrendSolverContext {
    constexpr static const float   C_ACCEPTABLE_DOT_CROSSING_DEVIATION_PERCENT = 0.05;
    constexpr static const uint8_t C_MIN_COUNT_OF_DOTS_TO_ANALIZE = 30;
    constexpr static const uint8_t C_COUNT_OF_DOTS_TO_GET_PATTERNS = 20;

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
    
    inline TrendType getTrendValue(const Trend trend) {
        return static_cast<TrendType>(trend);
    }
}

#endif // TRENDSOLVERCONTEXT_H
