#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

static float S_ACCEPTABLE_DOT_CROSSING_DEVIATION_PERCENT = 0.05;

class Dot {
public:
    using xCoord = uint8_t;
    using yCoord = uint8_t;
    
    
private:
    xCoord m_x;
    yCoord m_y;
    
public:
    Dot(const xCoord x, const yCoord y)
        : m_x{x}, m_y{y}
    {
        
    }
    
    xCoord getX() {
        return m_x;
    }
    
    yCoord getY() {
        return m_y;
    }
};

class Line {
public:
    enum class Side : uint8_t {
        S_UNDEFINED = 0,
        S_UP,
        S_DOWN
    };
    
    enum class Direction : uint8_t {
        D_PARALLEL = 0,
        D_TO_UP,
        D_TO_DOWN
    };
    
    enum class CrossingType : uint8_t {
        CT_NOTHING = 0,
        CT_DOT,
        CT_PINE
    };
    
private:
    std::shared_ptr<Dot> m_first;
    std::shared_ptr<Dot> m_second;
    
    std::vector<std::shared_ptr<Dot>> m_otherDots;
    
    Side m_side;
    Direction m_direction;
    
protected:
    Line(const std::shared_ptr<Dot> &first, 
         const std::shared_ptr<Dot> &second,
         const Side side,
         const Direction direction)
        : m_first{first},
          m_second{second},
          m_side{side},
          m_direction{direction}
    {
        
    }
    
public:
    static std::unique_ptr<Line> createLine(const std::shared_ptr<Dot> &first, 
                                            const std::shared_ptr<Dot> &second,
                                            const Side side)
    {
        if (!first.get() || !second.get())
            return std::unique_ptr<Line>();
        
        bool isValid = (first.get()->getX() != second.get()->getX())
                    || (first.get()->getY() != second.get()->getY());
        
        if (!isValid) 
            return std::unique_ptr<Line>();
        
        Direction dir = ((first.get()->getY() > second.get()->getY())
                         ? Direction::D_TO_DOWN
                         : (first.get()->getY() < second.get()->getY())
                           ? Direction::D_TO_UP : Direction::D_PARALLEL);
        
        return std::make_unique<Line>(Line(first, second, side, dir));
    }
    
    const std::shared_ptr<Dot>& getFirst() {
        return m_first;
    }
    
    const std::shared_ptr<Dot>& getSecond() {
        return m_second;
    }
    
    const std::vector<std::shared_ptr<Dot>>& getOtherDots() {
        return m_otherDots;
    }
    
    const Side getSide() {
        return m_side;
    }
    
    const Direction getDirection() {
        return m_direction;
    }
    
    void addDot(const std::shared_ptr<Dot>& dot) {
        m_otherDots.push_back(dot);
    }
    
    CrossingType checkDotCrossing(const std::shared_ptr<Dot>& dot) {
        Dot::xCoord x = dot.get()->getX();
        Dot::xCoord x1 = m_first.get()->getX();
        Dot::xCoord x2 = m_second.get()->getX();
        
        Dot::yCoord y = dot.get()->getY();
        Dot::yCoord y1 = m_first.get()->getY();
        Dot::yCoord y2 = m_second.get()->getY();
        
        float yLine = (static_cast<float>(x - x1) / (x2 - x1)) * (y2 - y1) + y1;
        
        if ((yLine + yLine * S_ACCEPTABLE_DOT_CROSSING_DEVIATION_PERCENT >= y
            && yLine <= y)
         || (yLine - yLine * S_ACCEPTABLE_DOT_CROSSING_DEVIATION_PERCENT <= y
            && yLine >= y))
        {
            return CrossingType::CT_DOT;
        }
        
        switch (m_side) {
        case Side::S_UP:   {
            return (yLine < y) ? CrossingType::CT_PINE : 
                   CrossingType::CT_NOTHING;
        }
        case Side::S_DOWN: {
            return (yLine > y) ? CrossingType::CT_PINE : 
                   CrossingType::CT_NOTHING;
        }
        }
        
        return CrossingType::CT_NOTHING;
    }
    
    uint8_t getCoverage() {
        return m_second.get()->getX() - m_first.get()->getX() + 1;
    }
    
};

class Stage {
private:
    std::vector<std::shared_ptr<Line>> m_upLines;
    std::vector<std::shared_ptr<Line>> m_downLines;
    
public:
    Stage(const std::vector<std::shared_ptr<Line>> &upLines,
          const std::vector<std::shared_ptr<Line>> &downLines)
        : m_upLines{std::move(upLines)},
          m_downLines{std::move(downLines)}
    {
        
    }
    
    const std::vector<std::shared_ptr<Line>>& getUpLines() const {
        return m_upLines;
    }
    
    const std::vector<std::shared_ptr<Line>>& getDownLines() const {
        return m_downLines;
    }
};

