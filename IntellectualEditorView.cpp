#include "IntellectualEditorView.h"

IntellectualEditorView::IntellectualEditorView(QTableView *patternTableView, 
                                               QTableView *linePatternTableView, 
                                               QWidget *parent)
    : QDialog{parent},
      m_patternTableView{patternTableView},
      m_linePatternTableView{linePatternTableView} // for New Pattern dialog...
{
    
    QLabel *patternListLabel = new QLabel{tr("Patterns:")};
    
    QPushButton *addPatternButton    = new QPushButton{tr("+")};
    QPushButton *removePatternButton = new QPushButton{tr("-")};
    
    QVBoxLayout *patternButtonsLayout = new QVBoxLayout{};
    
    patternButtonsLayout->addWidget(addPatternButton);
    patternButtonsLayout->addWidget(removePatternButton);
    
    QHBoxLayout *patternTableButtonsLayout = new QHBoxLayout{};
    
    patternTableButtonsLayout->addWidget(m_patternTableView);
    patternTableButtonsLayout->addLayout(patternButtonsLayout);
    
    QVBoxLayout *patternsLayout = new QVBoxLayout{};
    
    patternsLayout->addWidget(patternListLabel);
    patternsLayout->addLayout(patternTableButtonsLayout);
    
    QPushButton *backButton = new QPushButton{tr("Back")};
    
    QHBoxLayout *controlButtonsLayout = new QHBoxLayout{};
    
    controlButtonsLayout->addStretch(1);
    controlButtonsLayout->addWidget(backButton);
    
    QVBoxLayout *mainLayout = new QVBoxLayout{};
    
    mainLayout->addLayout(patternsLayout);
    mainLayout->addLayout(controlButtonsLayout);
    
    setLayout(mainLayout);
    
    connect(addPatternButton,    &QPushButton::clicked, this, &IntellectualEditorView::openPatternCreator);
    connect(removePatternButton, &QPushButton::clicked, this, &IntellectualEditorView::deleteSelectedPattern);
    
    connect(backButton, &QPushButton::clicked, this, &IntellectualEditorView::closeEditor);
}

void IntellectualEditorView::openPatternCreator()
{
    
}

void IntellectualEditorView::deleteSelectedPattern()
{
    
}

void IntellectualEditorView::closeEditor()
{
    close();
}

