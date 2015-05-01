/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/27 15:15:41 by ngoguey           #+#    #+#             */
/*   Updated: 2015/05/01 16:11:00 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cstdlib>
#include <dlfcn.h>
#include "IUI.hpp"

int main(void)
{
	//loading lib
	void *dlib = dlopen("lib/OpenGL.so", RTLD_LAZY | RTLD_LOCAL);
	if (dlib == NULL)
		return (1);
	//getting "init" function pointer
	void *fun = dlsym(dlib, "init");
	if (fun == NULL)
		return (1);

	//casting init ptr to right type (how to improve? static cast?)
	auto f = reinterpret_cast<IUI*(*)(std::pair<int, int>, float)>(fun);

	{
		//storing IUI pointer into unique ptr
		std::unique_ptr<IUI> u;
	
		try
		{
			//(how to improve without tmp)
			std::unique_ptr<IUI> tmp(f(std::make_pair(12, 20), 35.f));

			u = std::move(tmp);
		}
		catch (std::exception &e)
		{
			std::cout << "Could not build window: " << e.what() << std::endl;
			dlclose(dlib);
			return (0);
		}

		while (!u->windowShouldClose())
			u->draw();
	}
	dlclose(dlib); // do not close library before unique_ptr's DTOR is called
	// return (0);
	return (0);
}
