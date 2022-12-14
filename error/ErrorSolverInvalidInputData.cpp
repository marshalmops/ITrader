#include "ErrorSolverInvalidInputData.h"


ErrorSolverInvalidInputData::ErrorSolverInvalidInputData()
    : ErrorSolver{"Invalid input data has been occurred!", false}
{
    
}

ErrorType::ValueType ErrorSolverInvalidInputData::getType() const
{
    return ErrorType::Solver::S_INVALID_INPUT_DATA;
}