class LinePattern {
public:
    enum class AngleType : uint8_t {
        AT_ZERO = 0,
        AT_NEGATIVE,
        AT_POSITIVE
    };
    
private:
    uint64_t m_id;
    std::string m_name;
    AngleType m_angleType;
    
public:
    LinePattern(const uint64_t id, 
                const std::string &name, 
                const AngleType angleType)
        : m_id{id},
          m_name{name},
          m_angleType{angleType}
    {
        
    }
    
    uint64_t getId() {
        return m_id;
    }
    
    const std::string& getName() {
        return m_name;
    }
    
    AngleType getAngleType() {
        return m_angleType;
    }
};

LinePattern::AngleType angleTypeFromDirection(const Line::Direction dir) {
    switch (dir) {
        case Line::Direction::D_PARALLEL: return LinePattern::AngleType::AT_ZERO;
        case Line::Direction::D_TO_UP: return LinePattern::AngleType::AT_POSITIVE;
        case Line::Direction::D_TO_DOWN: return LinePattern::AngleType::AT_NEGATIVE;
    }
}

class LinePatternStore {
private:
    static std::shared_ptr<LinePatternStore> s_store;
    
    std::vector<std::shared_ptr<LinePattern>> m_linePatterns;
    
    LinePatternStore()
        : m_linePatterns{}
    {
        
    }
    
public:
    static void init() {
        if (!s_store.get())
            s_store = std::make_shared<LinePatternStore>(LinePatternStore());
    }
    
    static std::shared_ptr<LinePatternStore> getInstance() {
        return s_store;
    }
    
    const std::vector<std::shared_ptr<LinePattern>>& getLinePatterns() {
        return m_linePatterns;
    }
    
    const std::shared_ptr<LinePattern> getLinePatternById(const uint64_t id) {
        for (const auto& linePattern : m_linePatterns)
            if (linePattern->getId() == id) return linePattern;
        
        return std::shared_ptr<LinePattern>(nullptr);
    }
    
    const std::shared_ptr<LinePattern> getLinePatternByAngleType(const LinePattern::AngleType angleType) {
        for (const auto& linePattern : m_linePatterns)
            if (linePattern->getAngleType() == angleType) return linePattern;
        
        return std::shared_ptr<LinePattern>(nullptr);
    }
    
    bool addLinePattern(std::unique_ptr<LinePattern> &linePattern) {
        if (!linePattern.get()) return false;
        
        for (int i = 0; i < m_linePatterns.size(); ++i) {
            if (m_linePatterns.at(i)->getId()   == linePattern->getId()
             || m_linePatterns.at(i)->getName() == linePattern->getName())
            {
                return false;
            }
        }
        
        m_linePatterns.push_back(std::shared_ptr<LinePattern>(linePattern.release()));
        
        return true;
    }
};

std::shared_ptr<LinePatternStore> LinePatternStore::s_store = std::shared_ptr<LinePatternStore>{nullptr};

class PatternLine {
private:
    std::shared_ptr<LinePattern> m_linePattern;
    uint64_t m_index;
    Line::Side m_side;
    
public:
    PatternLine(const std::shared_ptr<LinePattern> linePattern,
                const uint64_t index,
                const Line::Side side)
        : m_linePattern{linePattern},
          m_index{index},
          m_side{side}
    {
        
    }
    
    const std::shared_ptr<LinePattern>& getLinePattern() const {
        return m_linePattern;
    }
    
    uint64_t getIndex() const {
        return m_index;
    }
    
    Line::Side getSide() const {
        return m_side;
    }
};

class Pattern {
public:
    enum class Trend : uint8_t {
        T_UNDEFINED = 0,
        T_UP,
        T_DOWN
    };
    
    static const char* trendToString(const Trend trend) {
        static const std::unordered_map<Trend, const char*> trendStringHash{
            {Trend::T_UNDEFINED, "Undefined"},
            {Trend::T_UP, "Up"},
            {Trend::T_DOWN, "Down"}
        };
        
        return trendStringHash.at(trend);
    }
    
private:
    uint64_t    m_id;
    std::string m_name;
    float       m_probability;
    uint64_t    m_countOfUses;
    Trend       m_prevTrend;
    Trend       m_futureTrend;
    
    std::vector<PatternLine> m_patternLines;
    
public:
    Pattern(const uint64_t id,
            const std::string& name,
            const float probability,
            const uint64_t countOfUses,
            const Trend prevTrend,
            const Trend futureTrend,
            const std::vector<PatternLine> &patternLines)
        : m_id{id},
          m_name{name},
          m_probability{probability},
          m_countOfUses{countOfUses},
          m_prevTrend{prevTrend},
          m_futureTrend{futureTrend},
          m_patternLines{patternLines}
    { }
    
    uint64_t getId() const {
        return m_id;
    }
    
    const std::string& getName() const {
        return m_name;
    }
    
    float getProbability() const {
        return m_probability;
    }
    
    uint64_t getCountOfUses() const {
        return m_countOfUses;
    }
    
    Trend getPrevTrend() const {
        return m_prevTrend;
    }
    
