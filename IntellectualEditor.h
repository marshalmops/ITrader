#ifndef INTELLECTUALEDITOR_H
#define INTELLECTUALEDITOR_H

#include <QObject>

#include "database/DatabaseManager.h"

class IntellectualEditor : public QObject
{
    Q_OBJECT
public:
    IntellectualEditor(QObject *parent = nullptr);
    
signals:
    void knowledgeBaseChanged(); // lets to PATTERNS RELOADING...
};

#endif // INTELLECTUALEDITOR_H
