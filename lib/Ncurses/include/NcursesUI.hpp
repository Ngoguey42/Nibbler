/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NcursesUI.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juloo <juloo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/05 20:58:49 by juloo             #+#    #+#             */
/*   Updated: 2015/05/05 21:09:21 by juloo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NCURSESUI_HPP
# define NCURSESUI_HPP

# include <utility>
# include "IUI.hpp"

class	NcursesUI : public IUI
{
public:
	NcursesUI(std::pair<int, int> gameSize);
	virtual ~NcursesUI(void);

	virtual Event::Type		getEvent(void);

	virtual void			draw(Game const &game);

	virtual bool			windowShouldClose(void) const;

protected:

	std::pair<int, int>		_gameSize;

	bool					_shouldClose;

private:
	NcursesUI(void);
	NcursesUI(NcursesUI const &src);
	NcursesUI				&operator=(NcursesUI const &rhs);
};

#endif