    Trend getFutureTrend() const {
        return m_futureTrend;
    }
    
    const std::vector<PatternLine>& getPatternLines() const {
        return m_patternLines;
    }
    
    bool findInLinesFromBack(const std::vector<PatternLine> &patternLines) const {
        if (patternLines.empty()) return false;
        if (patternLines.size() < m_patternLines.size()) return false;
        
        int lastPatternInnerIndex = m_patternLines.size() - 1;
        int patternInnerIndex = lastPatternInnerIndex;
        
        for (int i = patternLines.size() - 1; i >= 0; --i) {
            if (patternLines.at(i).getLinePattern()->getId() 
             == m_patternLines.at(patternInnerIndex).getLinePattern()->getId())
            {
                --patternInnerIndex;
            } else {
                if (patternInnerIndex != lastPatternInnerIndex && i < m_patternLines.size())
                    break;
            }
            
            if (patternInnerIndex == -1)
                return true;
        }
        
        return false;
    }
    
    friend std::ostream& operator<<(std::ostream &out, const Pattern &pattern) {
        out << "\nID: " << pattern.m_id << "\nName: " << pattern.m_name
            << "\nProbability: " << pattern.m_probability
            << "\nCount of uses: " << pattern.m_countOfUses
            << "\nPrevious trend: " << trendToString(pattern.m_prevTrend)
            << "\nFuture trend: " << trendToString(pattern.m_futureTrend);
        
        return out;
    }
};

void fillDotsVector(std::vector<std::shared_ptr<Dot>> &dotsVectorRef) {
    dotsVectorRef.push_back(std::make_shared<Dot>(0, 90));
    dotsVectorRef.push_back(std::make_shared<Dot>(0, 85));
    dotsVectorRef.push_back(std::make_shared<Dot>(0, 80));
    dotsVectorRef.push_back(std::make_shared<Dot>(0, 75));
    dotsVectorRef.push_back(std::make_shared<Dot>(0, 80));
    dotsVectorRef.push_back(std::make_shared<Dot>(0, 85));
    dotsVectorRef.push_back(std::make_shared<Dot>(0, 75));
    dotsVectorRef.push_back(std::make_shared<Dot>(0, 73));
    dotsVectorRef.push_back(std::make_shared<Dot>(0, 70));
    dotsVectorRef.push_back(std::make_shared<Dot>(0, 67));
    
    dotsVectorRef.push_back(std::make_shared<Dot>(0, 19));
    dotsVectorRef.push_back(std::make_shared<Dot>(1, 29));
    dotsVectorRef.push_back(std::make_shared<Dot>(2, 40));
    dotsVectorRef.push_back(std::make_shared<Dot>(3, 52));
    dotsVectorRef.push_back(std::make_shared<Dot>(4, 63));
    dotsVectorRef.push_back(std::make_shared<Dot>(5, 73));
    dotsVectorRef.push_back(std::make_shared<Dot>(6, 85));
    dotsVectorRef.push_back(std::make_shared<Dot>(7, 96));
    dotsVectorRef.push_back(std::make_shared<Dot>(8, 89));
    dotsVectorRef.push_back(std::make_shared<Dot>(9, 75));
    dotsVectorRef.push_back(std::make_shared<Dot>(10, 58));
    dotsVectorRef.push_back(std::make_shared<Dot>(11, 42));
    dotsVectorRef.push_back(std::make_shared<Dot>(12, 27));
    dotsVectorRef.push_back(std::make_shared<Dot>(13, 10));
    dotsVectorRef.push_back(std::make_shared<Dot>(14, 2));
    dotsVectorRef.push_back(std::make_shared<Dot>(15, 9));
    dotsVectorRef.push_back(std::make_shared<Dot>(16, 15));
    dotsVectorRef.push_back(std::make_shared<Dot>(17, 23));
    dotsVectorRef.push_back(std::make_shared<Dot>(18, 29));
    dotsVectorRef.push_back(std::make_shared<Dot>(19, 35));
}

