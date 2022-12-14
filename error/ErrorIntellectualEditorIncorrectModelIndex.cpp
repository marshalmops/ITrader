#include "ErrorIntellectualEditorIncorrectModelIndex.h"

ErrorIntellectualEditorIncorrectModelIndex::ErrorIntellectualEditorIncorrectModelIndex()
    : ErrorIntellectualEditor{"Incorrect model index has been passed!", true}
{
    
}

ErrorType::ValueType ErrorIntellectualEditorIncorrectModelIndex::getType() const
{
    return ErrorType::IntellectualEditor::IE_INCORRECT_MODEL_INDEX;
}
