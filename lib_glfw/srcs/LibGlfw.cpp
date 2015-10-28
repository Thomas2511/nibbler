/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_glfw.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/16 15:16:54 by tdieumeg          #+#    #+#             */
/*   Updated: 2015/10/22 13:25:31 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BMPLoader.hpp"
#include "LibGlfw.hpp"

std::map<int, int>      LibGlfw::_key_map =
{
    {GLFW_KEY_ESCAPE, 27},
    {GLFW_KEY_W, 119},
    {GLFW_KEY_A, 97},
    {GLFW_KEY_S, 115},
    {GLFW_KEY_D, 100},
    {GLFW_KEY_UP, 259},
    {GLFW_KEY_LEFT, 260},
    {GLFW_KEY_DOWN, 258},
    {GLFW_KEY_RIGHT, 261}
};

std::map<type_e, std::map<cardinal_e, std::string> >		LibGlfw::_sprites =
{
    {SNAKE_HEAD_1,{ {NORTH, "classy_head_B.tga"},
                      {EAST, "classy_head_L.tga"},
                      {WEST, "classy_head_R.tga"},
                      {SOUTH, "classy_head_T.tga"} }},
    {SNAKE_BODY_1,{ {NORTH, "classy_body_TB.tga"},
                      {EAST, "classy_body_LR.tga"},
                      {WEST, "classy_body_LR.tga"},
                      {SOUTH, "classy_body_TB.tga"},
                      {NORTH_EAST, "classy_BL.tga"},
                      {NORTH_WEST, "classy_BR.tga"},
                      {SOUTH_EAST, "classy_TL.tga"},
                      {SOUTH_WEST, "classy_TR.tga"} }},
    {SNAKE_TAIL_1,{ {NORTH, "classy_tail_T.tga"},
                      {EAST, "classy_tail_R.tga"},
                      {WEST, "classy_tail_L.tga"},
                      {SOUTH, "classy_tail_B.tga"} }},
    {SNAKE_HEAD_2,{ {NORTH, "classy_head_B.tga"},
                      {EAST, "classy_head_L.tga"},
                      {WEST, "classy_head_R.tga"},
                      {SOUTH, "classy_head_T.tga"} }},
    {SNAKE_BODY_2,{ {NORTH, "classy_body_TB.tga"},
                      {EAST, "classy_body_LR.tga"},
                      {WEST, "classy_body_LR.tga"},
                      {SOUTH, "classy_body_TB.tga"},
                      {NORTH_EAST, "classy_BL.tga"},
                      {NORTH_WEST, "classy_BR.tga"},
                      {SOUTH_EAST, "classy_TL.tga"},
                      {SOUTH_WEST, "classy_TR.tga"} }},
    {SNAKE_TAIL_2,{ {NORTH, "classy_tail_T.tga"},
                      {EAST, "classy_tail_R.tga"},
                      {WEST, "classy_tail_L.tga"},
                      {SOUTH, "classy_tail_B.tga"} }},
    {OBSTACLE, { {NORTH, "classy_obtacle.tga"} }},
    {FOOD, { {NORTH, "classy_food.tga"} }},
    {UNKNOWN, { {NORTH, "?"} }}
};

int                     LibGlfw::_glfw_key = 0;

const char              *LibGlfw::InitializationErrorException::what() const throw()
{
    return ("Failed to initialize the GLFW library");
}

const char              *LibGlfw::WindowCreationErrorException::what() const throw()
{
    return ("Failed to create the GLFW window");
}

LibGlfw::LibGlfw(void)
{
    if (glfwInit() != GL_TRUE)
        throw InitializationErrorException();
    this->_window = glfwCreateWindow(640, 480, "", NULL, NULL);
    if (!this->_window)
        throw WindowCreationErrorException();
    glfwMakeContextCurrent(this->_window);
    glfwSwapInterval(1);
    glfwSetKeyCallback(this->_window, LibGlfw::_key_callback);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 0, 0, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    return ;
}

LibGlfw::LibGlfw(int height, int width, std::string winName) : _win_height(height), _win_width(width), _sprite_id(0)
{
    if (!glfwInit())
        throw InitializationErrorException();
    this->_window = glfwCreateWindow(height, width, winName.c_str(), NULL, NULL);
    if (!this->_window)
        throw WindowCreationErrorException();
    glfwMakeContextCurrent(this->_window);
    glfwSwapInterval(1);
    glfwSetKeyCallback(this->_window, LibGlfw::_key_callback);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, height, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    return ;
}

LibGlfw::LibGlfw(LibGlfw const & src)
{
    *this = src;
    return ;
}

LibGlfw::~LibGlfw(void)
{
    return ;
}

LibGlfw             &LibGlfw::operator=(LibGlfw const & rhs)
{
    this->_window = rhs._window;
    this->_win_height = rhs._win_height;
    this->_win_width = rhs._win_width;
    this->_sprite_id = rhs._sprite_id;
    return *this;
}

int                 LibGlfw::keyhandler(void)
{
    glfwPollEvents();
    return LibGlfw::_glfw_key;
}


void                LibGlfw::display(std::list<IGameObject*> const game_objects){
    std::list<IGameObject*>::const_iterator								obj;
    std::map<type_e, std::map<cardinal_e, std::string> >::iterator		type;
    std::map<cardinal_e, std::string>::iterator							dir;

    for (obj = game_objects.begin(); obj != game_objects.end(); obj++)
    {
        type = LibGlfw::_sprites.find((*obj)->getType());
        if (type != LibGlfw::_sprites.end())
        {
            dir = type->second.find((*obj)->getCurrentDirection().getCardinal());
            if (dir != type->second.end())
                this->_display_sprite((*obj)->getPosition().getX(), (*obj)->getPosition().getY(), dir->second);
        }
    }
    return ;
}

void                LibGlfw::display_score(std::list<int> const scores)
{
    //TODO
    (void)scores;
    return ;
}

void                LibGlfw::_display_sprite(int const x, int const y, std::string const sprite)
{
    std::stringstream       ss;
    BMPImage                *img = new BMPImage();

    ss << "../resources/classy/" << sprite;
    img->loadBMP(ss.str().c_str());
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
    glClear( GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &(this->_sprite_id));
    glBindTexture(GL_TEXTURE_2D, this->_sprite_id);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img->getWidth(), img->getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, img->getData());
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0);
    glVertex2f(x, y);
    glTexCoord2f(1.0, 0.0);
    glVertex2f(x + 32.0, y);
    glTexCoord2f(1.0, 1.0);
    glVertex2f(x + 32.0, y + 32.0);
    glTexCoord2f(0.0, 1.0);
    glVertex2f(x, y + 32.0);
    glEnd();
    glfwSwapBuffers(this->_window);
}

void                LibGlfw::_key_callback(GLFWwindow *win, int key, int scancode, int action, int mods)
{
    (void)win;
    (void)scancode;
    (void)mods;

    if (action == GLFW_PRESS)
        if (_key_map.find(key) != _key_map.end())
            LibGlfw::_glfw_key = _key_map.find(key)->second;
}

extern "C"
{
	IGraphicLib			*getDynLibPointer(int const x, int const  y, std::string const winName)
	{
		return new LibGlfw(x, y, winName);
	}

	void				delLibPointer(IGraphicLib *lib_ptr)
	{
		delete lib_ptr;
	}
}
