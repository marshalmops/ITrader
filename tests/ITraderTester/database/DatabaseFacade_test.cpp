#include "DatabaseFacade_test.h"
#include "qtestcase.h"

DatabaseFacade_test::DatabaseFacade_test(QObject *parent)
    : QObject{parent}
{
    
}

void DatabaseFacade_test::initTestCase()
{
    std::shared_ptr<DatabaseSettings> dbSettings{std::make_shared<DatabaseSettings>()};
    
    dbSettings->load();
    
    auto driver = DatabaseDriverFabric::createDriverWithSettings(dbSettings);
    
    QVERIFY(driver.get() != nullptr);
    
    std::shared_ptr<DatabaseQueryProcessor> queryProcessor{nullptr};
    
    QVERIFY(DatabaseQueryProcessorFabric::createQueryProcessorWithSettings(dbSettings, std::move(driver), queryProcessor));
    
    std::unique_ptr<DatabaseFacade> dbFacade{std::make_unique<DatabaseFacade>(queryProcessor)};
    
    QVERIFY(dbFacade.get() != nullptr);
    
    m_dbFacade = std::move(dbFacade);
}

void DatabaseFacade_test::checkLinePatternsGetting_test()
{
    std::vector<std::shared_ptr<LinePattern>> linePatterns{};
    
    QVERIFY(m_dbFacade->getLinePatterns(linePatterns).get() == nullptr);
    
    // filling line pattern store...
    
    LinePatternStore::init();
    
    auto linePatternStore = LinePatternStore::getInstance();
    
    QVERIFY(linePatternStore.get() != nullptr);
    QVERIFY(linePatternStore->setLinePatterns(linePatterns));
}

void DatabaseFacade_test::checkPatternsGetting_test()
{
    std::vector<std::shared_ptr<Pattern>> patterns{};
    
    QVERIFY(m_dbFacade->getPatterns(patterns).get() == nullptr);
}

void DatabaseFacade_test::checkPatternGettingById_test()
{
    uint64_t patternToLoadId{1};
    std::shared_ptr<Pattern> pattern{};
    
    QVERIFY(m_dbFacade->getPatternById(patternToLoadId, pattern).get() == nullptr);
    QVERIFY(pattern->getId() == patternToLoadId);
}
