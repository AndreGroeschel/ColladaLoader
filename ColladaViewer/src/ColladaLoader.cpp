#include <stdlib.h>    // For malloc() etc.
#include <stdio.h>     // For printf(), fopen() etc.
#include <math.h>      // For sin(), cos() etc.
#include <GL/glfw.h>   // For GLFW, OpenGL and GLU
#include "DaeReader.h"
#include "render/OpenGLRenderer.h"

int main(int argc, char **argv)
{
	int ok; // Flag telling if the window was opened
	int running; // Flag telling if the program is running

	// Initialize GLFW
	glfwInit();

	// Set window title


	// Open window
	glfwOpenWindowHint(GLFW_FSAA_SAMPLES,2);
	ok = glfwOpenWindow(800, 600, // Width and height of window
			8, 8, 8, // Number of red, green, and blue bits for color buffer
			8, // Number of bits for alpha buffer
			24, // Number of bits for depth buffer (Z-buffer)
			0, // Number of bits for stencil buffer
			GLFW_WINDOW // We want a desktop window (could be GLFW_FULLSCREEN)
			);


	// If we could not open a window, exit now
	if (!ok)
	{
		glfwTerminate();
		return 0;
	}

	glfwSetWindowTitle("ColladaLoader");

	// Enable sticky keys
	glfwEnable(GLFW_STICKY_KEYS);

	//Collada Reader
	ColladaLoader::DaeReader* daeReader = new ColladaLoader::DaeReader;
	if (argc > 1)
	{
		std::cout << "Param1: " << argv[1];
		daeReader->load(argv[1]);
	}
	else
		daeReader->load("media/models/seymourplane_triangulate.dae");

	//OpenGL Renderer
	ColladaLoader::OpenGLRenderer* openGLRenderer = new ColladaLoader::OpenGLRenderer;

	double oldTime = glfwGetTime();
	double currentTime = 0.0;
	double deltaTime = 0.0;

	openGLRenderer->initialise();

	// Main rendering loop
	do
	{
		currentTime = glfwGetTime();
		deltaTime = currentTime - oldTime;

		//call render method
		openGLRenderer->update(deltaTime);

		// Swap front and back buffers (we use a double buffered display)
		glfwSwapBuffers();

		if(glfwGetKey(GLFW_KEY_F1)){
			openGLRenderer->switchGridOnOff();
		}

		if(glfwGetKey(GLFW_KEY_F2)){
			openGLRenderer->switchLightOnOff();
		}

		if(glfwGetKey(GLFW_KEY_F3)){
			openGLRenderer->switchTexturingOnOff();
		}

		if (glfwGetKey(GLFW_KEY_UP))
		{
			// decrease camera distance
			openGLRenderer->setCameraRadius(openGLRenderer->getCameraRadius() - 0.5);
		}

		if (glfwGetKey(GLFW_KEY_DOWN))
		{
			// increase camera distance
			openGLRenderer->setCameraRadius(openGLRenderer->getCameraRadius() + 0.5);
		}


		// Check if the escape key was pressed, or if the window was closed
		running = !glfwGetKey(GLFW_KEY_ESC) && glfwGetWindowParam(GLFW_OPENED);
	} while (running);

	// Terminate GLFW
	glfwTerminate();

	delete openGLRenderer;
	delete daeReader;

	// Exit program
	return 0;
}
