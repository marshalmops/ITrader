#include "TrendSolver_test.h"
#include "qtestcase.h"

TrendSolver_test::TrendSolver_test(QObject *parent)
    : QObject{parent}
{
    
}

void TrendSolver_test::initTestCase()
{
    QVERIFY(SettingsManager::init());
    
    QVERIFY(DatabaseManager::initWithSettings());
    
    auto dbManager = DatabaseManager::getInstance();
    
    QVERIFY(dbManager.get() != nullptr);
    
    std::unique_ptr<DatabaseFacadeTrendSolver> facade{dbManager->createTrendSolverFacade()};
    
    QVERIFY(facade.get() != nullptr);
    
    std::vector<std::shared_ptr<LinePattern>> linePatterns{};
    
    QVERIFY(facade->getLinePatterns(linePatterns).get() == nullptr);
    
    LinePatternStore::init();
    
    auto linePatternStore = LinePatternStore::getInstance();
    
    QVERIFY(linePatternStore.get() != nullptr);
    
    QVERIFY(linePatternStore->setLinePatterns(linePatterns));
    
    std::vector<std::shared_ptr<Pattern>> patterns{};
    
    QVERIFY(facade->getPatterns(patterns).get() == nullptr);
    
    PatternStore::init();
    
    auto patternStore = PatternStore::getInstance();
    
    QVERIFY(patternStore.get() != nullptr);
    
    QVERIFY(patternStore->setPatterns(patterns));
    
    m_trendSolver = std::make_unique<TrendSolver>(std::move(facade));
}

void TrendSolver_test::checkKlinToDownDotsAnalyzing_test()
{
    m_dots.clear();
    
    m_dots.push_back(std::make_shared<Dot>(0, 90));
    m_dots.push_back(std::make_shared<Dot>(0, 85));
    m_dots.push_back(std::make_shared<Dot>(0, 80));
    m_dots.push_back(std::make_shared<Dot>(0, 75));
    m_dots.push_back(std::make_shared<Dot>(0, 80));
    m_dots.push_back(std::make_shared<Dot>(0, 85));
    m_dots.push_back(std::make_shared<Dot>(0, 75));
    m_dots.push_back(std::make_shared<Dot>(0, 73));
    m_dots.push_back(std::make_shared<Dot>(0, 70));
    m_dots.push_back(std::make_shared<Dot>(0, 67));
    
    m_dots.push_back(std::make_shared<Dot>(0, 19));
    m_dots.push_back(std::make_shared<Dot>(1, 29));
    m_dots.push_back(std::make_shared<Dot>(2, 40));
    m_dots.push_back(std::make_shared<Dot>(3, 52));
    m_dots.push_back(std::make_shared<Dot>(4, 63));
    m_dots.push_back(std::make_shared<Dot>(5, 73));
    m_dots.push_back(std::make_shared<Dot>(6, 85));
    m_dots.push_back(std::make_shared<Dot>(7, 96));
    m_dots.push_back(std::make_shared<Dot>(8, 89));
    m_dots.push_back(std::make_shared<Dot>(9, 75));
    m_dots.push_back(std::make_shared<Dot>(10, 58));
    m_dots.push_back(std::make_shared<Dot>(11, 42));
    m_dots.push_back(std::make_shared<Dot>(12, 27));
    m_dots.push_back(std::make_shared<Dot>(13, 10));
    m_dots.push_back(std::make_shared<Dot>(14, 2));
    m_dots.push_back(std::make_shared<Dot>(15, 9));
    m_dots.push_back(std::make_shared<Dot>(16, 15));
    m_dots.push_back(std::make_shared<Dot>(17, 23));
    m_dots.push_back(std::make_shared<Dot>(18, 29));
    m_dots.push_back(std::make_shared<Dot>(19, 35));
    
    m_trendSolver->analyseDots(m_dots);
}

