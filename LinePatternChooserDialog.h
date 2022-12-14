#ifndef LINEPATTERNCHOOSERDIALOG_H
#define LINEPATTERNCHOOSERDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QTableView>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>

#include "LinePatternTableModel.h"

class LinePatternChooserDialog : public QDialog
{
    Q_OBJECT
public:
    LinePatternChooserDialog(LinePatternTableModel *linePatternTableModel,
                             std::shared_ptr<LinePattern> &linePattern,
                             QWidget *parent = nullptr);
    
public slots:
    void cancel();
    void confirm();
    
private:
    std::shared_ptr<LinePattern> &m_linePattern;
    
    LinePatternTableModel *m_linePatternTableModel;
    
    QTableView *m_linePatternTableView;
};

#endif // LINEPATTERNCHOOSERDIALOG_H
