#ifndef LINE_H
#define LINE_H

#include <cstdint>
#include <vector>
#include <memory>

#include "TrendSolverContext.h"
#include "Dot.h"

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
         const Direction direction);
    
public:
    static std::unique_ptr<Line> createLine(const std::shared_ptr<Dot> &first, 
                                            const std::shared_ptr<Dot> &second,
                                            const Side side);
    
    const std::shared_ptr<Dot>& getFirst() const;
    const std::shared_ptr<Dot>& getSecond() const;
    
    const std::vector<std::shared_ptr<Dot>>& getOtherDots() const;
    
    const Side getSide() const;
    
    const Direction getDirection() const;
    
    void addDot(const std::shared_ptr<Dot>& dot);
    
    CrossingType checkDotCrossing(const std::shared_ptr<Dot>& dot) const;
    
    uint8_t getCoverage() const;
    
};
#endif // LINE_H
