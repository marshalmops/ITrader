#ifndef DATABASEFACADETRENDSOLVER_H
#define DATABASEFACADETRENDSOLVER_H

#include <memory>

#include "DatabaseFacade.h"
#include "../queryProcessor/DatabaseQueryProcessor.h"

#include "pattern/Pattern.h"
#include "pattern/LinePattern.h"
#include "pattern/PatternLine.h"

#include "../../error/ErrorDatabaseQueryError.h"
#include "../../error/ErrorDatabaseIncorrectQuery.h"
#include "../../error/ErrorDatabaseIllegalState.h"

class DatabaseFacadeTrendSolver : public DatabaseFacade
{
public:
    DatabaseFacadeTrendSolver(const std::shared_ptr<DatabaseQueryProcessor> &processor);
    
    std::unique_ptr<ErrorDatabase> getLinePatterns(std::vector<LinePattern> &linePatterns);
    std::unique_ptr<ErrorDatabase> getPatterns    (const std::vector<LinePattern> &linePatterns,
                                                   std::vector<Pattern> &patterns);
};

#endif // DATABASEFACADETRENDSOLVER_H
