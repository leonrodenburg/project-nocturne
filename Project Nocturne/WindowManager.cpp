#include "WindowManager.h"	/* include WindowManager header */

/**
 * Default constructor.
 */
NocturneCore::WindowManager::WindowManager() : _windowList()
{
	/* initialize current window ID to 0 */
	this->_uiCurrentWindowIdentifier = 0;

	/* initialize full-screen window management flag */
	this->_bHasFullScreenWindow = false;

#ifdef _DEBUG_
	LOGALL("WindowManager constructed", "");
#endif
}

/**
 * Destructor.
 */
NocturneCore::WindowManager::~WindowManager()
{
	/* get an iterator for the window list */
	std::map<PN_WINDOW_ID, Window*>::iterator iterator;

	/* loop over the map */
	for(iterator = this->_windowList.begin(); iterator != this->_windowList.end(); ++iterator)
	{
		/* delete the window */
		delete iterator->second;
	}

	/* clear the window list */
	this->_windowList.clear();

#ifdef _DEBUG_
	LOGALL("WindowManager destroyed", "");
#endif
}

/**
 * Return the number of windows opened.
 *
 * @return	The number of windows opened.
 */
unsigned int NocturneCore::WindowManager::GetWindowCount()
{
	/* return the count */
	return this->_windowList.size();
}

/**
 * Destroy a window by passing in the identifier.
 *
 * @param	uiIdentifier	The identifier of the window
 */
void NocturneCore::WindowManager::DestroyWindow(PN_WINDOW_ID uiIdentifier)
{
	/* delete the object */
	delete this->_windowList[uiIdentifier];

	/* delete from the window list */
	this->_windowList.erase(this->_windowList.find(uiIdentifier));

#ifdef _DEBUG_
	LOGALL("Window removed from window list", "");
#endif
}

/**
 * Destroy a window by passing in the pointer.
 *
 * @param	pWindow		Pointer to the window to destroy
 */
void NocturneCore::WindowManager::DestroyWindow(Window* pWindow)
{
	/* destroy the window */
	this->DestroyWindow(pWindow->GetIdentifier());
}

/**
 * Add a window to the window list.
 *
 * @param	pWindow		Pointer to the window
 */
void NocturneCore::WindowManager::_AddWindowToList(Window* pWindow)
{
	/* store the window */
	this->_windowList[pWindow->GetIdentifier()] = pWindow;
}

/**
 * Return a new identifier for a window.
 *
 * @return	New identifier
 */
PN_WINDOW_ID NocturneCore::WindowManager::_GetNewWindowIdentifier()
{
	/* return incremented ID */
	return ++this->_uiCurrentWindowIdentifier;
}

/**
 * Return whether or not the window manager already manages
 * a full-screen window.
 *
 * @return	True if there is a full-screen window, false if not
 */
bool NocturneCore::WindowManager::_HasFullScreenWindow()
{
	/* return the value */
	return this->_bHasFullScreenWindow;
}

/**
 * Define whether or not this window manager is managing a
 * full-screen window.
 *
 * @param	bHasFullScreenWindow	True if it manages a full-screen window, false if not
 */
void NocturneCore::WindowManager::_SetHasFullScreenWindow(bool bHasFullScreenWindow)
{
	/* set the value */
	this->_bHasFullScreenWindow = bHasFullScreenWindow;
}