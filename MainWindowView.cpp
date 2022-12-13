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
    
    m_patternOutput = new QTextEdit{};
    
    QVBoxLayout *patternOutputLayout = new QVBoxLayout{};
    
    patternOutputLayout->addWidget(patternOutputText);
    patternOutputLayout->addWidget(m_patternOutput);
    
    QVBoxLayout *inputOuputLayout = new QVBoxLayout{};
    
    inputOuputLayout->addLayout(dotsLayout);
    inputOuputLayout->addLayout(patternOutputLayout);
    
    QPushButton *settingsButton = new QPushButton{tr("Settings...")};
    QPushButton *solveButton    = new QPushButton{tr("Solve")};
    
    QHBoxLayout *buttonsLayout = new QHBoxLayout{};
    
    buttonsLayout->addStretch(1);
    buttonsLayout->addWidget(settingsButton);
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

void MainWindowView::showChoosenPattern(const std::shared_ptr<Pattern> pattern)
{
    if (!pattern.get())
        m_patternOutput->setText(tr("No patterns!"));
    else
        m_patternOutput->setText(pattern->toString());
}
