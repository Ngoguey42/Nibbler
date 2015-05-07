/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IUI.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/29 08:02:43 by ngoguey           #+#    #+#             */
/*   Updated: 2015/05/07 13:20:08 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IUI_HPP
# define IUI_HPP

# include "nibbler.h"

class IUI
{
public:
	IUI(void){};
	virtual ~IUI(void){};

	virtual EventType		getEvent(void) = 0;

	virtual void			draw(IGame const &game) = 0;

	virtual bool			windowShouldClose(void) const = 0;

protected:

private:
	IUI(IUI const &src);
	IUI						&operator=(IUI const &rhs);
};

#endif
