// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/04/27 15:15:41 by ngoguey           #+#    #+#             //
//   Updated: 2015/04/27 15:15:42 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <iostream>
#include <cstdlib>
#include <GLFW/glfw3.h>
#include "Window.hpp"

int main(void)
{
	{
		Window glwin(std::make_pair(10, 10), 30.f);

		while (!glwin.windowShouldClose())
			glwin.draw();
	}	
	{
		Window glwin(std::make_pair(10, 10), 10.f);

		while (!glwin.windowShouldClose())
			glwin.draw();
	}
	return (0);
}
