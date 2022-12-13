#ifndef PATTERNSTORE_H
#define PATTERNSTORE_H

#include <memory>
#include <vector>

#include "Pattern.h"

class PatternStore
{
private:
    static std::shared_ptr<PatternStore> s_store;
    
    std::vector<std::shared_ptr<Pattern>> m_patterns;
    
    PatternStore();
    
public:
    static void init();
    
    static std::shared_ptr<PatternStore> getInstance();
    
    const std::vector<std::shared_ptr<Pattern>>& getPatterns() const;
    
    const std::shared_ptr<Pattern> getPatternById(const uint64_t id) const;
    
    bool addPattern  (std::unique_ptr<Pattern> &pattern);
    bool setPatterns(std::vector<std::shared_ptr<Pattern>> &patterns);
};

#endif // PATTERNSTORE_H
