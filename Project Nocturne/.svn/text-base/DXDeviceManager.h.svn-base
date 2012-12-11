#pragma once

#ifndef _DXDEVICEMANAGER_H_
#define _DXDEVICEMANAGER_H_

#include "Resources.h"			/* include resource definitions */
#include "DXWindow.h"			/* include DXWindow header */
#include "DXDevice.h"			/* include DXDevice header */
#include "DXSwapChain.h"		/* include DXSwapChain header */

namespace NocturneDeviceDX
{
	class DeviceManager
	{
	public:
		DeviceManager();
		virtual ~DeviceManager();

		Device* GetDevice();
		virtual PN_SWAPCHAIN_ID CreateDevice(NocturneCoreDX::Window* pWindow) = 0;
	protected:
		void _SetDevice(Device* pDevice);
	private:
		Device* _pDevice;
	};
}

#endif