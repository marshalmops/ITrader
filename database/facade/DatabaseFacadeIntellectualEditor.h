#ifndef DATABASEFACADEINTELLECTUALEDITOR_H
#define DATABASEFACADEINTELLECTUALEDITOR_H

#include "DatabaseFacade.h"

class DatabaseFacadeIntellectualEditor : public DatabaseFacade
{
public:
    DatabaseFacadeIntellectualEditor(const std::shared_ptr<DatabaseQueryProcessor> &processor);
    
    std::unique_ptr<ErrorDatabase> insertPattern(const std::shared_ptr<Pattern> &pattern);
    std::unique_ptr<ErrorDatabase> deletePattern(const std::shared_ptr<Pattern> &pattern);
    
private:
    std::unique_ptr<ErrorDatabase> getPatternByNameAndTrends(const std::string &name,
                                                             const Pattern::Trend prevTrend,
                                                             const Pattern::Trend futureTrend,
                                                             std::shared_ptr<Pattern> &gottenPattern);
    std::unique_ptr<ErrorDatabase> insertLineOfPattern(const PatternLine &patternLine,
                                                       const std::shared_ptr<Pattern> &pattern);
};

#endif // DATABASEFACADEINTELLECTUALEDITOR_H
