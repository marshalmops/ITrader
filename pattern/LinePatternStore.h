#ifndef LINEPATTERNSTORE_H
#define LINEPATTERNSTORE_H

#include <memory>
#include <vector>

#include "LinePattern.h"

class LinePatternStore {
private:
    static std::shared_ptr<LinePatternStore> s_store;
    
    std::vector<std::shared_ptr<LinePattern>> m_linePatterns;
    
    LinePatternStore();
    
public:
    static void init();
    
    static std::shared_ptr<LinePatternStore> getInstance();
    
    const std::vector<std::shared_ptr<LinePattern>>& getLinePatterns() const;
    
    const std::shared_ptr<LinePattern> getLinePatternById(const uint64_t id) const;
    const std::shared_ptr<LinePattern> getLinePatternByAngleType(const LinePattern::AngleType angleType) const;
    
    bool addLinePattern(std::unique_ptr<LinePattern> &linePattern);
};

#endif // LINEPATTERNSTORE_H
