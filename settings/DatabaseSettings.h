#ifndef DATABASESETTINGS_H
#define DATABASESETTINGS_H

#include "database/DatabaseContext.h"
#include "SettingsInterface.h"

class DatabaseSettings : public SettingsInterface
{
public:
    constexpr static const char* C_SETTINGS_GROUP = "database";
    
    constexpr static const char* C_DATABASE_TYPE_PROP = "DATABASE_TYPE";
    constexpr static const char* C_HOST_NAME_PROP     = "HOST_NAME";
    constexpr static const char* C_DATABASE_NAME_PROP = "DATABASE_NAME";
    constexpr static const char* C_USER_NAME_PROP     = "USER_NAME";
    constexpr static const char* C_PASSWORD_PROP      = "PASSWORD";
    constexpr static const char* C_PORT_PROP          = "PORT";
    
    constexpr static const DatabaseContext::Type C_DEFAULT_DATABASE_TYPE = DatabaseContext::Type::T_SQLITE;
    constexpr static const char*    C_DEFAULT_HOST_NAME     = "";
    constexpr static const char*    C_DEFAULT_DATABASE_NAME = "database.db";
    constexpr static const char*    C_DEFAULT_USER_NAME     = "";
    constexpr static const char*    C_DEFAULT_PASSWORD_NAME = "";
    constexpr static const uint16_t C_DEFAULT_PORT          = 0;
    
private:
    DatabaseContext::Type m_dbType;
    
    QString m_hostName;
    QString m_databaseName;
    QString m_userName;
    QString m_password;
    int     m_port;
    
public:
    DatabaseSettings();
    DatabaseSettings(const DatabaseContext::Type type,
                     const QString &hostName,
                     const QString &databaseName,
                     const QString &userName,
                     const QString &password,
                     const int     port);
    
    bool setDatabaseType(const DatabaseContext::Type type);
    bool setHostName    (const QString &hostName);
    bool setDatabaseName(const QString &hostName);
    bool setUserName    (const QString &hostName);
    bool setPassword    (const QString &hostName);
    bool setPort        (const int port);
    
    const DatabaseContext::Type getDatabaseType() const;
    const QString&              getHostName    () const;
    const QString&              getDatabaseName() const;
    const QString&              getUserName    () const;
    const QString&              getPasswordName() const;
    int                         getPort        () const;

    bool save() override;
    bool load() override;
    
protected:
    bool restoreDefaults() override;
};

#endif // DATABASESETTINGS_H
