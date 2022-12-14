#include "IntellectualEditorModel.h"

IntellectualEditorModel::IntellectualEditorModel(PatternTableModel *patternTableModel, 
                                                 LinePatternTableModel *linePatternTableModel, 
                                                 std::unique_ptr<DatabaseFacadeIntellectualEditor> &&facade, 
                                                 QObject *parent)
    : QObject{parent},
      m_patternTableModel{patternTableModel},
      m_linePatternTableModel{linePatternTableModel},
      m_facade{facade.release()}
{
    
}

void IntellectualEditorModel::resetFacade(std::shared_ptr<DatabaseFacadeIntellectualEditor> facade)
{
    m_facade = std::make_unique<DatabaseFacadeIntellectualEditor>(std::move(*facade));
}
