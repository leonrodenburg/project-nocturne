#pragma once
#ifndef _GLWINDOWMANAGER_H_
#define _GLWINDOWMANAGER_H_

#include "Resources.h"			/* include resource definitions */
#include <GL/glfw.h>			/* include GLFW header */
#include "WindowManager.h"		/* include WindowManager header */
#include "GLWindow.h"			/* include GLWindow header */

namespace NocturneCoreGL
{
	class WindowManager : public NocturneCore::WindowManager
	{
	public:
		WindowManager();
		virtual ~WindowManager();

		NocturneCore::Window* InitializeWindow(std::string sTitle, unsigned int uiWidth, unsigned int uiHeight,
			bool bFullScreen);
	private:
	};
}

#endif