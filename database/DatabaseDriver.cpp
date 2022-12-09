#include "DatabaseDriver.h"

DatabaseDriver::DatabaseDriver(const QString &connectionName)
    : m_connectionName{connectionName}
{
    
}

std::unique_ptr<DatabaseDriver> DatabaseDriver::createODBCDriverWithSettings(const std::shared_ptr<DatabaseSettings> &dbSettings)
{     
    // suspended..
    
    return std::unique_ptr<DatabaseDriver>{nullptr};
}

std::unique_ptr<DatabaseDriver> DatabaseDriver::createPSQLDriverWithSettings(const std::shared_ptr<DatabaseSettings> &dbSettings)
{
    // suspended..
    
    return std::unique_ptr<DatabaseDriver>{nullptr};
}

std::unique_ptr<DatabaseDriver> DatabaseDriver::createSQLiteDriverWithSettings(const std::shared_ptr<DatabaseSettings> &dbSettings)
{
    QSqlDatabase db = QSqlDatabase::addDatabase(DatabaseContext::getStringByDatabaseType(DatabaseContext::Type::T_SQLITE));
    
    db.setDatabaseName(dbSettings->getDatabaseName());
    
    if (!db.open()) {
        qInfo() << db.lastError().text();
        
        return std::unique_ptr<DatabaseDriver>{nullptr};
    }
    
    return std::make_unique<DatabaseDriver>(DatabaseDriver(db.connectionName()));
}

std::unique_ptr<DatabaseDriver> DatabaseDriver::createDriverWithSettings(const std::shared_ptr<DatabaseSettings> &dbSettings)
{
    std::unique_ptr<DatabaseDriver> driver{nullptr};
    
    switch (dbSettings->getDatabaseType()) {
    case DatabaseContext::Type::T_ODBC:   {driver = createODBCDriverWithSettings(dbSettings);}
    case DatabaseContext::Type::T_PSQL:   {driver = createPSQLDriverWithSettings(dbSettings);}
    case DatabaseContext::Type::T_SQLITE: {driver = createSQLiteDriverWithSettings(dbSettings);}
    }
    
    return std::move(driver);
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
