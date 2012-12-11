#include "GLKernel.h"		/* include OGLKernel header */

/* map Window to Kernel objects */
std::map<unsigned int, NocturneCoreGL::Kernel*> NocturneCoreGL::Kernel::_windowList;

/**
 * Default constructor.
 */
NocturneCoreGL::Kernel::Kernel() : NocturneCore::Kernel()
{
	/* initialize GLFW */
	glfwInit();

	/* initialize a window manager */
	WindowManager* pWindowManager = new WindowManager();

	/* set the window manager */
	this->SetWindowManager(pWindowManager);

#ifdef _DEBUG_
    LOGALL("OGLKernel constructed", "")
#endif
}

/**
 * Destructor.
 */
NocturneCoreGL::Kernel::~Kernel()
{
	/* terminate GLFW session */
	glfwTerminate();

#ifdef _DEBUG_
    LOGALL("OGLKernel destroyed", "")
#endif
}

/**
 * Start the engine.
 */
void NocturneCoreGL::Kernel::Run()
{    
	/* initialize sentinel value */
	int running = GL_TRUE;

	/* while the engine should run */
	while(running)
	{
		/* update the matrices */
		this->_Update();

		/* render */
		this->_Render();

		/* check if we should still run the application */
		running = glfwGetWindowParam(GLFW_OPENED) && !glfwGetKey(GLFW_KEY_ESC);
	}
}

/**
 * Register a window with the Kernel.
 */
void NocturneCoreGL::Kernel::RegisterWindow(NocturneCore::Window* pWindow)
{
	/* store the window in the window list */
	Kernel::_windowList[pWindow->GetIdentifier()] = this;

#ifdef _DEBUG_
	LOGALL("Window registered with OGLKernel", "");
#endif
}

/**
 * Update the scene.
 */
void NocturneCoreGL::Kernel::_Update()
{
	/* declare window width and height */
	int width, height;

	/* get the window size */
	glfwGetWindowSize(&width, &height);

	/* set viewport size */
	glViewport(0, 0, width, height);

	/* set matrix mode to projection */
	glMatrixMode(GL_PROJECTION);

	/* load identify matrix */
	glLoadIdentity();

	/* define orthographic matrix */
	gluOrtho2D(0, width, 0, height);

	/* set matrix mode to modelview */
	glMatrixMode(GL_MODELVIEW);

	/* load identity */
	glLoadIdentity();

	/* define starting time */
	static float lastTime = 0;

	/* calculate current time */
	float currentTime = static_cast<float>(glfwGetTime());

	/* define static translation */
	static float transX = 0.0f;

	/* increment translation */
	transX += (currentTime - lastTime) * 100.0f;

	/* translate */
	glTranslatef(transX, 0.0f, 0.0f);

	/* set last time */
	lastTime = currentTime;

	/* if the quad is out of view */
	if(transX > width)
	{
		/* set to 0 */
		transX = -128.0f;
	}
}

/**
 * Render the scene.
 */
void NocturneCoreGL::Kernel::_Render()
{
	/* clear the buffer */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/* begin drawing */
	glBegin(GL_QUADS);

	/* define four points */
	glVertex2f(0.0f, 0.0f);
	glVertex2f(0.0f, 128.0f);
	glVertex2f(128.0f, 128.0f);
	glVertex2f(128.0f, 0.0f);
	
	/* stop drawing */
	glEnd();

	/* swap the buffer */
	glfwSwapBuffers();
}