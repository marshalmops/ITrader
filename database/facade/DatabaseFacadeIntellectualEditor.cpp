#include "DatabaseFacadeIntellectualEditor.h"


DatabaseFacadeIntellectualEditor::DatabaseFacadeIntellectualEditor(const std::shared_ptr<DatabaseQueryProcessor> &processor)
    : DatabaseFacade{processor}
{
    
}

bool DatabaseFacadeIntellectualEditor::insertPattern(const std::shared_ptr<Pattern> &pattern)
{
    
    
    return m_processor->execInsertQuery();
}
