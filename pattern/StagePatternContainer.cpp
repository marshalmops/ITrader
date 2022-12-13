#include "StagePatternContainer.h"

StagePatternContainer::StagePatternContainer(const std::vector<std::shared_ptr<StagePatternLineContainer>> &patternLineContainers)
    : m_patternLineContainers{patternLineContainers}
{
    
}

const std::vector<std::shared_ptr<StagePatternLineContainer>> &StagePatternContainer::getPatternLineContainers() const
{
    return m_patternLineContainers;
}

bool StagePatternContainer::addPatternLineContainer(const std::shared_ptr<StagePatternLineContainer> &patternLineContainer)
{
    if (!patternLineContainer.get()) return false;
    
    m_patternLineContainers.push_back(patternLineContainer);
    
    return true;
}

bool StagePatternContainer::addPatternLineContainers(const std::vector<std::shared_ptr<StagePatternLineContainer> > &patternLineContainers)
{
    if (patternLineContainers.empty()) return false;
    
    m_patternLineContainers.insert(m_patternLineContainers.end(), patternLineContainers.begin(), patternLineContainers.end());
    
    return true;
}
