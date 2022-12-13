#include "AppInitializer.h"

bool AppInitializer::initializeApp(std::unique_ptr<AppCore> &appCore,
                                   std::unique_ptr<MainWindowView> &mainWindowView, 
                                   std::unique_ptr<MainWindowModel> &mainWindowModel,
                                   std::unique_ptr<TrendSolver> &trendSolver,
                                   std::unique_ptr<IntellectualEditor> &intellectualEditor)
{
    // basic init:
    
    if (!SettingsManager::init())
        return false;
    
    if (!DatabaseManager::initWithSettings())
        return false;
    
    auto dbManager = DatabaseManager::getInstance();
    
    std::unique_ptr<DatabaseFacadeTrendSolver>        trendSolverFacade       {dbManager->createTrendSolverFacade()};
    std::unique_ptr<DatabaseFacadeIntellectualEditor> intellectualEditorFacade{dbManager->createIntellectualEditorFacade()};
    
    if (!trendSolverFacade.get() || !intellectualEditorFacade.get())
        return false;
    
    std::vector<std::shared_ptr<LinePattern>> linePatterns{};
    
    if (trendSolverFacade->getLinePatterns(linePatterns).get())
        return false;
    
    LinePatternStore::init();
    
    auto linePatternStore = LinePatternStore::getInstance();
    
    if (!linePatternStore->setLinePatterns(linePatterns))
        return false;
    
    std::vector<std::shared_ptr<Pattern>> patterns{};
    
    if (trendSolverFacade->getPatterns(patterns).get())
        return false;
    
    PatternStore::init();
    
    auto patternStore = PatternStore::getInstance();
    
    if (!patternStore->setPatterns(patterns))
        return false;
    
    // init. modules:
    
    QTableView    *dotsTableView  = new QTableView{};
    DotTableModel *dotsTableModel = new DotTableModel{};
    
    dotsTableView->setModel(dotsTableModel);
    
    mainWindowView  = std::make_unique<MainWindowView>(dotsTableView);
    mainWindowModel = std::make_unique<MainWindowModel>(dotsTableModel);
    
    appCore = std::make_unique<AppCore>();
    
    trendSolver        = std::make_unique<TrendSolver>(std::move(trendSolverFacade));
    intellectualEditor = std::make_unique<IntellectualEditor>(std::move(intellectualEditorFacade));
    
    // connecting components...
    
    // mainWindowView -> mainWindowModel:
    
    QObject::connect(mainWindowView.get(), &MainWindowView::analyzeDots, mainWindowModel.get(), &MainWindowModel::analyzeDotsFromDotsModel);
    QObject::connect(mainWindowView.get(), &MainWindowView::addDot, mainWindowModel.get(), &MainWindowModel::addDotToModel);
    QObject::connect(mainWindowView.get(), &MainWindowView::removeDot, mainWindowModel.get(), &MainWindowModel::removeDotFromModel);
    
    // mainWindowModel -> mainWindowView:
    
    
    
    // mainWindowModel -> trendSolver:
    
    QObject::connect(mainWindowModel.get(), &MainWindowModel::dotsToAnalyzeGotten, trendSolver.get(), &TrendSolver::analyseDots);
    
    // trendSolver -> mainWindowView:
    
    QObject::connect(trendSolver.get(), &TrendSolver::patternGotten, mainWindowView.get(), &MainWindowView::showChoosenPattern);
    
    // errors to AppCore:
    
    
    
    return true;
}
