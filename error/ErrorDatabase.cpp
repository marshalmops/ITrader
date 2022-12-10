#include "ErrorDatabase.h"

ErrorDatabase::ErrorDatabase(const std::string message,
                             bool isCritical)
    : Error{message, isCritical}
{
    
}
