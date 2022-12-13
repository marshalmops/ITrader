#include "StagePatternLineContainer.h"

StagePatternLineContainer::StagePatternLineContainer(const std::vector<std::shared_ptr<Line> > &upLines,
                                                     const std::vector<std::shared_ptr<Line> > &downLines,
                                                     const std::shared_ptr<Pattern> &pattern)
    : m_upLines{upLines},
      m_downLines{downLines},
      m_pattern{pattern}
{
    
}

const std::vector<std::shared_ptr<Line>> &StagePatternLineContainer::getUpLines() const
{
    return m_upLines;
}

const std::vector<std::shared_ptr<Line> > &StagePatternLineContainer::getDownLines() const
{
    return m_downLines;
}

const std::shared_ptr<Pattern> &StagePatternLineContainer::getPattern() const
{
    return m_pattern;
}
