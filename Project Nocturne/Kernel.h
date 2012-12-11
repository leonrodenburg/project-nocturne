#pragma once

#ifndef _KERNEL_H_
#define _KERNEL_H_

#include "Resources.h"			/* include resource definitions */
#include "SceneManager.h"		/* include SceneManager header */
#include "WindowManager.h"		/* include WindowManager header */

namespace NocturneCore
{
	class Kernel
	{
	public:
		Kernel();
		virtual ~Kernel();

		static NocturneCore::Kernel* GetKernel(PN_KERNEL_TYPE iType);

		WindowManager* GetWindowManager();
		void SetWindowManager(WindowManager* pWindowManager);
		NocturneScene::SceneManager* GetSceneManager();
		void SetSceneManager(NocturneScene::SceneManager* pSceneManager);

		virtual void Run() = 0;
		virtual void RegisterWindow(Window* pWindow) = 0;
	private:
		WindowManager* _pWindowManager;
		NocturneScene::SceneManager* _pSceneManager;
	};
}

#endif