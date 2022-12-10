#include "DatabaseDriver_test.h"

DatabaseDriver_test::DatabaseDriver_test(QObject *parent)
    : QObject{parent}
{
    
}

void DatabaseDriver_test::initTestCase()
{
    std::shared_ptr<DatabaseSettings> dbSettings{std::make_shared<DatabaseSettings>()};
    
    QCOMPARE(dbSettings->load(), true);
    
    m_dbSettings = dbSettings;
    
    auto driver = DatabaseDriverFabric::createDriverWithSettings(dbSettings);
    
    QVERIFY(driver.get() != nullptr);
    
    m_dbDriver = std::move(driver);
}

void DatabaseDriver_test::checkDriverWithDefaults_test()
{
    std::unique_ptr<QSqlQuery> result{nullptr};
    
    QVERIFY(m_dbDriver->exec("SELECT * FROM Pattern;", result));
    QVERIFY(result.get() != nullptr);
}

void DatabaseDriver_test::checkSelectQueryWithDefaults_test()
{
    std::unique_ptr<QSqlQuery> result{nullptr};
    
    QVERIFY(m_dbDriver->exec("SELECT * FROM Pattern;", result));
    QVERIFY(result.get() != nullptr);
    
    while (result->next()) {
        QCOMPARE(result->record().count(), 6);
    }
}
