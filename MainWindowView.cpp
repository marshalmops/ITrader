#include "MainWindowView.h"

MainWindowView::MainWindowView(QTableView *tableView,
                               QWidget *parent)
    : QWidget{parent},
      m_costDotsTableView{tableView}
{
    resize(C_DEFAULT_WIDTH, C_DEFAULT_HEIGHT);
    
    QLabel *dotsTableLabel = new QLabel(tr("Dots:"));
    
    QPushButton *plusDotButton  = new QPushButton{"+"};
    QPushButton *minusDotButton = new QPushButton{"-"};
    
    QVBoxLayout *dotsTableButtonsLayout = new QVBoxLayout{};
    
    dotsTableButtonsLayout->addWidget(plusDotButton);
    dotsTableButtonsLayout->addWidget(minusDotButton);
    dotsTableButtonsLayout->addStretch(1);
    
    QHBoxLayout *dotsTableLayout = new QHBoxLayout{};
    
    dotsTableLayout->addWidget(m_costDotsTableView);
    dotsTableLayout->addLayout(dotsTableButtonsLayout);
    
    QVBoxLayout *dotsLayout = new QVBoxLayout{};
    
    dotsLayout->addWidget(dotsTableLabel);
    dotsLayout->addLayout(dotsTableLayout);
    
    QLabel *patternOutputText = new QLabel{tr("Pattern output:")};
    
    m_plot          = new QCustomPlot{};
    m_patternOutput = new QTextEdit{};
    
    m_plot->setMinimumWidth(320);
    
    m_plot->xAxis->setRange(0, TrendSolverContext::C_MIN_COUNT_OF_DOTS_TO_ANALIZE);
    m_plot->yAxis->setRange(0, 100);
    
    QHBoxLayout *patternOutputShowLayout = new QHBoxLayout{};
    
    patternOutputShowLayout->addWidget(m_plot);
    patternOutputShowLayout->addWidget(m_patternOutput);
    
    QVBoxLayout *patternOutputLayout = new QVBoxLayout{};
    
    patternOutputLayout->addWidget(patternOutputText);
    patternOutputLayout->addLayout(patternOutputShowLayout);
    
    QVBoxLayout *inputOuputLayout = new QVBoxLayout{};
    
    inputOuputLayout->addLayout(dotsLayout);
    inputOuputLayout->addLayout(patternOutputLayout);
    
    QPushButton *settingsButton = new QPushButton{tr("Settings...")};
    QPushButton *editorButton   = new QPushButton{tr("Editor...")};
    QPushButton *solveButton    = new QPushButton{tr("Solve")};
    
    settingsButton->setEnabled(false);
    editorButton->setEnabled(false);
    
    QHBoxLayout *buttonsLayout = new QHBoxLayout{};
    
    buttonsLayout->addStretch(1);
    buttonsLayout->addWidget(settingsButton);
    buttonsLayout->addWidget(editorButton);
    buttonsLayout->addWidget(solveButton);
    
    QVBoxLayout *mainLayout = new QVBoxLayout{};
    
    mainLayout->addLayout(inputOuputLayout);
    mainLayout->addLayout(buttonsLayout);
    
    setLayout(mainLayout);
    
    connect(plusDotButton,  &QPushButton::clicked, this, &MainWindowView::addDot);
    connect(minusDotButton, &QPushButton::clicked, this, &MainWindowView::removeDot);
    
    
    connect(settingsButton, &QPushButton::clicked, this, &MainWindowView::openSettings);
    connect(solveButton,    &QPushButton::clicked, this, &MainWindowView::analyzeDots);
}

void MainWindowView::openSettings()
{
    if ((new SettingsView(this))->exec() == QDialog::DialogCode::Accepted)
        emit settingsChanged();
}

void MainWindowView::showChoosenPattern(const std::shared_ptr<StagePatternLineContainer> patternLineContainer, 
                                        const std::vector<std::shared_ptr<Dot>> dots)
{
    if (!patternLineContainer.get()) {
        m_patternOutput->setText(tr("No patterns!"));
        
        return;
    }
    
    m_patternOutput->setText(patternLineContainer->getPattern()->toString());
    
    m_plot->clearGraphs();
    
    m_plot->addGraph();
            
    for (const auto &dot : dots)
        m_plot->graph(0)->addData(dot->getX(), dot->getY());
    
    auto drawSideLinesLambda = [&](const std::vector<std::shared_ptr<Line>> &sideLines) {
        for (const auto &sideLine : sideLines) {
            auto* graph = m_plot->addGraph();
            
            graph->setPen(QPen(Qt::red));
            
            auto firstDot  = sideLine->getFirst();
            auto secondDot = sideLine->getSecond();
            
            graph->addData(firstDot->getX(),  firstDot->getY());
            graph->addData(secondDot->getX(), secondDot->getY());
        }
    };
    
    drawSideLinesLambda(patternLineContainer->getUpLines());
    drawSideLinesLambda(patternLineContainer->getDownLines());
    
    m_plot->replot();
}
