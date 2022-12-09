#include "PatternLine.h"

PatternLine::PatternLine()
    : m_linePattern{},
      m_index{0},
      m_side{Line::Side::S_UNDEFINED}
{
    
}

PatternLine::PatternLine(const std::shared_ptr<LinePattern> linePattern,
                         const uint64_t index,
                         const Line::Side side)
    : m_linePattern{linePattern},
      m_index{index},
      m_side{side}
{
    
}

const std::shared_ptr<LinePattern>& PatternLine::getLinePattern() const {
    return m_linePattern;
}

uint64_t PatternLine::getIndex() const {
    return m_index;
}

Line::Side PatternLine::getSide() const {
    return m_side;
}

bool PatternLine::fillWithVariantsHash(const QHash<QString, QVariant> &stringVariantHash)
{
    
}
