// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/04/27 15:15:41 by ngoguey           #+#    #+#             //
//   Updated: 2015/04/27 16:01:31 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <iostream>
#include <cstdlib>
#include <GLFW/glfw3.h>
#include "Window.hpp"

int main(void)
{
	{
		Window glwin(std::make_pair(1, 1), 30.f);

		while (!glwin.windowShouldClose())
			glwin.draw();
	}	
	{
		Window glwin(std::make_pair(2, 2), 30.f);

		while (!glwin.windowShouldClose())
			glwin.draw();
	}
	return (0);
}
