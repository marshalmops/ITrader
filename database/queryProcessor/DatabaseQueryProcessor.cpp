#include "DatabaseQueryProcessor.h"

namespace {
    QString stringVectorToQStringForSQL(const std::vector<std::string> &stringVector, 
                                        const QString separator = ", ",
                                        const QString wrapper = "")
    {
        if (stringVector.empty()) return QString{};
        
        QString resultString    {};
        auto    stringVectorSize{stringVector.size()};
        
        for (decltype(stringVectorSize) i = 0; i < stringVectorSize; ++i) {
            const auto &curParam = stringVector.at(i);
            
            resultString += (wrapper + curParam.c_str() + wrapper);
            resultString += (i == stringVectorSize - 1 ? " " : separator);
        }
        
        return resultString;
    }
}

QString DatabaseQueryProcessor::orderFlagToString(const OrderFlag order)
{
    static QHash<OrderFlag, QString> orderFlagStringHash = {
        {OrderFlag::OF_ASC, "ASC"},
        {OrderFlag::OF_DESC, "DESC"}
    };
    
    return (orderFlagStringHash.contains(order) 
            ? orderFlagStringHash.value(order) 
            : QString{});
}

DatabaseQueryProcessor::DatabaseQueryProcessor(std::unique_ptr<DatabaseDriver> &&databaseDriver)
    : m_databaseDriver{databaseDriver.release()}
{
    
}

bool DatabaseQueryProcessor::execSelectQuery(const std::vector<std::string> &tableVector,
                                             std::unique_ptr<QSqlQuery> &queryResult,
                                             const std::vector<std::string> &paramVector,
                                             const std::vector<std::string> &conditionVector,
                                             const std::vector<std::pair<std::string, OrderFlag>> &orderParamFlagVector)
{
    if (tableVector.empty()) return false;
    
    QString queryString{"SELECT "};
    
    if (paramVector.empty())
        queryString += "* ";
    else
        queryString += stringVectorToQStringForSQL(paramVector);
    
    queryString += "FROM ";
    queryString += ::stringVectorToQStringForSQL(tableVector);
    
    if (!conditionVector.empty()) {
        queryString += "WHERE ";
        queryString += ::stringVectorToQStringForSQL(conditionVector, " AND ");
    }
    
    if (!orderParamFlagVector.empty()) {
        queryString += "ORDER BY ";
        
        auto orderParamVectorSize = orderParamFlagVector.size();
        
        for (decltype(orderParamVectorSize) i = 0; i < orderParamVectorSize; ++i) {
            const auto &curOrderParam = orderParamFlagVector.at(i);
            
            queryString += (curOrderParam.first.c_str());
            queryString += " ";
            queryString += orderFlagToString(curOrderParam.second);
            queryString += (i == orderParamVectorSize - 1 ? ' ' : ',');
        }
    }
    
    queryString += ";";
    
    return m_databaseDriver->exec(queryString, queryResult);
}

bool DatabaseQueryProcessor::execInsertQuery(const std::string &table,
                                             const std::vector<std::string> &valueVector,
                                             const std::vector<std::string> &paramVector)
{
    if (table.empty() || valueVector.empty())
        return false;
    
    QString queryString{"INSERT INTO "};
    
    queryString += table.c_str();
    
    if (!paramVector.empty()) {
        queryString += "(";
        queryString += ::stringVectorToQStringForSQL(paramVector);
        queryString += ")";
    }
    
    queryString += " VALUES(";
    queryString += ::stringVectorToQStringForSQL(valueVector, ", ", "'");
    queryString += ");";
    
    return m_databaseDriver->exec(queryString);
}

bool DatabaseQueryProcessor::execUpdateQuery(const std::vector<std::string> &tableVector, 
                                             const std::vector<std::pair<std::string, std::string>> &paramValueVector,
                                             const std::vector<std::string> &conditionVector)
{
    if (tableVector.empty() || paramValueVector.empty())
        return false;
    
    QString queryString{"UPDATE "};
    
    queryString += ::stringVectorToQStringForSQL(tableVector);
    queryString += "SET ";
    
    auto paramValueVectorSize{paramValueVector.size()};
    
    for (decltype(paramValueVectorSize) i = 0; i < paramValueVectorSize; ++i) {
        const auto &curParamValue = paramValueVector.at(i);
        
        queryString += curParamValue.first.c_str();
        queryString += " = ";
        queryString += (QString{'\''} + curParamValue.second.c_str() + '\'');
        queryString += (i == paramValueVectorSize - 1 ? ' ' : ',');
    }
    
    if (!conditionVector.empty()) {
        queryString += "WHERE ";
        queryString += ::stringVectorToQStringForSQL(conditionVector, " AND ");
    }
    
    queryString += ";";
    
    return m_databaseDriver->exec(queryString);
}

bool DatabaseQueryProcessor::execDeleteQuery(const std::string &table, 
                                             const std::vector<std::string> &conditionVector)
{
    if (table.empty()) return false;
    
    QString queryString{"DELETE FROM "};
    
    queryString += table.c_str();
    
    if (!conditionVector.empty()) {
        queryString += " WHERE ";
        queryString += ::stringVectorToQStringForSQL(conditionVector, " AND ");
    }
    
    queryString += ";";
    
    return m_databaseDriver->exec(queryString);
}
