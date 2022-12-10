QT += testlib sql
QT += gui
CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

SOURCES +=  \
            database/DatabaseDriver_test.cpp \
            ../../pattern/Pattern.cpp \
            ../../pattern/LinePattern.cpp \
            ../../pattern/PatternLine.cpp \
            ../../settings/DatabaseSettings.cpp \
            ../../database/driver/DatabaseDriverFabric.cpp \
            ../../database/driver/DatabaseDriver.cpp \
            ../../database/queryProcessor/DatabaseQueryProcessor.cpp \
            ../../database/queryProcessor/DatabaseQueryProcessorFabric.cpp \
            database/DatabaseQueryProcessor_test.cpp \
            main.cpp

HEADERS += \
    database/DatabaseDriver_test.h \
    ../../TrendSolverContext.h \
    ../../pattern/Pattern.h \
    ../../pattern/LinePattern.h \
    ../../pattern/PatternLine.h \
    ../../settings/DatabaseSettings.h \
    ../../database/driver/DatabaseDriverFabric.h \
    ../../database/driver/DatabaseDriver.h \
    ../../database/queryProcessor/DatabaseQueryProcessor.h \
    ../../database/queryProcessor/DatabaseQueryProcessorFabric.h \
    database/DatabaseQueryProcessor_test.h


