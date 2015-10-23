#include "Spawner.hpp"

IGameObject             Spawner::randomSpawn(std::vector<Position> av_positions, type_e type)
{
    std::random_device  rd;
    std::mt19937        gen(rd());
    std::uniform_int_distribution<>     random_pos(0, av_positions.size() - 1);

    return (Spawner::spawnAtPos(av_positions[random_pos(gen)], type));
}

IGameObject             Spawner::spawnAtPos(Position pos, type_e type)
{
    return (Spawner::_createIGameObject(pos, type));
}

IGameObject             Spawner::_createIGameObject(Position pos, type_e type)
{
    std::map<type_e, f> fun_map =
    {
        { FOOD, &_createFood },
        { OBSTACLE, &_createObstacle },
        { SNAKE_HEAD_1, &_createSnakeHead },
        { SNAKE_HEAD_2, &_createSnakeHead },
        { SNAKE_BODY_1, &_createSnakeBody },
        { SNAKE_BODY_2, &_createSnakeBody },
        { SNAKE_TAIL_1, &_createSnakeBody },
        { SNAKE_TAIL_2, &_createSnakeBody }
    };
    std::map<type_e, f>::const_iterator it = fun_map.find(type);
    
    if (it != fun_map.end())
        return (it(pos, type));
}
