#ifndef ERRORSOLVERINVALIDINPUTDATA_H
#define ERRORSOLVERINVALIDINPUTDATA_H

#include "ErrorSolver.h"

class ErrorSolverInvalidInputData : public ErrorSolver
{
public:
    ErrorSolverInvalidInputData();
    
    ErrorType::ValueType getType() const override;
};

#endif // ERRORSOLVERINVALIDINPUTDATA_H