void TrendSolver_test::checkTriangleToDownDotsAnalyzing_test()
{
    m_dots.clear();    
    
    m_dots.push_back(std::make_shared<Dot>(0, 90));
    m_dots.push_back(std::make_shared<Dot>(0, 85));
    m_dots.push_back(std::make_shared<Dot>(0, 80));
    m_dots.push_back(std::make_shared<Dot>(0, 75));
    m_dots.push_back(std::make_shared<Dot>(0, 80));
    m_dots.push_back(std::make_shared<Dot>(0, 85));
    m_dots.push_back(std::make_shared<Dot>(0, 75));
    m_dots.push_back(std::make_shared<Dot>(0, 73));
    m_dots.push_back(std::make_shared<Dot>(0, 70));
    m_dots.push_back(std::make_shared<Dot>(0, 67));
    
    m_dots.push_back(std::make_shared<Dot>(0, 0));
    m_dots.push_back(std::make_shared<Dot>(1, 29));
    m_dots.push_back(std::make_shared<Dot>(2, 40));
    m_dots.push_back(std::make_shared<Dot>(3, 52));
    m_dots.push_back(std::make_shared<Dot>(4, 63));
    m_dots.push_back(std::make_shared<Dot>(5, 73));
    m_dots.push_back(std::make_shared<Dot>(6, 85));
    m_dots.push_back(std::make_shared<Dot>(7, 96));
    m_dots.push_back(std::make_shared<Dot>(8, 89));
    m_dots.push_back(std::make_shared<Dot>(9, 75));
    m_dots.push_back(std::make_shared<Dot>(10, 58));
    m_dots.push_back(std::make_shared<Dot>(11, 42));
    m_dots.push_back(std::make_shared<Dot>(12, 27));
    m_dots.push_back(std::make_shared<Dot>(13, 10));
    m_dots.push_back(std::make_shared<Dot>(14, 2));
    m_dots.push_back(std::make_shared<Dot>(15, 9));
    m_dots.push_back(std::make_shared<Dot>(16, 15));
    m_dots.push_back(std::make_shared<Dot>(17, 23));
    m_dots.push_back(std::make_shared<Dot>(18, 29));
    m_dots.push_back(std::make_shared<Dot>(19, 0));
    
    m_trendSolver->analyseDots(m_dots);
}

void TrendSolver_test::checkIncorrectPrevTrendDotsAnalyzing_test()
{
    m_dots.clear();
    
    m_dots.push_back(std::make_shared<Dot>(0, 0));
    m_dots.push_back(std::make_shared<Dot>(0, 0));
    m_dots.push_back(std::make_shared<Dot>(0, 0));
    m_dots.push_back(std::make_shared<Dot>(0, 0));
    m_dots.push_back(std::make_shared<Dot>(0, 0));
    m_dots.push_back(std::make_shared<Dot>(0, 0));
    m_dots.push_back(std::make_shared<Dot>(0, 0));
    m_dots.push_back(std::make_shared<Dot>(0, 0));
    m_dots.push_back(std::make_shared<Dot>(0, 0));
    m_dots.push_back(std::make_shared<Dot>(0, 0));
    
    m_dots.push_back(std::make_shared<Dot>(0, 19));
    m_dots.push_back(std::make_shared<Dot>(1, 29));
    m_dots.push_back(std::make_shared<Dot>(2, 40));
    m_dots.push_back(std::make_shared<Dot>(3, 52));
    m_dots.push_back(std::make_shared<Dot>(4, 63));
    m_dots.push_back(std::make_shared<Dot>(5, 73));
    m_dots.push_back(std::make_shared<Dot>(6, 85));
    m_dots.push_back(std::make_shared<Dot>(7, 96));
    m_dots.push_back(std::make_shared<Dot>(8, 89));
    m_dots.push_back(std::make_shared<Dot>(9, 75));
    m_dots.push_back(std::make_shared<Dot>(10, 58));
    m_dots.push_back(std::make_shared<Dot>(11, 42));
    m_dots.push_back(std::make_shared<Dot>(12, 27));
    m_dots.push_back(std::make_shared<Dot>(13, 10));
    m_dots.push_back(std::make_shared<Dot>(14, 2));
    m_dots.push_back(std::make_shared<Dot>(15, 9));
    m_dots.push_back(std::make_shared<Dot>(16, 15));
    m_dots.push_back(std::make_shared<Dot>(17, 23));
    m_dots.push_back(std::make_shared<Dot>(18, 29));
    m_dots.push_back(std::make_shared<Dot>(19, 35));
    
    m_trendSolver->analyseDots(m_dots);
}

void TrendSolver_test::checkIncorrectDotsAnalyzing_test()
{
    
}
