#pragma once

#ifndef _DX9DEVICEMANAGER_H_
#define _DX9DEVICEMANAGER_H_

#include "Resources.h"			/* include resource definitions */
#include <d3dx9.h>				/* include D3DX 9 header */
#include "DXDeviceManager.h"	/* include DXDeviceManager header */
#include "DX9Device.h"			/* include DX9Device header */
#include "DX9SwapChain.h"		/* include DX9SwapChain header */

namespace NocturneDeviceDX9
{
	class DeviceManager : public NocturneDeviceDX::DeviceManager
	{
	public:
		DeviceManager();
		virtual ~DeviceManager();

		PN_SWAPCHAIN_ID CreateDevice(NocturneCoreDX::Window* pWindow);
	private:
		IDirect3D9* _pInterface;
	};
}

#endif