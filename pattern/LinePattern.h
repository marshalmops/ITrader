#ifndef LINEPATTERN_H
#define LINEPATTERN_H

#include <cstdint>
#include <string>

#include "DatabaseEntity.h"
#include "../geometry/Line.h"

class LinePattern : public DatabaseEntity {
public:
    constexpr static const char* C_DATABASE_TABLE_NAME = "LinePattern";
    
    constexpr static const char* C_DATABASE_ID_PROP    = "id";
    constexpr static const char* C_DATABASE_NAME_PROP  = "name";
    constexpr static const char* C_DATABASE_ANGLE_TYPE = "angleType";
    
    enum class AngleType : uint8_t {
        AT_ZERO = 0,
        AT_NEGATIVE,
        AT_POSITIVE
    };
    
    static LinePattern::AngleType angleTypeFromDirection(const Line::Direction dir);
    
private:
    uint64_t    m_id;
    std::string m_name;
    AngleType   m_angleType;
    
public:
    LinePattern();
    LinePattern(const uint64_t     id, 
                const std::string &name, 
                const AngleType    angleType);
    
    uint64_t           getId       () const;
    const std::string& getName     () const;
    AngleType          getAngleType() const;
    
    virtual bool fillWithVariantsHash(const QHash<QString, QVariant> &stringVariantHash) override;
};

#endif // LINEPATTERN_H
