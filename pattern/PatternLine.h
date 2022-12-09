#ifndef PATTERNLINE_H
#define PATTERNLINE_H

#include <cstdint>
#include <memory>

#include "../geometry/Line.h"
#include "LinePattern.h"

class PatternLine : public DatabaseEntity {
public:
    constexpr static const char* C_DATABASE_TABLE_NAME = "PatternLine";   
    
    constexpr static const char* C_DATABASE_PATTERN_ID_PROP = "patternID";   
    constexpr static const char* C_DATABASE_LINE_ID_PROP    = "lineID";   
    constexpr static const char* C_DATABASE_LINE_INDEX_PROP = "lineIndex";   
    constexpr static const char* C_DATABASE_LINE_SIDE_PROP  = "lineSide";       
    
private:
    uint64_t   m_index;
    Line::Side m_side;
    
    std::shared_ptr<LinePattern> m_linePattern;
    
public:
    PatternLine();
    PatternLine(const std::shared_ptr<LinePattern> linePattern,
                const uint64_t index,
                const Line::Side side);
    
    const std::shared_ptr<LinePattern>& getLinePattern() const;
    
    uint64_t getIndex() const;
    
    Line::Side getSide() const;
    
    virtual bool fillWithVariantsHash(const QHash<QString, QVariant> &stringVariantHash) override;
};

#endif // PATTERNLINE_H
