#include "DatabaseDriver_test.h"

DatabaseDriver_test::DatabaseDriver_test(QObject *parent)
    : QObject{parent}
{
    
}

void DatabaseDriver_test::createDriver_test()
{
    std::shared_ptr<DatabaseSettings> dbSettings{std::make_shared<DatabaseSettings>()};
    
    QCOMPARE(dbSettings->load(), true);
    
    auto driver = DatabaseDriverFabric::createDriverWithSettings(dbSettings);
    
    QVERIFY(driver.get() != nullptr);
}

void DatabaseDriver_test::checkDriverWithDefaults_test()
{
    std::shared_ptr<DatabaseSettings> dbSettings{std::make_shared<DatabaseSettings>()};
    
    dbSettings->load();
    
    auto driver = DatabaseDriverFabric::createDriverWithSettings(dbSettings);
    
    std::unique_ptr<QSqlQuery> result{nullptr};
    
    QVERIFY(driver->exec("SELECT * FROM Pattern;", result));
    QVERIFY(result.get() != nullptr);
}

void DatabaseDriver_test::checkSelectQueryWithDefaults_test()
{
    std::shared_ptr<DatabaseSettings> dbSettings{std::make_shared<DatabaseSettings>()};
    
    dbSettings->load();
    
    auto driver = DatabaseDriverFabric::createDriverWithSettings(dbSettings);
    
    std::unique_ptr<QSqlQuery> result{nullptr};
    
    QVERIFY(driver->exec("SELECT * FROM Pattern;", result));
    QVERIFY(result.get() != nullptr);
    
    while (result->next()) {
        QCOMPARE(result->record().count(), 6);
    }
}
