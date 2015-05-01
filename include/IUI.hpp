/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IUI.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/29 08:02:43 by ngoguey           #+#    #+#             */
/*   Updated: 2015/05/01 16:07:56 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IUI_HPP
# define IUI_HPP

class IUI
{
public:
	IUI(){};
	virtual ~IUI(){};

	virtual void			draw(void) const = 0;
	virtual bool			windowShouldClose(void) const = 0;

protected:
private:
	IUI(IUI const &src);
	IUI						&operator=(IUI const &rhs);
};

#endif
