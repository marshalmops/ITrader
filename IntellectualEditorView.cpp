#include "IntellectualEditorView.h"

IntellectualEditorView::IntellectualEditorView(IntellectualEditorModel *model,
                                               QWidget *parent)
    : QDialog{parent},
      m_model{model}
{
    resize(640, 250);
    
    m_model->setParent(this);
    
    QLabel *patternListLabel = new QLabel{tr("Patterns:")};
    
    QPushButton *addPatternButton    = new QPushButton{tr("+")};
    QPushButton *removePatternButton = new QPushButton{tr("-")};
    
    QVBoxLayout *patternButtonsLayout = new QVBoxLayout{};
    
    patternButtonsLayout->addWidget(addPatternButton);
    patternButtonsLayout->addWidget(removePatternButton);
    patternButtonsLayout->addStretch(1);
    
    m_patternTableView = new QTableView{};
    
    m_patternTableView->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
    m_patternTableView->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);

    m_patternTableView->setModel(m_model->getPatternTableModel());
    
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
    std::shared_ptr<Pattern> newPattern{};
    
    PatternEditorDialog *patternEditor = new PatternEditorDialog{m_model->getLinePatternTableModel(), newPattern, this};
    
    patternEditor->prepareModels();
    
    if (patternEditor->exec() == QDialog::DialogCode::Rejected)
        return;
    
    m_model->insertNewPattern(newPattern);
}

void IntellectualEditorView::deleteSelectedPattern()
{
    QModelIndex curIndex = m_patternTableView->currentIndex();
    
    if (!curIndex.isValid()) {
        QMessageBox::warning(this, tr("Error!"), tr("Choose some pattern before removing!"));
        
        return;
    }
    
    auto pressedButton = QMessageBox::question(this, 
                                               tr("Confirmation"), 
                                               tr("Are you sure to delete the selected pattern?"));
    
    if (pressedButton != QMessageBox::StandardButton::Yes) return;
    
    m_model->deleteSelectedPattern(m_patternTableView->currentIndex().row());
}

void IntellectualEditorView::closeEditor()
{
    close();
}

int IntellectualEditorView::exec()
{
    m_model->prepareModels();
    
    return QDialog::exec();
}

