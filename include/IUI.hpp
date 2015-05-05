/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IUI.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/29 08:02:43 by ngoguey           #+#    #+#             */
/*   Updated: 2015/05/05 21:02:31 by juloo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IUI_HPP
# define IUI_HPP

# include "nibbler.h"
# include "Event.hpp"

class IUI
{
public:
	IUI(void){};
	virtual ~IUI(void){};

	virtual Event::Type		getEvent(void) = 0;

	virtual void			draw(Game const &game) = 0;

	virtual bool			windowShouldClose(void) const = 0;

protected:

private:
	IUI(IUI const &src);
	IUI						&operator=(IUI const &rhs);
};

#endif
