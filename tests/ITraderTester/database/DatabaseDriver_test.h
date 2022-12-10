#ifndef DATABASEDRIVER_TEST_H
#define DATABASEDRIVER_TEST_H

#include <QObject>
#include <QTest>
#include <QSqlRecord>

#include "../../settings/DatabaseSettings.h"

#include "../../database/DatabaseContext.h"
#include "../../database/driver/DatabaseDriverFabric.h"

class DatabaseDriver_test : public QObject
{
    Q_OBJECT
public:
    explicit DatabaseDriver_test(QObject *parent = nullptr);
    
signals:
    
private slots:
    void initTestCase();
    void checkDriverWithDefaults_test();
    void checkSelectQueryWithDefaults_test();
    
private:
    std::shared_ptr<DatabaseSettings> m_dbSettings;
    std::unique_ptr<DatabaseDriver> m_dbDriver;
};

#endif // DATABASEDRIVER_TEST_H
