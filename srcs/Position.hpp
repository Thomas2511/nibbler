#ifndef POSITION_HPP
# define POSITION_HPP
# include "Direction.hpp"
# include <iostream>
# include <sstream>

class Direction;
class Position
{
    public:
        Position(void);
        Position(int const x, int const y);
        Position(Position const & src);
        virtual ~Position(void);
        Position &          operator=(Position const & rhs);

        int                 getX() const;
        int                 getY() const;

        Position            move(Direction const & dir) const;
        bool                outOfBounds(int height, int width) const;

        Position            operator+(Position const & rhs) const;
        bool                operator==(Position const & rhs) const;
        bool                operator!=(Position const & rhs) const;

        std::string         toString() const;

    private:
        int                 _x;
        int                 _y;
};

std::ostream &              operator<<(std::ostream & o, Position const & rhs);
#endif
