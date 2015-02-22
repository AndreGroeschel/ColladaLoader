/*
The MIT License (MIT)

Copyright (c) 2010 Andre Groeschel

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#include <math.h>
#include <GL/glfw.h>
#include "render/SceneRenderer.h"
#include "render/OpenGLRenderer.h"

namespace ColladaLoader
{

OpenGLRenderer::OpenGLRenderer() :
	sceneRenderer_(new SceneRenderer), isGridVisible_(true),
	isLightEnabled_(true), isTexturingEnabled_(true), cameraRadius_(DEFAULT_CAMERA_RADIUS)
{
	lightPosition_[0] = 300.0;
	lightPosition_[1] = 300.0;
	lightPosition_[2] = 300.0;
	lightPosition_[3] = 0.0;

	lightColor_[0] = 1.0;
	lightColor_[1] = 1.0;
	lightColor_[2] = 1.0;
	lightColor_[3] = 1.0;

}

OpenGLRenderer::~OpenGLRenderer()
{
	delete sceneRenderer_;
}

void OpenGLRenderer::initialise(void)
{
	// Enable Z buffering
	glEnable(GL_DEPTH_TEST);

	GLfloat modelAmbient[] = {0.1,0.1,0.1,1.0};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, modelAmbient);
	//glEnable(GL_NORMALIZE);

	glEnable(GL_MULTISAMPLE);
}

void OpenGLRenderer::switchGridOnOff()
{
	isGridVisible_ = !isGridVisible_;
}

void OpenGLRenderer::switchLightOnOff()
{
	isLightEnabled_ = !isLightEnabled_;
}

void OpenGLRenderer::switchTexturingOnOff()
{
	isTexturingEnabled_ = !isTexturingEnabled_;
}

void OpenGLRenderer::setCameraRadius(double val)
{
	if ((val >= MIN_CAMERA_RADIUS) &&
		(val <= MAX_CAMERA_RADIUS))
		cameraRadius_ = val;
}

double OpenGLRenderer::getCameraRadius()
{
	return cameraRadius_;
}

void OpenGLRenderer::update(double timeElapsed)
{
	int width, height; // Window dimensions
	double t; // Time (in seconds)
	double field_of_view; // Camera field of view
	double camera_x, camera_y, camera_z; // Camera position

	// Get current time
	t = glfwGetTime();

	// Get window size
	glfwGetWindowSize(&width, &height);

	// Make sure that height is non-zero to avoid division by zero
	height = height < 1 ? 1 : height;

	// Set viewport
	glViewport(0, 0, width, height);

	// Clear color and depht buffers
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);

	// Calculate field of view as a function of time
//	field_of_view = 50.0 + 30.0 * sin(0.5 * t);
	field_of_view = 60.0;

	// Set up projection matrix
	glMatrixMode(GL_PROJECTION); // Select projection matrix
	glLoadIdentity(); // Start with an identity matrix
	gluPerspective( // Set perspective view
			field_of_view, // Field of view
			(double) width / (double) height, // Window aspect (assumes square pixels)
			1.0, // Near Z clipping plane
			1000.0 // Far Z clippling plane
	);

	// Calculate camera position
	//TODO: set distance value via UP and DOWN
	camera_x = cameraRadius_ * cos(0.3 * t);
	camera_z = cameraRadius_ * sin(0.3 * t);
	camera_y = 1.0;

	// Set up modelview matrix
	glMatrixMode(GL_MODELVIEW); // Select modelview matrix
	glLoadIdentity(); // Start with an identity matrix
	gluLookAt( // Set camera position and orientation
			camera_x, camera_y, camera_z, // Camera position (x,y,z)
			0.0, 1.0, 0.0, // View point (x,y,z)
			0.0, 1.0, 0.0 // Up-vector (x,y,z)
	);

	if (isGridVisible_)
	{
		// Draw a grid
		glColor3f(0.5f, 0.5f, 0.5f);
		glBegin(GL_LINES);
		for (int i = -10; i <= 10; i++)
		{
			glVertex3f(-10.0f, 0.0f, (float) i); // Line along X axis
			glVertex3f(10.0f, 0.0f, (float) i); // -"-
			glVertex3f((float) i, 0.0f, -10.0f); // Line along Z axis
			glVertex3f((float) i, 0.0f, 10.0f); // -"-
		}
		glEnd();
	}

	if (isTexturingEnabled_)
		glEnable(GL_TEXTURE_2D);

	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition_);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor_);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightColor_);

	if (isLightEnabled_)
	{
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
	}

	sceneRenderer_->update(timeElapsed);

	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);


	glFlush();
}

}

