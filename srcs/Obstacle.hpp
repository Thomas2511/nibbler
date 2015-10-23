#ifndef OBSTACLE_HPP
# define OBSTACLE_HPP
# include "AGameObject.hpp"

class Obstacle: public AGameObject
{
    public:
        Obstacle(void);
        Obstacle(Position _pos, Direction _dir);
        Obstacle(Obstacle const & src);
        virtual ~Obstacle(void);
        Obstacle &    operator=(Obstacle const & rhs);

};
std::ostream & operator<<(std::ostream & o, Obstacle const & rhs);
#endif
