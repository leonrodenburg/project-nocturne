#pragma once

#ifndef _WINDOWMANAGER_H_
#define _WINDOWMANAGER_H_

#include "Resources.h"			/* include resource definitions */
#include <string>				/* include string header */
#include <map>					/* include map header */
#include "Window.h"				/* include Window header */

namespace NocturneCore
{
	class WindowManager
	{
	public:
		WindowManager();
		virtual ~WindowManager();

		unsigned int GetWindowCount();

		virtual Window* InitializeWindow(std::string sTitle, unsigned int uiWidth, unsigned int uiHeight,
			bool bFullScreen = false) = 0;
		void DestroyWindow(PN_WINDOW_ID uiIdentifier);
		void DestroyWindow(Window* pWindow);
	protected:
		void _AddWindowToList(Window* pWindow);
		PN_WINDOW_ID _GetNewWindowIdentifier();
		bool _HasFullScreenWindow();
		void _SetHasFullScreenWindow(bool bHasFullScreenWindow);
	private:
		std::map<PN_WINDOW_ID, Window*> _windowList;
		PN_WINDOW_ID _uiCurrentWindowIdentifier;
		bool _bHasFullScreenWindow;
	};
}

#endif