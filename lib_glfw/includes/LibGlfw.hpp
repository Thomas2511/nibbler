/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LibGlfw.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/16 15:45:00 by tdieumeg          #+#    #+#             */
/*   Updated: 2015/10/22 13:25:33 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_GLFW_HPP
# define LIB_GLFW_HPP

# include <map>
# include "GLFW/glfw3.h"
# include "IGraphicLib.interface.hpp"
# include "IGameObject.interface.hpp"

class LibGlfw : public IGraphicLib
{
	public:
		LibGlfw(int height, int width, std::string winName);
		LibGlfw(LibGlfw const & src);
		virtual ~LibGlfw(void);

		LibGlfw			&operator=(LibGlfw const & rhs);

		int				keyhandler(void);
		void			display(std::list<IGameObject*> const game_object);
		void			display_score(std::list<int> const scores);

	private:
		LibGlfw(void);
        void            _display_sprite(int const x, int const y, std::string const sprite);
        static void     _key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);

		GLFWwindow		*_window;
        int             _win_height;
        int             _win_width;
        size_t          _sprite_id;
		static std::map<type_e, std::map<cardinal_e, std::string> > _sprites;
        static int      _glfw_key;
};

#endif
