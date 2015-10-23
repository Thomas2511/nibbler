#include "Food.hpp"

Food::Food(void) : AGameObject(), _type(FOOD)
{
    return ;
}

Food::Food(int x, int y) : AGameObject(x, y, NORTH), _type(FOOD)
{
    return ;
}

Food::Food(Position pos) : AGameObject(pos.getX(), pos.getY(), NORTH), _type(FOOD)
{
    return ;
}

Food::Food(Food const & src) : AGameObject(src)
{
    *this = src;
    return ;
}

Food::~Food(void)
{
    return ;
}

std::ostream &          operator<<(std::ostream & o, Food const & rhs)
{
    o << rhs.toString();
    return o;
}
