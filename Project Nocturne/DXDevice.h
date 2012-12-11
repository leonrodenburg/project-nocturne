#pragma once

#ifndef _DXDEVICE_H_
#define _DXDEVICE_H_

#include "Resources.h"			/* include resource definitions */
#include <map>					/* include map header */
#include <vector>				/* include vector header */
#include "DXSwapChain.h"		/* include DXSwapChain header */
#include "DXWindow.h"			/* include DXWindow header */

namespace NocturneDeviceDX
{
	class Device
	{
	public:
		enum ClearTarget { TARGET = 0x1, DEPTHSTENCIL = 0x2 };

		Device();
		virtual ~Device();

		virtual void Clear(unsigned int uiTargets, unsigned int uiRed, unsigned int uiGreen, unsigned int uiBlue) = 0;
		virtual void BeginScene() = 0;
		virtual void EndScene() = 0;
		virtual PN_SWAPCHAIN_ID CreateSwapChain(NocturneCoreDX::Window* pWindow) = 0;
		virtual void ResizeSwapChain(PN_SWAPCHAIN_ID uiIdentifier, unsigned int uiWidth, unsigned int uiHeight) = 0;

		virtual void Present();
		unsigned int GetSwapChainCount();
		std::vector<PN_SWAPCHAIN_ID> GetSwapChainIdentifiers();
		PN_SWAPCHAIN_ID GetActiveSwapChainIdentifier();
		virtual void SetActiveSwapChain(PN_SWAPCHAIN_ID uiIdentifier);
		virtual void DestroySwapChain(PN_SWAPCHAIN_ID uiIdentifier);
		virtual void SwitchFullScreen(PN_SWAPCHAIN_ID uiIdentifier);
	protected:
		void _AddSwapChainToList(SwapChain* pSwapChain);
		SwapChain* _GetActiveSwapChain();
		SwapChain* _GetSwapChain(PN_SWAPCHAIN_ID uiIdentifier);
	private:
		std::map<PN_SWAPCHAIN_ID, SwapChain*> _swapChainList;
		SwapChain* _pActiveSwapChain;
	};
}

#endif