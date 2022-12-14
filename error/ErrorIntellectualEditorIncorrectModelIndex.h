#ifndef ERRORINTELLECTUALEDITORINCORRECTMODELINDEX_H
#define ERRORINTELLECTUALEDITORINCORRECTMODELINDEX_H

#include "ErrorIntellectualEditor.h"

class ErrorIntellectualEditorIncorrectModelIndex : public ErrorIntellectualEditor
{
public:
    ErrorIntellectualEditorIncorrectModelIndex();
    
    virtual ErrorType::ValueType getType() const override;
};

#endif // ERRORINTELLECTUALEDITORINCORRECTMODELINDEX_H
