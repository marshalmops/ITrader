#ifndef STAGEPATTERNLINECONTAINER_H
#define STAGEPATTERNLINECONTAINER_H

#include "../geometry/Line.h"
#include "Pattern.h"

class StagePatternLineContainer {
private:
    std::vector<std::shared_ptr<Line>> m_upLines;
    std::vector<std::shared_ptr<Line>> m_downLines;
    
    std::shared_ptr<Pattern> m_pattern;
    
public:
    StagePatternLineContainer(const std::vector<std::shared_ptr<Line>> &upLines,
                              const std::vector<std::shared_ptr<Line>> &downLines,
                              const std::shared_ptr<Pattern> &pattern);
    
    const std::vector<std::shared_ptr<Line>>& getUpLines() const;
    
    const std::vector<std::shared_ptr<Line>>& getDownLines() const;
    
    const std::shared_ptr<Pattern>& getPattern() const;
};

#endif // STAGEPATTERNLINECONTAINER_H
