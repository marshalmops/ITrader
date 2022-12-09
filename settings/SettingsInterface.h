#ifndef SETTINGSINTERFACE_H
#define SETTINGSINTERFACE_H

#include <QSettings>

class SettingsInterface {
public:
    virtual bool save() = 0;
    virtual bool load() = 0;
    
protected:
    virtual bool restoreDefaults() = 0;
};

#endif // SETTINGSINTERFACE_H
