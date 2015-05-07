/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NcursesUI.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juloo <juloo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/05 20:58:49 by juloo             #+#    #+#             */
/*   Updated: 2015/05/07 13:19:34 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NCURSESUI_HPP
# define NCURSESUI_HPP

# include <map>
# include <utility>
# include "nibbler.h"
# include "IUI.hpp"

class	NcursesUI : public IUI
{
public:
	NcursesUI(std::pair<int, int> gameSize);
	virtual ~NcursesUI(void);

	virtual EventType			getEvent(void);

	virtual void				draw(IGame const &game);

	virtual bool				windowShouldClose(void) const;

protected:

	std::pair<int, int>			_gameSize;

	std::pair<int, int>			_winSize;
	std::pair<int, int>			_offset;
	int							_chunkWidth;
	int							_chunkHeight;

	std::map<int, EventType>	_events;

	bool						_shouldClose;

	void						_updateSize(void);

	void						_startText(int x, int y);
	void						_drawChunk(int x, int y, int color, char c);

private:
	NcursesUI(void);
	NcursesUI(NcursesUI const &src);
	NcursesUI					&operator=(NcursesUI const &rhs);
};

#endif
