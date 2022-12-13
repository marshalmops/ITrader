#ifndef STAGEPATTERNCONTAINER_H
#define STAGEPATTERNCONTAINER_H

#include <vector>
#include <memory>

#include "../geometry/Line.h"
#include "Pattern.h"

#include "StagePatternLineContainer.h"

class StagePatternContainer {
private:
    std::vector<std::shared_ptr<StagePatternLineContainer>> m_patternLineContainers;
    
public:
    StagePatternContainer(const std::vector<std::shared_ptr<StagePatternLineContainer>> &patternLineContainers
                          = std::vector<std::shared_ptr<StagePatternLineContainer>>{});
    
    const std::vector<std::shared_ptr<StagePatternLineContainer>>& getPatternLineContainers() const;
    
    bool addPatternLineContainer (const std::shared_ptr<StagePatternLineContainer> &patternLineContainer);
    bool addPatternLineContainers(const std::vector<std::shared_ptr<StagePatternLineContainer>> &patternLineContainers);
};

#endif // STAGEPATTERNCONTAINER_H
