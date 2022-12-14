#include "AppInitializer.h"

bool AppInitializer::initializeApp(std::unique_ptr<AppCore> &appCore,
                                   std::unique_ptr<MainWindowView> &mainWindowView, 
                                   std::unique_ptr<TrendSolver> &trendSolver)
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
    
    DotTableModel *dotsTableModel = new DotTableModel{};

    PatternTableModel     *patternTableModel = new PatternTableModel{};
    LinePatternTableModel *linePatternTableModel = new LinePatternTableModel{};
    
    IntellectualEditorModel *intellectualEditorModel = new IntellectualEditorModel{patternTableModel,
                                                                                   linePatternTableModel,
                                                                                   std::move(intellectualEditorFacade)};
    MainWindowModel *mainWindowModel = new MainWindowModel{dotsTableModel, intellectualEditorModel};
    
    mainWindowView = std::make_unique<MainWindowView>(mainWindowModel);
    
    appCore = std::make_unique<AppCore>();
    
    trendSolver = std::make_unique<TrendSolver>(std::move(trendSolverFacade));
    
//    QObject::connect(mainWindowView.get(), &MainWindowView::analyzeDots, mainWindowModel.get(), &MainWindowModel::analyzeDotsFromDotsModel);
//    QObject::connect(mainWindowView.get(), &MainWindowView::addDot,      mainWindowModel.get(), &MainWindowModel::addDotToModel);
//    QObject::connect(mainWindowView.get(), &MainWindowView::removeDot,   mainWindowModel.get(), &MainWindowModel::removeDotFromModel);
    QObject::connect(mainWindowView.get(), &MainWindowView::errorOccured,    appCore.get(), &AppCore::processError);
    QObject::connect(mainWindowView.get(), &MainWindowView::settingsChanged, appCore.get(), &AppCore::handleSettingsUpdate);
    
    QObject::connect(mainWindowModel, &MainWindowModel::errorOccured,        appCore.get(), &AppCore::processError);
    QObject::connect(mainWindowModel, &MainWindowModel::dotsToAnalyzeGotten, trendSolver.get(), &TrendSolver::analyseDots);
    
    QObject::connect(trendSolver.get(), &TrendSolver::patternGotten, mainWindowView.get(), &MainWindowView::showChoosenPattern);
    QObject::connect(trendSolver.get(), &TrendSolver::errorOccurred, appCore.get(), &AppCore::processError);
    
    //QObject::connect(intellectualEditorView.get(), &IntellectualEditorView::errorOccurred, appCore.get(), &AppCore::processError);
    
    QObject::connect(intellectualEditorModel, &IntellectualEditorModel::errorOccurred, appCore.get(), &AppCore::processError);
    
    QObject::connect(appCore.get(), &AppCore::resetTrendSolverFacade,        trendSolver.get(),       &TrendSolver::resetFacade);
    QObject::connect(appCore.get(), &AppCore::resetIntellectualEditorFacade, intellectualEditorModel, &IntellectualEditorModel::resetFacade);
    
    return true;
}
