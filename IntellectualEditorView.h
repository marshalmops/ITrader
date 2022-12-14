#ifndef INTELLECTUALEDITORVIEW_H
#define INTELLECTUALEDITORVIEW_H

#include <QDialog>
#include <QTableView>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include "error/Error.h"

#include "pattern/Pattern.h"
#include "pattern/LinePattern.h"

class IntellectualEditorView : public QDialog
{
    Q_OBJECT
public:
    explicit IntellectualEditorView(QTableView *patternTableView,
                                    QTableView *linePatternTableView,
                                    QWidget *parent = nullptr);
    
signals:
    void errorOccurred(const std::shared_ptr<Error> error);
    
    void insertNewPatternRequired     ();
    void deleteSelectedPatternRequired(const uint64_t patternId);
    
public slots:
    void openPatternCreator();
    void deleteSelectedPattern();
    
    void closeEditor();
    
private:
    QTableView *m_patternTableView;
    QTableView *m_linePatternTableView;
};

#endif // INTELLECTUALEDITORVIEW_H
