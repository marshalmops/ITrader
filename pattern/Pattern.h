#ifndef PATTERN_H
#define PATTERN_H

#include <cstdint>
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <QVariant>

#include "DatabaseEntity.h"
#include "../TrendSolverContext.h"
#include "PatternLine.h"

class Pattern : public DatabaseEntity {
public:
    constexpr static const char* C_DATABASE_TABLE_NAME = "Pattern";
    
    constexpr static const char* C_DATABASE_ID_PROP           = "id";
    constexpr static const char* C_DATABASE_NAME_PROP         = "name";
    constexpr static const char* C_DATABASE_PROBABILITY_PROP  = "probability";
    constexpr static const char* C_DATABASE_USE_COUNT_PROP    = "countOfUses";
    constexpr static const char* C_DATABASE_PREV_TREND_PROP   = "prevTrend";
    constexpr static const char* C_DATABASE_FUTURE_TREND_PROP = "futureTrend";
    
    using Trend = TrendSolverContext::Trend;
    
    static const char* trendToString(const Trend trend) {
        static const std::unordered_map<Trend, const char*> trendStringHash{
            {Trend::T_UNDEFINED, "Undefined"},
            {Trend::T_UP, "Up"},
            {Trend::T_DOWN, "Down"}
        };
        
        return trendStringHash.at(trend);
    }
    
private:
    uint64_t    m_id;
    std::string m_name;
    float       m_probability;
    uint64_t    m_countOfUses;
    Trend       m_prevTrend;
    Trend       m_futureTrend;
    
    std::vector<PatternLine> m_patternLines;
    
public:
    Pattern();
    Pattern(const std::string& name,
            const float probability,
            const Trend prevTrend,
            const Trend futureTrend,
            std::vector<PatternLine> &&patternLines);
    Pattern(const uint64_t id,
            const std::string& name,
            const float probability,
            const uint64_t countOfUses,
            const Trend prevTrend,
            const Trend futureTrend,
            std::vector<PatternLine> &&patternLines = std::vector<PatternLine>{});
    
    uint64_t getId() const;
    
    const std::string& getName() const;
    
    float getProbability() const;
    
    uint64_t getCountOfUses() const;
    
    Trend getPrevTrend() const;
    Trend getFutureTrend() const;
    
    const std::vector<PatternLine>& getPatternLines() const;
    
    bool initPatternLines(std::vector<PatternLine> &&patternLines);
    
    bool findInLinesFromBack(const std::vector<PatternLine> &patternLines) const;
    
    virtual bool fillWithVariantsHash(const QHash<QString, QVariant> &stringVariantHash) override;
    
    friend std::ostream& operator<<(std::ostream &out, const Pattern &pattern);
};

#endif // PATTERN_H
