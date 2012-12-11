#include "GLWindow.h"	/* include OGLWindow header */

/**
 * Constructor, setting the identifier, title, heigth, width
 * and whether or not the window is full screen.
 *
 * @param	uiIdentifier	The identifier
 * @param	sTitle			The title of the window
 * @param	uiWidth			The width of the window
 * @param	uiHeight		The height of the window
 * @param	bFullScreen		Whether or not it is fullscreen
 */
NocturneCoreGL::Window::Window(PN_WINDOW_ID uiIdentifier, std::string sTitle, unsigned int uiWidth, 
	unsigned int uiHeight, bool bFullScreen) : NocturneCore::Window(uiIdentifier, sTitle, uiWidth, uiHeight, bFullScreen)
{    
	/* define result */
	int result = 1;

	/* if the window should be full screen */
	if(bFullScreen)
	{
		/* open full screen */
		result = glfwOpenWindow(uiWidth, uiHeight, 0, 0, 0, 0, 0, 0, GLFW_FULLSCREEN);
	}
	else
	{
		/* open a window */
		result = glfwOpenWindow(uiWidth, uiHeight, 0, 0, 0, 0, 0, 0, GLFW_WINDOW);
	}

	/* set the window title */
	glfwSetWindowTitle(sTitle.c_str());

	/* if opening the window failed */
	if(!result)
	{
		/* throw exception */
#ifdef _DEBUG_
		LOGERRORALL("GLWindow creation failed", "");
#endif
	}
	
#ifdef _DEBUG_
	LOGALL("GLWindow constructed", "");
#endif
}

/**
 * Destructor.
 */
NocturneCoreGL::Window::~Window()
{
#ifdef _DEBUG_
	LOGALL("OGLWindow destroyed", "")
#endif
}

/**
 * Show the window.
 */
void NocturneCoreGL::Window::Show()
{
	/* do nothing */
}

/**
 * Close the window.
 */
void NocturneCoreGL::Window::Close()
{
	/* close the window */
	glfwCloseWindow();
}