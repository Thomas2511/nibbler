#ifndef FOODFACTORY_HPP
# define FOODFACTORY_HPP
# include <vector>
# include <random>
# include "Food.hpp"

class FoodFactory
{
    public:
        static Food             randomSpawn(std::vector<Position> av_positions);
        static Food             spawnAtPos(Position pos);

    private:
        FoodFactory(void);
        FoodFactory(FoodFactory const & src);
        virtual ~FoodFactory(void);
        FoodFactory &    operator=(FoodFactory const & rhs);
};

#endif
