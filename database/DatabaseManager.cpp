#include "DatabaseManager.h"

std::shared_ptr<DatabaseManager> DatabaseManager::m_instance = std::shared_ptr<DatabaseManager>{nullptr};

DatabaseManager::DatabaseManager(std::unique_ptr<DatabaseQueryProcessor> &&queryProcessor)
    : m_queryProcessor{std::shared_ptr<DatabaseQueryProcessor>(queryProcessor.release())}
{
    
}

bool DatabaseManager::initWithSettings()
{
    auto settings = SettingsManager::getInstance();
    
    if (!settings.get()) return false;
    
    auto dbSettings = settings->getDatabaseSettings();
    
    if (!dbSettings.get()) return false;
    
    auto driver = DatabaseDriver::createDriverWithSettings(dbSettings);
    
    if (!driver.get()) return false;
    
    std::unique_ptr<DatabaseQueryProcessor> queryProcessor{nullptr};
    
    bool dbQueryProcResult = DatabaseQueryProcessorFabric::createQueryProcessorWithSettings(dbSettings,
                                                                                            std::move(driver),
                                                                                            queryProcessor);
    
    if (!dbQueryProcResult) return false;
    
    m_instance = std::make_shared<DatabaseManager>(std::move(queryProcessor));
    
    return true;
}

std::shared_ptr<DatabaseManagerInterface> DatabaseManager::getInstance()
{
    return m_instance;
}

std::unique_ptr<DatabaseFacadeIntellectualEditor> DatabaseManager::getDatabaseIntellectualEditorFacade()
{
    return std::make_unique<DatabaseFacadeIntellectualEditor>(m_queryProcessor);
}

std::unique_ptr<DatabaseFacadeTrendSolver> DatabaseManager::getDatabaseTrendSolverFacade()
{
    return std::make_unique<DatabaseFacadeTrendSolver>(m_queryProcessor);
}