bool loadPatterns(std::vector<Pattern> &loadedPatterns) {
    LinePatternStore::init();
    
    std::shared_ptr<LinePatternStore> instance = LinePatternStore::getInstance();
    
    std::unique_ptr<LinePattern> flatLinePattern         = std::make_unique<LinePattern>(0, "Parallel", LinePattern::AngleType::AT_ZERO);
    std::unique_ptr<LinePattern> downDirectedLinePattern = std::make_unique<LinePattern>(1, "Down directed", LinePattern::AngleType::AT_NEGATIVE);
    std::unique_ptr<LinePattern> upDirectedLinePattern   = std::make_unique<LinePattern>(2, "Up directed",   LinePattern::AngleType::AT_POSITIVE);
    
    if (!instance->addLinePattern(flatLinePattern)) return false;
    if (!instance->addLinePattern(downDirectedLinePattern)) return false;
    if (!instance->addLinePattern(upDirectedLinePattern)) return false;
    
    std::vector<PatternLine> triangleToDownLines{
        PatternLine{instance->getLinePatternById(0), 0, Line::Side::S_DOWN},
        PatternLine{instance->getLinePatternById(1), 0, Line::Side::S_UP}
    };
    Pattern triangleToDownPattern{0, "Triangle to Down",
                                  0.75, 0, Pattern::Trend::T_DOWN,
                                  Pattern::Trend::T_DOWN,
                                  triangleToDownLines};
    
    std::vector<PatternLine> triangleToUpLines{
        PatternLine{instance->getLinePatternById(0), 0, Line::Side::S_UP},
        PatternLine{instance->getLinePatternById(2), 0, Line::Side::S_DOWN}
    };
    Pattern triangleToUpPattern{0, "Triangle to Up",
                                0.75, 0, Pattern::Trend::T_UP,
                                Pattern::Trend::T_UP,
                                triangleToUpLines};
    
    std::vector<PatternLine> klinToDownLines{
        PatternLine{instance->getLinePatternById(1), 0, Line::Side::S_UP},
        PatternLine{instance->getLinePatternById(1), 0, Line::Side::S_DOWN}
    };
    Pattern klinToDownPattern{0, "Klin to Down",
                              0.75, 0, Pattern::Trend::T_DOWN,
                              Pattern::Trend::T_UP,
                              klinToDownLines};
    
    loadedPatterns.push_back(std::move(triangleToDownPattern));
    loadedPatterns.push_back(std::move(triangleToUpPattern));
    loadedPatterns.push_back(std::move(klinToDownPattern));
    
    return true;
}

bool checkLinePineCross(const std::vector<std::shared_ptr<Dot>> &dots, 
                        const Dot::xCoord startIndex,
                        const Dot::xCoord endIndex,
                        const std::unique_ptr<Line>& line)
{
    for (uint8_t i = 0; i < endIndex - startIndex + 1; ++i) {
        const std::shared_ptr<Dot>& dot = dots.at(startIndex + i);
         
        Line::CrossingType crossingType = line.get()->checkDotCrossing(dot);
        
        if (crossingType == Line::CrossingType::CT_PINE) {
            return true;
        }
    }
    
    return false;
}

bool getSidedMinMaxDotsOnInterval(const std::vector<std::shared_ptr<Dot>> &dots,
                                  const Dot::xCoord startIndex,
                                  const Dot::xCoord endIndex,
                                  std::vector<std::shared_ptr<Dot>> &minMaxDots,
                                  const Line::Side side = Line::Side::S_UNDEFINED)
{
    if (endIndex - startIndex + 1 < 3) return false;
    
    minMaxDots.push_back(dots.at(startIndex));
    
    std::shared_ptr<Dot> curMinMaxDot{dots.at(startIndex + 1)};
    
    // processing [start + 1, end - 1]:
    
    for (uint8_t i = 1; i < endIndex - startIndex + 1 - 1; ++i) {
        const std::shared_ptr<Dot>& prevDot{dots.at(startIndex + i - 1)};
        const std::shared_ptr<Dot>& dot{dots.at(startIndex + i + 0)};
        const std::shared_ptr<Dot>& nextDot{dots.at(startIndex + i + 1)};
         
        if (side == Line::Side::S_UP) {
            // getting MAXs:
            
            if (prevDot->getY() < dot->getY()
             && nextDot->getY() < dot->getY())
            {
                minMaxDots.push_back(dot);
            }
            
        } else if (side == Line::Side::S_DOWN) {
            // getting MINs:
            
            if (prevDot->getY() > dot->getY()
             && nextDot->getY() > dot->getY())
            {
                minMaxDots.push_back(dot);
            }
            
        } else {
            // getting MINs and MAXs:
            
            if (prevDot->getY() < dot->getY()
             && nextDot->getY() < dot->getY())
            {
                minMaxDots.push_back(dot);
            } else if (
                prevDot->getY() > dot->getY()
             && nextDot->getY() > dot->getY())
            {
                minMaxDots.push_back(dot);
            }
        }
    }
    
    minMaxDots.push_back(dots.at(endIndex));
    
    return true;
}

