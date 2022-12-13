#include "DatabaseManager.h"

std::shared_ptr<DatabaseManager> DatabaseManager::m_instance = std::shared_ptr<DatabaseManager>{nullptr};

DatabaseManager::DatabaseManager(const std::shared_ptr<DatabaseQueryProcessor> &queryProcessor)
    : m_queryProcessor{queryProcessor}
{
    
}

bool DatabaseManager::initWithSettings()
{
    auto settings = SettingsManager::getInstance();
    
    if (!settings.get()) return false;
    
    auto dbSettings = settings->getDatabaseSettings();
    
    if (!dbSettings.get()) return false;
    
    auto driver = DatabaseDriverFabric::createDriverWithSettings(dbSettings);
    
    if (!driver.get()) return false;
    
    std::shared_ptr<DatabaseQueryProcessor> queryProcessor{nullptr};
    
    bool dbQueryProcResult = DatabaseQueryProcessorFabric::createQueryProcessorWithSettings(dbSettings,
                                                                                            std::move(driver),
                                                                                            queryProcessor);
    
    if (!dbQueryProcResult) return false;
    
    m_instance = std::make_shared<DatabaseManager>(DatabaseManager{queryProcessor});
    
    return true;
}

std::shared_ptr<DatabaseManager> DatabaseManager::getInstance()
{
    return m_instance;
}

std::unique_ptr<DatabaseFacadeIntellectualEditor> DatabaseManager::createIntellectualEditorFacade()
{
    return std::make_unique<DatabaseFacadeIntellectualEditor>(m_queryProcessor);
}

std::unique_ptr<DatabaseFacadeTrendSolver> DatabaseManager::createTrendSolverFacade()
{
    return std::make_unique<DatabaseFacadeTrendSolver>(m_queryProcessor);
}
