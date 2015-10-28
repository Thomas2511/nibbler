/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/19 17:31:07 by tdieumeg          #+#    #+#             */
/*   Updated: 2015/10/21 13:35:19 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <unistd.h>
# include <dlfcn.h>
# include "IGameObject.interface.hpp"
# include "IGraphicLib.interface.hpp"

class Trololo : public IGameObject
{
	public:
		Trololo(int x, int y, type_e type): _pos(Position(x, y)), _type(type) {};
		~Trololo(void) {};

		Trololo				&operator=(Trololo const & rhs) { this->_pos = rhs._pos; this->_type = rhs._type; return *this;}
		Position			getPosition() const { return _pos; };
		Direction			getCurrentDirection() const { return Direction(NORTH_EAST); };
		type_e				getType() const { return _type; };

	private:
		Trololo(void) {};
		Position		_pos;
		type_e			_type;
};

int				main(void)
{
	std::list<IGameObject*>		lst;
	Trololo			*obj = new Trololo(10, 10, SNAKE_BODY_1);
	void			*dl_handle;
	IGraphicLib		*(*lnc)(int, int, std::string);
	void			(*del)(IGraphicLib *);
	IGraphicLib		*lib;
	std::list<int>	scores;
    int             i;

	dl_handle = dlopen("lib_ncurses.so", RTLD_LAZY | RTLD_LOCAL);
	if (!dl_handle)
	{
		std::cout << "lol" << std::endl;
		return 1;
	}

	lnc = (IGraphicLib *(*)(int, int, std::string)) (dlsym(dl_handle, "getDynLibPointer"));
	if (!lnc)
	{
		std::cout << "pouet" << std::endl;
		return 1;
	}
	del = (void (*)(IGraphicLib *)) (dlsym(dl_handle, "delLibPointer"));
	if (!del)
	{
		std::cout << "bleh" << std::endl;
		return 1;
	}
	lst.push_back(obj);
	scores.push_back(0);
	scores.push_back(2000);
	lib = lnc(45, 120, "Nibbler");

	//lib->display(lst);
	//lib->display_score(scores);
	while((i = lib->keyhandler()) != 27)
        std::cout << i << std::endl;

	del(lib);
	dlclose(dl_handle);

	return (0);
}