std::unique_ptr<Line> getBroadLineOnInterval(const std::vector<std::shared_ptr<Dot>> &dots, 
                                             const Dot::xCoord startIndex,
                                             const Dot::xCoord endIndex,
                                             const Line::Side side)
{
    std::unique_ptr<Line> broadLine{nullptr};
    
    const int dotsSize = dots.size();
    
    if (startIndex >= endIndex)               return broadLine;
    if (dotsSize < 2 || dotsSize <= endIndex) return broadLine;
    
    // trying to make broad with start and end points:
    
    broadLine = Line::createLine(dots.at(startIndex), dots.at(endIndex), side);
    
    bool isPineChecked = checkLinePineCross(dots, startIndex, endIndex, broadLine);
    
    if (!isPineChecked) return broadLine;
    
    // MORE THAN 2 elems remaining!
    
    // getting ALL MINMAXes on the INTERVAL...
    
    std::vector<std::shared_ptr<Dot>> minMaxDots{};
    
    if (!getSidedMinMaxDotsOnInterval(dots, startIndex, endIndex, minMaxDots, side))
        return std::unique_ptr<Line>{nullptr};
    
    // processing RIGHT and LEFT sides...?
    
    // searching for LINE crossing 2 MINMAXes with THE WIDEST DOTS INTERVAL...
    
    std::unique_ptr<Line> lineWithWidestCoverage{nullptr};
    const int minMaxDotsSize = minMaxDots.size();
    
    for (uint8_t i = 0; i < minMaxDotsSize; ++i) {
        for (uint8_t j = i + 1; j < minMaxDotsSize; ++j) {
            const std::shared_ptr<Dot>& firstDot = minMaxDots.at(i);
            const std::shared_ptr<Dot>& secondDot = minMaxDots.at(j);
            
            std::unique_ptr<Line> curLine = Line::createLine(firstDot, secondDot, side);
            
            if (checkLinePineCross(dots, firstDot->getX(), secondDot->getX(), curLine))
                continue;
            
            if (!lineWithWidestCoverage.get()) {
                lineWithWidestCoverage = std::unique_ptr<Line>(curLine.release());
                
                continue;
            }
            
            if (lineWithWidestCoverage->getCoverage() < curLine->getCoverage())
                lineWithWidestCoverage = std::unique_ptr<Line>(curLine.release());
        }
    }
    
    return lineWithWidestCoverage;
} 

bool breakLineIntoTwoLines(const std::vector<std::shared_ptr<Dot>> &dots,
                           const std::shared_ptr<Line> &lineToBreak,
                           std::vector<std::shared_ptr<Line>> &gottenLines)
{
    if (!lineToBreak.get())              return false;
    if (lineToBreak->getCoverage() <= 2) return false;
    
    // getting MINMAXes...
    
    std::vector<std::shared_ptr<Dot>> minMaxDots{};
    
    Dot::xCoord startIndex = lineToBreak->getFirst()->getX();
    Dot::xCoord endIndex = lineToBreak->getSecond()->getX();
    
    if (!getSidedMinMaxDotsOnInterval(dots, startIndex, endIndex, minMaxDots))
        return false;
    
    // choosing MIDDLE dot without PINE CROSSING...
    
    for (uint8_t i = 1; i < minMaxDots.size() - 1; ++i) {
        std::unique_ptr<Line> firstLine = Line::createLine(lineToBreak->getFirst(), minMaxDots[i], lineToBreak->getSide());
        
        if (!firstLine.get()) continue;
        
        if (checkLinePineCross(dots, firstLine->getFirst()->getX(), firstLine->getSecond()->getX(), firstLine))
            continue;
        
        std::unique_ptr<Line> secondLine = Line::createLine(minMaxDots[i], lineToBreak->getSecond(), lineToBreak->getSide());
        
        if (!secondLine.get()) continue;
        
        if (checkLinePineCross(dots, secondLine->getFirst()->getX(), secondLine->getSecond()->getX(), secondLine))
            continue;
        
        gottenLines.push_back(std::shared_ptr<Line>(firstLine.release()));
        gottenLines.push_back(std::shared_ptr<Line>(secondLine.release()));
        
        return true;
    }
}

bool getLinePatternByLine(const std::shared_ptr<Line> &line,
                          std::shared_ptr<LinePatternStore> &lineStoreInstance,
                          std::shared_ptr<LinePattern> &linePattern)
{
    if (!line.get()) return false;
    
    const std::shared_ptr<LinePattern> curLinePattern{
                lineStoreInstance->getLinePatternByAngleType(
                    angleTypeFromDirection(line->getDirection()))};
    
    if (!curLinePattern.get()) return false;
    
    linePattern = curLinePattern;
    
    return true;
}

bool findPatternsInLines(const std::vector<Pattern> &patterns,
                         const std::vector<std::shared_ptr<Line>> &upLines,
                         const std::vector<std::shared_ptr<Line>> &downLines,
                         const Pattern::Trend prevTrend,
                         std::vector<Pattern> &foundPatterns)
{
    if (patterns.empty() || (upLines.empty() && downLines.empty()))
        return false;
    
    std::shared_ptr<LinePatternStore> lineStoreInstance = LinePatternStore::getInstance();
    
    if (!lineStoreInstance.get()) return false;
    
    std::vector<PatternLine> curPatternLines{};
    
    for (uint8_t i = 0; i < upLines.size(); ++i) {
        const std::shared_ptr<Line> &curUpLine{upLines.at(i)};
        std::shared_ptr<LinePattern> curLinePattern{};
        
        if (!getLinePatternByLine(curUpLine, lineStoreInstance, curLinePattern)) 
            return false;
        
        curPatternLines.push_back(PatternLine(curLinePattern, i, curUpLine->getSide()));
    }
    
    for (uint8_t i = 0; i < downLines.size(); ++i) {
        const std::shared_ptr<Line> &curDownLine{downLines.at(i)};
        std::shared_ptr<LinePattern> curLinePattern{};
        
        if (!getLinePatternByLine(curDownLine, lineStoreInstance, curLinePattern)) 
            return false;
        
        curPatternLines.push_back(PatternLine(curLinePattern, i, curDownLine->getSide()));
    }
    
    // getting pattern:
    
    for (const auto& pattern : patterns) {
        if (pattern.getPrevTrend() != prevTrend) 
            continue;
        
        if (pattern.findInLinesFromBack(curPatternLines))
            foundPatterns.push_back(pattern);
    }
    
    return true;
}

