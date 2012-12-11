#pragma once

#ifndef _DX10DEVICE_H_
#define _DX10DEVICE_H_

#include "Resources.h"			/* include resource definitions */
#include <D3DX10.h>				/* include D3DX 10 header */
#include <vector>				/* include vector header */
#include "DXDevice.h"			/* include DXDevice header */
#include "DX10SwapChain.h"		/* include DX10SwapChain header */
#include "DXGIHandler.h"		/* include DXGIHandler header */

namespace NocturneDeviceDX10
{
	class Device : public NocturneDeviceDX::Device
	{
	public:
		Device(NocturneCoreDX::Window* pWindow);
		virtual ~Device();

		PN_SWAPCHAIN_ID CreateSwapChain(NocturneCoreDX::Window* pWindow);
		void ResizeSwapChain(PN_SWAPCHAIN_ID uiIdentifier, unsigned int uiWidth, unsigned int uiHeight);
		void SetActiveSwapChain(PN_SWAPCHAIN_ID uiIdentifier);
		void DestroySwapChain(PN_SWAPCHAIN_ID uiIdentifier);
		void SwitchFullScreen(PN_SWAPCHAIN_ID uiIdentifier);

		void BeginScene();
		void EndScene();

		void Clear(unsigned int uiTargets, unsigned int uiRed, unsigned int uiGreen, unsigned int uiBlue);
	protected:
		ID3D10Device* _CreateDevice(IDXGIAdapter* pAdapter);
		ID3D10RenderTargetView* _CreateRenderTargetView(ID3D10Device* pDevice, IDXGISwapChain* pSwapChain);
		ID3D10DepthStencilView* _CreateDepthStencilView(ID3D10Device* pDevice, unsigned int uiWidth, unsigned int uiHeight);
		D3D10_VIEWPORT _CreateViewport(unsigned int uiTopLeftX, unsigned int uiTopLeftY, unsigned int uiWidth, unsigned int uiHeight);
	private:
		NocturneDeviceDX::DXGIHandler* _pDXGIHandler;
		ID3D10Device* _pHandle;
		IDXGIFactory* _pFactory;
		std::vector<IDXGIAdapter*> _adapterList;
	};
}

#endif