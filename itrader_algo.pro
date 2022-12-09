TEMPLATE = app
CONFIG += console c++17 sql
CONFIG -= app_bundle

SOURCES += \
        AppCore.cpp \
        AppInitializer.cpp \
        database/driver/DatabaseDriver.cpp \
        database/driver/DatabaseDriverFabric.cpp \
        database/facade/DatabaseFacadeIntellectualEditor.cpp \
        database/facade/DatabaseFacadeTrendSolver.cpp \
        database/DatabaseManager.cpp \
        database/queryProcessor/DatabaseQueryProcessor.cpp \
        database/queryProcessor/DatabaseQueryProcessorFabric.cpp \
        error/ErrorDatabase.cpp \
        error/ErrorDatabaseIllegalState.cpp \
        error/ErrorDatabaseIncorrectQuery.cpp \
        error/ErrorDatabaseInitFailed.cpp \
        error/ErrorDatabaseQueryError.cpp \
        geometry/Dot.cpp \
        error/Error.cpp \
        error/ErrorApp.cpp \
        error/ErrorAppIncorrectBehaviour.cpp \
        error/ErrorSolver.cpp \
        error/ErrorSolverInvalidInputData.cpp \
        IntellectualEditor.cpp \
        geometry/Line.cpp \
        pattern/LinePattern.cpp \
        pattern/LinePatternStore.cpp \
        MainWindowModel.cpp \
        MainWindowView.cpp \
        pattern/Pattern.cpp \
        pattern/PatternLine.cpp \
        settings/DatabaseSettings.cpp \
        settings/SettingsManager.cpp \
        geometry/StageLineContainer.cpp \
        pattern/StagePatternContainer.cpp \
        TrendSolver.cpp \
        main.cpp

HEADERS += \
    AppContext.h \
    AppCore.h \
    AppInitializer.h \
    database/DatabaseContext.h \
    database/driver/DatabaseDriver.h \
    database/driver/DatabaseDriverFabric.h \
    database/facade/DatabaseFacade.h \
    database/facade/DatabaseFacadeIntellectualEditor.h \
    database/facade/DatabaseFacadeTrendSolver.h \
    database/DatabaseManager.h \
    database/DatabaseManagerIntellectualEditorInterface.h \
    database/DatabaseManagerInterface.h \
    database/DatabaseManagerTrendSolverInterface.h \
    database/queryProcessor/DatabaseQueryProcessor.h \
    database/queryProcessor/DatabaseQueryProcessorFabric.h \
    error/ErrorDatabase.h \
    error/ErrorDatabaseIllegalState.h \
    error/ErrorDatabaseIncorrectQuery.h \
    error/ErrorDatabaseInitFailed.h \
    error/ErrorDatabaseQueryError.h \
    geometry/Dot.h \
    error/Error.h \
    error/ErrorApp.h \
    error/ErrorAppIncorrectBehaviour.h \
    error/ErrorSolver.h \
    error/ErrorSolverInvalidInputData.h \
    error/ErrorType.h \
    IntellectualEditor.h \
    geometry/Line.h \
    pattern/DatabaseEntity.h \
    pattern/LinePattern.h \
    pattern/LinePatternStore.h \
    MainWindowModel.h \
    MainWindowView.h \
    pattern/Pattern.h \
    pattern/PatternLine.h \
    settings/DatabaseSettings.h \
    settings/SettingsInterface.h \
    settings/SettingsManager.h \
    geometry/StageLineContainer.h \
    pattern/StagePatternContainer.h \
    TrendSolver.h \
    TrendSolverContext.h

QT += widgets
