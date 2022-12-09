#ifndef STAGELINECONTAINER_H
#define STAGELINECONTAINER_H

#include <vector>
#include <memory>

#include "Line.h"

class StageLineContainer {
private:
    std::vector<std::shared_ptr<Line>> m_upLines;
    std::vector<std::shared_ptr<Line>> m_downLines;
    
public:
    StageLineContainer(const std::vector<std::shared_ptr<Line>> &upLines,
                       const std::vector<std::shared_ptr<Line>> &downLines);
    
    const std::vector<std::shared_ptr<Line>>& getUpLines() const;
    const std::vector<std::shared_ptr<Line>>& getDownLines() const;
};

#endif // STAGELINECONTAINER_H
