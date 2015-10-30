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
    {SNAKE_HEAD_1,{ {NORTH, "classy_head_B.bmp"},
                      {EAST, "classy_head_L.bmp"},
                      {WEST, "classy_head_R.bmp"},
                      {SOUTH, "classy_head_T.bmp"} }},
    {SNAKE_BODY_1,{ {NORTH, "classy_body_TB.bmp"},
                      {EAST, "classy_body_LR.bmp"},
                      {WEST, "classy_body_LR.bmp"},
                      {SOUTH, "classy_body_TB.bmp"},
                      {NORTH_EAST, "classy_BL.bmp"},
                      {NORTH_WEST, "classy_BR.bmp"},
                      {SOUTH_EAST, "classy_TL.bmp"},
                      {SOUTH_WEST, "classy_TR.bmp"} }},
    {SNAKE_TAIL_1,{ {NORTH, "classy_tail_T.bmp"},
                      {EAST, "classy_tail_R.bmp"},
                      {WEST, "classy_tail_L.bmp"},
                      {SOUTH, "classy_tail_B.bmp"} }},
    {SNAKE_HEAD_2,{ {NORTH, "classy_head_B.bmp"},
                      {EAST, "classy_head_L.bmp"},
                      {WEST, "classy_head_R.bmp"},
                      {SOUTH, "classy_head_T.bmp"} }},
    {SNAKE_BODY_2,{ {NORTH, "classy_body_TB.bmp"},
                      {EAST, "classy_body_LR.bmp"},
                      {WEST, "classy_body_LR.bmp"},
                      {SOUTH, "classy_body_TB.bmp"},
                      {NORTH_EAST, "classy_BL.bmp"},
                      {NORTH_WEST, "classy_BR.bmp"},
                      {SOUTH_EAST, "classy_TL.bmp"},
                      {SOUTH_WEST, "classy_TR.bmp"} }},
    {SNAKE_TAIL_2,{ {NORTH, "classy_tail_T.bmp"},
                      {EAST, "classy_tail_R.bmp"},
                      {WEST, "classy_tail_L.bmp"},
                      {SOUTH, "classy_tail_B.bmp"} }},
    {OBSTACLE, { {NORTH, "classy_obtacle.bmp"} }},
    {FOOD, { {NORTH, "crate.bmp"} }},
    {UNKNOWN, { {NORTH, "?"} }}
};

int                     LibGlfw::_glfw_key = 0;

const int               LibGlfw::_scale = 32;

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
    glOrtho(0, width, 0, height, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
    glClear( GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
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

    for (obj = game_objects.begin(); obj != game_objects.end(); ++obj)
    {
        type = LibGlfw::_sprites.find((*obj)->getType());
        if (type != LibGlfw::_sprites.end())
        {
            dir = type->second.find((*obj)->getCurrentDirection().getCardinal());
            if (dir != type->second.end())
                this->_display_sprite((*obj)->getPosition().getX(), (*obj)->getPosition().getY(), dir->second);
        }
    }
    glfwSwapBuffers(this->_window);
    return ;
}

void                LibGlfw::display_score(std::list<int> const scores)
{
    std::stringstream           ss;

    ss << "P1: " << scores.front();
    glDisable(GL_TEXTURE_2D);
    glColor3ub(255, 255, 255);
    //glRasterPos2f(this->getScale(), this->_win_height - this->getScale());
    glRasterPos2i(300,300);
    for(size_t i = 0; i < ss.str().length(); i++)
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, ss.str().at(i));
    /*ss.str(std::string());
    ss << "P2: " << scores.back();
    glRasterPos2f(this->_win_width / 2, this->_win_height - this->getScale());
    for(size_t i = 0; i < ss.str().length(); i++)
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, ss.str().at(i));*/
    glEnable(GL_TEXTURE_2D);
    return ;
}

float               LibGlfw::getScale(void)
{
    return LibGlfw::_scale * (this->_win_height / 1000.0);
}

void                LibGlfw::_display_sprite(int const x, int const y, std::string const sprite)
{
    std::stringstream       ss;
    BMPImage                img;

    ss << "../resources/classy/" << sprite;
    img.loadBMP(ss.str().c_str());
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &(this->_sprite_id));
    glBindTexture(GL_TEXTURE_2D, this->_sprite_id);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
    glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);
    glPixelStorei(GL_UNPACK_SKIP_ROWS, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img.getWidth(), img.getHeight(), 0, GL_BGR, GL_UNSIGNED_BYTE, img.getData());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0);
    glVertex2f(x * this->getScale(), y * this->getScale());
    glTexCoord2f(1.0, 0.0);
    glVertex2f((x * this->getScale()) + this->getScale(), y * this->getScale());
    glTexCoord2f(1.0, 1.0);
    glVertex2f(x * this->getScale() + this->getScale(), y * this->getScale() + this->getScale());
    glTexCoord2f(0.0, 1.0);
    glVertex2f(x * this->getScale(), y * this->getScale() + this->getScale());
    glEnd();
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
