#ifndef ERRORDATABASEINCORRECTQUERY_H
#define ERRORDATABASEINCORRECTQUERY_H

#include "ErrorDatabase.h"

class ErrorDatabaseIncorrectQuery : public ErrorDatabase
{
public:
    ErrorDatabaseIncorrectQuery();
    
    ErrorType::ValueType getType() const override;
};

#endif // ERRORDATABASEINCORRECTQUERY_H
