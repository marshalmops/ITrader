#ifndef STAGEPATTERNCONTAINER_H
#define STAGEPATTERNCONTAINER_H

#include <vector>
#include <memory>

#include "../geometry/Line.h"
#include "Pattern.h"

class StagePatternContainer {
private:
    std::vector<std::shared_ptr<Line>> m_upLines;
    std::vector<std::shared_ptr<Line>> m_downLines;
    std::vector<std::shared_ptr<Pattern>> m_patterns;
    
public:
    StagePatternContainer(const std::vector<std::shared_ptr<Line>> &upLines,
                          const std::vector<std::shared_ptr<Line>> &downLines,
                          const std::vector<std::shared_ptr<Pattern>> &patterns);
    
    const std::vector<std::shared_ptr<Line>>& getUpLines() const;
    
    const std::vector<std::shared_ptr<Line>>& getDownLines() const;
    
    const std::vector<std::shared_ptr<Pattern>>& getPatterns() const;
};

#endif // STAGEPATTERNCONTAINER_H
