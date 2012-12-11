#pragma once

#ifndef _GLWINDOW_H_
#define _GLWINDOW_H_

#include "Resources.h"			/* include resource definitions */
#include <GL/glfw.h>			/* include GLFW header */
#include "Window.h"				/* include Window header */

namespace NocturneCoreGL
{
	class Window : public NocturneCore::Window
	{
	public:
		Window(PN_WINDOW_ID uiIdentifier, std::string sTitle, unsigned int uiWidth, 
			unsigned int uiHeight, bool bFullScreen = false);
		virtual ~Window();

		void Show();
		void Close();
	private:
	};
}

#endif