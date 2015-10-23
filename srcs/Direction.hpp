#ifndef DIRECTION_HPP
# define DIRECTION_HPP
# include "Position.hpp"
# include <iostream>
# include <map>

enum cardinal_e {NORTH = 1, EAST = 3, WEST = 7, SOUTH = 15, NORTH_EAST = 4, NORTH_WEST = 8, SOUTH_EAST = 10, SOUTH_WEST = 22};
class Position;
class Direction
{
    public:
        Direction(void);
        Direction(cardinal_e const cardinal);
        Direction(Direction const & src);
        virtual ~Direction(void);
        Direction &     operator=(Direction const & rhs);
        Direction       operator+(Direction const & rhs) const;

        cardinal_e      getCardinal() const;
        Position        toPosition() const;
        Direction       opposite() const;

        std::string     toString() const;

    private:
        cardinal_e          _dir;
};

std::ostream &          operator<<(std::ostream & o, Direction const & rhs);
#endif
