#include <QtTest>

#include "database/DatabaseDriver_test.h"
#include "database/DatabaseQueryProcessor_test.h"
#include "database/DatabaseFacade_test.h"
#include "database/DatabaseFacadeIntellectualEditor_test.h"

#include "module/TrendSolver_test.h"

int main(int argc, char *argv[]) {
    
    QTest::qExec(new TrendSolver_test, argc, argv);
    
    return 0;
}
