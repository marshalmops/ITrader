#ifndef LINEPATTERNTABLEMODEL_H
#define LINEPATTERNTABLEMODEL_H

#include <QAbstractTableModel>

#include "pattern/LinePattern.h"

class LinePatternTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit LinePatternTableModel(QObject *parent = nullptr);
    
    virtual int rowCount(const QModelIndex &parent = QModelIndex{}) const override;
    virtual int columnCount(const QModelIndex &parent = QModelIndex{}) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    virtual Qt::ItemFlags flags(const QModelIndex &index = QModelIndex{}) const override;
    
    bool addLinePattern(const std::shared_ptr<LinePattern> &linePattern);
    
protected:
    virtual bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex{}) override;
    virtual bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex{}) override;
    
private:
    std::vector<std::shared_ptr<LinePattern>> m_linePatterns;
};

#endif // LINEPATTERNTABLEMODEL_H
