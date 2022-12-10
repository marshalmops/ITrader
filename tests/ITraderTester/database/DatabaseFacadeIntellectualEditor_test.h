#ifndef DATABASEFACADEINTELLECTUALEDITOR_TEST_H
#define DATABASEFACADEINTELLECTUALEDITOR_TEST_H

#include <QObject>

#include "../../settings/DatabaseSettings.h"
#include "../../database/driver/DatabaseDriverFabric.h"
#include "../../database/queryProcessor/DatabaseQueryProcessorFabric.h"
#include "../../database/facade/DatabaseFacadeIntellectualEditor.h"

class DatabaseFacadeIntellectualEditor_test : public QObject
{
    Q_OBJECT
public:
    explicit DatabaseFacadeIntellectualEditor_test(QObject *parent = nullptr);
    
private slots:
    void initTestCase();
    void checkPatternInsert_test();
    void checkPatternDelete_test();
    
private:
    std::unique_ptr<DatabaseFacadeIntellectualEditor> m_dbFacade;
    std::vector<std::shared_ptr<Pattern>> m_patterns;
};

#endif // DATABASEFACADEINTELLECTUALEDITOR_TEST_H
