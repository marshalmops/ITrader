#ifndef DATABASEFACADEINTELLECTUALEDITOR_H
#define DATABASEFACADEINTELLECTUALEDITOR_H

#include "DatabaseFacade.h"

#include "pattern/Pattern.h"
#include "pattern/LinePattern.h"

class DatabaseFacadeIntellectualEditor : public DatabaseFacade
{
public:
    DatabaseFacadeIntellectualEditor(const std::shared_ptr<DatabaseQueryProcessor> &processor);
    
    bool getPatterns(std::vector<std::shared_ptr<Pattern>> &patterns);
    bool getLinePatterns(std::vector<std::shared_ptr<LinePattern>> &patterns);
    
    bool insertPattern(const std::shared_ptr<Pattern> &pattern);
    bool deletePattern(const std::shared_ptr<Pattern> &pattern);
};

#endif // DATABASEFACADEINTELLECTUALEDITOR_H
