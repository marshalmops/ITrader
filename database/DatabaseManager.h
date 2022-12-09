#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <memory>

#include "DatabaseManagerTrendSolverInterface.h"
#include "DatabaseManagerIntellectualEditorInterface.h"

#include "queryProcessor/DatabaseQueryProcessorFabric.h"

#include "settings/SettingsManager.h"

class DatabaseManager
        : public DatabaseManagerTrendSolverInterface,
          public DatabaseManagerIntellectualEditorInterface
{
private:
    static std::shared_ptr<DatabaseManager> m_instance;
    
    std::shared_ptr<DatabaseQueryProcessor> m_queryProcessor;
    
    DatabaseManager(std::unique_ptr<DatabaseQueryProcessor> &&queryProcessor);
    
public:
    static bool                                      initWithSettings();
    static std::shared_ptr<DatabaseManagerInterface> getInstance     ();
    
    std::unique_ptr<DatabaseFacadeIntellectualEditor> getDatabaseIntellectualEditorFacade() override;
    std::unique_ptr<DatabaseFacadeTrendSolver>        getDatabaseTrendSolverFacade       () override;

};

#endif // DATABASEMANAGER_H
