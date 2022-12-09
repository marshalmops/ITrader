#include "SettingsManager.h"

std::shared_ptr<SettingsManager> SettingsManager::m_instance = std::shared_ptr<SettingsManager>{nullptr};

SettingsManager::SettingsManager()
    : m_dbSettings{std::make_shared<DatabaseSettings>()}
{
    
}

bool SettingsManager::init()
{
    if (!m_instance.get()) return true;
    
    m_instance = std::make_shared<SettingsManager>();
    
    QCoreApplication::setOrganizationName(AppContext::C_ORGANIZATION_NAME);
    QCoreApplication::setOrganizationDomain(AppContext::C_ORGANIZATION_DOMAIN);
    QCoreApplication::setApplicationName(AppContext::C_APPLICATION_NAME);
    
    // initialization:
    // initializing DatabaseSettings...
    
    return (m_instance->m_dbSettings->load());
}

std::shared_ptr<SettingsManager> SettingsManager::getInstance()
{
    return m_instance;
}

std::shared_ptr<DatabaseSettings> SettingsManager::getDatabaseSettings() const
{
    return m_dbSettings;
}
