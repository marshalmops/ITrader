#ifndef INTELLECTUALEDITOR_H
#define INTELLECTUALEDITOR_H

#include <QObject>

#include "error/Error.h"

#include "database/facade/DatabaseFacadeIntellectualEditor.h"

class IntellectualEditor : public QObject
{
    Q_OBJECT
public:
    IntellectualEditor(std::unique_ptr<DatabaseFacadeIntellectualEditor> &&facade,
                       QObject *parent = nullptr);
    
signals:
    void errorOccurred(const std::shared_ptr<Error> error);
    
public slots:
    void resetFacade(std::shared_ptr<DatabaseFacadeIntellectualEditor> facade);
    
private:
    std::unique_ptr<DatabaseFacadeIntellectualEditor> m_facade;
};

#endif // INTELLECTUALEDITOR_H
