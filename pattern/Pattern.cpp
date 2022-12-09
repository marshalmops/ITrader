#include "Pattern.h"

std::ostream& operator<<(std::ostream &out, const Pattern &pattern) {
    out << "\nID: " << pattern.m_id << "\nName: " << pattern.m_name
        << "\nProbability: " << pattern.m_probability
        << "\nCount of uses: " << pattern.m_countOfUses
        << "\nPrevious trend: " << Pattern::trendToString(pattern.m_prevTrend)
        << "\nFuture trend: " << Pattern::trendToString(pattern.m_futureTrend);
    
    return out;
}

Pattern::Pattern()
    : m_id{0},
      m_name{std::string{}},
      m_probability{0.},
      m_countOfUses{0},
      m_prevTrend{Trend::T_UNDEFINED},
      m_futureTrend{Trend::T_UNDEFINED},
      m_patternLines{std::vector<PatternLine>{}}
{
    
}

Pattern::Pattern(const uint64_t id,
                 const std::string& name,
                 const float probability,
                 const uint64_t countOfUses,
                 const Trend prevTrend,
                 const Trend futureTrend,
                 std::vector<PatternLine> &&patternLines)
    : m_id{id},
      m_name{name},
      m_probability{probability},
      m_countOfUses{countOfUses},
      m_prevTrend{prevTrend},
      m_futureTrend{futureTrend},
      m_patternLines{patternLines}
{ }

uint64_t Pattern::getId() const {
    return m_id;
}

const std::string& Pattern::getName() const {
    return m_name;
}

float Pattern::getProbability() const {
    return m_probability;
}

uint64_t Pattern::getCountOfUses() const {
    return m_countOfUses;
}

Pattern::Trend Pattern::getPrevTrend() const {
    return m_prevTrend;
}

Pattern::Trend Pattern::getFutureTrend() const {
    return m_futureTrend;
}

const std::vector<PatternLine>& Pattern::getPatternLines() const {
    return m_patternLines;
}

bool Pattern::initPatternLines(std::vector<PatternLine> &&patternLines)
{
    if (m_patternLines.empty()) return false;
    
    m_patternLines = std::move(patternLines);
    
    return true;
}

bool Pattern::findInLinesFromBack(const std::vector<PatternLine> &patternLines) const {
    if (patternLines.empty()) return false;
    if (patternLines.size() < m_patternLines.size()) return false;
    
    int lastPatternInnerIndex = m_patternLines.size() - 1;
    int patternInnerIndex = lastPatternInnerIndex;
    
    for (int i = patternLines.size() - 1; i >= 0; --i) {
        if (patternLines.at(i).getLinePattern()->getId() 
         == m_patternLines.at(patternInnerIndex).getLinePattern()->getId())
        {
            --patternInnerIndex;
        } else {
            if (patternInnerIndex != lastPatternInnerIndex && i < m_patternLines.size())
                break;
        }
        
        if (patternInnerIndex == -1)
            return true;
    }
    
    return false;
}

bool Pattern::fillWithVariantsHash(const QHash<QString, QVariant> &stringVariantHash)
{
    if (stringVariantHash.empty()) return false;
    
    if (!stringVariantHash.contains(C_DATABASE_ID_PROP)
     || !stringVariantHash.contains(C_DATABASE_NAME_PROP)
     || !stringVariantHash.contains(C_DATABASE_PROBABILITY_PROP)
     || !stringVariantHash.contains(C_DATABASE_USE_COUNT_PROP)
     || !stringVariantHash.contains(C_DATABASE_PREV_TREND_PROP)
     || !stringVariantHash.contains(C_DATABASE_FUTURE_TREND_PROP))
    {
        return false;
    }
    
    QVariant idVariant         {stringVariantHash.value(Pattern::C_DATABASE_ID_PROP)};
    QVariant nameVariant       {stringVariantHash.value(Pattern::C_DATABASE_NAME_PROP)};
    QVariant probabilityVariant{stringVariantHash.value(Pattern::C_DATABASE_PROBABILITY_PROP)};
    QVariant countOfUsesVariant{stringVariantHash.value(Pattern::C_DATABASE_USE_COUNT_PROP)};
    QVariant prevTrendVariant  {stringVariantHash.value(Pattern::C_DATABASE_PREV_TREND_PROP)};
    QVariant futureTrendVariant{stringVariantHash.value(Pattern::C_DATABASE_FUTURE_TREND_PROP)};
    
    if (!idVariant.isValid()          || !nameVariant.isValid()
     || !probabilityVariant.isValid() || !countOfUsesVariant.isValid()
     || !prevTrendVariant.isValid()   || !futureTrendVariant.isValid())
    {
        return false;
    }
    
    std::unique_ptr<uint64_t> rawId{};
    std::unique_ptr<QString>  rawName{};
    std::unique_ptr<float>    rawProbability{};
    std::unique_ptr<uint64_t> rawCountOfUses{};
    std::unique_ptr<Trend>    rawPrevTrend{};
    std::unique_ptr<Trend>    rawFutureTrend{};
    
    if (!DatabaseEntity::getValueByVariant(idVariant,          rawId)
     || !DatabaseEntity::getValueByVariant(nameVariant,        rawName)
     || !DatabaseEntity::getValueByVariant(probabilityVariant, rawProbability)
     || !DatabaseEntity::getValueByVariant(countOfUsesVariant, rawCountOfUses)
     || !DatabaseEntity::getValueByVariant(prevTrendVariant,   rawPrevTrend)
     || !DatabaseEntity::getValueByVariant(futureTrendVariant, rawFutureTrend))
    {
        return false;
    }
    
    m_id          = *rawId;
    m_name        = rawName->toStdString();
    m_probability = *rawProbability;
    m_countOfUses = *rawCountOfUses;
    m_prevTrend   = *rawPrevTrend;
    m_futureTrend = *rawFutureTrend;
    
    return true;
}
