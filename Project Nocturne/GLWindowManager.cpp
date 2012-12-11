#include "GLWindowManager.h"	/* include OGLWindowManager header */

/**
 * Default constructor.
 */
NocturneCoreGL::WindowManager::WindowManager() : NocturneCore::WindowManager()
{

}

/**
 * Destructor.
 */
NocturneCoreGL::WindowManager::~WindowManager()
{
#ifdef _DEBUG_
	LOGALL("OGLWindowManager destroyed", "");
#endif
}

/**
 * Initialize a window.
 *
 * @param	sTitle			The title of the window
 * @param	uiWidth			The width of the window
 * @param	uiHeight		The height of the window
 * @param	bFullScreen		Whether or not the window is full screen
 */
NocturneCore::Window* NocturneCoreGL::WindowManager::InitializeWindow(std::string sTitle, unsigned int uiWidth, 
	unsigned int uiHeight, bool bFullScreen)
{
	/* declare new window pointer */
	Window* pWindow = NULL;

	/* if the window manager doesn't have a full-screen window yet */
	if(!this->_HasFullScreenWindow())
	{
		/* get identifier for window */
		PN_WINDOW_ID uiIdentifier = this->_GetNewWindowIdentifier();

		/* create the window */
		pWindow = new Window(uiIdentifier, sTitle, uiWidth, uiHeight, bFullScreen);

		/* if the window is NULL */
		if(NULL != pWindow)
		{
			/* add the window to the window list */
			this->_AddWindowToList(pWindow);

#ifdef _DEBUG_
			LOGALL("OGLWindow added to window list", "");
#endif
		}
		else
		{
#ifdef _DEBUG_
			LOGERRORALL("Failed to add window to window list", "");
#endif
		}
	}
	else
	{
#ifdef _DEBUG_
		LOGERRORALL("Cannot create GLWindow: multiple windows not allowed if full-screen");
#endif
	}

	/* return the window pointer */
	return pWindow;
}

