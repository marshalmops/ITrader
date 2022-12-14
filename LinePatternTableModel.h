#ifndef LINEPATTERNTABLEMODEL_H
#define LINEPATTERNTABLEMODEL_H

#include <QAbstractTableModel>

#include "pattern/LinePattern.h"

class LinePatternTableModel : public QAbstractTableModel
{
    Q_OBJECT

    constexpr static const int C_PROP_TO_SHOW_COUNT = 2;

public:
    explicit LinePatternTableModel(QObject *parent = nullptr);
    
    virtual int rowCount(const QModelIndex &parent = QModelIndex{}) const override;
    virtual int columnCount(const QModelIndex &parent = QModelIndex{}) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    virtual Qt::ItemFlags flags(const QModelIndex &index = QModelIndex{}) const override;
    
    bool addLinePattern       (const std::shared_ptr<LinePattern> &linePattern);
    bool removeLinePattern    (const int linePatternIndex);
    bool getLinePatternByIndex(const int linePatternIndex, 
                               std::shared_ptr<LinePattern> &linePattern);
    
    bool setLinePatterns(const std::vector<std::shared_ptr<LinePattern>> linePatternsToBeSet);
    
    std::vector<std::shared_ptr<LinePattern>> getLinePatterns() const;
    
protected:
    void clearLinePatterns();
    
private:
    QList<std::shared_ptr<LinePattern>> m_linePatterns;
};

#endif // LINEPATTERNTABLEMODEL_H
