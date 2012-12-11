#pragma once

#ifndef _DX10SWAPCHAIN_H_
#define _DX10SWAPCHAIN_H_

#include "Resources.h"			/* include resource definitions */
#include <D3DX10.h>				/* include D3DX 10 header */
#include "DXSwapChain.h"		/* include DXSwapChain header */

namespace NocturneDeviceDX10
{
	class SwapChain : public NocturneDeviceDX::SwapChain
	{
	public:
		SwapChain(PN_SWAPCHAIN_ID uiIdentifier, IDXGISwapChain* pSwapChain, 
			ID3D10RenderTargetView* pRenderTargetView, ID3D10DepthStencilView* pDepthStencilView,
			D3D10_VIEWPORT* pViewport, bool bIsFullScreen);
		virtual ~SwapChain();

		IDXGISwapChain* GetHandle();
		void SetHandle(IDXGISwapChain* pSwapChain);

		ID3D10RenderTargetView* GetRenderTargetView();
		void SetRenderTargetView(ID3D10RenderTargetView* pRenderTargetView);
		ID3D10DepthStencilView* GetDepthStencilView();
		void SetDepthStencilView(ID3D10DepthStencilView* pDepthStencilView);
		D3D10_VIEWPORT* GetViewport();
		void SetViewport(D3D10_VIEWPORT* pViewport);

		void Present();

		void SwitchFullScreen();
	private:
		IDXGISwapChain* _pHandle;
		ID3D10RenderTargetView* _pRenderTargetView;
		ID3D10DepthStencilView* _pDepthStencilView;
		D3D10_VIEWPORT _viewport;
	};
}

#endif