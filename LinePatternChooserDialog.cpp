#include "LinePatternChooserDialog.h"

LinePatternChooserDialog::LinePatternChooserDialog(LinePatternTableModel *linePatternTableModel,
                                                   std::shared_ptr<LinePattern> &linePattern,
                                                   QWidget *parent)
    : QDialog{parent},
      m_linePattern{linePattern},
      m_linePatternTableModel{linePatternTableModel}
{
    QLabel *linePatternTableLabel = new QLabel{tr("Line Patterns:")}; 
    
    m_linePatternTableView = new QTableView{};
    
    m_linePatternTableView->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
    m_linePatternTableView->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
    m_linePatternTableView->setModel(m_linePatternTableModel);
    
    QVBoxLayout *linePatternTableLayout = new QVBoxLayout{};
    
    linePatternTableLayout->addWidget(linePatternTableLabel);
    linePatternTableLayout->addWidget(m_linePatternTableView);
    
    QPushButton *cancelButton  = new QPushButton{tr("Cancel")};
    QPushButton *confirmButton = new QPushButton{tr("Confirm")};
    
    QHBoxLayout *dialogButtonsLayout = new QHBoxLayout{};
    
    dialogButtonsLayout->addStretch(1);
    dialogButtonsLayout->addWidget(confirmButton);
    dialogButtonsLayout->addWidget(cancelButton);
    
    QVBoxLayout *mainLayout = new QVBoxLayout{};
    
    mainLayout->addLayout(linePatternTableLayout);
    mainLayout->addLayout(dialogButtonsLayout);
    
    setLayout(mainLayout);
    
    connect(cancelButton,  &QPushButton::clicked, this, &LinePatternChooserDialog::cancel);
    connect(confirmButton, &QPushButton::clicked, this, &LinePatternChooserDialog::confirm);
}

void LinePatternChooserDialog::cancel()
{
    reject();
}

void LinePatternChooserDialog::confirm()
{
    QModelIndex linePatternIndex{m_linePatternTableView->currentIndex()};
    
    if (!linePatternIndex.isValid()) {
        QMessageBox::warning(this, tr("Error!"), tr("Choose the line pattern!"));
        
        return;
    }
    
    std::shared_ptr<LinePattern> linePattern{};
    
    if (!m_linePatternTableModel->getLinePatternByIndex(linePatternIndex.row(), linePattern)) {
        // error handling?
        
        return;
    }
    
    m_linePattern = linePattern;
    
    accept();
}
