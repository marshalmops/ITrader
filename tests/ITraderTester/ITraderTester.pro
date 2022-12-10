QT += testlib sql
QT += gui
CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

SOURCES +=  \
            database/DatabaseDriver_test.cpp \
            ../../pattern/Pattern.cpp \
            ../../pattern/LinePattern.cpp \
            ../../pattern/PatternLine.cpp \
            ../../pattern/LinePatternStore.cpp \
            ../../settings/DatabaseSettings.cpp \
            ../../database/driver/DatabaseDriverFabric.cpp \
            ../../database/driver/DatabaseDriver.cpp \
            ../../database/queryProcessor/DatabaseQueryProcessor.cpp \
            ../../database/queryProcessor/DatabaseQueryProcessorFabric.cpp \
            ../../error/ErrorDatabase.cpp \
            ../../error/ErrorDatabaseIllegalState.cpp \
            ../../error/ErrorDatabaseIncorrectQuery.cpp \
            ../../error/ErrorDatabaseInitFailed.cpp \
            ../../error/ErrorDatabaseQueryError.cpp \
            ../../error/Error.cpp \
            ../../error/ErrorApp.cpp \
            ../../error/ErrorAppIncorrectBehaviour.cpp \
            ../../error/ErrorSolver.cpp \
            ../../error/ErrorSolverInvalidInputData.cpp \
            ../../database/facade/DatabaseFacade.cpp \
            ../../database/facade/DatabaseFacadeIntellectualEditor.cpp \
            database/DatabaseFacadeIntellectualEditor_test.cpp \
            database/DatabaseFacade_test.cpp \
            database/DatabaseQueryProcessor_test.cpp \
            main.cpp

HEADERS += \
    database/DatabaseDriver_test.h \
    ../../TrendSolverContext.h \
    ../../pattern/Pattern.h \
    ../../pattern/LinePattern.h \
    ../../pattern/PatternLine.h \
    ../../pattern/LinePatternStore.h \
    ../../settings/DatabaseSettings.h \
    ../../database/driver/DatabaseDriverFabric.h \
    ../../database/driver/DatabaseDriver.h \
    ../../database/queryProcessor/DatabaseQueryProcessor.h \
    ../../database/queryProcessor/DatabaseQueryProcessorFabric.h \
    ../../error/ErrorDatabase.h \
    ../../error/ErrorDatabaseIllegalState.h \
    ../../error/ErrorDatabaseIncorrectQuery.h \
    ../../error/ErrorDatabaseInitFailed.h \
    ../../error/ErrorDatabaseQueryError.h \
    ../../error/Error.h \
    ../../error/ErrorApp.h \
    ../../error/ErrorAppIncorrectBehaviour.h \
    ../../error/ErrorSolver.h \
    ../../error/ErrorSolverInvalidInputData.h \
    ../../database/facade/DatabaseFacade.h \
    ../../database/facade/DatabaseFacadeIntellectualEditor.h \
    database/DatabaseFacadeIntellectualEditor_test.h \
    database/DatabaseFacade_test.h \
    database/DatabaseQueryProcessor_test.h


