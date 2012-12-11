#include "DX9SwapChain.h"	/* include DX9SwapChain headers */

/**
 * Constructor, setting the swap chain handle.
 *
 * @param	pSwapChain	The swap chain handle
 */
NocturneDeviceDX9::SwapChain::SwapChain(PN_SWAPCHAIN_ID uiIdentifier, IDirect3DSwapChain9* pSwapChain,
	IDirect3DSurface9* pDepthStencilSurface, bool bIsFullScreen) : 
	NocturneDeviceDX::SwapChain(uiIdentifier, bIsFullScreen)
{
	/* if the swap chain is not NULL */
	if(NULL != pSwapChain)
	{
		/* set the handle */
		this->_pHandle = pSwapChain;

		/* declare back buffer surface */
		IDirect3DSurface9* pBackBufferSurface = NULL;

		/* get the back buffer surface from the swap chain */
		this->_pHandle->GetBackBuffer(0, D3DBACKBUFFER_TYPE_MONO, &pBackBufferSurface);

		/* if the back buffer surface is not null */
		if(NULL != pBackBufferSurface)
		{
			/* set the back buffer surface */
			this->_pBackBufferSurface = pBackBufferSurface;

			/* if the depth stencil surface is not null */
			if(NULL != pDepthStencilSurface)
			{
				/* set the depth stencil surface */
				this->_pDepthStencilSurface = pDepthStencilSurface;

#ifdef _DEBUG_
				LOGALL("DX9SwapChain constructed", "");
#endif
			}
			else
			{
				/* throw exception */
				throw NocturneDevice::Exception("Failed to create DX9SwapChain with NULL depth stencil surface");
			}	
		}
		else
		{
			/* throw exception */
			throw NocturneDevice::Exception("Failed to create DX9SwapChain because the back buffer could not be retrieved");
		}
	}
	else
	{
		/* throw exception */
		throw NocturneDevice::Exception("Failed to create DX9SwapChain with NULL swap chain handle");
	}
}

/**
 * Destructor.
 */
NocturneDeviceDX9::SwapChain::~SwapChain()
{
	/* if there is a depth stencil surface */
	if(NULL != this->_pDepthStencilSurface)
	{
		/* release the depth stencil surface */
		this->_pDepthStencilSurface->Release();
	}

	/* if there is a back buffer surface */
	if(NULL != this->_pBackBufferSurface)
	{
		/* release the back buffer surface */
		this->_pBackBufferSurface->Release();
	}

	/* if there is a swap chain */
	if(NULL != this->_pHandle)
	{
		/* release the swap chain */
		this->_pHandle->Release();
	}

#ifdef _DEBUG_
	LOGALL("DX9SwapChain destroyed")
#endif
}

/**
 * Return the handle to the swap chain.
 *
 * @return	The swap chain handle
 */
IDirect3DSwapChain9* NocturneDeviceDX9::SwapChain::GetHandle()
{
	/* return the handle */
	return this->_pHandle;
}

/**
 * Set the swap chain handle.
 *
 * @param	pSwapChain	The swap chain handle
 */
void NocturneDeviceDX9::SwapChain::SetHandle(IDirect3DSwapChain9* pSwapChain)
{
	/* if there is an old handle */
	if(NULL != this->_pHandle)
	{
		/* release the old handle */
		this->_pHandle->Release();
	}

	/* set the swap chain handle */
	this->_pHandle = pSwapChain;
}

/**
 * Return the back buffer surface.
 *
 * @return	The back buffer surface
 */
IDirect3DSurface9* NocturneDeviceDX9::SwapChain::GetBackBufferSurface()
{
	/* return the back buffer surface */
	return this->_pBackBufferSurface;
}

/**
 * Set the back buffer surface used by the swap chain.
 *
 * @param	pBackBufferSurface	The new back buffer surface (or NULL to release old surface)
 */
void NocturneDeviceDX9::SwapChain::SetBackBufferSurface(IDirect3DSurface9* pBackBufferSurface)
{
	/* if there is an old back buffer surface */
	if(NULL != this->_pBackBufferSurface)
	{
		/* release the old surface */
		this->_pBackBufferSurface->Release();
	}

	/* set the new back buffer surface */
	this->_pBackBufferSurface = pBackBufferSurface;
}

/**
 * Return the depth stencil surface.
 *
 * @return	The depth stencil surface
 */
IDirect3DSurface9* NocturneDeviceDX9::SwapChain::GetDepthStencilSurface()
{
	/* return the depth stencil surface */
	return this->_pDepthStencilSurface;
}

/**
 * Set the depth stencil surface.
 *
 * @param	pDepthStencilSurface	The depth stencil surface (or NULL to release old surface)
 */
void NocturneDeviceDX9::SwapChain::SetDepthStencilSurface(IDirect3DSurface9* pDepthStencilSurface)
{
	/* if there is an old depth stencil surface */
	if(NULL != this->_pDepthStencilSurface)
	{
		/* release the old surface */
		this->_pDepthStencilSurface->Release();
	}

	/* set the depth stencil surface */
	this->_pDepthStencilSurface = pDepthStencilSurface;
}

/**
 * Present the swap chain's buffer contents.
 */
void NocturneDeviceDX9::SwapChain::Present()
{
	/* if the handle is not null */
	if(NULL != this->_pHandle)
	{
		/* present the swap chain's contents */
		this->_pHandle->Present(0, 0, 0, 0, 0);
	}
}


