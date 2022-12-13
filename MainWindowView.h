#ifndef MAINWINDOWVIEW_H
#define MAINWINDOWVIEW_H

#include <QWidget>
#include <QTableView>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

#include "qcustomplot/qcustomplot.h"

#include "error/Error.h"

#include "pattern/StagePatternLineContainer.h"

#include "SettingsView.h"

class MainWindowView : public QWidget
{
    constexpr static const int C_DEFAULT_WIDTH  = 640;
    constexpr static const int C_DEFAULT_HEIGHT = 480;
    
    Q_OBJECT
public:
    explicit MainWindowView(QTableView *tableView,
                            QWidget *parent = nullptr);
    
signals:
    void errorOccured(const std::shared_ptr<Error> error);
    void settingsChanged();
    
    void analyzeDots();
    
    void addDot();
    void removeDot();
    
public slots:
    void openSettings();
    
    void showChoosenPattern(const std::shared_ptr<StagePatternLineContainer> pattern, 
                            const std::vector<std::shared_ptr<Dot>> dots);
    
private:
    QTableView  *m_costDotsTableView;
    QTextEdit   *m_patternOutput;
    QCustomPlot *m_plot;
};

#endif // MAINWINDOWVIEW_H
