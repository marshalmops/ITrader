#include "DatabaseDriver.h"

DatabaseDriver::DatabaseDriver(const QString &connectionName)
    : m_connectionName{connectionName}
{
    
}

bool DatabaseDriver::exec(const QString &queryString,
                          std::unique_ptr<QSqlQuery> &queryResult)
{
    if (queryString.isEmpty()) return false;
    
    QSqlDatabase db = QSqlDatabase::database(m_connectionName);
    
    if (!db.isOpen()) return false;
    
    QSqlQuery query{queryString, db};
    
    if (!query.isValid()) return false;
    
    queryResult = std::make_unique<QSqlQuery>(std::move(query));
    
    if (!queryResult->exec(queryString))
        return false;
    
    return queryResult->lastError().isValid();
}

bool DatabaseDriver::exec(const QString &queryString)
{
    std::unique_ptr<QSqlQuery> queryResult{};
    
    return exec(queryString, queryResult);
}
