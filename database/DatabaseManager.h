#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <memory>

#include "driver/DatabaseDriverFabric.h"
#include "queryProcessor/DatabaseQueryProcessorFabric.h"
#include "facade/DatabaseFacadeIntellectualEditor.h"
#include "facade/DatabaseFacadeTrendSolver.h"

#include "../settings/SettingsManager.h"

class DatabaseManager
{
private:
    static std::shared_ptr<DatabaseManager> m_instance;
    
    std::shared_ptr<DatabaseQueryProcessor> m_queryProcessor;
    
    DatabaseManager(const std::shared_ptr<DatabaseQueryProcessor> &queryProcessor);
    
public:
    static bool                             initWithSettings();
    static std::shared_ptr<DatabaseManager> getInstance     ();
    
    std::unique_ptr<DatabaseFacadeIntellectualEditor> createIntellectualEditorFacade();
    std::unique_ptr<DatabaseFacadeTrendSolver>        createTrendSolverFacade();
};

#endif // DATABASEMANAGER_H
