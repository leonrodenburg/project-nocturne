#pragma once

#ifndef _DX9SWAPCHAIN_H_
#define _DX9SWAPCHAIN_H_

#include "Resources.h"			/* include resource definitions */
#include <d3dx9.h>				/* include D3DX 9 header */
#include "DXSwapChain.h"		/* include DXSwapChain header */

namespace NocturneDeviceDX9
{
	class SwapChain : public NocturneDeviceDX::SwapChain
	{
	public:
		SwapChain(PN_SWAPCHAIN_ID uiIdentifier, IDirect3DSwapChain9* pSwapChain,
			IDirect3DSurface9* pDepthStencilSurface, bool bIsFullScreen);
		virtual ~SwapChain();

		IDirect3DSwapChain9* GetHandle();
		void SetHandle(IDirect3DSwapChain9* pSwapChain);
		IDirect3DSurface9* GetBackBufferSurface();
		void SetBackBufferSurface(IDirect3DSurface9* pBackBufferSurface);
		IDirect3DSurface9* GetDepthStencilSurface();
		void SetDepthStencilSurface(IDirect3DSurface9* pDepthStencilSurface);

		void Present();
	private:
		IDirect3DSwapChain9* _pHandle;
		IDirect3DSurface9* _pBackBufferSurface;
		IDirect3DSurface9* _pDepthStencilSurface;
	};
}

#endif