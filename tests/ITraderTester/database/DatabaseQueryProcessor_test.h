#ifndef DATABASEQUERYPROCESSOR_TEST_H
#define DATABASEQUERYPROCESSOR_TEST_H

#include <QObject>
#include <QSqlRecord>

#include "../../database/queryProcessor/DatabaseQueryProcessorFabric.h"
#include "../../database/driver/DatabaseDriverFabric.h"

#include "../../pattern/Pattern.h"
#include "../../pattern/LinePattern.h"

class DatabaseQueryProcessor_test : public QObject
{
    Q_OBJECT
public:
    explicit DatabaseQueryProcessor_test(QObject *parent = nullptr);
    
private slots:
    void initTestCase();
    void checkSelectQuery_test();
    void checkInsertQuery_test();
    void checkUpdateQuery_test();
    void checkDeleteQuery_test();
    
private:
    std::shared_ptr<DatabaseSettings>       m_dbSettings;
    std::shared_ptr<DatabaseQueryProcessor> m_queryProcessor;
};

#endif // DATABASEQUERYPROCESSOR_TEST_H
