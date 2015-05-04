/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IUI.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/29 08:02:43 by ngoguey           #+#    #+#             */
//   Updated: 2015/05/04 14:30:06 by ngoguey          ###   ########.fr       //
/*                                                                            */
/* ************************************************************************** */

#ifndef IUI_HPP
# define IUI_HPP

class IUI
{
public:
	IUI(){};
	virtual ~IUI(){};

	virtual void			draw(void) = 0;
	virtual bool			windowShouldClose(void) const = 0;

protected:
private:
	IUI(IUI const &src);
	IUI						&operator=(IUI const &rhs);
};

#endif
