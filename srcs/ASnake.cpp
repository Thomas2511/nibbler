#include "ASnake.hpp"

ASnake::ASnake(void) : AGameObject()
{
    return ;
}

ASnake::ASnake(int x, int y, cardinal_e dir, type_e type): AGameObject(x, y, dir), _type(type), _next(NULL)
{
    return ;
}

ASnake::ASnake(ASnake const & src): AGameObject(src)
{
    return ;
}

ASnake::~ASnake(void)
{
    delete this->_next;
}

ASnake &            ASnake::operator=(ASnake const & rhs)
{
    AGameObject::operator=(rhs);
    this->_next = rhs._next;
    return *this;
}


bool                ASnake::move()
{
    if (this->isTail() || (this->_pos.move(this->_dir) != this->getNext()->getPosition()))
    {
        this->_pos = this->_pos.move(this->_dir);
        if (!this->isTail())
            this->getNext()->move();
        return true ;
    }
    return false ;
}

bool                ASnake::isTail() const
{
    return (this->getNext() == NULL);
}

ASnake *            ASnake::getNext() const
{
    return this->_next;
}
