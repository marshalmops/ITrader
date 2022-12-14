TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle

SOURCES += \
        AppCore.cpp \
        AppInitializer.cpp \
        DotTableModel.cpp \
        IntellectualEditorModel.cpp \
        IntellectualEditorView.cpp \
        LinePatternChooserDialog.cpp \
        LinePatternTableModel.cpp \
        MainWindowView.cpp \
        PatternEditorDialog.cpp \
        PatternTableModel.cpp \
        SettingsView.cpp \
        database/driver/DatabaseDriver.cpp \
        database/driver/DatabaseDriverFabric.cpp \
        database/facade/DatabaseFacade.cpp \
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
        error/ErrorIntellectualEditor.cpp \
        error/ErrorIntellectualEditorIncorrectModelIndex.cpp \
        geometry/Dot.cpp \
        error/Error.cpp \
        error/ErrorApp.cpp \
        error/ErrorAppIncorrectBehaviour.cpp \
        error/ErrorSolver.cpp \
        error/ErrorSolverInvalidInputData.cpp \
        geometry/Line.cpp \
        pattern/LinePattern.cpp \
        pattern/LinePatternStore.cpp \
        MainWindowModel.cpp \
        pattern/Pattern.cpp \
        pattern/PatternLine.cpp \
        pattern/PatternStore.cpp \
        pattern/StagePatternLineContainer.cpp \
        qcustomplot/qcustomplot.cpp \
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
    DotTableModel.h \
    IntellectualEditorModel.h \
    IntellectualEditorView.h \
    LinePatternChooserDialog.h \
    LinePatternTableModel.h \
    MainWindowView.h \
    PatternEditorDialog.h \
    PatternTableModel.h \
    SettingsView.h \
    database/DatabaseContext.h \
    database/driver/DatabaseDriver.h \
    database/driver/DatabaseDriverFabric.h \
    database/facade/DatabaseFacade.h \
    database/facade/DatabaseFacadeIntellectualEditor.h \
    database/facade/DatabaseFacadeTrendSolver.h \
    database/DatabaseManager.h \
    database/queryProcessor/DatabaseQueryProcessor.h \
    database/queryProcessor/DatabaseQueryProcessorFabric.h \
    error/ErrorDatabase.h \
    error/ErrorDatabaseIllegalState.h \
    error/ErrorDatabaseIncorrectQuery.h \
    error/ErrorDatabaseInitFailed.h \
    error/ErrorDatabaseQueryError.h \
    error/ErrorIntellectualEditor.h \
    error/ErrorIntellectualEditorIncorrectModelIndex.h \
    geometry/Dot.h \
    error/Error.h \
    error/ErrorApp.h \
    error/ErrorAppIncorrectBehaviour.h \
    error/ErrorSolver.h \
    error/ErrorSolverInvalidInputData.h \
    error/ErrorType.h \
    geometry/Line.h \
    pattern/DatabaseEntity.h \
    pattern/LinePattern.h \
    pattern/LinePatternStore.h \
    MainWindowModel.h \
    pattern/Pattern.h \
    pattern/PatternLine.h \
    pattern/PatternStore.h \
    pattern/StagePatternLineContainer.h \
    qcustomplot/qcustomplot.h \
    settings/DatabaseSettings.h \
    settings/SettingsInterface.h \
    settings/SettingsManager.h \
    geometry/StageLineContainer.h \
    pattern/StagePatternContainer.h \
    TrendSolver.h \
    TrendSolverContext.h

QT += widgets sql printsupport
