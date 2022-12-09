#include "DatabaseSettings.h"

DatabaseSettings::DatabaseSettings()
    : m_dbType      {DatabaseContext::Type::T_INVALID},
      m_hostName    {QString()},
      m_databaseName{QString()},
      m_userName    {QString()},
      m_password    {QString()},
      m_port        {-1}
{
          
}
    
DatabaseSettings::DatabaseSettings(const DatabaseContext::Type type,
                                   const QString &hostName,
                                   const QString &databaseName, 
                                   const QString &userName,
                                   const QString &password, 
                                   const int port)
    : m_dbType      {type},
      m_hostName    {hostName},
      m_databaseName{databaseName},
      m_userName    {userName},
      m_password    {password},
      m_port        {port}
{
    
}

bool DatabaseSettings::setDatabaseType(const DatabaseContext::Type type)
{
    if (!DatabaseContext::checkDatabaseTypeValidity(type))
        return false;
    
    m_dbType = type;
    
    return true;
}

bool DatabaseSettings::setHostName(const QString &hostName)
{
    if (hostName.isEmpty()) return false;
    
    m_hostName = hostName;
    
    return true;
}

bool DatabaseSettings::setDatabaseName(const QString &databaseName)
{
    if (databaseName.isEmpty()) return false;
    
    m_databaseName = databaseName;
    
    return true;
}

bool DatabaseSettings::setUserName(const QString &userName)
{
    if (userName.isEmpty()) return false;
    
    m_userName = userName;
    
    return true;
}

bool DatabaseSettings::setPassword(const QString &password)
{
    if (password.isEmpty()) return false;
    
    m_password = password;
    
    return true;
}

bool DatabaseSettings::setPort(const int port)
{
    if (port <= 0) return false;
    
    m_port = port;
    
    return true;
}

const DatabaseContext::Type DatabaseSettings::getDatabaseType() const
{
    return m_dbType;
}

const QString &DatabaseSettings::getHostName() const
{
    return m_hostName;
}

const QString &DatabaseSettings::getDatabaseName() const
{
    return m_databaseName;
}

const QString &DatabaseSettings::getUserName() const
{
    return m_userName;
}

const QString &DatabaseSettings::getPasswordName() const
{
    return m_password;
}

int DatabaseSettings::getPort() const
{
    return m_port;
}

bool DatabaseSettings::save()
{
    QSettings settings{};
    
    settings.beginGroup(C_SETTINGS_GROUP);
    
    settings.setValue(C_DATABASE_TYPE_PROP, QVariant::fromValue(m_dbType));
    settings.setValue(C_HOST_NAME_PROP,     QVariant::fromValue(m_hostName));
    settings.setValue(C_DATABASE_NAME_PROP, QVariant::fromValue(m_databaseName));
    settings.setValue(C_USER_NAME_PROP,     QVariant::fromValue(m_userName));
    settings.setValue(C_PASSWORD_PROP,      QVariant::fromValue(m_password));
    settings.setValue(C_PORT_PROP,          QVariant::fromValue(m_port));
    
    settings.endGroup();
    
    return true;
}

bool DatabaseSettings::load()
{
    QSettings settings{};
    
    settings.beginGroup(C_SETTINGS_GROUP);
    
    if (!settings.contains(C_DATABASE_TYPE_PROP)
     || !settings.contains(C_HOST_NAME_PROP)
     || !settings.contains(C_DATABASE_NAME_PROP)
     || !settings.contains(C_USER_NAME_PROP)
     || !settings.contains(C_PASSWORD_PROP)
     || !settings.contains(C_PORT_PROP))
    {
        return restoreDefaults();
    }
    
    QVariant typeVariant     = settings.value(C_DATABASE_TYPE_PROP);
    QVariant hostVariant     = settings.value(C_HOST_NAME_PROP);
    QVariant dbNameVariant   = settings.value(C_DATABASE_NAME_PROP);
    QVariant userNameVariant = settings.value(C_USER_NAME_PROP);
    QVariant passwordVariant = settings.value(C_PASSWORD_PROP);
    QVariant portVariant     = settings.value(C_PORT_PROP);
    
    settings.endGroup();
    
    if (!typeVariant.isValid()
     || !hostVariant.isValid()
     || !dbNameVariant.isValid()
     || !userNameVariant.isValid()
     || !passwordVariant.isValid()
     || !portVariant.isValid()) 
    {
        return restoreDefaults();
    }
    
    bool     checkConv   {false};
    uint32_t rawTypeAsInt{typeVariant.toUInt(&checkConv)};
    
    if (!checkConv) return false;
    
    DatabaseContext::Type typeBuffer{DatabaseContext::getDatabaseTypeByUInt(rawTypeAsInt)};
    
    if (typeBuffer == DatabaseContext::Type::T_INVALID)
        return false;
    
    uint16_t rawPort = portVariant.toUInt(&checkConv);
    
    if (!checkConv) return false;
    
    m_dbType       = typeBuffer;
    m_hostName     = hostVariant.toString();
    m_databaseName = dbNameVariant.toString();
    m_userName     = userNameVariant.toString();
    m_password     = passwordVariant.toString();
    m_port         = rawPort;
    
    return true;
}

bool DatabaseSettings::restoreDefaults()
{
    m_dbType       = C_DEFAULT_DATABASE_TYPE;
    m_hostName     = C_DEFAULT_HOST_NAME;
    m_databaseName = C_DEFAULT_DATABASE_NAME;
    m_userName     = C_DEFAULT_USER_NAME;
    m_password     = C_DEFAULT_PASSWORD_NAME;
    m_port         = C_DEFAULT_PORT;
    
    return true;
}


