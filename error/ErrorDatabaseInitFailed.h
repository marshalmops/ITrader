#ifndef ERRORDATABASEINITFAILED_H
#define ERRORDATABASEINITFAILED_H

#include "ErrorDatabase.h"

class ErrorDatabaseInitFailed : public ErrorDatabase
{
public:
    ErrorDatabaseInitFailed();
    
    ErrorType::ValueType getType() const override;
};

#endif // ERRORDATABASEINITFAILED_H
