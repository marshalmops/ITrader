#ifndef DATABASEMANAGERTRENDSOLVERINTERFACE_H
#define DATABASEMANAGERTRENDSOLVERINTERFACE_H

#include "DatabaseManagerInterface.h"
#include "facade/DatabaseFacadeTrendSolver.h"

class DatabaseManagerTrendSolverInterface
    : virtual public DatabaseManagerInterface 
{
public:
    virtual std::unique_ptr<DatabaseFacadeTrendSolver> getDatabaseTrendSolverFacade() = 0;
};

#endif // DATABASEMANAGERTRENDSOLVERINTERFACE_H
