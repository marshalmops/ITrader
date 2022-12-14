#ifndef ERRORINTELLECTUALEDITOR_H
#define ERRORINTELLECTUALEDITOR_H

#include "Error.h"

class ErrorIntellectualEditor : public Error
{
public:
    ErrorIntellectualEditor(const std::string message,
                            bool isCritical);
};

#endif // ERRORINTELLECTUALEDITOR_H
