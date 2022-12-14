#include "PatternEditorDialog.h"

PatternEditorDialog::PatternEditorDialog(LinePatternTableModel *const linePatternTableModel,
                                         std::shared_ptr<Pattern> &pattern,
                                         QWidget *parent)
    : QDialog{parent},
      m_pattern{pattern},
      m_linePatternTableModel{linePatternTableModel}
{
    QLabel *nameLabel        = new QLabel{tr("Name:")};
    QLabel *probabilityLabel = new QLabel{tr("Probability:")};
    QLabel *prevTrendLabel   = new QLabel{tr("Prev. trend:")};
    QLabel *futureTrendLabel = new QLabel{tr("Future trend:")};
    
    QVBoxLayout *smallControlsLabelsLayout = new QVBoxLayout{};
    
    smallControlsLabelsLayout->addWidget(nameLabel);
    smallControlsLabelsLayout->addWidget(probabilityLabel);
    smallControlsLabelsLayout->addWidget(prevTrendLabel);
    smallControlsLabelsLayout->addWidget(futureTrendLabel);
    
    m_nameLineEdit        = new QLineEdit{};
    m_probabilitySpinBox  = new QDoubleSpinBox{};
    m_prevTrendComboBox   = new QComboBox{};
    m_futureTrendComboBox = new QComboBox{};
    
    m_nameLineEdit->setValidator(new QRegularExpressionValidator{QRegularExpression{"[A-zА-я0-9\\-_\\s]{1,}"}});
    m_probabilitySpinBox->setRange(0., 1.);
    m_probabilitySpinBox->setSingleStep(0.01);
    
    QStringList trendList{};
    
    for (TrendSolverContext::TrendType i = 0; i < TrendSolverContext::getTrendValue(Pattern::Trend::T_COUNT); ++i)
    {
        trendList += Pattern::trendToString(TrendSolverContext::getTrendByValue(i));
    }
    
    m_prevTrendComboBox->addItems(trendList);
    m_futureTrendComboBox->addItems(trendList);
    
    QVBoxLayout *smallControlsElemsLayout = new QVBoxLayout{};
    
    smallControlsElemsLayout->addWidget(m_nameLineEdit);
    smallControlsElemsLayout->addWidget(m_probabilitySpinBox);
    smallControlsElemsLayout->addWidget(m_prevTrendComboBox);
    smallControlsElemsLayout->addWidget(m_futureTrendComboBox);
    
    QHBoxLayout *smallControlsLayout = new QHBoxLayout{};
    
    smallControlsLayout->addLayout(smallControlsLabelsLayout);
    smallControlsLayout->addLayout(smallControlsElemsLayout);
    
    QLabel *upLinesLabel = new QLabel{tr("Up Lines:")};
    
    m_upLinePatternTableView = new QTableView{};
    
    m_upLinePatternTableModel = new LinePatternTableModel{};
    
    m_upLinePatternTableView->setModel(m_upLinePatternTableModel);
    m_upLinePatternTableView->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
    m_upLinePatternTableView->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
    
    QPushButton *addUpLineButton    = new QPushButton{tr("+")};
    QPushButton *removeUpLineButton = new QPushButton{tr("-")};
    
    QHBoxLayout *addRemoveUpLineButtonsLayout = new QHBoxLayout{};
    
    addRemoveUpLineButtonsLayout->addWidget(addUpLineButton);
    addRemoveUpLineButtonsLayout->addWidget(removeUpLineButton);
    
    QVBoxLayout *upLinesLayout = new QVBoxLayout{};
    
    upLinesLayout->addWidget(upLinesLabel);
    upLinesLayout->addWidget(m_upLinePatternTableView);
    upLinesLayout->addLayout(addRemoveUpLineButtonsLayout);
    
    QLabel *downLinesLabel = new QLabel{tr("Down Lines:")};
    
    m_downLinePatternTableView = new QTableView{};
    
    m_downLinePatternTableModel = new LinePatternTableModel{};
    
    m_downLinePatternTableView->setModel(m_downLinePatternTableModel);
    m_downLinePatternTableView->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
    m_downLinePatternTableView->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
    
    QPushButton *addDownLineButton    = new QPushButton{tr("+")};
    QPushButton *removeDownLineButton = new QPushButton{tr("-")};
    
    QHBoxLayout *addRemoveDownLineButtonsLayout = new QHBoxLayout{};
    
    addRemoveDownLineButtonsLayout->addWidget(addDownLineButton);
    addRemoveDownLineButtonsLayout->addWidget(removeDownLineButton);
    
    QVBoxLayout *downLinesLayout = new QVBoxLayout{};
    
    downLinesLayout->addWidget(downLinesLabel);
    downLinesLayout->addWidget(m_downLinePatternTableView);
    downLinesLayout->addLayout(addRemoveDownLineButtonsLayout);
    
    QHBoxLayout *linesLayout = new QHBoxLayout{};
    
    linesLayout->addLayout(upLinesLayout);
    linesLayout->addLayout(downLinesLayout);
    
    QPushButton *createPatternButton = new QPushButton{tr("Create")};
    QPushButton *cancelButton        = new QPushButton{tr("Cancel")};
    
    QHBoxLayout *dialogButtonLayout = new QHBoxLayout{};
    
    dialogButtonLayout->addStretch(1);
    dialogButtonLayout->addWidget(createPatternButton);
    dialogButtonLayout->addWidget(cancelButton);
    
    QVBoxLayout *mainLayout = new QVBoxLayout{};
    
    mainLayout->addLayout(smallControlsLayout);
    mainLayout->addLayout(linesLayout);
    mainLayout->addLayout(dialogButtonLayout);
    
    setLayout(mainLayout);
    
    connect(addUpLineButton, &QPushButton::clicked, this, &PatternEditorDialog::addUpLinePattern);
    connect(removeUpLineButton, &QPushButton::clicked, this, &PatternEditorDialog::removeUpLinePattern);
    
    connect(addDownLineButton, &QPushButton::clicked, this, &PatternEditorDialog::addDownLinePattern);
    connect(removeDownLineButton, &QPushButton::clicked, this, &PatternEditorDialog::removeDownLinePattern);
    
    connect(createPatternButton, &QPushButton::clicked, this, &PatternEditorDialog::createPattern);
    connect(cancelButton, &QPushButton::clicked, this, &PatternEditorDialog::cancel);
}

