QT += testlib sql
QT += gui
CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

SOURCES +=  \
            database/DatabaseDriver_test.cpp \
            ../../settings/DatabaseSettings.cpp \
            ../../database/driver/DatabaseDriverFabric.cpp \
            ../../database/driver/DatabaseDriver.cpp \
            main.cpp

HEADERS += \
    database/DatabaseDriver_test.h \
    ../../settings/DatabaseSettings.h \
    ../../database/driver/DatabaseDriverFabric.h \
    ../../database/driver/DatabaseDriver.h


