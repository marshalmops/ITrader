#include "IntellectualEditor.h"

IntellectualEditor::IntellectualEditor(std::unique_ptr<DatabaseFacadeIntellectualEditor> &&facade, 
                                       QObject *parent)
    : QObject{parent},
      m_facade{facade.release()}
{
    
}

void IntellectualEditor::resetFacade(std::shared_ptr<DatabaseFacadeIntellectualEditor> facade)
{
    m_facade = std::make_unique<DatabaseFacadeIntellectualEditor>(std::move(*facade));
}
