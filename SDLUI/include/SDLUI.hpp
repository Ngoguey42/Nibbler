/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SDLUI.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/20 19:14:35 by jaguillo          #+#    #+#             */
/*   Updated: 2015/05/20 19:24:07 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SDLUI_HPP
# define SDLUI_HPP

# include <utility>
# include <SDL2/SDL.h>
# include "nibbler.h"
# include "IUI.hpp"

# define CHUNK_SIZE			16

class	SDLUI : public IUI
{
public:
	SDLUI(std::pair<int, int> gameSize);
	virtual ~SDLUI(void);

protected:

	std::pair<int, int>		_gameSize;

	SDL_Window				*_window;

private:
	SDLUI(SDLUI const &src);
	SDLUI					&operator=(SDLUI const &rhs);
};

#endif
