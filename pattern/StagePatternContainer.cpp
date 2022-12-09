#include "StagePatternContainer.h"

StagePatternContainer::StagePatternContainer(const std::vector<std::shared_ptr<Line>> &upLines,
                                             const std::vector<std::shared_ptr<Line>> &downLines,
                                             const std::vector<Pattern> &patterns)
    : m_upLines{upLines},
      m_downLines{downLines},
      m_patterns{std::move(patterns)}
{
    
}

const std::vector<std::shared_ptr<Line>>& StagePatternContainer::getUpLines() const {
    return m_upLines;
}

const std::vector<std::shared_ptr<Line>>& StagePatternContainer::getDownLines() const {
    return m_downLines;
}

const std::vector<Pattern>& StagePatternContainer::getPatterns() const {
    return m_patterns;
}