class StagePatternContainer {
private:
    const std::vector<std::shared_ptr<Line>> &m_upLines;
    const std::vector<std::shared_ptr<Line>> &m_downLines;
    const std::vector<Pattern> m_patterns;
    
public:
    StagePatternContainer(const std::vector<std::shared_ptr<Line>> &upLines,
                          const std::vector<std::shared_ptr<Line>> &downLines,
                          const std::vector<Pattern> &patterns)
        : m_upLines{upLines},
          m_downLines{downLines},
          m_patterns{std::move(patterns)}
    {
        
    }
    
    const std::vector<std::shared_ptr<Line>>& getUpLines() const {
        return m_upLines;
    }
    
    const std::vector<std::shared_ptr<Line>>& getDownLines() const {
        return m_downLines;
    }
    
    const std::vector<Pattern>& getPatterns() const {
        return m_patterns;
    }
    
};

void findPatterns(const std::vector<Pattern> &patterns, 
                  const std::vector<std::shared_ptr<Stage>> &stages,
                  const Pattern::Trend prevTrend,
                  std::vector<StagePatternContainer> &foundPatternsOnStages)
{
    const std::shared_ptr<Stage> lastStage{stages.back()};
    const int stagesCount = stages.size();
    
    for (int8_t i = stagesCount - 1; i >= 0; --i) {
        const std::shared_ptr<Stage> curPrevStage = stages.at(i);
        std::vector<Pattern> foundLastUpPatternsOnStage{};
        
        // last upLines to prev downLines...
        
        if (findPatternsInLines(patterns,
                                lastStage->getUpLines(), 
                                curPrevStage->getDownLines(),
                                prevTrend,
                                foundLastUpPatternsOnStage))
        {
            foundPatternsOnStages.push_back(StagePatternContainer(lastStage->getUpLines(),
                                                                  curPrevStage->getDownLines(),
                                                                  std::move(foundLastUpPatternsOnStage)));
        }
        
        if (i == stagesCount - 1) continue;  
        
        // last downLines to prev upLines...
        
        std::vector<Pattern> foundLastDownPatternsOnStage{};
        
        if (findPatternsInLines(patterns,
                                curPrevStage->getUpLines(), 
                                lastStage->getDownLines(),
                                prevTrend,
                                foundLastDownPatternsOnStage))
        {
            foundPatternsOnStages.push_back(StagePatternContainer(curPrevStage->getUpLines(),
                                                                  lastStage->getDownLines(),
                                                                  foundLastDownPatternsOnStage));
        }
    }
}

void printPatterns(const std::vector<Pattern> &patternsToPrint) {
    for (const auto &pattern : patternsToPrint) {
        std::cout << pattern;
    }
}

std::unique_ptr<Line> getBroadingStageLines(const std::vector<std::shared_ptr<Dot>> &dots,
                                            const std::vector<std::shared_ptr<Line>> &prevStageLines)
{
    if (dots.empty() || prevStageLines.empty()) 
        return std::unique_ptr<Line>(nullptr);
    
    const std::shared_ptr<Line> &leftPrevLine  = prevStageLines.front();
    const std::shared_ptr<Line> &rightPrevLine = prevStageLines.back();
    
    std::unique_ptr<Line> newLeftUpEdgeBroadLine = getBroadLineOnInterval(dots,
                                                                          dots.front()->getX(),
                                                                          leftPrevLine->getFirst()->getX(),
                                                                          leftPrevLine->getSide());
    
//    if (!newLeftUpEdgeBroadLine.get()) {
//        linesByBroading.push_back(std::move(newLeftUpEdgeBroadLine));
//    }
    
    std::unique_ptr<Line> newRightEdgeBroadLine = getBroadLineOnInterval(dots,
                                                                         rightPrevLine->getSecond()->getX(),
                                                                         dots.back()->getX(),
                                                                         rightPrevLine->getSide());
    
//    if (!newRightEdgeBroadLine.get()) {
//        linesByBroading.push_back(std::move(newLeftUpEdgeBroadLine));
//    }
    
    if (newLeftUpEdgeBroadLine.get() && newRightEdgeBroadLine.get()) {
        if (newLeftUpEdgeBroadLine->getCoverage() > newRightEdgeBroadLine->getCoverage())
            return std::move(newLeftUpEdgeBroadLine);
        else
            return std::move(newRightEdgeBroadLine);
    } else if (newRightEdgeBroadLine.get())
        return newRightEdgeBroadLine;
        
    return std::move(newLeftUpEdgeBroadLine);
}

