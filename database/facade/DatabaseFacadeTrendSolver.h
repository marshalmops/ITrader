#ifndef DATABASEFACADETRENDSOLVER_H
#define DATABASEFACADETRENDSOLVER_H

#include <memory>

#include "DatabaseFacade.h"
#include "../queryProcessor/DatabaseQueryProcessor.h"

class DatabaseFacadeTrendSolver : public DatabaseFacade
{
public:
    DatabaseFacadeTrendSolver(const std::shared_ptr<DatabaseQueryProcessor> &processor);
};

#endif // DATABASEFACADETRENDSOLVER_H
