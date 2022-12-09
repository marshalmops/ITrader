#ifndef ERRORDATABASE_H
#define ERRORDATABASE_H

#include "Error.h"

class ErrorDatabase : public Error
{
protected:
    ErrorDatabase(const std::string message,
                  bool isCritical);
};

#endif // ERRORDATABASE_H
