#ifndef ERRORDATABASEILLEGALSTATE_H
#define ERRORDATABASEILLEGALSTATE_H

#include "ErrorDatabase.h"

class ErrorDatabaseIllegalState : public ErrorDatabase
{
public:
    ErrorDatabaseIllegalState();
    
    virtual ErrorType::ValueType getType() const override;
};

#endif // ERRORDATABASEILLEGALSTATE_H
