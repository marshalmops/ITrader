#ifndef DATABASEDRIVER_H
#define DATABASEDRIVER_H

#include <QString>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>

#include "DatabaseContext.h"
#include "../settings/SettingsManager.h"

/*
    THE LOWEST LEVEL on DB layer.
    Making QUERRIES depending on DB TYPE.
*/

class DatabaseDriver
{
private:
    DatabaseDriver(const QString &connectionName = QString{});
    
    static std::unique_ptr<DatabaseDriver> createODBCDriverWithSettings  (const std::shared_ptr<DatabaseSettings> &dbSettings);
    static std::unique_ptr<DatabaseDriver> createPSQLDriverWithSettings  (const std::shared_ptr<DatabaseSettings> &dbSettings);
    static std::unique_ptr<DatabaseDriver> createSQLiteDriverWithSettings(const std::shared_ptr<DatabaseSettings> &dbSettings);
    
public:
    static std::unique_ptr<DatabaseDriver> createDriverWithSettings(const std::shared_ptr<DatabaseSettings> &dbSettings);
    
    bool exec(const QString &queryString,
              std::unique_ptr<QSqlQuery> &queryResult);
    bool exec(const QString &queryString);
    
private:
    QString m_connectionName;
};

#endif // DATABASEDRIVER_H
