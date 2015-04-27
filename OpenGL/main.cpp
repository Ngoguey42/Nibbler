#include <iostream>
#include <cstdlib>
#include <GLFW/glfw3.h>

static void error_callback(int error, const char* description)
{
	std::cout << description << "(" << error << ")" << std::endl;
}

static void key_callback(GLFWwindow* window, int key, int, int action, int)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

void draw_triangle(GLFWwindow* window)
{
	float ratio;
	int width, height; //useless?

	glfwGetFramebufferSize(window, &width, &height); //useless?
	ratio = width / static_cast<float>(height); //useless?
	glViewport(0, 0, width, height); //useless?
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION); //useless?
	glLoadIdentity(); //useless?
	glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f); //useless?
	glMatrixMode(GL_MODELVIEW); //useless?
	glLoadIdentity();
	glRotatef(static_cast<float>(glfwGetTime()) * 50.f, 0.f, 0.f, 1.f);
	glBegin(GL_TRIANGLES);
	glColor3f(1.f, 0.f, 0.f);
	glVertex3f(-0.6f, -0.4f, 0.f);
	glColor3f(0.f, 1.f, 0.f);
	glVertex3f(0.6f, -0.4f, 0.f);
	glColor3f(0.f, 0.f, 1.f);
	glVertex3f(0.f, 0.6f, 0.f);


	glEnd();
	glfwSwapBuffers(window);
	glfwPollEvents();
	return ;
}


void draw_grid(GLFWwindow* window)
{
	float ratio;
	int width, height; //useless?

	glfwGetFramebufferSize(window, &width, &height); //useless?
	ratio = width / static_cast<float>(height); //useless?
	glViewport(0, 0, width, height); //useless?
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION); //useless?
	glLoadIdentity(); //useless?
	glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f); //useless?
	glMatrixMode(GL_MODELVIEW); //useless?
	glLoadIdentity();
	// glRotatef(static_cast<float>(glfwGetTime()) * 50.f, 0.f, 0.f, 1.f);
	glBegin(GL_LINES);

	glColor3f(1.f, 0.f, 0.f);
	for (float y = -0.9f; y < 0.95f; y += 0.1)
	{
		glVertex3f(-0.9f, y, 0.f);
		glVertex3f(0.9f, y, 0.f);
	}
	for (float x = -0.9f; x < 0.95f; x += 0.1)
	{
		glVertex3f(x, -0.9f, 0.f);
		glVertex3f(x, 0.9f, 0.f);
	}
	/*
	glColor3f(0.f, 1.f, 0.f);
	glVertex3f(0.6f, -0.4f, 0.f);
	glColor3f(0.f, 0.f, 1.f);
	glVertex3f(0.f, 0.6f, 0.f);
	*/

	glEnd();
	glfwSwapBuffers(window);
	glfwPollEvents();
	return ;
}


void init_window(int x, int y)
{
	GLFWwindow*		window;

	window = glfwCreateWindow(x, y, "Simple example", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window); //useless?
	glfwSwapInterval(1); //useless?
	glfwSetKeyCallback(window, key_callback);
	while (!glfwWindowShouldClose(window))
	{
		// draw_triangle(window);
		draw_grid(window);
	}
	glfwDestroyWindow(window);	
	return ;
}


int main(void)
{
	glfwSetErrorCallback(error_callback);
	if (!glfwInit())
		exit(EXIT_FAILURE);
	init_window(500, 500);
	init_window(200, 200);
	glfwTerminate();	
	return (0);
}
