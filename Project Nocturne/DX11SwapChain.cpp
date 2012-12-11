#include "DX11SwapChain.h"		/* include DX11SwapChain header */

/**
 * Constructor, passing in a swap chain object, a render
 * target view and a depth stencil view.
 *
 * @param	uiIdentifier		The identifier of the swap chain
 * @param	pSwapChain			The swap chain object
 * @param	pRenderTargetView	The render target view
 * @param	pDepthStencilView	The depth stencil view
 * @param	bIsFullScreen		Whether or not the swap chain is full screen
 */
NocturneDeviceDX11::SwapChain::SwapChain(PN_SWAPCHAIN_ID uiIdentifier, IDXGISwapChain* pSwapChain, ID3D11RenderTargetView* pRenderTargetView, 
	ID3D11DepthStencilView* pDepthStencilView, D3D11_VIEWPORT* pViewport, bool bIsFullScreen) : NocturneDeviceDX::SwapChain(uiIdentifier, bIsFullScreen)
{
	/* check for valid parameters */
	if(NULL != pSwapChain && NULL != pRenderTargetView && NULL != pDepthStencilView && NULL != pViewport)
	{
		/* assign the swap chain */
		this->_pHandle = pSwapChain;

		/* assign the render target view */
		this->_pRenderTargetView = pRenderTargetView;

		/* assign the depth stencil view */
		this->_pDepthStencilView = pDepthStencilView;

		/* assign the viewport */
		this->_viewport = *pViewport;

#ifdef _DEBUG_
		LOGALL("DX11SwapChain constructed");
#endif
	}
	else
	{
		/* throw exception */
		throw NocturneDevice::Exception("DX11SwapChain creation failed: invalid or null parameters passed");
	}
}

/**
 * Destructor.
 */
NocturneDeviceDX11::SwapChain::~SwapChain()
{
	/* if there is an initialized depth stencil view */
	if(NULL != this->_pDepthStencilView)
	{
		/* release the depth stencil view */
		this->_pDepthStencilView->Release();
	}

	/* if there is an initialized render target view */
	if(NULL != this->_pRenderTargetView)
	{
		/* release the render target view */
		this->_pRenderTargetView->Release();
	}

	/* if there is an initialized handle */
	if(NULL != this->_pHandle)
	{
		/* release the handle */
		this->_pHandle->Release();
	}

#ifdef _DEBUG_
	LOGALL("DX11SwapChain destroyed");
#endif
}

/**
 * Return the handle to the swap chain.
 *
 * @return	The handle
 */
IDXGISwapChain* NocturneDeviceDX11::SwapChain::GetHandle()
{
	/* return the handle */
	return this->_pHandle;
}

/**
 * Set the handle of this swap chain.
 *
 * @param	pSwapChain	The swap chain handle
 */
void NocturneDeviceDX11::SwapChain::SetHandle(IDXGISwapChain* pSwapChain)
{
	/* if the swap chain is not null */
	if(NULL != pSwapChain)
	{
		/* if there is an old swap chain */
		if(NULL != this->_pHandle)
		{
			/* release the old swap chain */
			this->_pHandle->Release();
		}

		/* assign the new swap chain */
		this->_pHandle = pSwapChain;
	}
	else
	{
		/* throw exception */
		throw NocturneDevice::Exception("NULL swap chain passed to SetHandle() in DX10SwapChain");
	}
}

/**
 * Return a pointer to the render target view of this swap chain.
 *
 * @return	The render target view
 */
ID3D11RenderTargetView* NocturneDeviceDX11::SwapChain::GetRenderTargetView()
{
	/* return the render target view */
	return this->_pRenderTargetView;
}

/**
 * Set the render target view used by this swap chain.
 *
 * @param	pRenderTargetView	Pointer to a valid render target view or null
 */
void NocturneDeviceDX11::SwapChain::SetRenderTargetView(ID3D11RenderTargetView* pRenderTargetView)
{
	/* if there is an old render target view */
	if(NULL != this->_pRenderTargetView)
	{
		/* release the old render target view */
		this->_pRenderTargetView->Release();
	}

	/* assign the new render target view */
	this->_pRenderTargetView = pRenderTargetView;
}

/**
 * Return a pointer to the depth stencil view used by this swap chain.
 *
 * @return	The depth stencil view
 */
ID3D11DepthStencilView* NocturneDeviceDX11::SwapChain::GetDepthStencilView()
{
	/* return pointer to the depth stencil view */
	return this->_pDepthStencilView;
}

/**
 * Set the depth stencil view used by this swap chain.
 *
 * @param	pDepthStencilView	Pointer to a valid depth stencil view or null
 */
void NocturneDeviceDX11::SwapChain::SetDepthStencilView(ID3D11DepthStencilView* pDepthStencilView)
{
	/* if there is an old depth stencil view */
	if(NULL != this->_pDepthStencilView)
	{
		/* release the old depth stencil view */
		this->_pDepthStencilView->Release();
	}

	/* assign the new depth stencil view */
	this->_pDepthStencilView = pDepthStencilView;
}

/**
 * Return a pointer to a viewport associated with this
 * swap chain.
 *
 * @return	Pointer to the viewport
 */
D3D11_VIEWPORT* NocturneDeviceDX11::SwapChain::GetViewport()
{
	/* return pointer to the viewport */
	return &(this->_viewport);
}

/**
 * Set the viewport used by this swap chain.
 *
 * @param	pViewport	Pointer to the viewport
 */
void NocturneDeviceDX11::SwapChain::SetViewport(D3D11_VIEWPORT* pViewport)
{
	/* if the viewport is not NULL */
	if(NULL != pViewport)
	{
		/* assign the viewport */
		this->_viewport = *pViewport;
	}
	else
	{
		/* throw exception */
		throw NocturneDevice::Exception("NULL viewport passed to SetViewport() in DX10SwapChain");
	}
}

/**
 * Present the back buffer by flipping it with the front buffer.
 */
void NocturneDeviceDX11::SwapChain::Present()
{
	/* present the swap chain */
	this->_pHandle->Present(0, 0);
}

/**
 * Switch full-screen mode.
 */
void NocturneDeviceDX11::SwapChain::SwitchFullScreen()
{
	/* call superclass constructor */
	NocturneDeviceDX::SwapChain::SwitchFullScreen();

	/* switch the full-screen mode */
	this->_pHandle->SetFullscreenState(this->IsFullScreen(), NULL);
}