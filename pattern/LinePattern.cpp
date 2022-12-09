#include "LinePattern.h"

LinePattern::AngleType LinePattern::angleTypeFromDirection(const Line::Direction dir)
{
    switch (dir) {
        case Line::Direction::D_PARALLEL: return LinePattern::AngleType::AT_ZERO;
        case Line::Direction::D_TO_UP: return LinePattern::AngleType::AT_POSITIVE;
        case Line::Direction::D_TO_DOWN: return LinePattern::AngleType::AT_NEGATIVE;
    }
}

LinePattern::LinePattern()
    : m_id{0},
      m_name{std::string{}},
      m_angleType{AngleType::AT_ZERO}
{
    
}

LinePattern::LinePattern(const uint64_t id, 
                         const std::string &name, 
                         const AngleType angleType)
    : m_id{id},
      m_name{name},
      m_angleType{angleType}
{
    
}

uint64_t LinePattern::getId() const {
    return m_id;
}

const std::string& LinePattern::getName() const {
    return m_name;
}

LinePattern::AngleType LinePattern::getAngleType() const {
    return m_angleType;
}

bool LinePattern::fillWithVariantsHash(const QHash<QString, QVariant> &stringVariantHash) {
    if (stringVariantHash.empty()) return false;
    
    
    
    return true;
}
