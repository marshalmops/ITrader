#ifndef PATTERNEDITORDIALOG_H
#define PATTERNEDITORDIALOG_H

#include <QDialog>
#include <QTableView>
#include <QLabel>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QComboBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QRegularExpressionValidator>
#include <QMessageBox>

#include "pattern/Pattern.h"
#include "pattern/LinePatternStore.h"

#include "LinePatternTableModel.h"

#include "LinePatternChooserDialog.h"

class PatternEditorDialog : public QDialog
{
    Q_OBJECT
public:
    PatternEditorDialog(LinePatternTableModel *const linePatternTableModel,
                        std::shared_ptr<Pattern> &pattern,
                        QWidget *parent = nullptr);
    
public slots:
    virtual int exec() override;
    
    void prepareModels();
    
    void addUpLinePattern();
    void addDownLinePattern();
    
    void removeUpLinePattern();
    void removeDownLinePattern();
    
    void createPattern();
    void cancel();
    
protected:
    virtual void closeEvent(QCloseEvent *event) override;
    
private:
    LinePatternTableModel *m_linePatternTableModel;
    
    QLineEdit      *m_nameLineEdit;
    QDoubleSpinBox *m_probabilitySpinBox;
    QComboBox      *m_prevTrendComboBox;
    QComboBox      *m_futureTrendComboBox;
    
    LinePatternTableModel *m_upLinePatternTableModel;
    LinePatternTableModel *m_downLinePatternTableModel;
    
    QTableView *m_upLinePatternTableView;
    QTableView *m_downLinePatternTableView;
    
    std::shared_ptr<Pattern> &m_pattern;
};

#endif // PATTERNEDITORDIALOG_H
