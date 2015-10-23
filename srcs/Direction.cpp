#include "Direction.hpp"

Direction::Direction(void) : _dir(NORTH)
{
    return ;
}

Direction::Direction(cardinal_e const cardinal) : _dir(cardinal)
{
    return ;
}

Direction::Direction(Direction const & src)
{
    *this = src;
    return ;
}

Direction::~Direction(void)
{
    return ;
}

Direction &         Direction::operator=(Direction const & rhs)
{
    this->_dir = rhs._dir;
    return *this;
}

Direction           Direction::operator+(Direction const & rhs) const
{
    return Direction(static_cast<cardinal_e>(static_cast<int>(this->_dir) + static_cast<int>(rhs._dir)));
}

cardinal_e          Direction::getCardinal() const
{
    return this->_dir;
}

Position            Direction::toPosition() const
{
    std::map<cardinal_e, Position> card_to_pos =
    {
        {NORTH, Position(0, 1)},
        {EAST, Position(1, 0)},
        {SOUTH, Position(0, -1)},
        {WEST, Position(-1, 0)},
        {NORTH_EAST, Position(1, 1)},
        {NORTH_WEST, Position(1, -1)},
        {SOUTH_EAST, Position(-1, 1)},
        {SOUTH_WEST, Position(-1, -1)}
    };

    return (card_to_pos.find(this->_dir))->second;
}

Direction           Direction::opposite() const
{
    std::map<cardinal_e, cardinal_e>    opposite =
    {
        {NORTH, SOUTH},
        {EAST, WEST},
        {SOUTH, NORTH},
        {WEST, EAST},
        {NORTH_EAST, SOUTH_WEST},
        {NORTH_WEST, SOUTH_EAST},
        {SOUTH_EAST, NORTH_WEST},
        {SOUTH_WEST, NORTH_EAST}
    };

    return Direction((opposite.find(this->_dir))->second);
}

std::string         Direction::toString() const
{
    std::stringstream ss;
    std::map<cardinal_e, std::string> card_to_string =
    {
        {NORTH, "North"},
        {EAST, "East"},
        {SOUTH, "South"},
        {WEST, "West"},
        {NORTH_EAST, "North-East"},
        {NORTH_WEST, "North-West"},
        {SOUTH_EAST, "South-East"},
        {SOUTH_WEST, "South-West"}
    };

    ss << "Direction (" << (card_to_string.find(this->_dir))->second << ")";
    return ss.str();
}

std::ostream &      operator<<(std::ostream & o, Direction const & rhs)
{
    o << rhs.toString();
    return o;
}
