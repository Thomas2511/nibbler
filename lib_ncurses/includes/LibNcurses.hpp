/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LibNcurses.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/19 12:01:04 by tdieumeg          #+#    #+#             */
/*   Updated: 2015/10/21 12:47:54 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_NCURSES_HPP
# define LIB_NCURSES_HPP

# include <ncurses.h>
# include <map>
# include <list>
# include "IGraphicLib.interface.hpp"
# include "IGameObject.interface.hpp"

# define K_ESC		27
# define K_UP		4283163
# define K_DOWN		4348699
# define K_LEFT		4479771
# define K_RIGHT	4414235

class LibNcurses : public IGraphicLib
{
	public:
		LibNcurses(int height, int width, std::string winName);
		LibNcurses(LibNcurses const & src);
		virtual ~LibNcurses(void);

		LibNcurses			&operator=(LibNcurses const & rhs);

		int					keyhandler(void);
		void				display(std::list<IGameObject*> const game_objects);
		void				display_score(std::list<int> const scores);

	private:
		LibNcurses(void);
		void				_display_sprite(int const x, int const y, std::string const sprite, type_e const type);
		void				_draw_outline(void);
		void				_terminate();

		WINDOW				*_window;
		std::string			_name;
		static std::map<type_e, std::map<cardinal_e, std::string> >	_sprites;
};

#endif
