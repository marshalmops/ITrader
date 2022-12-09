#include "ErrorDatabaseQueryError.h"

ErrorDatabaseQueryError::ErrorDatabaseQueryError()
    : ErrorDatabase{"Database query error!", true}
{
    
}

ErrorType::ValueType ErrorDatabaseQueryError::getType() const
{
    return ErrorType::Database::D_QUERY_ERROR;
}
