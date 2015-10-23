/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LibNcurses.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/19 12:27:33 by tdieumeg          #+#    #+#             */
/*   Updated: 2015/10/21 13:36:47 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LibNcurses.hpp"

std::map<type_e, std::map<cardinal_e, std::string> >		LibNcurses::_sprites =
{
	{SNAKE_HEAD_1,{ {NORTH, "^"}, {EAST, ">"}, {WEST, "<"}, {SOUTH, "v"} }},
	{SNAKE_BODY_1,{ {NORTH, "|"}, {EAST, "-"}, {WEST, "-"}, {SOUTH, "|"}, {NORTH_EAST, "+"}, {NORTH_WEST, "+"}, {SOUTH_EAST, "+"}, {SOUTH_WEST, "+"} }},
	{SNAKE_TAIL_1,{ {NORTH, "|"}, {EAST, "-"}, {WEST, "-"}, {SOUTH, "|"} }},
	{SNAKE_HEAD_2,{ {NORTH, "^"}, {EAST, ">"}, {WEST, "<"}, {SOUTH, "v"} }},
	{SNAKE_BODY_2,{ {NORTH, "|"}, {EAST, "-"}, {WEST, "-"}, {SOUTH, "|"}, {NORTH_EAST, "+"}, {NORTH_WEST, "+"}, {SOUTH_EAST, "+"}, {SOUTH_WEST, "+"} }},
	{SNAKE_TAIL_2,{ {NORTH, "|"}, {EAST, "-"}, {WEST, "-"}, {SOUTH, "|"} }},
	{OBSTACLE, { {NORTH, " "} }},
	{FOOD, { {NORTH, "o"} }},
	{UNKNOWN, { {NORTH, "?"} }}
};

LibNcurses::LibNcurses(void)
{
	initscr();
	start_color();
	init_pair(1, COLOR_BLACK, COLOR_WHITE);
	init_pair(2, COLOR_RED, COLOR_BLACK);
	init_pair(3, COLOR_GREEN, COLOR_BLACK);
	init_pair(4, COLOR_MAGENTA, COLOR_BLACK);
	cbreak();
	refresh();
	curs_set(0);
	this->_window = newwin(0, 0, 0, 0);
	keypad(this->_window, true);
	return ;
}

LibNcurses::LibNcurses(LibNcurses const & src)
{
	*this = src;
	return ;
}

LibNcurses::LibNcurses(int height, int width, std::string winName)
{
	(void)winName;
	initscr();
	start_color();
	init_pair(1, COLOR_BLACK, COLOR_WHITE);
	init_pair(2, COLOR_RED, COLOR_BLACK);
	init_pair(3, COLOR_GREEN, COLOR_BLACK);
	init_pair(4, COLOR_MAGENTA, COLOR_BLACK);
	cbreak();
	refresh();
	curs_set(0);
	this->_window = newwin(height, width, 0, 0);
	this->_name = winName;
	keypad(this->_window, true);
	return ;
}

LibNcurses::~LibNcurses(void)
{
	_terminate();
	return ;
}

LibNcurses &		LibNcurses::operator=(LibNcurses const & rhs)
{
	this->_window = rhs._window;
	return *this;
}

int					LibNcurses::keyhandler(void)
{
	return wgetch(this->_window);
}

void				LibNcurses::display(std::list<IGameObject*> const game_objects)
{
	std::list<IGameObject*>::const_iterator								obj;
	std::map<type_e, std::map<cardinal_e, std::string> >::iterator		type;
	std::map<cardinal_e, std::string>::iterator							dir;

	werase(this->_window);
	for (obj = game_objects.begin(); obj != game_objects.end(); obj++)
	{
		type = LibNcurses::_sprites.find((*obj)->getType());
		if (type != LibNcurses::_sprites.end())
		{
			dir = type->second.find((*obj)->getCurrentDirection().getCardinal());
			if (dir != type->second.end())
				this->_display_sprite((*obj)->getPosition().getX(), (*obj)->getPosition().getY(), dir->second, (*obj)->getType());
		}
	}
	this->_draw_outline();
	wrefresh(this->_window);
	return ;
}

void				LibNcurses::display_score(std::list<int> const scores)
{
	int				max_x;
	int				max_y;
	int				p1;
	int				p2;

	getmaxyx(this->_window, max_y, max_x);
	p1 = scores.front();
	p2 = scores.back();
	wmove(this->_window, (max_y - 1), 1);
	wprintw(this->_window, "P1:%d", p1);
	wmove(this->_window, (max_y - 1), (max_x - (((std::to_string(p2)).length()) + 4)));
	wprintw(this->_window, "P2:%d", p2);
	wrefresh(this->_window);
	return ;
}

void				LibNcurses::_display_sprite(int const x, int const y, std::string const sprite, type_e const type)
{
	int				pair;

	pair = 1;
	wmove(this->_window, y, x);
	if (type == OBSTACLE)
		pair = 1;
	if (type == FOOD)
		pair = 2;
	if ((type == SNAKE_HEAD_1) || (type == SNAKE_BODY_1) || (type == SNAKE_TAIL_1))
		pair = 3;
	if ((type == SNAKE_HEAD_2) || (type == SNAKE_BODY_2) || (type == SNAKE_TAIL_2))
		pair = 4;
	wattron(this->_window, COLOR_PAIR(pair));
	wprintw(this->_window, "%s", sprite.c_str());
	wattroff(this->_window, COLOR_PAIR(pair));
	return ;
}

void				LibNcurses::_draw_outline(void)
{
	int				x;
	int				y;

	getmaxyx(this->_window, y , x);
	wattron(this->_window, COLOR_PAIR(1));
	wborder(this->_window, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
	wattroff(this->_window, COLOR_PAIR(1));
	wmove(this->_window, 0, ((x / 2) - (this->_name.length() / 2)));
	wprintw(this->_window, "%s", this->_name.c_str());
	return ;
}

void				LibNcurses::_terminate(void)
{
	wclear(this->_window);
	wrefresh(this->_window);
	delwin(this->_window);
	endwin();
	return ;
}

extern "C"
{
	IGraphicLib			*getDynLibPointer(int const x, int const  y, std::string const winName)
	{
		return new LibNcurses(x, y, winName);
	}

	void				delLibPointer(IGraphicLib *lib_ptr)
	{
		delete lib_ptr;
	}
}
