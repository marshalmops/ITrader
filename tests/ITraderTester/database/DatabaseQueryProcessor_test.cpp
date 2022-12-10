#include "DatabaseQueryProcessor_test.h"
#include "qtestcase.h"

DatabaseQueryProcessor_test::DatabaseQueryProcessor_test(QObject *parent)
    : QObject{parent}
{
    
}

void DatabaseQueryProcessor_test::initTestCase()
{
    std::shared_ptr<DatabaseSettings> dbSettings{std::make_shared<DatabaseSettings>()};
    
    dbSettings->load();
    
    m_dbSettings = dbSettings;
    
    auto driver = DatabaseDriverFabric::createDriverWithSettings(dbSettings);
    
    QVERIFY(driver.get() != nullptr);
    
    std::shared_ptr<DatabaseQueryProcessor> queryProcessor{nullptr};
    
    QVERIFY(DatabaseQueryProcessorFabric::createQueryProcessorWithSettings(dbSettings, std::move(driver), queryProcessor));
    
    m_queryProcessor = queryProcessor;
}

void DatabaseQueryProcessor_test::checkSelectQuery_test()
{
    std::unique_ptr<QSqlQuery> queryResult{};
    
    QVERIFY(m_queryProcessor->execSelectQuery({"Pattern"}, queryResult));
    QVERIFY(queryResult.get() != nullptr);
    
    while (queryResult->next()) {
        QCOMPARE(queryResult->record().count(), 6);
    }
}

void DatabaseQueryProcessor_test::checkInsertQuery_test()
{
    QString testPatternName{"testPattern"};
    
    std::vector<std::string> valueVector{testPatternName.toStdString(), "1", "2"};
    std::vector<std::string> paramVector{Pattern::C_DATABASE_NAME_PROP, 
                Pattern::C_DATABASE_PREV_TREND_PROP,
                Pattern::C_DATABASE_FUTURE_TREND_PROP};
    
    QVERIFY(m_queryProcessor->execInsertQuery(Pattern::C_DATABASE_TABLE_NAME, valueVector, paramVector));
    
    std::unique_ptr<QSqlQuery> queryResult{};
    
    QVERIFY(m_queryProcessor->execSelectQuery({Pattern::C_DATABASE_TABLE_NAME}, queryResult));
    QVERIFY(queryResult.get() != nullptr);
    
    bool isInserted{false};
    
    while (queryResult->next()) {
        QVariant patternNameVariant{queryResult->value(Pattern::C_DATABASE_NAME_PROP)};
        
        QVERIFY(patternNameVariant.isValid());
        QVERIFY(patternNameVariant.typeId() == QMetaType::Type::QString);
        
        QString patternName{patternNameVariant.toString()};
        
        if (patternName == testPatternName) {
            isInserted = true;
            
            break;
        }
    }
    
    QVERIFY(isInserted);
}

void DatabaseQueryProcessor_test::checkUpdateQuery_test()
{
    QString testPatternName{"updatedPattern"};
    
    std::vector<std::string> tableVector{Pattern::C_DATABASE_TABLE_NAME};
    std::vector<std::pair<std::string, std::string>> paramValueVector{
        {Pattern::C_DATABASE_NAME_PROP, testPatternName.toStdString()}
    };
    std::vector<std::string> conditionVector{"name = 'testPattern'"};
    
    QVERIFY(m_queryProcessor->execUpdateQuery(tableVector, paramValueVector, conditionVector));
    
    std::unique_ptr<QSqlQuery> queryResult{};
    
    QVERIFY(m_queryProcessor->execSelectQuery({Pattern::C_DATABASE_TABLE_NAME}, queryResult));
    QVERIFY(queryResult.get() != nullptr);
    
    bool isUpdated{false};
    
    while (queryResult->next()) {
        QVariant patternNameVariant{queryResult->value(Pattern::C_DATABASE_NAME_PROP)};
        
        QVERIFY(patternNameVariant.isValid());
        QVERIFY(patternNameVariant.typeId() == QMetaType::Type::QString);
        
        QString patternName{patternNameVariant.toString()};
        
        if (patternName == testPatternName) {
            isUpdated = true;
            
            break;
        }
    }
    
    QVERIFY(isUpdated);
}

void DatabaseQueryProcessor_test::checkDeleteQuery_test()
{
    QString patternToDeleteName{"updatedPattern"};
    
    std::vector<std::string> conditionVector{"name = \'" + patternToDeleteName.toStdString() + '\''};
    
    QVERIFY(m_queryProcessor->execDeleteQuery(Pattern::C_DATABASE_TABLE_NAME, conditionVector));
    
    std::unique_ptr<QSqlQuery> queryResult{};
    
    QVERIFY(m_queryProcessor->execSelectQuery({Pattern::C_DATABASE_TABLE_NAME}, queryResult));
    QVERIFY(queryResult.get() != nullptr);
    
    bool isDeleted{true};
    
    while (queryResult->next()) {
        QVariant patternNameVariant{queryResult->value(Pattern::C_DATABASE_NAME_PROP)};
        
        QVERIFY(patternNameVariant.isValid());
        QVERIFY(patternNameVariant.typeId() == QMetaType::Type::QString);
        
        QString patternName{patternNameVariant.toString()};
        
        if (patternName == patternToDeleteName) {
            isDeleted = false;
            
            break;
        }
    }
    
    QVERIFY(isDeleted);
}


