#include "SnakeHead.hpp"

SnakeHead::SnakeHead(void) : ASnake()
{
    return ;
}

SnakeHead::SnakeHead(int x, int y, cardinal_e dir, type_e type) : ASnake(x, y, dir, type)
{
    return ;
}

SnakeHead::SnakeHead(SnakeHead const & src) : ASnake(src)
{
    return ;
}

SnakeHead::~SnakeHead(void)
{
    return ;
}

SnakeHead &         SnakeHead::operator=(SnakeHead const & rhs)
{
    ASnake::operator=(rhs);
    return *this;
}

Direction           SnakeHead::getCurrentDirection() const
{
    return this->_dir;
}

bool                SnakeHead::grow(std::list<IGameObject*> & list)
{
    type_e          tail_type;

    if (this->isTail())
    {
        Position tail_pos = this->_pos.move(this->_dir.opposite());
        if (this->_type == SNAKE_HEAD_1)
            tail_type = SNAKE_TAIL_1;
        else
            tail_type = SNAKE_TAIL_2;
        this->_next = new SnakeBody(tail_pos.getX(), tail_pos.getY(), this->_dir.getCardinal(), tail_type, this);
        list.push_back(this->_next);
        return true ;
    }
    else
        this->getNext()->grow(list);
    return false ;
}

bool                SnakeHead::checkCollision(std::list<IGameObject*> & list, int height, int width)
{
    for (std::list<IGameObject*>::iterator it = list.begin(); it != list.end(); ++it)
        if ((this->_pos == (*it)->getPosition()))
        {
            if ((*it)->getType() == FOOD)
                return this->grow(list);
            else
                this->_dead = true;
            return true ;
        }
    if (this->_pos.outOfBounds(height, width))
    {
        this->_dead = true;
        return true;
    }
    return false ;
}

bool                SnakeHead::isDead() const
{
    return this->_dead;
}

void                SnakeHead::setDirection(Direction const & dir)
{
    this->_dir = dir;
}
