#include "DXWindow.h"	/* include DXWindow header */

/**
 * Constructor, initializing a window using the passed in parameters. Note that if 
 * the window is initialized in windowed mode, the height and width specified are
 * the height and width of the client area (so excluding title bar, borders, etc.)
 *
 * @param	uiIdentifier	The identifier of the window
 * @param	sTitle			The title of the window
 * @param	uiWidth			The width of the client area
 * @param	uiHeight		The height of the client area
 * @param	windowClass		The window class used to create the window handle
 * @param	hInstance		The application handle
 * @param	bFullScreen		Whether or not the window is full screen
 */
NocturneCoreDX::Window::Window(PN_WINDOW_ID uiIdentifier, std::string sTitle, unsigned int uiWidth, unsigned int uiHeight, 
	WNDCLASSEX windowClass, HINSTANCE hInstance, bool bFullScreen) : NocturneCore::Window(uiIdentifier, sTitle, uiWidth, uiHeight, bFullScreen)
{
	/* initialize the window handle to NULL */
	this->_windowHandle = NULL;

	/* if the window should be fullscreen */
	if(bFullScreen)
	{
		/* try to initialize window */
		this->_windowHandle = ::CreateWindow(
			windowClass.lpszClassName,					/* window class name */
			sTitle.c_str(),								/* window name */
			WS_EX_TOPMOST | WS_POPUP,					/* window type */
			0,											/* x-position */
			0,											/* y-position */
			uiWidth,									/* width */
			uiHeight,									/* height */
			NULL,										/* parent window */
			NULL,										/* menu name */
			hInstance,									/* application handle */
			this										/* user-defined parameters */
		);							
	}
	else
	{
		/* define client rectangle */
		RECT clientRect;

		/* set client rectangle settings */
		clientRect.top = 0;
		clientRect.left = 0;
		clientRect.right = uiWidth;
		clientRect.bottom = uiHeight;

		/* calculate window size */
		AdjustWindowRect(
			&clientRect, 
			WS_OVERLAPPEDWINDOW,
			FALSE
		);

		/* try to initialize window */
		this->_windowHandle = ::CreateWindow(
			windowClass.lpszClassName,					/* window class name */
			sTitle.c_str(),								/* window name */
			WS_OVERLAPPEDWINDOW,						/* window type */
			CW_USEDEFAULT,								/* x-position */
			CW_USEDEFAULT,								/* y-position */
			clientRect.right - clientRect.left,			/* width */
			clientRect.bottom - clientRect.top,			/* height */
			NULL,										/* parent window */
			NULL,										/* menu name */
			hInstance,									/* application handle */
			this										/* user-defined parameters */
		);	
	}

	/* if initialization failed */
	if(NULL == this->_windowHandle)
	{
#ifdef _DEBUG_
		LOGERRORALL("DXWindow construction failed");
#endif

	}
	else
	{
#ifdef _DEBUG_
		LOGALL("DXWindow constructed");
#endif
	}
}

/**
 * Destructor
 */
NocturneCoreDX::Window::~Window()
{
	/* destroy the window handle */
	DestroyWindow(this->_windowHandle);

#ifdef _DEBUG_
	LOGALL("DXWindow destroyed");
#endif
}

/**
 * Return the window handle of this window.
 *
 * @return	The window handle
 */
HWND NocturneCoreDX::Window::GetWindowHandle()
{
	/* return the window handle */
	return this->_windowHandle;
}

/**
 * Show the window.
 */
void NocturneCoreDX::Window::Show()
{
	/* if the window is full screen */
	if(this->IsFullScreen())
	{
		/* show the window */
		::ShowWindow(this->_windowHandle, SW_SHOWMAXIMIZED);

		/* disable cursor */
		ShowCursor(false);
	}
	else
	{
		/* show the window */
		::ShowWindow(this->_windowHandle, SW_SHOWDEFAULT);
	}

	/* update the window */
	::UpdateWindow(this->_windowHandle);

#ifdef _DEBUG_
	LOGALL("DXWindow shown");
#endif
}

/**
 * Close the window.
 */
void NocturneCoreDX::Window::Close()
{
	/* close the window */
	::CloseWindow(this->_windowHandle);
}