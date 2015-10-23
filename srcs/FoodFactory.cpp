#include "FoodFactory.hpp"

Food                    FoodFactory::randomSpawn(std::vector<Position> av_positions)
{
    std::random_device  rd;
    std::mt19937        gen(rd());
    std::uniform_int_distribution<> randomw(0, av_positions.size() - 1);


    return (Food(av_positions[randomw(gen)]));
}

Food                    FoodFactory::spawnAtPos(Position pos)
{
    return (Food(pos));
}
