#ifndef SNAKEHEAD_HPP
# define SNAKEHEAD_HPP
# include <list>
# include "ASnake.hpp"
# include "SnakeBody.hpp"

class SnakeHead : public ASnake
{
    public:
        SnakeHead(void);
        SnakeHead(int x, int y, cardinal_e dir, type_e type);
        SnakeHead(SnakeHead const & src);
        virtual ~SnakeHead(void);
        SnakeHead &    operator=(SnakeHead const & rhs);

        Direction           getCurrentDirection() const;

        bool                grow(std::list<IGameObject*> & list);
        bool                checkCollision(std::list<IGameObject*> & list, int height, int width);

        ASnake *            getNext() const;
        bool                isDead() const;
        bool                isTail() const;

        void                setDirection(Direction const & dir);

    private:
        bool                _dead;
};

#endif
