#pragma once

#ifndef _DXSWAPCHAIN_H_
#define _DXSWAPCHAIN_H_

#include "Resources.h"			/* include resource definitions */

namespace NocturneDeviceDX
{
	class SwapChain
	{
	public:
		SwapChain(PN_SWAPCHAIN_ID uiIdentifier, bool bIsFullScreen);
		virtual ~SwapChain();

		PN_SWAPCHAIN_ID GetIdentifier();
		virtual void SwitchFullScreen();
		bool IsFullScreen();

		virtual void Present() = 0;
	private:
		PN_SWAPCHAIN_ID _uiIdentifier;
		bool _bIsFullScreen;
	};
}

#endif