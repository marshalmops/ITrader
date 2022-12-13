#include "PatternStore.h"

std::shared_ptr<PatternStore> PatternStore::s_store = std::shared_ptr<PatternStore>{nullptr};

PatternStore::PatternStore()
    : m_patterns{}
{
    
}

void PatternStore::init()
{
    if (s_store.get()) return;
    
    s_store = std::make_shared<PatternStore>(PatternStore{});
}

std::shared_ptr<PatternStore> PatternStore::getInstance()
{
    return s_store;
}

const std::vector<std::shared_ptr<Pattern> > &PatternStore::getPatterns() const
{
    return m_patterns;
}

const std::shared_ptr<Pattern> PatternStore::getPatternById(const uint64_t id) const
{
    for (const auto &pattern : m_patterns)
        if (pattern->getId() == id)
            return pattern;
    
    return std::shared_ptr<Pattern>{nullptr};
}

bool PatternStore::addPattern(std::unique_ptr<Pattern> &pattern)
{
    if (!pattern.get()) return false;
    
    for (const auto &curPattern : m_patterns)
        if (curPattern->getId() == pattern->getId())
            return false;
    
    m_patterns.push_back(std::shared_ptr<Pattern>(pattern.release()));
    
    return true;
}

bool PatternStore::setPatterns(std::vector<std::shared_ptr<Pattern> > &patterns)
{
    if (patterns.empty()) return false;
    
    m_patterns = std::move(patterns);
    
    return true;
}
