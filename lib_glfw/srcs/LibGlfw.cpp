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

#include "TGALoader.hpp"
#include "LibGlfw.hpp"

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

int                 LibGlfw::keyhandler(void)
{
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
    glfwSwapBuffers(this->_window);
    glfwPollEvents();
    return ;
}

void                LibGlfw::_display_sprite(int const x, int const y, std::string const sprite)
{
    std::stringstream       ss;
    Image                   *img;

    ss << "../resources/" << sprite;
    glGenTextures(1, &(this->_sprite_id));
    glBindTexture(GL_TEXTURE_2D, this->_sprite_id);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 4, GL_RGBA, img->getWidth(), img->getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, img->getDataForOpenGL());
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex2f(x, y);
    glTexCoord2f(1, 0);
    glVertex2f(x + 32, y);
    glTexCoord2f(1, 1);
    glVertex2f(x + 32, y + 32);
    glTexCoord2f(0, 1);
    glVertex2f(x, y + 32);
    glEnd();
}

void                LibGlfw::_key_callback(GLFWwindow *win, int key, int scancode, int action, int mods)
{
    (void)win;
    (void)scancode;
    (void)mods;
    if (((key == GLFW_KEY_ESCAPE) ||
            (key == GLFW_KEY_W) ||
            (key == GLFW_KEY_A) ||
            (key == GLFW_KEY_S) ||
            (key == GLFW_KEY_D) ||
            (key == GLFW_KEY_UP) ||
            (key == GLFW_KEY_DOWN) ||
            (key == GLFW_KEY_RIGHT) ||
            (key == GLFW_KEY_LEFT)) && (action == GLFW_PRESS))
        LibGlfw::_glfw_key = key;
}
