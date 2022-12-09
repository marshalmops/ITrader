#ifndef ERRORAPP_H
#define ERRORAPP_H

#include "Error.h"

class ErrorApp : public Error
{
protected:
    ErrorApp(const std::string message,
             bool isCritical);
};

#endif // ERRORAPP_H
