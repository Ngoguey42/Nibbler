// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/04/27 15:15:41 by ngoguey           #+#    #+#             //
//   Updated: 2015/04/29 07:26:14 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <iostream>
#include <cstdlib>
#include <GLFW/glfw3.h>
#include "Window.hpp"

int main(void)
{
	std::unique_ptr<Window>	glwin;

	try
	{
		glwin = std::make_unique<Window>(std::make_pair(10, 10), 3.f);
	}
	catch (std::exception &e)
	{
		std::cout << "Could not build window: " << e.what() << std::endl;
		return (0);
	}
	while (!glwin->windowShouldClose())
		glwin->draw();
	return (0);
}
