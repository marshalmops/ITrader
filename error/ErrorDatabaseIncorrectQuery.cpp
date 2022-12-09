#include "ErrorDatabaseIncorrectQuery.h"

ErrorDatabaseIncorrectQuery::ErrorDatabaseIncorrectQuery()
    : ErrorDatabase{"Database query is incorrect!", false}
{
    
}

ErrorType::ValueType ErrorDatabaseIncorrectQuery::getType() const
{
    return ErrorType::Database::D_INCORRECT_QUERY;
}