int PatternEditorDialog::exec()
{
    return QDialog::exec();
}

void PatternEditorDialog::prepareModels()
{
    auto linePatternStore = LinePatternStore::getInstance();
    
    if (!linePatternStore.get()) {
        // error handling?
        
        return;
    }
    
    auto linePatterns = linePatternStore->getLinePatterns();
    
    if (!m_linePatternTableModel->setLinePatterns(linePatterns)) {
        // error handling?
        
        return;
    }
}

void PatternEditorDialog::addUpLinePattern()
{
    std::shared_ptr<LinePattern> linePattern{};
    
    auto resultCode = (new LinePatternChooserDialog{m_linePatternTableModel, linePattern, this})->exec();
    
    if (resultCode != QDialog::DialogCode::Accepted)
        return;
    
    m_upLinePatternTableModel->addLinePattern(linePattern);
}

void PatternEditorDialog::addDownLinePattern()
{
    std::shared_ptr<LinePattern> linePattern{};
    
    auto resultCode = (new LinePatternChooserDialog{m_linePatternTableModel, linePattern, this})->exec();
    
    if (resultCode != QDialog::DialogCode::Accepted)
        return;
    
    m_downLinePatternTableModel->addLinePattern(linePattern);
}

void PatternEditorDialog::removeUpLinePattern()
{
    QModelIndex curIndex{m_upLinePatternTableView->currentIndex()};
    
    if (!curIndex.isValid()) {
        QMessageBox::warning(this, tr("Error!"), tr("Choose an UP line to remove!"));
        
        return;
    }
    
    auto pressedButton = QMessageBox::question(this, 
                                               tr("Confirmation"), 
                                               tr("Are you sure to delete the selected UP line pattern?"));
    
    if (pressedButton != QMessageBox::StandardButton::Yes) return;
    
    m_upLinePatternTableModel->removeLinePattern(curIndex.row());
}

void PatternEditorDialog::removeDownLinePattern()
{
    QModelIndex curIndex{m_downLinePatternTableView->currentIndex()};
    
    if (!curIndex.isValid()) {
        QMessageBox::warning(this, tr("Error!"), tr("Choose a DOWN line to remove!"));
        
        return;
    }
    
    auto pressedButton = QMessageBox::question(this, 
                                               tr("Confirmation"), 
                                               tr("Are you sure to delete the selected DOWN line pattern?"));
    
    if (pressedButton != QMessageBox::StandardButton::Yes) return;
    
    m_downLinePatternTableModel->removeLinePattern(curIndex.row());
}

void PatternEditorDialog::createPattern()
{
    QString name       {m_nameLineEdit->text()};
    double  probability{m_probabilitySpinBox->value()};
    
    TrendSolverContext::Trend prevTrend  {TrendSolverContext::getTrendByValue(static_cast<TrendSolverContext::TrendType>(m_prevTrendComboBox->currentIndex()))};
    TrendSolverContext::Trend futureTrend{TrendSolverContext::getTrendByValue(static_cast<TrendSolverContext::TrendType>(m_futureTrendComboBox->currentIndex()))};
    
    auto upLinePatterns   = m_upLinePatternTableModel->getLinePatterns();
    auto downLinePatterns = m_downLinePatternTableModel->getLinePatterns();
    
    qInfo() << upLinePatterns.size() << "; " << downLinePatterns.size();
    
    if (name.isEmpty() || probability <= 0. 
     || futureTrend == TrendSolverContext::Trend::T_UNDEFINED
     || (upLinePatterns.empty() && downLinePatterns.empty()))
    {
        QMessageBox::warning(this, tr("Error!"), tr("Provided data is incorrect!"));
        
        return;
    }
    
    std::vector<PatternLine> upPatternLines;
    
    for (uint64_t i = 0; i < upLinePatterns.size(); ++i) {
        const auto& upLinePattern = upLinePatterns.at(i);
        
        upPatternLines.push_back(PatternLine{upLinePattern->getId(), i, Line::Side::S_UP});
    }
    
    std::vector<PatternLine> downPatternLines;
    
    for (uint64_t i = 0; i < downLinePatterns.size(); ++i) {
        const auto& downLinePattern = downLinePatterns.at(i);
        
        upPatternLines.push_back(PatternLine{downLinePattern->getId(), i, Line::Side::S_DOWN});
    }
    
    std::shared_ptr<Pattern> newPattern{std::make_shared<Pattern>(name.toStdString(), 
                                                                  static_cast<float>(probability), 
                                                                  prevTrend, 
                                                                  futureTrend, 
                                                                  std::move(upPatternLines),
                                                                  std::move(downPatternLines))};
    
    m_pattern = newPattern;
    
    accept();
}

void PatternEditorDialog::cancel()
{
    reject();
}

void PatternEditorDialog::closeEvent(QCloseEvent *event)
{
    setResult(QDialog::DialogCode::Rejected);
    
    QDialog::closeEvent(event);
}
