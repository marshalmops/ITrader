#ifndef DATABASEQUERYPROCESSOR_H
#define DATABASEQUERYPROCESSOR_H

#include "../DatabaseDriver.h"

/*
    MIDDLE-LEVELED abstraction class.
    Creating SELECT, UPDATE, DELETE and INSERT querries' strings.
*/

class DatabaseQueryProcessor
{
public:
    enum class OrderFlag : uint8_t {
        OF_ASC = 0,
        OF_DESC
    };
    
    static QString orderFlagToString(const OrderFlag order);
    
public:
    DatabaseQueryProcessor(std::unique_ptr<DatabaseDriver> &&databaseDriver);
    
    virtual bool execSelectQuery(const std::vector<std::string> &tableVector,
                                 std::unique_ptr<QSqlQuery> &queryResult,
                                 const std::vector<std::string> &paramVector = std::vector<std::string>{},
                                 const std::vector<std::string> &conditionVector = std::vector<std::string>{},
                                 const std::vector<std::pair<std::string, OrderFlag>> &orderParamFlagVector = std::vector<std::pair<std::string, OrderFlag>>{});
    virtual bool execInsertQuery(const std::string &table,
                                 const std::vector<std::string> &valueVector,
                                 const std::vector<std::string> &paramVector = std::vector<std::string>{});
    virtual bool execUpdateQuery(const std::vector<std::string> &tableVector,
                                 const std::vector<std::pair<std::string, std::string>> &paramValueVector,
                                 const std::vector<std::string> &conditionVector = std::vector<std::string>{});
    virtual bool execDeleteQuery(const std::string &table,
                                 const std::vector<std::string> &conditionVector = std::vector<std::string>{});
    
private:
    std::unique_ptr<DatabaseDriver> m_databaseDriver;
};

#endif // DATABASEQUERYPROCESSOR_H
