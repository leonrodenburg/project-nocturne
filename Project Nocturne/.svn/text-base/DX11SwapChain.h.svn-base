#pragma once

#ifndef _DX11SWAPCHAIN_H_
#define _DX11SWAPCHAIN_H_

#include "Resources.h"			/* include resource definitions */
#include <D3DX11.h>				/* include D3DX 11 header */
#include "DXSwapChain.h"		/* include DXSwapChain header */

namespace NocturneDeviceDX11
{
	class SwapChain : public NocturneDeviceDX::SwapChain
	{
	public:
		SwapChain(PN_SWAPCHAIN_ID uiIdentifier, IDXGISwapChain* pSwapChain, 
			ID3D11RenderTargetView* pRenderTargetView, ID3D11DepthStencilView* pDepthStencilView,
			D3D11_VIEWPORT* pViewport, bool bIsFullScreen);
		virtual ~SwapChain();

		IDXGISwapChain* GetHandle();
		void SetHandle(IDXGISwapChain* pSwapChain);

		ID3D11RenderTargetView* GetRenderTargetView();
		void SetRenderTargetView(ID3D11RenderTargetView* pRenderTargetView);
		ID3D11DepthStencilView* GetDepthStencilView();
		void SetDepthStencilView(ID3D11DepthStencilView* pDepthStencilView);
		D3D11_VIEWPORT* GetViewport();
		void SetViewport(D3D11_VIEWPORT* pViewport);

		void Present();

		void SwitchFullScreen();
	private:
		IDXGISwapChain* _pHandle;
		ID3D11RenderTargetView* _pRenderTargetView;
		ID3D11DepthStencilView* _pDepthStencilView;
		D3D11_VIEWPORT _viewport;
	};
}

#endif