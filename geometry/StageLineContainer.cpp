#include "StageLineContainer.h"

StageLineContainer::StageLineContainer(const std::vector<std::shared_ptr<Line>> &upLines,
                                       const std::vector<std::shared_ptr<Line>> &downLines)
    : m_upLines{std::move(upLines)},
      m_downLines{std::move(downLines)}
{
    
}

const std::vector<std::shared_ptr<Line>>& StageLineContainer::getUpLines() const {
    return m_upLines;
}

const std::vector<std::shared_ptr<Line>>& StageLineContainer::getDownLines() const {
    return m_downLines;
}
