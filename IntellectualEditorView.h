#ifndef INTELLECTUALEDITORVIEW_H
#define INTELLECTUALEDITORVIEW_H

#include <QDialog>
#include <QTableView>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>

#include "error/Error.h"

#include "pattern/Pattern.h"
#include "pattern/LinePattern.h"

#include "PatternEditorDialog.h"

#include "IntellectualEditorModel.h"

class IntellectualEditorView : public QDialog
{
    Q_OBJECT
public:
    explicit IntellectualEditorView(IntellectualEditorModel *model,
                                    QWidget *parent = nullptr);
    
signals:
    void errorOccurred(const std::shared_ptr<Error> error);
    
public slots:
    void openPatternCreator();
    void deleteSelectedPattern();
    
    void closeEditor();
    
    int exec() override;
    
private:
    IntellectualEditorModel *m_model;
    
    QTableView *m_patternTableView;
};

#endif // INTELLECTUALEDITORVIEW_H
