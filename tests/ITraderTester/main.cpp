#include <QtTest>

#include "database/DatabaseDriver_test.h"

int main(int argc, char *argv[]) {
    
    QTest::qExec(new DatabaseDriver_test, argc, argv);
    
    return 0;
}
