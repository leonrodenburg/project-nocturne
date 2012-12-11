#include "DXWindowManager.h"	/* include DXWindowManager header */
#include "DXKernel.h"			/* include DXKernel header */

/**
 * Constructor. Creates and registers a window class, sets the application handle
 * and show command as local member variables and calls parent constructor.
 */
NocturneCoreDX::WindowManager::WindowManager() : NocturneCore::WindowManager()
{
	/* find the HINSTANCE */
	HINSTANCE hInstance = GetModuleHandle(NULL);

	/* declare window class */
	WNDCLASSEX windowClass;

	/* fill window class structure */
	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.style = CS_HREDRAW | CS_VREDRAW;	
	windowClass.lpfnWndProc = Kernel::WndProc;
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;
	windowClass.hInstance = hInstance;
	windowClass.hIcon = ::LoadIcon(hInstance, (LPCTSTR)IDI_APPLICATION);
	windowClass.hCursor = ::LoadCursor(hInstance, (LPCTSTR)IDC_ARROW);
	windowClass.hbrBackground = NULL;
	windowClass.lpszMenuName = NULL;
	windowClass.lpszClassName = reinterpret_cast<LPCTSTR>("NocturneWindow");
	windowClass.hIconSm = NULL;

	/* register the window class */
	if(!::RegisterClassEx(&windowClass))
	{
#ifdef _DEBUG_
		LOGALL("DXWindowManager construction failed");
#endif
	}
	else
	{
#ifdef _DEBUG_
		LOGALL("DXWindowManager constructed");
#endif
	}

	/* set the window class as a local member */
	this->_windowClass = windowClass;

	/* set the HINSTANCE as a local member */
	this->_hInstance = hInstance;
}

/**
 * Destructor.
 */
NocturneCoreDX::WindowManager::~WindowManager()
{
#ifdef _DEBUG_
	LOGALL("DXWindowManager destroyed");
#endif
}

/**
 * Initialize a window object and add it to the window list.
 *
 * @param	sTitle		The title of the window
 * @param	uiWidth		The width of the window
 * @param	uiHeight	The height of the window
 * @param	pKernel		The kernel requesting a new window
 *
 * @return	Pointer to initialized Window
 */
NocturneCore::Window* NocturneCoreDX::WindowManager::InitializeWindow(std::string sTitle, unsigned int uiWidth, 
	unsigned int uiHeight, bool bFullScreen)
{
	/* declare window object */
	Window* pWindow = NULL;

	/* if there is no full-screen window already */
	if(!this->_HasFullScreenWindow())
	{
		/* get identifier for window */
		PN_WINDOW_ID uiIdentifier = this->_GetNewWindowIdentifier();

		/* create a new window object */
		pWindow = new Window(uiIdentifier, sTitle, uiWidth, uiHeight, this->_windowClass, 
			this->_hInstance, bFullScreen);

		/* if the window is NULL */
		if(NULL != pWindow)
		{
			/* add the window to the window list */
			this->_AddWindowToList(pWindow);

			/* if this window is full-screen */
			if(pWindow->IsFullScreen())
			{
				/* notify the parent */
				this->_SetHasFullScreenWindow(true);
			}

#ifdef _DEBUG_
			LOGALL("DXWindow added to window list");
#endif
		}
		else
		{
			/* throw exception */
			NocturneCore::Exception("Failed to add window to window list");
		}
	}
	else
	{
		/* throw exception */
		NocturneCore::Exception("Cannot create DXWindow: multiple windows not allowed if full-screen");
	}

	/* return the window pointer */
	return pWindow;
}