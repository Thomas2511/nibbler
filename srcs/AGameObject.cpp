#include "AGameObject.hpp"

AGameObject::AGameObject(void) : _pos(Position(0, 0)), _dir(Direction(NORTH)), _type(UNKNOWN)
{
    return ;
}

AGameObject::AGameObject(AGameObject const & src)
{
    *this = src;
    return ;
}

AGameObject::AGameObject(int x, int y, cardinal_e dir) : _pos(Position(x, y)), _dir(Direction(dir)), _type(UNKNOWN)
{
    return ;
}

AGameObject::~AGameObject(void)
{
    return ;
}

AGameObject &           AGameObject::operator=(AGameObject const & rhs)
{
    this->_pos = rhs._pos;
    this->_dir = rhs._dir;
    this->_type = rhs._type;
    this->_to_be_deleted = rhs._to_be_deleted;
    return *this;
}

Position                AGameObject::getPosition() const
{
    return _pos;
}

Direction               AGameObject::getCurrentDirection() const
{
    return _dir;
}

Direction               AGameObject::getSavedDirection() const
{
    return _dir;
}

type_e                  AGameObject::getType() const
{
    return this->_type;
}

bool                    AGameObject::isToBeDeleted() const
{
    return _to_be_deleted;
}

std::string             AGameObject::_typeToString(type_e const type) const
{
    std::string name[9] = { "SNAKE_HEAD_1", "SNAKE_BODY_1", "SNAKE_TAIL_1", "SNAKE_HEAD_2", "SNAKE_BODY_2", "SNAKE_TAIL_2", "OBSTACLE", "FOOD", "UNKNOWN" };

    return name[static_cast<int>(type)];
}

std::string             AGameObject::toString() const
{
    std::stringstream ss;

    ss << "Game Object has position : " << this->_pos << ", direction :"
        << this->_dir << ", type :" << this->_typeToString(this->_type);
    return ss.str();
}

std::ostream &          operator<<(std::ostream & o, AGameObject const & rhs)
{
    o << rhs.toString();
    return o;
}
