#ifndef ERRORDATABASEQUERYERROR_H
#define ERRORDATABASEQUERYERROR_H

#include "ErrorDatabase.h"

class ErrorDatabaseQueryError : public ErrorDatabase
{
public:
    ErrorDatabaseQueryError();
    
    ErrorType::ValueType getType() const override;
};

#endif // ERRORDATABASEQUERYERROR_H
