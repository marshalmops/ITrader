#ifndef DATABASEMANAGERINTELLECTUALEDITORINTERFACE_H
#define DATABASEMANAGERINTELLECTUALEDITORINTERFACE_H

#include <memory>

#include "DatabaseManagerInterface.h"
#include "facade/DatabaseFacadeIntellectualEditor.h"

class DatabaseManagerIntellectualEditorInterface
        : virtual public DatabaseManagerInterface
{
public:
    virtual std::unique_ptr<DatabaseFacadeIntellectualEditor> getDatabaseIntellectualEditorFacade() = 0;
};

#endif // DATABASEMANAGERINTELLECTUALEDITORINTERFACE_H
