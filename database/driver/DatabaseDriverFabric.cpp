#include "DatabaseDriverFabric.h"

std::unique_ptr<DatabaseDriver> DatabaseDriverFabric::createODBCDriverWithSettings(const std::shared_ptr<DatabaseSettings> &dbSettings)
{     
    // suspended..
    
    return std::unique_ptr<DatabaseDriver>{nullptr};
}

std::unique_ptr<DatabaseDriver> DatabaseDriverFabric::createPSQLDriverWithSettings(const std::shared_ptr<DatabaseSettings> &dbSettings)
{
    // suspended..
    
    return std::unique_ptr<DatabaseDriver>{nullptr};
}

std::unique_ptr<DatabaseDriver> DatabaseDriverFabric::createSQLiteDriverWithSettings(const std::shared_ptr<DatabaseSettings> &dbSettings)
{
    QSqlDatabase db = QSqlDatabase::addDatabase(DatabaseContext::getStringByDatabaseType(DatabaseContext::Type::T_SQLITE));
    
    db.setDatabaseName(dbSettings->getDatabaseName());
    
    if (!db.open()) {
        qInfo() << db.lastError().text();
        
        return std::unique_ptr<DatabaseDriver>{nullptr};
    }
    
    return std::make_unique<DatabaseDriver>(DatabaseDriver(db.connectionName()));
}

std::unique_ptr<DatabaseDriver> DatabaseDriverFabric::createDriverWithSettings(const std::shared_ptr<DatabaseSettings> &dbSettings)
{
    std::unique_ptr<DatabaseDriver> driver{nullptr};
    
    switch (dbSettings->getDatabaseType()) {
    case DatabaseContext::Type::T_ODBC:   {driver = createODBCDriverWithSettings(dbSettings);}
    case DatabaseContext::Type::T_PSQL:   {driver = createPSQLDriverWithSettings(dbSettings);}
    case DatabaseContext::Type::T_SQLITE: {driver = createSQLiteDriverWithSettings(dbSettings);}
    }
    
    return std::move(driver);
}
