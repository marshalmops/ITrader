#ifndef DATABASECONTEXT_H
#define DATABASECONTEXT_H

#include <cstdint>
#include <QString>
#include <QHash>

namespace DatabaseContext {
    enum class Type : uint8_t {
        T_INVALID = 0,
        T_ODBC,
        T_PSQL,
        T_SQLITE,
        T_COUNT
    };
    
    QString getStringByDatabaseType(const Type dbType) {
        static QHash<Type, QString> dbTypeStringHash {
            {Type::T_ODBC,   "QODBC"},
            {Type::T_PSQL,   "QPSQL"},
            {Type::T_SQLITE, "QSQLITE"}
        };
        
        return (dbTypeStringHash.contains(dbType)
              ? dbTypeStringHash.value(dbType)
              : QString());
    }
    
    Type getDatabaseTypeByUInt(const uint32_t typeAsInt) {
        if (typeAsInt <= static_cast<uint8_t>(Type::T_INVALID)
         || typeAsInt >= static_cast<uint8_t>(Type::T_COUNT))
        {
            return Type::T_INVALID;
        }
        
        return static_cast<Type>(typeAsInt);
    }
    
    bool checkDatabaseTypeValidity(const Type type) {
        if (type <= Type::T_INVALID || type >= Type::T_COUNT)
            return false;
        
        return true;
    }
}

#endif // DATABASECONTEXT_H
