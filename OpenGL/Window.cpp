// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Window.cpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/04/27 14:11:05 by ngoguey           #+#    #+#             //
//   Updated: 2015/04/27 15:15:22 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

//#include <iostream>
#include "Window.hpp"
#include <cmath>


// * STATICS **************************************************************** //
// * CONSTRUCTORS *********************************************************** //
static void error_callback(int error, const char* description)
{
	std::cout << description << "(" << error << ")" << std::endl;
}

static void key_callback(GLFWwindow* window, int key, int, int action, int)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

Window::Window(std::pair<int, int> gridSize, float cellSize) :
	_tmpGridSize(gridSize),
	_cellSize(cellSize),
	_tmpWinSize(
		std::make_pair(
			static_cast<int>(std::ceilf(
								 static_cast<float>(gridSize.first) *
								 cellSize)) + 10 * 2,
			static_cast<int>(std::ceilf(
								 static_cast<float>(gridSize.second) *
								 cellSize)) + 10 * 2
			))
{
	std::cout << "[Window](std::pair<int>,std::pair<int>) Ctor called" << std::endl;
	// glfwSetErrorCallback(error_callback);
	if (!glfwInit())
		exit(EXIT_FAILURE);	
	_win = glfwCreateWindow(_tmpWinSize.first, _tmpWinSize.second,
							"Simple example", NULL, NULL);
	if (!_win)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	// glfwMakeContextCurrent(_win); //useless?
	// glfwSwapInterval(1); //useless?
	// glfwSetKeyCallback(_win, key_callback);
	return ;
}

// * DESTRUCTORS ************************************************************ //
Window::~Window()
{
	std::cout << "[Window]() Dtor called" << std::endl;
	glfwDestroyWindow(_win);
	glfwTerminate();
	return ;
}

// * OPERATORS ************************************************************** //
// * GETTERS **************************************************************** //
// * SETTERS **************************************************************** //
// * MEMBER FUNCTIONS / METHODS ********************************************* //
void						Window::_put_grid(void) const
{
	glBegin(GL_LINES);
	glColor3f(1.f, 0.f, 0.f);
	for (float y = -0.9f; y < 0.95f; y += 0.1)
	{
		glVertex3f(-0.9f, y, 0.f);
		glVertex3f(0.9f, y, 0.f);
	}
	glBegin(GL_LINE_STRIP);
	for (float x = -0.9f; x < 0.95f; x += 0.1)
	{
		glVertex3f(x, -0.9f, 0.f);
		glVertex3f(x, 0.9f, 0.f);
	}
	return ;
}

void						Window::draw(void) const
{
	// float ratio; //useless?
	// int width, height; //useless?

	// glfwGetFramebufferSize(_win, &width, &height); //useless?
	// ratio = width / static_cast<float>(height); //useless?
	// glViewport(0, 0, width, height); //useless?
	glClear(GL_COLOR_BUFFER_BIT);
	// glMatrixMode(GL_PROJECTION); //useless?
	// glLoadIdentity(); //useless?
	// glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f); //useless?
	// glMatrixMode(GL_MODELVIEW); //useless?
	glLoadIdentity();
	_put_grid();
	glEnd();
	glfwSwapBuffers(_win);
	glfwPollEvents();
	return ;
}
bool						Window::windowShouldClose(void) const
{
	return (glfwWindowShouldClose(_win));
}


// * NESTED_CLASSES ********************************************************* //
