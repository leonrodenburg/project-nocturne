#pragma once

#ifndef _DXWINDOW_H_
#define _DXWINDOW_H_

#include "Resources.h"			/* include resource definitions */
#include <windows.h>			/* include Windows header */
#include <string>				/* include string header */
#include "Window.h"				/* include Window header */

namespace NocturneCoreDX
{
	class Window : public NocturneCore::Window
	{
	public:
		Window(PN_WINDOW_ID uiIdentifier, std::string sTitle, unsigned int uiWidth, unsigned int uiHeight, 
			WNDCLASSEX windowClass, HINSTANCE hInstance, bool bFullScreen = false);		
		virtual ~Window();

		HWND GetWindowHandle();

		void Show();
		void Close();
	private:
		HWND _windowHandle;
	};
}

#endif