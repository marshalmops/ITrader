#include "MainWindowModel.h"

MainWindowModel::MainWindowModel(DotTableModel *dotTableModel, 
                                 QObject *parent)
    : QObject{parent},
      m_dotTableModel{dotTableModel}
{
    
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
