#include "LinePatternStore.h"

std::shared_ptr<LinePatternStore> LinePatternStore::s_store = std::shared_ptr<LinePatternStore>{nullptr};

LinePatternStore::LinePatternStore()
    : m_linePatterns{}
{
    
}

void LinePatternStore::init() {
    if (!s_store.get())
        s_store = std::make_shared<LinePatternStore>(LinePatternStore());
}

std::shared_ptr<LinePatternStore> LinePatternStore::getInstance() {
    return s_store;
}

const std::vector<std::shared_ptr<LinePattern>>& LinePatternStore::getLinePatterns() const {
    return m_linePatterns;
}

const std::shared_ptr<LinePattern> LinePatternStore::getLinePatternById(const uint64_t id) const {
    for (const auto& linePattern : m_linePatterns)
        if (linePattern->getId() == id) return linePattern;
    
    return std::shared_ptr<LinePattern>(nullptr);
}

const std::shared_ptr<LinePattern> LinePatternStore::getLinePatternByAngleType(const LinePattern::AngleType angleType) const {
    for (const auto& linePattern : m_linePatterns)
        if (linePattern->getAngleType() == angleType) return linePattern;
    
    return std::shared_ptr<LinePattern>(nullptr);
}

bool LinePatternStore::addLinePattern(std::unique_ptr<LinePattern> &linePattern) {
    if (!linePattern.get()) return false;
    
    for (int i = 0; i < m_linePatterns.size(); ++i) {
        if (m_linePatterns.at(i)->getId()   == linePattern->getId()
         || m_linePatterns.at(i)->getName() == linePattern->getName())
        {
            return false;
        }
    }
    
    m_linePatterns.push_back(std::shared_ptr<LinePattern>(linePattern.release()));
    
    return true;
}

bool LinePatternStore::initLinePatterns(std::vector<std::shared_ptr<LinePattern> > &linePatterns)
{
    if (!m_linePatterns.empty()) return false;
    
    m_linePatterns = std::move(linePatterns);
    
    return true;
}
