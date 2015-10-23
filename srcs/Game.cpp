#include "Game.hpp"

Game::Game(void): _height(400), _width(400)
{
    return ;
}

Game::Game(int height, int width): _height(height), _width(width)
{
    return ;
}

Game::Game(Game const & src)
{
    *this = src;
    return ;
}

Game::~Game(void)
{
    for (std::list<IGameObject*>::const_iterator it = this->_object_list.begin(); it != this->_object_list.end(); ++it)
    {
        delete *it;
    }
    this->_object_list.clear();
    return ;
}

Game &          Game::operator=(Game const & rhs)
{
    this->_object_list = rhs._object_list;
    this->_players = rhs._players;
    this->_height = rhs._height;
    this->_width = rhs._width;
    return *this;
}

void                            Game::init()
{

}

void                            Game::move()
{
    for (std::list<Player>::iterator it = this->_players.begin(); it != this->_players.end(); ++it)
        it->move();
}

void                            Game::checkCollision()
{
    for (std::list<Player>::iterator it = this->_players.begin(); it != this->_players.end(); ++it)
        it->checkCollision(*this);
}

std::list<IGameObject*> &       Game::getObjectList(void)
{
    return this->_object_list;
}

size_t                          Game::getWidth(void) const
{
    return this->_width;
}

size_t                          Game::getHeight(void) const
{
    return this->_height;
}

std::list<int>                  Game::getScores(void) const
{
    std::list<int>  lst;

    for (std::list<Player>::const_iterator it = this->_players.begin(); it != this->_players.end(); ++it)
    {
        lst.push_back(it->getScore());
    }
    return lst;
}

std::vector<Position>             Game::_availablePositions() const
{
    std::vector<Position>             pos_list;
    std::vector<Position>::iterator   res;

    if (this->_object_list.size() == this->_width * this->_height)
        return pos_list;

    for (size_t i = 0; i < this->_width; i++)
        for (size_t j = 0; j < this->_height; j++)
            pos_list.push_back(Position(i, j));

    for (std::list<IGameObject*>::const_iterator it = this->_object_list.begin(); it != this->_object_list.end(); it++)
    {
        res = std::find(pos_list.begin(), pos_list.end(), ((*it)->getPosition()));
        if (res != pos_list.end())
            pos_list.erase(res);
    }
    return pos_list;
}
