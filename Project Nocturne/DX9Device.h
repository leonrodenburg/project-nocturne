#pragma once

#ifndef _DX9DEVICE_H_
#define _DX9DEVICE_H_

#include "Resources.h"			/* include resource definitions */
#include <d3dx9.h>				/* include D3DX 9 header */
#include "DXDevice.h"			/* include DXDevice header */
#include "DXWindow.h"			/* include DXWindow header */
#include "DX9SwapChain.h"		/* include DX9SwapChain header */

namespace NocturneDeviceDX9
{
	class Device : public NocturneDeviceDX::Device
	{
	public:
		Device(NocturneCoreDX::Window* pWindow, IDirect3D9* pInterface);
		virtual ~Device();

		PN_SWAPCHAIN_ID CreateSwapChain(PN_SWAPCHAIN_ID uiIdentifier, D3DPRESENT_PARAMETERS* pPresentParameters);
		PN_SWAPCHAIN_ID CreateSwapChain(NocturneCoreDX::Window* pWindow);
		void ResizeSwapChain(PN_SWAPCHAIN_ID uiIdentifier, unsigned int uiWidth, unsigned int uiHeight);
		void SetActiveSwapChain(PN_SWAPCHAIN_ID uiIdentifier);
		void SwitchFullScreen(PN_SWAPCHAIN_ID uiIdentifier);

		void BeginScene();
		void EndScene();

		void Clear(unsigned int uiTargets, unsigned int uiRed, unsigned int uiGreen, unsigned int uiBlue);
	protected:
		IDirect3DDevice9* _CreateDevice(IDirect3D9* pInterface, UINT uiAdapter, NocturneCoreDX::Window* pWindow);
		PN_SWAPCHAIN_ID _CreateSwapChainFromDevice(PN_SWAPCHAIN_ID uiIdentifier, IDirect3DDevice9* pDevice, bool bIsFullScreen);
		IDirect3DSurface9* _CreateDepthStencilSurface(IDirect3DDevice9* pDevice, IDirect3DSwapChain9* pSwapChain, unsigned int uiWidth, unsigned int uiHeight);
	private:
		IDirect3DDevice9* _pHandle;
		D3DCAPS9 _deviceCaps;
	};
}

#endif