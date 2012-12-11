#pragma once

#ifndef _DXKERNEL_H_
#define _DXKERNEL_H_

#include "Resources.h"			/* include resource definitions */
#include <windows.h>			/* include Windows header */
#include <map>					/* include map header */
#include "Kernel.h"				/* include Kernel header */
#include "DXWindowManager.h"	/* include DXWindowManager header */
#include "DXDeviceManager.h"	/* include DXDeviceManager header */

namespace NocturneCoreDX
{

	class Kernel : public NocturneCore::Kernel
	{
	public:
		Kernel();
		virtual ~Kernel();

		virtual void Run();
		void RegisterWindow(NocturneCore::Window* pWindow);

		NocturneDeviceDX::DeviceManager* GetDeviceManager();
		void SetDeviceManager(NocturneDeviceDX::DeviceManager* pDeviceManager);

		static LRESULT CALLBACK WndProc(HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam);
	protected:
		void _MessageLoop();
	private:
		static std::map<NocturneCore::Window*, Kernel*> _windowList;
		NocturneDeviceDX::DeviceManager* _pDeviceManager;
		
		LRESULT _WndProc(HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam, NocturneCore::Window* pWindow);
		virtual void _UnregisterWindow(NocturneCore::Window* pWindow);

		bool _bResizing;

		/* remove after tests */
		void _Render(float fTimeDelta);
	};
}

#endif