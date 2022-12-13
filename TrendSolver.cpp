#include "TrendSolver.h"

namespace {
    std::shared_ptr<Pattern> getMostProbablePattern(const std::vector<std::vector<StagePatternContainer>> &foundPatternsOnStages)
    {
        if (foundPatternsOnStages.empty()) 
            return std::unique_ptr<Pattern>(nullptr);
        
        std::shared_ptr<Pattern> mostProbablePattern{nullptr};
        
        for (const auto& foundPatternsOnStage : foundPatternsOnStages) {
            for (const auto& stagePatternContainer : foundPatternsOnStage) {
                for (const auto& curPattern : stagePatternContainer.getPatterns()) {
                    if (!mostProbablePattern.get()) {
                        mostProbablePattern = curPattern;
                        
                        continue;
                    }
                    
                    if (mostProbablePattern->getProbability() < curPattern->getProbability()) {
                        mostProbablePattern = curPattern;
                    }
                            
                }
            }
        }
        
        return mostProbablePattern;
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
    
    bool dotIntervalToIndexes(const std::vector<std::shared_ptr<Dot>> &dots, 
                              const Dot::xCoord startX,
                              const Dot::xCoord endX,
                              Dot::xCoord &startIndex,
                              Dot::xCoord &endIndex)
    {
        if (dots.empty()) return false;
        if (startX > endX) return false;
        
        Dot::xCoord startIndexBuffer{0};
        Dot::xCoord endIndexBuffer  {0};
        
        for (Dot::xCoord i = 0; i < dots.size(); ++i) {
            const auto& curDot = dots.at(i);
            
            if (curDot->getX() == startX)
                startIndexBuffer = i;
            else if (curDot->getX() == endX)
                endIndexBuffer = i;
        }
        
        startIndex = startIndexBuffer;
        endIndex = endIndexBuffer;
        
        return true;
    }
    
    bool checkLinePineCross(const std::vector<std::shared_ptr<Dot>> &dots, 
                            const Dot::xCoord startX,
                            const Dot::xCoord endX,
                            const std::unique_ptr<Line>& line)
    {
        Dot::xCoord startIndex{};
        Dot::xCoord endIndex{};
        
        if (!dotIntervalToIndexes(dots, startX, endX, startIndex, endIndex))
            return false;
        
        for (uint8_t i = 0; i < endIndex - startIndex + 1; ++i) {
            const std::shared_ptr<Dot>& dot = dots.at(startIndex + i);
             
            Line::CrossingType crossingType = line.get()->checkDotCrossing(dot);
            
            if (crossingType == Line::CrossingType::CT_PINE) {
                return true;
            }
        }
        
        return false;
    }
    
    std::shared_ptr<Dot> getLineMaxPineCross(const std::vector<std::shared_ptr<Dot>> &dots, 
                                             const Dot::xCoord startX,
                                             const Dot::xCoord endX,
                                             const std::unique_ptr<Line>& line)
    {
        std::shared_ptr<Dot> maxPineDot{nullptr};
        
        Dot::xCoord startIndex{0};
        Dot::xCoord endIndex{0};
        
        for (int i = 0; i < dots.size(); ++i) {
            if (dots.at(i)->getX() == startX)
                startIndex = i;
            else if (dots.at(i)->getX() == endX)
                endIndex = i;
        }
        
        for (uint8_t i = 0; i < endIndex - startIndex + 1; ++i) {
            const std::shared_ptr<Dot>& dot = dots.at(startIndex + i);
             
            Line::CrossingType crossingType = line.get()->checkDotCrossing(dot);
            
            if (crossingType == Line::CrossingType::CT_PINE) {
                if (!maxPineDot.get()) {
                    maxPineDot = dot;
                    
                    continue;
                }
                
                switch (line->getSide()) {
                case Line::Side::S_UP: {
                    if (maxPineDot->getY() < dot->getY())
                        maxPineDot = dot;
                    
                    break;
                }
                case Line::Side::S_DOWN: {
                    if (maxPineDot->getY() > dot->getY())
                        maxPineDot = dot;
                    
                    break;
                }
                default: return std::shared_ptr<Dot>{nullptr};
                }
            }
        }
        
        return maxPineDot;
    }
    
    bool getSidedMinMaxDotsOnInterval(const std::vector<std::shared_ptr<Dot>> &dots,
                                      const Dot::xCoord startX,
                                      const Dot::xCoord endX,
                                      std::vector<std::shared_ptr<Dot>> &minMaxDots,
                                      const Line::Side side = Line::Side::S_UNDEFINED)
    {
        Dot::xCoord startIndex{};
        Dot::xCoord endIndex{};
        
        if (!dotIntervalToIndexes(dots, startX, endX, startIndex, endIndex))
            return false;
        
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
                                                 const Dot::xCoord startX,
                                                 const Dot::xCoord endX,
                                                 const Line::Side side)
    {
        std::unique_ptr<Line> broadLine{nullptr};
        
        const int dotsSize = dots.size();
        
        Dot::xCoord startIndex{};
        Dot::xCoord endIndex{};
        
        if (!dotIntervalToIndexes(dots, startX, endX, startIndex, endIndex))
            return broadLine;
        
        if (startIndex >= endIndex)               return broadLine;
        if (dotsSize < 2 || dotsSize <= endIndex) return broadLine;
        
        // trying to make broad with start and end points:
        
        broadLine = Line::createLine(dots.at(startIndex), dots.at(endIndex), side);
        
        bool isPineChecked = checkLinePineCross(dots, startX, endX, broadLine);
        
        if (!isPineChecked) return broadLine;
        
        // MORE THAN 2 elems remaining!
        
        // getting ALL MINMAXes on the INTERVAL...
        
        std::vector<std::shared_ptr<Dot>> minMaxDots{};
        
        if (!getSidedMinMaxDotsOnInterval(dots, startX, endX, minMaxDots, side))
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
        
        if (!getSidedMinMaxDotsOnInterval(dots, lineToBreak->getFirst()->getX(), lineToBreak->getSecond()->getX(), minMaxDots))
            return false;
        
        // choosing MIDDLE dot without PINE CROSSING...
        
        for (uint8_t i = 1; i < minMaxDots.size() - 1; ++i) {
            std::unique_ptr<Line> firstLine  = Line::createLine(lineToBreak->getFirst(), minMaxDots[i], lineToBreak->getSide());
            std::unique_ptr<Line> secondLine{};
            
            if (!firstLine.get())  continue;
            
            std::shared_ptr<Dot> maxPineDot{getLineMaxPineCross(dots, firstLine->getFirst()->getX(), firstLine->getSecond()->getX(), firstLine)};
            
            if (maxPineDot.get()) {
                firstLine  = Line::createLine(lineToBreak->getFirst(), maxPineDot, lineToBreak->getSide());
                secondLine = Line::createLine(maxPineDot, lineToBreak->getSecond(), lineToBreak->getSide());
                
                if (!firstLine.get())  continue;
                if (!secondLine.get()) continue;
                
                if (!checkLinePineCross(dots, secondLine->getFirst()->getX(), secondLine->getSecond()->getX(), secondLine)) {
                    gottenLines.push_back(std::shared_ptr<Line>(firstLine.release()));
                    gottenLines.push_back(std::shared_ptr<Line>(secondLine.release()));
                    
                    return true;
                }
            }
            
            secondLine = Line::createLine(minMaxDots[i], lineToBreak->getSecond(), lineToBreak->getSide());
            maxPineDot = getLineMaxPineCross(dots, secondLine->getFirst()->getX(), secondLine->getSecond()->getX(), secondLine);
            
            if (maxPineDot.get()) {
                firstLine  = Line::createLine(lineToBreak->getFirst(), maxPineDot, lineToBreak->getSide());
                secondLine = Line::createLine(maxPineDot, lineToBreak->getSecond(), lineToBreak->getSide());
                
                if (!firstLine.get())  continue;
                if (!secondLine.get()) continue;
                
                if (!checkLinePineCross(dots, firstLine->getFirst()->getX(), firstLine->getSecond()->getX(), firstLine)) {
                    gottenLines.push_back(std::shared_ptr<Line>(firstLine.release()));
                    gottenLines.push_back(std::shared_ptr<Line>(secondLine.release()));
                    
                    return true;
                }
            }
        }
        
        return false;
    }
    
    bool getLinePatternByLine(const std::shared_ptr<Line> &line,
                              std::shared_ptr<LinePatternStore> &lineStoreInstance,
                              std::shared_ptr<LinePattern> &linePattern)
    {
        if (!line.get()) return false;
        
        const std::shared_ptr<LinePattern> curLinePattern{
                    lineStoreInstance->getLinePatternByAngleType(
                        LinePattern::angleTypeFromDirection(line->getDirection()))};
        
        if (!curLinePattern.get()) return false;
        
        linePattern = curLinePattern;
        
        return true;
    }
    
    bool findPatternsInLines(const std::vector<std::shared_ptr<Pattern>> &patterns,
                             const std::vector<std::shared_ptr<Line>> &upLines,
                             const std::vector<std::shared_ptr<Line>> &downLines,
                             const Pattern::Trend prevTrend,
                             std::vector<std::shared_ptr<Pattern>> &foundPatterns)
    {
        if (patterns.empty() || (upLines.empty() && downLines.empty()))
            return false;
        
        std::shared_ptr<LinePatternStore> lineStoreInstance = LinePatternStore::getInstance();
        
        if (!lineStoreInstance.get()) return false;
        
        std::vector<PatternLine> upPatternLines{};
        
        for (uint8_t i = 0; i < upLines.size(); ++i) {
            const std::shared_ptr<Line> &curUpLine{upLines.at(i)};
            std::shared_ptr<LinePattern> curLinePattern{};
            
            if (!getLinePatternByLine(curUpLine, lineStoreInstance, curLinePattern)) 
                return false;
            
            upPatternLines.push_back(PatternLine(curLinePattern->getId(), i, curUpLine->getSide()));
        }
        
        std::vector<PatternLine> downPatternLines{};
        
        for (uint8_t i = 0; i < downLines.size(); ++i) {
            const std::shared_ptr<Line> &curDownLine{downLines.at(i)};
            std::shared_ptr<LinePattern> curLinePattern{};
            
            if (!getLinePatternByLine(curDownLine, lineStoreInstance, curLinePattern)) 
                return false;
            
            downPatternLines.push_back(PatternLine(curLinePattern->getId(), i, curDownLine->getSide()));
        }
        
        // getting pattern:
        
        for (const auto& pattern : patterns) {
            if (pattern->getPrevTrend() != prevTrend) 
                continue;
            
            if (pattern->findInLinesFromBack(upPatternLines, downPatternLines))
                foundPatterns.push_back(pattern);
        }
        
        return true;
    }
    
    void findPatterns(const std::vector<std::shared_ptr<Pattern>> &patterns, 
                      const std::vector<std::shared_ptr<StageLineContainer>> &stages,
                      const Pattern::Trend prevTrend,
                      std::vector<StagePatternContainer> &foundPatternsOnStages)
    {
        const std::shared_ptr<StageLineContainer> lastStage{stages.back()};
        const int stagesCount = stages.size();
        
        for (int8_t i = stagesCount - 1; i >= 0; --i) {
            const std::shared_ptr<StageLineContainer> curPrevStage = stages.at(i);
            std::vector<std::shared_ptr<Pattern>> foundLastUpPatternsOnStage{};
            
            // last upLines to prev downLines...
            
            if (!findPatternsInLines(patterns,
                                    lastStage->getUpLines(), 
                                    curPrevStage->getDownLines(),
                                    prevTrend,
                                    foundLastUpPatternsOnStage))
            {
                return;
            }
            
            foundPatternsOnStages.push_back(StagePatternContainer(lastStage->getUpLines(),
                                                                  curPrevStage->getDownLines(),
                                                                  std::move(foundLastUpPatternsOnStage)));
            
            if (i == stagesCount - 1) continue;  
            
            // last downLines to prev upLines...
            
            std::vector<std::shared_ptr<Pattern>> foundLastDownPatternsOnStage{};
            
            if (!findPatternsInLines(patterns,
                                    curPrevStage->getUpLines(), 
                                    lastStage->getDownLines(),
                                    prevTrend,
                                    foundLastDownPatternsOnStage))
            {
                return;
            }
            
            foundPatternsOnStages.push_back(StagePatternContainer(curPrevStage->getUpLines(),
                                                                  lastStage->getDownLines(),
                                                                  foundLastDownPatternsOnStage));
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

        std::unique_ptr<Line> newRightEdgeBroadLine = getBroadLineOnInterval(dots,
                                                                             rightPrevLine->getSecond()->getX(),
                                                                             dots.back()->getX(),
                                                                             rightPrevLine->getSide());
        
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
                    const std::shared_ptr<StageLineContainer> &prevStage,
                    const Line::Side side,
                    std::vector<std::shared_ptr<Line>> &linesOrdered)
    {
        if (!prevStage.get()) return false;
        
        const std::vector<std::shared_ptr<Line>> &prevStageLines
                = (side == Line::Side::S_DOWN 
                 ? prevStage->getDownLines()
                 : prevStage->getUpLines());
        
        if (broadingLine.get()) {
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
                //linesOrdered.insert(linesOrdered.end(), prevStageLines.begin(), prevStageLines.end());  
                
                return false;
            
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
                                                 const std::shared_ptr<StageLineContainer> &prevStage,
                                                 std::unique_ptr<StageLineContainer> &newStage)
    {
        std::vector<std::shared_ptr<Line>> upLinesOrdered{};
        
        if (!orderLines(upBroadingLine, upBreakingLines, prevStage, Line::Side::S_UP, upLinesOrdered))
            return false;
        
        std::vector<std::shared_ptr<Line>> downLinesOrdered{};
        
        if (!orderLines(downBroadingLine, downBreakingLines, prevStage, Line::Side::S_DOWN, downLinesOrdered))
            return false;
        
        newStage = std::make_unique<StageLineContainer>(upLinesOrdered, downLinesOrdered);
        
        return true;
    }
    
    bool getPatternsPrevTrendAndDotsToAnalyze(const std::vector<std::shared_ptr<Dot>> &dots,
                                              std::vector<std::shared_ptr<Pattern>> &patterns,
                                              std::vector<std::shared_ptr<Dot>> &dotsToAnalyze,
                                              Pattern::Trend &prevTrend)
    {
        const int dotsCount = dots.size();
        
        if (dotsCount < TrendSolverContext::C_MIN_COUNT_OF_DOTS_TO_ANALIZE)
            return false;
        
        auto patternStore = PatternStore::getInstance();
        
        if (!patternStore.get())
            return false;
        
        auto patternsBuffer = patternStore->getPatterns();
        
        if (patternsBuffer.empty())
            return false;
        
        std::vector<std::shared_ptr<Dot>>::const_iterator startDotToAnalize{dots.end()};
        
        startDotToAnalize -= TrendSolverContext::C_COUNT_OF_DOTS_TO_GET_PATTERNS;
        
        std::vector<std::shared_ptr<Dot>> dotsToDetectTrend{dots.begin(), startDotToAnalize};
        
        patterns = std::move(patternsBuffer);
        dotsToAnalyze = std::vector<std::shared_ptr<Dot>>{startDotToAnalize, dots.end()};
        prevTrend = detectTrendByDots(dotsToDetectTrend);
        
        return true;
    }
    
    std::vector<std::shared_ptr<Dot>> createSharedDotVector(const QList<uint64_t> inputDots) {
        std::vector<std::shared_ptr<Dot>> resultDots{};
        
        uint64_t maxY{inputDots.front()};
        uint64_t minY{inputDots.front()};
        
        for (const auto &inputDot : inputDots) {
            if (inputDot > maxY) maxY = inputDot;
            if (inputDot < minY) minY = inputDot;
        }
        
        const uint64_t minMaxDelta{maxY - minY};
        
        for (Dot::yCoord i = 0; i < inputDots.size(); ++i) {
            const auto& inputDot{inputDots.at(i)};
            
            Dot::yCoord normalizedY = static_cast<Dot::yCoord>((static_cast<float>(inputDot - minY) / minMaxDelta) * 100);
            
            resultDots.push_back(std::make_shared<Dot>(i, normalizedY));
        }
        
        return std::move(resultDots);
    }
}

TrendSolver::TrendSolver(std::unique_ptr<DatabaseFacadeTrendSolver> &&facade, 
                         QObject *parent)
    : QObject{parent},
      m_facade{std::move(facade)}
{
    
}

void TrendSolver::resetFacade(std::shared_ptr<DatabaseFacadeTrendSolver> facade)
{
    m_facade = std::make_unique<DatabaseFacadeTrendSolver>(std::move(*facade));
}

void TrendSolver::analyseDots(const QList<uint64_t> inputDots)
{
    const std::vector<std::shared_ptr<Dot>> inputSharedDots{createSharedDotVector(inputDots)};

    std::vector<std::shared_ptr<Pattern>> patterns{};
    Pattern::Trend prevTrend{}; //= detectTrendByDots(dotsToDetectTrend);
    std::vector<std::shared_ptr<Dot>> dots{};
    
    if (!getPatternsPrevTrendAndDotsToAnalyze(inputSharedDots, patterns, dots, prevTrend)) {
        emit errorOccurred(std::make_shared<ErrorSolverInvalidInputData>());
        
        return;
    }
    
    std::vector<std::shared_ptr<StageLineContainer>> stages;
    
    std::unique_ptr<Line> upLine   = getBroadLineOnInterval(dots, dots.front()->getX(), dots.back()->getX(), Line::Side::S_UP);
    std::unique_ptr<Line> downLine = getBroadLineOnInterval(dots, dots.front()->getX(), dots.back()->getX(), Line::Side::S_DOWN);
    
    if (!upLine.get() || !downLine.get()) {
        emit errorOccurred(std::make_shared<ErrorSolverInvalidInputData>());        
        
        return;
    }
    
    std::shared_ptr<StageLineContainer> initStageLines{
        std::make_shared<StageLineContainer>(
            std::vector<std::shared_ptr<Line>>{std::shared_ptr<Line>(upLine.release())}, 
            std::vector<std::shared_ptr<Line>>{std::shared_ptr<Line>(downLine.release())})
    };
    
    stages.push_back(initStageLines);
    
    std::vector<StagePatternContainer> foundInitPatterns{};
    
    findPatterns(patterns, stages, prevTrend, foundInitPatterns);
    
    std::vector<std::vector<StagePatternContainer>> foundPatternsOnStages{};
    
    foundPatternsOnStages.push_back(std::move(foundInitPatterns));
    
    for (uint8_t i = 1; i < dots.size() - 1; ++i) {
        const std::shared_ptr<StageLineContainer> &prevStage = stages.at(i - 1);
        
        if (prevStage->getUpLines().size() <= 0
         || prevStage->getDownLines().size() <= 0)
        {
            break;
        }
        
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
            break;
        }
        
        std::unique_ptr<StageLineContainer> newStage{};
        
        if (!generateStageByBreakingAndBroadingLines(upLinesByBreaking, 
                                                     downLinesByBreaking,
                                                     upLineByBroading, 
                                                     downLineByBroading,
                                                     prevStage,
                                                     newStage))
        {
            break;
        }
        
        stages.push_back(std::shared_ptr<StageLineContainer>(newStage.release()));
        
        findPatterns(patterns, stages, prevTrend, foundPatternsOnStage);
            
        foundPatternsOnStages.push_back(std::move(foundPatternsOnStage));
    }
    
    // getting most PROBABLE pattern:
    
    std::shared_ptr<Pattern> mostProbablePattern = getMostProbablePattern(foundPatternsOnStages);
    
    emit patternGotten(mostProbablePattern);
}
