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
    
public slots:
    void createDriver_test();
    void checkDriverWithDefaults_test();
    
private slots:
    void checkSelectQueryWithDefaults_test();
};

#endif // DATABASEDRIVER_TEST_H
