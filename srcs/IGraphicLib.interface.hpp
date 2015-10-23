/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IGraphicLib.interface.hpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/20 14:38:16 by tdieumeg          #+#    #+#             */
/*   Updated: 2015/10/20 18:02:05 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef IGRAPHICLIB_INTERFACE_HPP
# define IGRAPHICLIB_INTERFACE_HPP

# include <list>
# include "IGameObject.interface.hpp"

class IGraphicLib
{
	public:
		virtual ~IGraphicLib(void) {};

		virtual int			keyhandler(void) = 0;
		virtual void		display(std::list<IGameObject*> const game_objects) = 0;
		virtual void		display_score(std::list<int> const scores) = 0;
};

extern "C"
{
	IGraphicLib *getDynLibPointer(int const x, int const y, std::string const winName);
	void		delLibPointer(IGraphicLib *lib_ptr);
}

#endif
