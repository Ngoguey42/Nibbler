/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NcursesUI.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juloo <juloo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/05 20:58:49 by juloo             #+#    #+#             */
/*   Updated: 2015/05/06 17:02:39 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NCURSESUI_HPP
# define NCURSESUI_HPP

# include <map>
# include <utility>
# include "IUI.hpp"
# include "Event.hpp"

class	NcursesUI : public IUI
{
public:
	NcursesUI(std::pair<int, int> gameSize);
	virtual ~NcursesUI(void);

	virtual Event::Type			getEvent(void);

	virtual void				draw(Game const &game);

	virtual bool				windowShouldClose(void) const;

protected:

	std::pair<int, int>			_gameSize;

	std::pair<int, int>			_winSize;
	std::pair<int, int>			_offset;
	int							_chunkWidth;
	int							_chunkHeight;

	std::map<int, Event::Type>	_events;

	bool						_shouldClose;

	void						_updateSize(void);

	void						_drawChunk(int x, int y, int color, char c);

private:
	NcursesUI(void);
	NcursesUI(NcursesUI const &src);
	NcursesUI					&operator=(NcursesUI const &rhs);
};

#endif
