#ifndef SETTINGSVIEW_H
#define SETTINGSVIEW_H

#include <QDialog>

#include "settings/SettingsManager.h"

class SettingsView : public QDialog
{
    Q_OBJECT
public:
    SettingsView(QWidget *parent = nullptr);
    
    virtual int exec() override;
    
public slots:
    
    
private:
    bool m_isSettingsChanged;
};

#endif // SETTINGSVIEW_H
