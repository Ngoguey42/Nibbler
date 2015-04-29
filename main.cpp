// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/04/27 15:15:41 by ngoguey           #+#    #+#             //
//   Updated: 2015/04/29 08:45:58 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <iostream>
#include <cstdlib>
#include <dlfcn.h>
#include <IWindow.hpp>

int main(void)
{
	//loading lib
	void *dlib = dlopen("OpenGL.so", RTLD_LAZY | RTLD_LOCAL);
	std::cout << "dlib = " << dlib << std::endl;






	
	//getting "init" function pointer
	void *fun = dlsym(dlib, "init");
	std::cout << "fun = " << fun << std::endl;

	//casting init ptr to right type (how to improve? static cast?)
	auto f = reinterpret_cast<IWindow*(*)(std::pair<int, int>, float)>(fun);

	{
		//storing IWindow pointer into unique ptr
		std::unique_ptr<IWindow> u;
	
		try
		{
			std::unique_ptr<IWindow> tmp(f(std::make_pair(10, 10), 3.f));

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
	return (0);
}
