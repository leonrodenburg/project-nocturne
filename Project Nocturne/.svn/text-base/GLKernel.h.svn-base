
#pragma once

#ifndef _GLKERNEL_H_
#define _GLKERNEL_H_

#include "Resources.h"			/* include resource definitions */
#include <GL/glfw.h>			/* include GLFW headers */
#include "Kernel.h"				/* sinclude Kernel header */
#include "GLWindowManager.h"	/* include GLWindowManager header */

namespace NocturneCoreGL
{
	class Kernel : public NocturneCore::Kernel
	{
	public:
		Kernel();
		virtual ~Kernel();

		virtual void Run();
		virtual void RegisterWindow(NocturneCore::Window* pWindow);
	private:
		static std::map<unsigned int, Kernel*> _windowList;

		void _Update();
		void _Render();
	};
}

#endif