#ifndef DATABASEFACADE_TEST_H
#define DATABASEFACADE_TEST_H

#include <QObject>

#include "../../settings/DatabaseSettings.h"
#include "../../database/driver/DatabaseDriverFabric.h"
#include "../../database/queryProcessor/DatabaseQueryProcessorFabric.h"
#include "../../database/facade/DatabaseFacade.h"

class DatabaseFacade_test : public QObject
{
    Q_OBJECT
public:
    explicit DatabaseFacade_test(QObject *parent = nullptr);
    
private slots:
    void initTestCase();
    void checkLinePatternsGetting_test();
    void checkPatternsGetting_test();
    void checkPatternGettingById_test();
    
private:
    std::unique_ptr<DatabaseFacade> m_dbFacade;
};

#endif // DATABASEFACADE_TEST_H
