#pragma once

#ifndef _DXWINDOWMANAGER_H_
#define _DXWINDOWMANAGER_H_

#include "Resources.h"			/* include resource definitions */
#include <windows.h>			/* include Windows header */
#include "WindowManager.h"		/* include WindowManager header */
#include "Window.h"				/* include Window header */
#include "DXWindow.h"			/* include DXWindow header */

/* forward namespace declaration */
namespace NocturneCore
{
	/* forward class declaration */
	class Kernel;
}

namespace NocturneCoreDX
{
	class WindowManager : public NocturneCore::WindowManager
	{
	public:
		WindowManager();
		virtual ~WindowManager();

		NocturneCore::Window* InitializeWindow(std::string sTitle, unsigned int uiWidth, unsigned int uiHeight,
			bool bFullScreen = false);
	private:
		WNDCLASSEX _windowClass;
		HINSTANCE _hInstance;
	};
}

#endif