#include "PatternLine.h"

PatternLine::PatternLine()
    : m_patternId{},
      m_lineId{},
      m_index{0},
      m_side{Line::Side::S_UNDEFINED}
{
    
}

PatternLine::PatternLine(const uint64_t lineId, 
                         const uint64_t index, 
                         const Line::Side side)
    : m_patternId{},
      m_lineId   {lineId},
      m_index    {index},
      m_side     {side}
{
    
}

PatternLine::PatternLine(const uint64_t patternId, 
                         const uint64_t lineId,
                         const uint64_t index,
                         const Line::Side side)
    : m_patternId{patternId},
      m_lineId   {lineId},
      m_index    {index},
      m_side     {side}
{
    
}

uint64_t PatternLine::getPatternId() const
{
    return m_patternId;
}

uint64_t PatternLine::getLineId() const
{
    return m_lineId;
}

uint64_t PatternLine::getIndex() const {
    return m_index;
}

Line::Side PatternLine::getSide() const {
    return m_side;
}

bool PatternLine::fillWithVariantsHash(const QHash<QString, QVariant> &stringVariantHash)
{
    if (stringVariantHash.empty()) return false;
    
    if (!stringVariantHash.contains(C_DATABASE_LINE_ID_PROP)
     || !stringVariantHash.contains(C_DATABASE_PATTERN_ID_PROP)
     || !stringVariantHash.contains(C_DATABASE_LINE_INDEX_PROP)
     || !stringVariantHash.contains(C_DATABASE_LINE_SIDE_PROP))
    {
        return false;
    }
    
    QVariant lineIdVariant   {stringVariantHash.value(PatternLine::C_DATABASE_LINE_ID_PROP)};
    QVariant patternIdVariant{stringVariantHash.value(PatternLine::C_DATABASE_PATTERN_ID_PROP)};
    QVariant lineIndexVariant{stringVariantHash.value(PatternLine::C_DATABASE_LINE_INDEX_PROP)};
    QVariant lineSideVariant {stringVariantHash.value(PatternLine::C_DATABASE_LINE_SIDE_PROP)};
    
    if (!lineIdVariant.isValid()    || !patternIdVariant.isValid()
     || !lineIndexVariant.isValid() || !lineSideVariant.isValid())
    {
        return false;
    }
    
    m_patternId = patternIdVariant.value<uint64_t>();
    m_lineId    = lineIdVariant.value<uint64_t>();
    m_index     = lineIndexVariant.value<uint64_t>();
    m_side      = lineSideVariant.value<Line::Side>();
    
    return true;
}
