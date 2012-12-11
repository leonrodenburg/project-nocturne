#pragma once

#ifndef _DX11DEVICE_H_
#define _DX11DEVICE_H_

#include "Resources.h"			/* include resource definitions */
#include <D3DX11.h>				/* include D3DX 11 header */
#include <vector>				/* include vector header */
#include "DXDevice.h"			/* include DXDevice header */
#include "DX11SwapChain.h"		/* include DX10SwapChain header */
#include "DXGIHandler.h"		/* include DXGIHandler header */

namespace NocturneDeviceDX11
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
		ID3D11Device* _CreateDevice(IDXGIAdapter* pAdapter);
		ID3D11RenderTargetView* _CreateRenderTargetView(ID3D11Device* pDevice, IDXGISwapChain* pSwapChain);
		ID3D11DepthStencilView* _CreateDepthStencilView(ID3D11Device* pDevice, unsigned int uiWidth, unsigned int uiHeight);
		D3D11_VIEWPORT _CreateViewport(unsigned int uiTopLeftX, unsigned int uiTopLeftY, unsigned int uiWidth, unsigned int uiHeight);
	private:
		NocturneDeviceDX::DXGIHandler* _pDXGIHandler;
		ID3D11Device* _pHandle;
		ID3D11DeviceContext* _pContext;
		IDXGIFactory* _pFactory;
		std::vector<IDXGIAdapter*> _adapterList;
	};
}

#endif