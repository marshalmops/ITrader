#ifndef DATABASEFACADEINTELLECTUALEDITOR_H
#define DATABASEFACADEINTELLECTUALEDITOR_H

#include "DatabaseFacade.h"

class DatabaseFacadeIntellectualEditor : public DatabaseFacade
{
public:
    DatabaseFacadeIntellectualEditor(const std::shared_ptr<DatabaseQueryProcessor> &processor);
    
    bool insertPattern(const std::shared_ptr<Pattern> &pattern);
    bool deletePattern(const std::shared_ptr<Pattern> &pattern);
};

#endif // DATABASEFACADEINTELLECTUALEDITOR_H
