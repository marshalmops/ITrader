#ifndef DATABASEDRIVERFABRIC_H
#define DATABASEDRIVERFABRIC_H

#include "DatabaseDriver.h"

class DatabaseDriverFabric
{
public:
    DatabaseDriverFabric() = delete;
    
public:
    static std::unique_ptr<DatabaseDriver> createDriverWithSettings(const std::shared_ptr<DatabaseSettings> &dbSettings);
    
private:
    static std::unique_ptr<DatabaseDriver> createODBCDriverWithSettings  (const std::shared_ptr<DatabaseSettings> &dbSettings);
    static std::unique_ptr<DatabaseDriver> createPSQLDriverWithSettings  (const std::shared_ptr<DatabaseSettings> &dbSettings);
    static std::unique_ptr<DatabaseDriver> createSQLiteDriverWithSettings(const std::shared_ptr<DatabaseSettings> &dbSettings);
    
};

#endif // DATABASEDRIVERFABRIC_H
