#ifndef DATABASEFACADETRENDSOLVER_H
#define DATABASEFACADETRENDSOLVER_H

#include <memory>

#include "DatabaseFacade.h"
#include "../queryProcessor/DatabaseQueryProcessor.h"

class DatabaseFacadeTrendSolver : public DatabaseFacade
{
public:
    DatabaseFacadeTrendSolver(const std::shared_ptr<DatabaseQueryProcessor> &processor);
    
    // TODO: countOfUse update method...
};

#endif // DATABASEFACADETRENDSOLVER_H