bool orderLines(std::unique_ptr<Line> &broadingLine,
                const std::vector<std::shared_ptr<Line>> &breakingLines,
                const std::shared_ptr<Stage> &prevStage,
                const Line::Side side,
                std::vector<std::shared_ptr<Line>> &linesOrdered)
{
    if (!prevStage.get()) return false;
    
    const std::vector<std::shared_ptr<Line>> &prevStageLines
            = (side == Line::Side::S_DOWN 
             ? prevStage->getDownLines()
             : prevStage->getUpLines());
    
    if (broadingLine.get()) {
        //upLinesToAdd.push_back(std::shared_ptr<Line>(upBroadingLine.release()));
        
        if (prevStageLines.front()->getFirst()->getX()
          > broadingLine->getFirst()->getX())
        {
            linesOrdered.push_back(std::shared_ptr<Line>(broadingLine.release()));
            linesOrdered.insert(linesOrdered.end(), prevStageLines.begin(), prevStageLines.end());
        
        } else {
            linesOrdered.insert(linesOrdered.end(), prevStageLines.begin(), prevStageLines.end());
            linesOrdered.push_back(std::shared_ptr<Line>(broadingLine.release()));                        
        }
            
        
    } else {
        if (breakingLines.empty()) {
            linesOrdered.insert(linesOrdered.end(), prevStageLines.begin(), prevStageLines.end());            
        
        } else {
            for (const auto& line : prevStageLines) {
                if (line->getFirst()->getX()  == breakingLines.front()->getFirst()->getX()
                 && line->getSecond()->getX() == breakingLines.back()->getSecond()->getX())
                {
                    linesOrdered.insert(linesOrdered.end(), breakingLines.begin(), breakingLines.end());                                
                
                } else {
                    linesOrdered.push_back(line);
                }
            }
        }
    }
    
    return true;
}

bool generateStageByBreakingAndBroadingLines(const std::vector<std::shared_ptr<Line>> &upBreakingLines,
                                             const std::vector<std::shared_ptr<Line>> &downBreakingLines,
                                             std::unique_ptr<Line> &upBroadingLine,
                                             std::unique_ptr<Line> &downBroadingLine,
                                             const std::shared_ptr<Stage> &prevStage,
                                             std::unique_ptr<Stage> &newStage)
{
    std::vector<std::shared_ptr<Line>> upLinesOrdered{};
    
    if (!orderLines(upBroadingLine, upBreakingLines, prevStage, Line::Side::S_UP, upLinesOrdered))
        return false;
    
    std::vector<std::shared_ptr<Line>> downLinesOrdered{};
    
    if (!orderLines(downBroadingLine, downBreakingLines, prevStage, Line::Side::S_DOWN, downLinesOrdered))
        return false;
    
    newStage = std::make_unique<Stage>(upLinesOrdered, downLinesOrdered);
    
    return true;
}

const std::unique_ptr<Pattern> getMostProbablePattern(const std::vector<std::vector<StagePatternContainer>> &foundPatternsOnStages) {
    if (foundPatternsOnStages.empty()) 
        return std::unique_ptr<Pattern>(nullptr);
    
    std::unique_ptr<Pattern> mostProbablePattern{nullptr};
    
    for (const auto& foundPatternsOnStage : foundPatternsOnStages) {
        for (const auto& stagePatternContainer : foundPatternsOnStage) {
            for (const auto& curPattern : stagePatternContainer.getPatterns()) {
                if (!mostProbablePattern.get()
                  || mostProbablePattern->getProbability() < curPattern.getProbability())
                {
                    mostProbablePattern = std::make_unique<Pattern>(std::move(curPattern));
                }
                        
            }
        }
    }
    
    return std::move(mostProbablePattern);
}

Pattern::Trend detectTrendByDots(const std::vector<std::shared_ptr<Dot>>& dotsToInspect) {
    if (dotsToInspect.empty()) 
        return Pattern::Trend::T_UNDEFINED;
    
    // making streight line:
    
    std::unique_ptr<Line> line = Line::createLine(dotsToInspect.front(), dotsToInspect.back(), Line::Side::S_UNDEFINED);
    
    if (!line.get()) 
        return Pattern::Trend::T_UNDEFINED;
    
    switch (line->getDirection()) {
    case Line::Direction::D_TO_DOWN: return Pattern::Trend::T_DOWN;
    case Line::Direction::D_TO_UP: return Pattern::Trend::T_UP;
    }
    
    return Pattern::Trend::T_UNDEFINED;
}

