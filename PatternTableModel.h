#ifndef PATTERNTABLEMODEL_H
#define PATTERNTABLEMODEL_H

#include <QAbstractTableModel>

#include "pattern/Pattern.h"

class PatternTableModel : public QAbstractTableModel
{
    Q_OBJECT

    constexpr static const int C_PATTERN_PROP_TO_SHOW_COUNT = 5;

public:
    explicit PatternTableModel(QObject *parent = nullptr);
    
    virtual int rowCount(const QModelIndex &parent = QModelIndex{}) const override;
    virtual int columnCount(const QModelIndex &parent = QModelIndex{}) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    virtual Qt::ItemFlags flags(const QModelIndex &index = QModelIndex{}) const override;
    
    bool addPattern       (const std::shared_ptr<Pattern> &pattern);
    bool removePattern    (const int patternIndex);
    bool getPatternByIndex(const int patternIndex, 
                           std::shared_ptr<Pattern> &pattern);
    
    bool setPatterns(const std::vector<std::shared_ptr<Pattern>> patternsToBeSet);
    
protected:
    void clearPatterns();
    
private:
    QList<std::shared_ptr<Pattern>> m_patterns;
};

#endif // PATTERNTABLEMODEL_H
