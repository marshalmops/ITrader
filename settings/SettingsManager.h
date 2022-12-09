#ifndef APPSETTINGS_H
#define APPSETTINGS_H

#include <memory>
#include <QCoreApplication>

#include "AppContext.h"
#include "DatabaseSettings.h"

class SettingsManager
{
private:
    static std::shared_ptr<SettingsManager> m_instance;
    
    std::shared_ptr<DatabaseSettings> m_dbSettings;
    
private:
    SettingsManager();
    
public:
    static bool init();
    static std::shared_ptr<SettingsManager> getInstance();
    
    std::shared_ptr<DatabaseSettings> getDatabaseSettings() const;
    
};

#endif // APPSETTINGS_H
