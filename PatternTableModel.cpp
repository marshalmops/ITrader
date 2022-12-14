#include "PatternTableModel.h"

PatternTableModel::PatternTableModel(QObject *parent)
    : QAbstractTableModel{parent},
      m_patterns{}
{
    
}

int PatternTableModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) return 0;

    return m_patterns.size();
}

int PatternTableModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid()) return 0;

    return C_PATTERN_PROP_TO_SHOW_COUNT;
}

QVariant PatternTableModel::data(const QModelIndex &index, int role) const
{
    if (role != Qt::DisplayRole || !index.isValid())
        return QVariant{};

    if (index.row() >= m_patterns.size())
        return QVariant{};

    auto curPattern = m_patterns.at(index.row());

    if (!curPattern.get())
        return QVariant{};

    switch (index.column()) {
    case 0: return QVariant{curPattern->getName().c_str()};
    case 1: return QVariant{curPattern->getProbability()};
    case 2: return QVariant{curPattern->getCountOfUses()};
    case 3: return QVariant{Pattern::trendToString(curPattern->getPrevTrend())};
    case 4: return QVariant{Pattern::trendToString(curPattern->getFutureTrend())};
    }

    return QVariant{};
}

QVariant PatternTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole) return QVariant{};

    switch (orientation) {
    case Qt::Orientation::Horizontal: {
        switch (section) {
        case 0: return QVariant{Pattern::C_DATABASE_NAME_PROP};
        case 1: return QVariant{Pattern::C_DATABASE_PROBABILITY_PROP};
        case 2: return QVariant{Pattern::C_DATABASE_USE_COUNT_PROP};
        case 3: return QVariant{Pattern::C_DATABASE_PREV_TREND_PROP};
        case 4: return QVariant{Pattern::C_DATABASE_FUTURE_TREND_PROP};
        }

        return QVariant{};
    }
    case Qt::Orientation::Vertical: {
        if (section > m_patterns.size() || section < 0)
            return QVariant{};

        return QVariant{section};
    }
    }

    return QVariant{};
}

Qt::ItemFlags PatternTableModel::flags(const QModelIndex &index) const
{
    return Qt::ItemFlags{Qt::ItemFlag::ItemIsEnabled | Qt::ItemFlag::ItemIsSelectable};

}

bool PatternTableModel::addPattern(const std::shared_ptr<Pattern> &pattern)
{
    if (!pattern.get()) return false;

    auto countOfPatterns = rowCount();
    
    beginInsertRows(QModelIndex{}, countOfPatterns, countOfPatterns);

    m_patterns.append(pattern);

    endInsertRows();
    
    emit layoutChanged();

    return true;
}

bool PatternTableModel::removePattern(const int patternIndex)
{
    auto countOfPatterns = rowCount();
    
    if (patternIndex >= countOfPatterns) return false;
    
    beginRemoveRows(QModelIndex{}, patternIndex, patternIndex);

    m_patterns.removeAt(patternIndex);

    endRemoveRows();
    
    emit layoutChanged();

    return true;
}

bool PatternTableModel::getPatternByIndex(const int patternIndex, 
                                          std::shared_ptr<Pattern> &pattern)
{
    if (patternIndex >= rowCount()) return false;
    
    pattern = m_patterns.at(patternIndex);
    
    return true;
}

bool PatternTableModel::setPatterns(const std::vector<std::shared_ptr<Pattern> > patternsToBeSet)
{
    clearPatterns();
    
    for (const auto &pattern : patternsToBeSet)
        if (!addPattern(pattern)) return false;
    
    return true;
}

void PatternTableModel::clearPatterns()
{
    beginRemoveRows(QModelIndex{}, 0, rowCount());
    
    m_patterns.clear();
    
    endRemoveRows();
    
    emit layoutChanged();
}

