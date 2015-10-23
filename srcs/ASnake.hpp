#ifndef ASNAKE_HPP
# define ASNAKE_HPP
#include "AGameObject.hpp"
#include <list>

class ASnake : public AGameObject
{
    public:
        ASnake(void);
        ASnake(int x, int y, cardinal_e dir, type_e type);
        ASnake(ASnake const & src);
        virtual ~ASnake(void);
        ASnake &    operator=(ASnake const & rhs);

        virtual bool                move();
        virtual bool                grow(std::list<IGameObject*> & list) = 0;

        virtual bool                isTail() const;
        virtual ASnake *            getNext() const;
    protected:
        type_e      _type;
        ASnake *    _next;

};

#endif