int main()
{
    std::vector<Pattern> patterns{};
    
    // catching patterns from DB...
    
    if (!loadPatterns(patterns)) {
        std::cout << "Failed to load patterns!" << std::endl;
        
        return -1;
    }
    
    std::vector<std::shared_ptr<Dot>> allDots{};
    
    // getting input data as DOTS (30 DOTS!):
    
    fillDotsVector(allDots);
    
    if (allDots.size() < 30) return -1;
    
    std::vector<std::shared_ptr<Dot>>::iterator startDotToAnalize{allDots.end()};
    
    startDotToAnalize -= 20;
    
    std::vector<std::shared_ptr<Dot>> dotsToDetectTrend{allDots.begin(), startDotToAnalize};
    std::vector<std::shared_ptr<Dot>> dots{startDotToAnalize, allDots.end()};
    
    // getting PREV TREND by first 10 dots:
    
    Pattern::Trend prevTrend = detectTrendByDots(dotsToDetectTrend);
    
    const int dotsCount = dots.size();
    
    if (dotsCount <= 0) return -1;
    
    std::vector<std::shared_ptr<Stage>> stages;
    
    std::unique_ptr<Line> upLine   = getBroadLineOnInterval(dots, 0, dots.size() - 1, Line::Side::S_UP);
    std::unique_ptr<Line> downLine = getBroadLineOnInterval(dots, 0, dots.size() - 1, Line::Side::S_DOWN);
    
    if (!upLine.get() || !downLine.get()) {
        std::cout << "Init. lines are invalid!" << std::endl;
        
        return -1;
    }
    
    Stage initStageLines{
        {std::shared_ptr<Line>(upLine.release())}, 
        {std::shared_ptr<Line>(downLine.release())}};
    
    stages.push_back(std::make_shared<Stage>(std::move(initStageLines)));
    
    std::vector<StagePatternContainer> foundInitPatterns{};
    
    findPatterns(patterns, stages, prevTrend, foundInitPatterns);
    
    std::vector<std::vector<StagePatternContainer>> foundPatternsOnStages{};
    
    foundPatternsOnStages.push_back(std::move(foundInitPatterns));
    
    for (uint8_t i = 1; i < dotsCount - 1; ++i) {
        const std::shared_ptr<Stage> &prevStage = stages.at(i - 1);
        
        if (prevStage->getUpLines().size() <= 0
         || prevStage->getDownLines().size() <= 0)
        {
            break;
        }
        
        //std::vector<std::shared_ptr<Line>> curStageLines{};
        
        // breaking:
        
        std::vector<std::shared_ptr<Line>> upLinesByBreaking{};
        
        for (uint8_t j = 0; j < prevStage->getUpLines().size(); ++j) {
            std::vector<std::shared_ptr<Line>> curLinesByBreaking{};
            
            if (breakLineIntoTwoLines(dots, prevStage->getUpLines().at(j), curLinesByBreaking)) {
                upLinesByBreaking = std::move(curLinesByBreaking);
                
                break;
            }
        }
        
        std::vector<std::shared_ptr<Line>> downLinesByBreaking{};
        
        for (uint8_t j = 0; j < prevStage->getDownLines().size(); ++j) {
            std::vector<std::shared_ptr<Line>> curLinesByBreaking{};
            
            if (breakLineIntoTwoLines(dots, prevStage->getDownLines().at(j), curLinesByBreaking)) {
                downLinesByBreaking = std::move(curLinesByBreaking);
                
                break;
            }
        }        
        
        // broading:
        
        std::unique_ptr<Line> upLineByBroading  {getBroadingStageLines(dots, prevStage->getUpLines())};
        std::unique_ptr<Line> downLineByBroading{getBroadingStageLines(dots, prevStage->getDownLines())};        
        
        std::vector<StagePatternContainer> foundPatternsOnStage{};
        
        if (upLinesByBreaking.empty() && downLinesByBreaking.empty() 
        && !upLineByBroading.get() && !downLineByBroading.get())
        {
            findPatterns(patterns, stages, prevTrend, foundPatternsOnStage);
            
            foundPatternsOnStages.push_back(std::move(foundPatternsOnStage));

            break;
        }
        
        std::unique_ptr<Stage> newStage{};
        
        if (!generateStageByBreakingAndBroadingLines(upLinesByBreaking, 
                                                     downLinesByBreaking,
                                                     upLineByBroading, 
                                                     downLineByBroading,
                                                     prevStage,
                                                     newStage))
        {
            break;
        }
        
        stages.push_back(std::shared_ptr<Stage>(newStage.release()));
        
        // pattern searching...
        
        findPatterns(patterns, stages, prevTrend, foundPatternsOnStage);
            
        foundPatternsOnStages.push_back(std::move(foundPatternsOnStage));
    }
    
    // getting most PROBABLE pattern:
    
    std::unique_ptr<Pattern> mostProbablePattern = getMostProbablePattern(foundPatternsOnStages);
    
    std::cout << "Most probable pattern: " << std::endl;
    std::cout << *mostProbablePattern << std::endl;
    
    return 0;
}
