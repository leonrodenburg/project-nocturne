#include "Window.h"		/* AbstractWindow header */

/**
 * Constructor, setting the title, width and height of the
 * window.
 *
 * @param	uiIdentifier	The window identifier
 * @param	sTitle			The title of the window
 * @param	uiWidth			The width of the window
 * @param	uiHeight		The height of the window
 * @param	bFullScreen		Whether or not the window is full screen
 */
NocturneCore::Window::Window(PN_WINDOW_ID uiIdentifier, std::string sTitle, unsigned int uiWidth, 
	unsigned int uiHeight, bool bFullScreen)
{
	/* set the identifier */
	this->_uiIdentifier = uiIdentifier;

	/* set the title */
	this->_sTitle = sTitle;

	/* set the width */
	this->_uiWidth = uiWidth;

	/* set the height */
	this->_uiHeight = uiHeight;

	/* set full screen boolean */
	this->_bFullScreen = bFullScreen;

#ifdef _DEBUG_
	LOGALL("Window constructed", "");
#endif
}

/**
 * Destructor.
 */
NocturneCore::Window::~Window()
{
#ifdef _DEBUG_
	LOGALL("Window destroyed", "");
#endif
}

/**
 * Return the identifier of the window.
 *
 * @return	The identifier of the window
 */
PN_WINDOW_ID NocturneCore::Window::GetIdentifier()
{
	/* return the identifier of the window */
	return this->_uiIdentifier;
}

/**
 * Return the title of the window.
 *
 * @return	The title of the window
 */
std::string NocturneCore::Window::GetTitle()
{
	/* return the title of the window */
	return this->_sTitle;
}

/**
 * Set the title of the window.
 *
 * @param	sTitle	The title of the window
 */
void NocturneCore::Window::SetTitle(std::string sTitle)
{
	/* set the title of the window */
	this->_sTitle = sTitle;
}

/**
 * Return the width of the window.
 *
 * @return	The width of the window
 */
unsigned int NocturneCore::Window::GetWidth()
{
	/* return the width of the window */
	return this->_uiWidth;
}

/**
 * Set the width of the window.
 *
 * @param	uiWidth		The width of the window
 */
void NocturneCore::Window::SetWidth(unsigned int uiWidth)
{
	/* set the width of the window */
	this->_uiWidth = uiWidth;
}

/**
 * Return the height of the window.
 *
 * @return	The height of the window
 */
unsigned int NocturneCore::Window::GetHeight()
{
	/* return the height of the window */
	return this->_uiHeight;
}

/**
 * Set the height of the window.
 *
 * @param	uiHeight	The height of the window
 */
void NocturneCore::Window::SetHeight(unsigned int uiHeight)
{
	/* set the height of the window */
	this->_uiHeight = uiHeight;
}

/**
 * Return whether or not the window is full screen.
 *
 * @return	Whether or not the window is full screen
 */
bool NocturneCore::Window::IsFullScreen()
{
	/* return whether or not this window is full screen */
	return this->_bFullScreen;
}