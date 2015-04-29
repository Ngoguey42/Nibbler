// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   IWindow.hpp                                        :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/04/29 08:02:43 by ngoguey           #+#    #+#             //
//   Updated: 2015/04/29 08:34:53 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef IWINDOW_HPP
# define IWINDOW_HPP

//# include <string>
//# include <iostream>
//# include <stdexcept>

class IWindow
{
public:
	IWindow() {}; //comment se debarasser de ces machins ?
	virtual ~IWindow() {}; //comment se debarasser de ces machins ?

	virtual void				draw(void) const = 0;
	virtual bool				windowShouldClose(void) const = 0;
	
protected:
private:
	IWindow(IWindow const &src);
	IWindow						&operator=(IWindow const &rhs);
};
//std::ostream					&operator<<(std::ostream &o, IWindow const &rhs);

#endif // ******************************************************* IWINDOW_HPP //
