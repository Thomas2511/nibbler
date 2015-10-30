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
# include <GLUT/glut.h>
# include "GLFW/glfw3.h"
# include "IGraphicLib.interface.hpp"
# include "IGameObject.interface.hpp"

class LibGlfw : public IGraphicLib
{
	public:
        class LibGlfwException : public std::exception
        {
        };
        class InitializationErrorException : public LibGlfwException
        {
            public:
                virtual const char *    what() const throw();
        };
        class WindowCreationErrorException : public LibGlfwException
        {
            public:
                virtual const char *    what() const throw();
        };
		LibGlfw(int height, int width, std::string winName);
		LibGlfw(LibGlfw const & src);
		virtual ~LibGlfw(void);

		LibGlfw			&operator=(LibGlfw const & rhs);

		int				keyhandler(void);
		void			display(std::list<IGameObject*> const game_object);
		void			display_score(std::list<int> const scores);
        float           getScale(void);

	private:
		LibGlfw(void);
        void            _display_sprite(int const x, int const y, std::string const sprite);
        static void     _key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);

		GLFWwindow		    *_window;
        float               _win_height;
        float               _win_width;
        GLuint              _sprite_id;
        static std::map<int, int> _key_map;
		static std::map<type_e, std::map<cardinal_e, std::string> > _sprites;
        static int          _glfw_key;
        static const int    _scale;
};

#endif
