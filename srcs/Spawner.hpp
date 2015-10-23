#ifndef SPAWNER_HPP
#define SPAWNER_HPP
# include <vector>
# include <random>
# include "IGameObject.interface.hpp"

class Spawner
{
    public:
        static IGameObject          randomSpawn(std::vector<Position> av_positions, type_e type);
        static IGameObject          spawnAtPos(Position pos, type_e type);

    private:
        Spawner();
        Spawner(Spawner const & src);
        virtual ~Spawner(void);
        Spawner &    operator=(Spawner const & rhs);

        static IGameObject          _createIGameObject(Position pos, type_e type);
        static IGameObject          _createFood(Position pos, type_e type);
        static IGameObject          _createObstacle(Position pos, type_e, type);
        static IGameObject          _createSnakeHead(Position pos, type_e type);
        static IGameObject          _createSnakeBody(Position pos, type_e type);

};
typedef IGameObject (Spawner::*f)(Position pos, type_e type);

#endif
