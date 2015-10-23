#ifndef SNAKEBODY_HPP
# define SNAKEBODY_HPP
# include "ASnake.hpp"

class SnakeBody : public ASnake
{
    public:
        SnakeBody(void);
        SnakeBody(int x, int y, cardinal_e dir, type_e type, ASnake * previous);
        SnakeBody(SnakeBody const & src);
        virtual ~SnakeBody(void);
        SnakeBody &         operator=(SnakeBody const & rhs);
        Direction           getCurrentDirection() const;
        bool                move();
        bool                grow(std::list<IGameObject*> & list);
        ASnake *            getPrevious() const;
        ASnake *            getNext() const;

    private:
        ASnake *            _previous;
};

#endif
