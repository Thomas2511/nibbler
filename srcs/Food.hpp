#ifndef FOOD_HPP
# define FOOD_HPP
# include "AGameObject.hpp"

class Food : public AGameObject
{
    public:
        Food(void);
        Food(int x, int y);
        Food(Position pos);
        Food(Food const & src);
        virtual ~Food(void);
        Food &      operator=(Food const & rhs);

    private:
        type_e      _type;

};
std::ostream & operator<<(std::ostream & o, Food const & rhs);
#endif
