#ifndef GAME_CPP
# define GAME_CPP
# include <algorithm>
# include <vector>
# include "AGameObject.hpp"
# include "Player.hpp"

class Game
{
    public:
        Game(Game const & src);
        Game(int height, int width);
        virtual ~Game(void);
        Game &    operator=(Game const & rhs);

        void init();
        void move();
        void checkCollision();

        std::list<IGameObject*> &   getObjectList();
        size_t                      getWidth() const;
        size_t                      getHeight() const;
        std::list<int>              getScores() const;


    private:
        Game(void);

        std::vector<Position>       _availablePositions() const;
        std::list<IGameObject*>     _object_list;
        std::list<Player>           _players;
        size_t                      _height;
        size_t                      _width;
};
#endif
