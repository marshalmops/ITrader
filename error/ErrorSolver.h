#ifndef ERRORSOLVER_H
#define ERRORSOLVER_H

#include "Error.h"

class ErrorSolver : public Error
{
protected:
    ErrorSolver(const std::string message,
                bool isCritical);
};

#endif // ERRORSOLVER_H
