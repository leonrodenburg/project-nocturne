#pragma once

#ifndef _DX10DEVICEMANAGER_H_
#define _DX10DEVICEMANAGER_H_

#include "Resources.h"			/* include resource definitions */
#include <D3DX10.h>				/* include D3DX 10 header */
#include "DXDeviceManager.h"	/* include DXDeviceManager header */
#include "DX10Device.h"			/* include DX10Device header */
#include "DX10SwapChain.h"		/* include DX10SwapChain header */

namespace NocturneDeviceDX10
{
	class DeviceManager : public NocturneDeviceDX::DeviceManager
	{
	public:
		DeviceManager();
		virtual ~DeviceManager();

		PN_SWAPCHAIN_ID CreateDevice(NocturneCoreDX::Window* pWindow);
	private:
		
	};
}

#endif