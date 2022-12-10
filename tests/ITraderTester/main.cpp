#include <QtTest>

#include "database/DatabaseDriver_test.h"
#include "database/DatabaseQueryProcessor_test.h"

int main(int argc, char *argv[]) {
    
    QTest::qExec(new DatabaseQueryProcessor_test, argc, argv);
    
    return 0;
}
