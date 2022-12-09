#ifndef STAGEPATTERNCONTAINER_H
#define STAGEPATTERNCONTAINER_H

#include <vector>
#include <memory>

#include "../geometry/Line.h"
#include "Pattern.h"

class StagePatternContainer {
private:
    const std::vector<std::shared_ptr<Line>> &m_upLines;
    const std::vector<std::shared_ptr<Line>> &m_downLines;
    const std::vector<Pattern> m_patterns;
    
public:
    StagePatternContainer(const std::vector<std::shared_ptr<Line>> &upLines,
                          const std::vector<std::shared_ptr<Line>> &downLines,
                          const std::vector<Pattern> &patterns);
    
    const std::vector<std::shared_ptr<Line>>& getUpLines() const;
    
    const std::vector<std::shared_ptr<Line>>& getDownLines() const;
    
    const std::vector<Pattern>& getPatterns() const;
};

#endif // STAGEPATTERNCONTAINER_H
