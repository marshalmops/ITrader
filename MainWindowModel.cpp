#include "MainWindowModel.h"

MainWindowModel::MainWindowModel(DotTableModel *dotTableModel, 
                                 IntellectualEditorModel *intellectualEditorModel, 
                                 QObject *parent)
    : QObject{parent},
      m_dotTableModel{dotTableModel},
      m_intellectualEditorModel{intellectualEditorModel}
{
    
}

DotTableModel *MainWindowModel::getDotTableModel()
{
    return m_dotTableModel;
}

IntellectualEditorModel *MainWindowModel::getIntellectualEditorModel()
{
    return m_intellectualEditorModel;
}

void MainWindowModel::analyzeDotsFromDotsModel()
{
    emit dotsToAnalyzeGotten(m_dotTableModel->getDots());
}

void MainWindowModel::addDotToModel()
{
    m_dotTableModel->addDot();
}

void MainWindowModel::removeDotFromModel()
{
    m_dotTableModel->removeDot();
}
