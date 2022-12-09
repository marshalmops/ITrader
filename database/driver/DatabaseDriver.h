#ifndef DATABASEDRIVER_H
#define DATABASEDRIVER_H

#include <QString>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>

#include "../DatabaseContext.h"
#include "../../settings/SettingsManager.h"

/*
    THE LOWEST LEVEL on DB layer.
    Making QUERRIES depending on DB TYPE.
*/

class DatabaseDriver
{
public:
    DatabaseDriver(const QString &connectionName = QString{});
    
    bool exec(const QString &queryString,
              std::unique_ptr<QSqlQuery> &queryResult);
    bool exec(const QString &queryString);
    
private:
    QString m_connectionName;
};

#endif // DATABASEDRIVER_H
