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
    
    queryResult = std::make_unique<QSqlQuery>(db.exec(queryString));
    
    if (queryResult->lastError().isValid()) {
        qInfo() << queryResult->lastError();
        
        return false;
    }
    
    return true;
}

bool DatabaseDriver::exec(const QString &queryString)
{
    std::unique_ptr<QSqlQuery> queryResult{};
    
    return exec(queryString, queryResult);
}
