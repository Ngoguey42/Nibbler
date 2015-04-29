// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Window.cpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/04/27 14:11:05 by ngoguey           #+#    #+#             //
//   Updated: 2015/04/29 11:28:50 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

//#include <iostream>
#include "Window.hpp"
#include <cmath>

#define TMP_PADDING ((int)10)

extern "C" Window	*init(std::pair<int, int> gridSize, float cellSize)
{
	std::cout << "init from OpenGL" << std::endl;
	
	return (new Window(gridSize, cellSize));
}

auto truc = &init;
void * t = reinterpret_cast<void*>(truc);
std::function<IWindow*(std::pair<int, int>, float)> f =

									   reinterpret_cast<
	IWindow*(*)(std::pair<int, int>, float)
	>(t);

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
	_winSize(
		std::make_pair(
			static_cast<int>(std::ceilf(
								 static_cast<float>(gridSize.first) *
								 cellSize)) + TMP_PADDING * 2,
			static_cast<int>(std::ceilf(
								 static_cast<float>(gridSize.second) *
								 cellSize)) + TMP_PADDING * 2
			)),
	_topLeftCell(std::make_pair(
					 static_cast<float>(TMP_PADDING) /
					 static_cast<float>(_winSize.first) * 2.f - 1.f,
					 static_cast<float>(TMP_PADDING) /
					 static_cast<float>(_winSize.second) * -2.f + 1.f
					 )),
	_cellPadding(std::make_pair(
					 cellSize / static_cast<float>(_winSize.first) * 2.f,
					 cellSize / static_cast<float>(_winSize.second) * -2.f
					 ))
{
	if (cellSize < 3.f || gridSize.first < 1 || gridSize.second < 1)
		throw std::invalid_argument("Grid attributes invalid");
	glfwSetErrorCallback(error_callback);
	if (!glfwInit())
		exit(EXIT_FAILURE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	_win = glfwCreateWindow(_winSize.first, _winSize.second,
							"Nibbler", NULL, NULL);
	if (!_win)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	// glfwMakeContextCurrent(_win); //useless?
	// glfwSwapInterval(1); //useless?
	glfwSetKeyCallback(_win, key_callback);


	glMatrixMode(GL_PROJECTION); //useless?
	glLoadIdentity(); //useless?
	glEnable(GL_DEPTH_TEST); //added


	std::cout << "[Window](std::pair<int, int>,float) Ctor called" << std::endl;
	return ;
}

// * DESTRUCTORS ************************************************************ //
Window::~Window()
{
	glfwDestroyWindow(_win);
	glfwTerminate();
	std::cout << "[Window]() Dtor called" << std::endl;
	return ;
}

// * OPERATORS ************************************************************** //
// * GETTERS **************************************************************** //
// * SETTERS **************************************************************** //
// * MEMBER FUNCTIONS / METHODS ********************************************* //
void						Window::_put_grid(void) const
{
	int		i;

	glBegin(GL_LINES);
	glColor3f(1.f, 0.f, 0.f);
	i = 0;
	for (float y = _topLeftCell.second; i <= _tmpGridSize.second;
		 i++, y += _cellPadding.second)
	{		
		glVertex3f(_topLeftCell.first, y, 0.f);
		glVertex3f(-_topLeftCell.first, y, 0.f);		
	}
	i = 0;
	for (float x = _topLeftCell.first; i <= _tmpGridSize.first;
		 i++, x += _cellPadding.first)
	{
		glVertex3f(x, _topLeftCell.second, 0.f);
		glVertex3f(x, -_topLeftCell.second, 0.f);		
	}	
	glEnd();
	return ;
}

void						Window::_put_block(std::pair<int, int> const &pos)
	const
{
	std::pair<float, float>		topLeft(
		_topLeftCell.first + _cellPadding.first * static_cast<float>(pos.first),
		_topLeftCell.second + _cellPadding.second * static_cast<float>(pos.second));
	float					tmp;

	float z;
	
	z = -1.f;
	glColor3f(0.f, 0.5f, 0.f);
	glBegin(GL_QUADS);
	{
		glVertex3f(topLeft.first, topLeft.second, z);
		tmp = topLeft.first;
		topLeft.first += _cellPadding.first;
		glVertex3f(topLeft.first, topLeft.second, 0.f);
		topLeft.second += _cellPadding.second;
		glVertex3f(topLeft.first, topLeft.second, 0.f);
		glVertex3f(tmp, topLeft.second, z);
	}
	z = -0.f;
	glColor3f(0.f, 0.0f, 0.5f);
	{
		glVertex3f(topLeft.first, topLeft.second, z);
		tmp = topLeft.first;
		topLeft.first += _cellPadding.first;
		glVertex3f(topLeft.first, topLeft.second, z);
		topLeft.second += _cellPadding.second;
		glVertex3f(topLeft.first, topLeft.second, z);
		glVertex3f(tmp, topLeft.second, z);
	}
	z = 1.f;
	glColor3f(0.5f, 0.5f, 0.f);
	{
		glVertex3f(topLeft.first, topLeft.second, z);
		tmp = topLeft.first;
		topLeft.first += _cellPadding.first;
		glVertex3f(topLeft.first, topLeft.second, z);
		topLeft.second += _cellPadding.second;
		glVertex3f(topLeft.first, topLeft.second, z);
		glVertex3f(tmp, topLeft.second, z);
	}
	glEnd();
	return ;
}

void						Window::draw(void) const
{
	// float ratio; //useless?
	// int width, height; //useless?

	// glfwGetFramebufferSize(_win, &width, &height); //useless?
	// ratio = width / static_cast<float>(height); //useless?
	// glViewport(0, 0, width, height); //useless?
	// GLKMatrix4MakePerspective(70,(double)640/480,1,1000);
	
	// glOrtho(-1, 1, -1.f, 1.f, 1.f, -1.f); //useless?
	// glClear(GL_COLOR_BUFFER_BIT);
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) ;
	glMatrixMode(GL_MODELVIEW); //useless?
	glLoadIdentity();
	// glEnable(GL_DEPTH_TEST);
	// gluLookAt(3,3,3,0,0,0,0,0,1);
	// _put_grid();
	_put_block(std::make_pair<int, int>(1, 1));
	// glEnd();
	glFlush();
	glfwSwapBuffers(_win);
	glfwPollEvents();
	return ;
}
bool						Window::windowShouldClose(void) const
{
	return (glfwWindowShouldClose(_win));
}

// * NESTED_CLASSES ********************************************************* //
