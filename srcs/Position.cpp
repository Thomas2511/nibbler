#include "Position.hpp"

Position::Position(void) : _x(0), _y(0)
{
    return ;
}

Position::Position(int const x, int const y) : _x(x), _y(y)
{
    return ;
}

Position::Position(Position const & src)
{
    *this = src;
    return ;
}

Position::~Position(void)
{
    return ;
}

Position &      Position::operator=(Position const & rhs)
{
    this->_x = rhs._x;
    this->_y = rhs._y;
    return *this;
}

int             Position::getX() const
{
    return this->_x;
}

int             Position::getY() const
{
    return this->_y;
}

Position        Position::move(Direction const & dir) const
{
    return ((*this) + dir.toPosition());
}

bool            Position::outOfBounds(int height, int width) const
{
    return (this->_x < 0 || this->_x >= width || this->_y < 0 || this->_y >= height);
}

Position        Position::operator+(Position const & rhs) const
{
    return Position(this->_x + rhs._x, this->_y + rhs._y);
}

bool            Position::operator==(Position const & rhs) const
{
    return (this->_x == rhs._x && this->_y == rhs._y);
}

bool            Position::operator!=(Position const & rhs) const
{
    return !(*this == rhs);
}

std::string     Position::toString() const
{
    std::stringstream ss;

    ss << "Position (" << this->_x << "; " << this->_y << ")";
    return ss.str();
}
