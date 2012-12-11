#include "DX11Device.h"		/* include DX11Device header */

/**
 * Constructor, creates a DirectX 11 device using the passed in
 * window and interface.
 *
 * @param	pWindow		The window to associate with
 */
NocturneDeviceDX11::Device::Device(NocturneCoreDX::Window* pWindow) : NocturneDeviceDX::Device()
{
	/* initialize the DXGI handler */
	this->_pDXGIHandler = new NocturneDeviceDX::DXGIHandler();

	/* initialize the factory */
	this->_pFactory = this->_pDXGIHandler->CreateFactory();

	/* enumerate the adapters */
	this->_adapterList = this->_pDXGIHandler->EnumerateAdapters(this->_pFactory);

	/* create a device */
	this->_pHandle = this->_CreateDevice(this->_adapterList[0]);

	/* create a swap chain */
	this->CreateSwapChain(pWindow);

#ifdef _DEBUG_
	LOGALL("DX11Device constructed", "");
#endif
}

/**
 * Destructor.
 */
NocturneDeviceDX11::Device::~Device()
{
	/* if there is a DXGIHandler */
	if(NULL != this->_pDXGIHandler)
	{
		/* delete the handler */
		delete this->_pDXGIHandler;
	}

	/* if there is a context */
	if(NULL != this->_pContext)
	{
		/* release the context */
		this->_pContext->ClearState();
		this->_pContext->Flush();
		this->_pContext->Release();
	}

	/* if there is a device */
	if(NULL != this->_pHandle)
	{
		/* release the device */
		this->_pHandle->Release();
	}

	/* if there is a factory */
	if(NULL != this->_pFactory)
	{
		/* release the factory */
		this->_pFactory->Release();
	}

	/* if there are adapters in the vector */
	if(this->_adapterList.size() > 0)
	{
		/* declare iterator */
		std::vector<IDXGIAdapter*>::iterator it;

		/* loop over all adapters */
		for(it = this->_adapterList.begin(); it != this->_adapterList.end(); ++it)
		{
			/* release the adapter */
			(*it)->Release();
		}
	}

#ifdef _DEBUG_
	LOGALL("DX11Device destroyed", "");
#endif
}

/**
 * Create another swap chain for the window that is passed in.
 *
 * @param	pWindow		The window to create a swap chain for
 */
PN_SWAPCHAIN_ID NocturneDeviceDX11::Device::CreateSwapChain(NocturneCoreDX::Window* pWindow)
{
	/* define result as 0 */
	PN_SWAPCHAIN_ID uiResult = 0;

	/* if the device handle is not null */
	if(NULL != this->_pHandle)
	{
		/* if the factory is not null */
		if(NULL != this->_pFactory)
		{
			/* declare suitable mode */
			DXGI_MODE_DESC suitableMode;

			/* zero out all properties */
			ZeroMemory(&suitableMode, sizeof(suitableMode));

			/* set up properties */
			suitableMode.Width = pWindow->GetWidth();
			suitableMode.Height = pWindow->GetHeight();
			suitableMode.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

			/* find the most suitable mode */
			suitableMode = this->_pDXGIHandler->GetMostSuitableMode(this->_pHandle, suitableMode);

			/* create swap chain description */
			DXGI_SWAP_CHAIN_DESC swapChainDesc;

			/* fill in buffer properties */
			swapChainDesc.BufferDesc.Width = suitableMode.Width;
			swapChainDesc.BufferDesc.Height = suitableMode.Height;
			swapChainDesc.BufferDesc.RefreshRate.Numerator = suitableMode.RefreshRate.Numerator;
			swapChainDesc.BufferDesc.RefreshRate.Denominator = suitableMode.RefreshRate.Denominator;
			swapChainDesc.BufferDesc.Format = suitableMode.Format;
			swapChainDesc.BufferDesc.ScanlineOrdering = suitableMode.ScanlineOrdering;
			swapChainDesc.BufferDesc.Scaling = suitableMode.Scaling;

			/* fill in multisample properties */
			swapChainDesc.SampleDesc.Count = 1;
			swapChainDesc.SampleDesc.Quality = 0;

			/* fill in other properties */
			swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
			swapChainDesc.BufferCount = 1;
			swapChainDesc.OutputWindow = pWindow->GetWindowHandle();
			swapChainDesc.Windowed = !pWindow->IsFullScreen();
			swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
			swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

			/* declare a swap chain */
			IDXGISwapChain* pSwapChain = NULL;

			/* create a swap chain */
			this->_pFactory->CreateSwapChain(this->_pHandle, &swapChainDesc, &pSwapChain);

			/* if the swap chain is not null */
			if(NULL != pSwapChain)
			{
				/* make window association to prevent DXGI from handling alt-enter */
				this->_pFactory->MakeWindowAssociation(pWindow->GetWindowHandle(), DXGI_MWA_NO_WINDOW_CHANGES);

				/* create a render target view */
				ID3D11RenderTargetView* pRenderTargetView = this->_CreateRenderTargetView(this->_pHandle, pSwapChain);

				/* if the render target view is not null */
				if(NULL != pRenderTargetView)
				{
					/* create a depth stencil view */
					ID3D11DepthStencilView* pDepthStencilView = this->_CreateDepthStencilView(this->_pHandle, suitableMode.Width, suitableMode.Height);

					/* if the depth stencil view is not null */
					if(NULL != pDepthStencilView)
					{
						/* create a viewport */
						D3D11_VIEWPORT viewport = this->_CreateViewport(0, 0, suitableMode.Width, suitableMode.Height);

						/* create a new swap chain */
						SwapChain* pNewSwapChain = new SwapChain(
							pWindow->GetIdentifier(),
							pSwapChain,
							pRenderTargetView,
							pDepthStencilView,
							&viewport,
							pWindow->IsFullScreen()
						);

						/* add the swap chain to the list */
						this->_AddSwapChainToList(pNewSwapChain);
						
						/* set the result to the new swap chain identifier */
						uiResult = pNewSwapChain->GetIdentifier();
					}
					else
					{
						/* throw exception */
						throw NocturneDevice::Exception("Failed to initialize depth stencil view in CreateSwapChain() in DX11Device");
					}
				}
				else
				{
					/* throw exception */
					throw NocturneDevice::Exception("Failed to initialize render target view in CreateSwapChain() in DX11Device");
				}
			}
			else
			{
				/* throw exception */
				throw NocturneDevice::Exception("Failed to initialize swap chain in CreateSwapChain() in DX11Device");
			}
		}
		else
		{
			/* throw exception */
			throw NocturneDevice::Exception("NULL IDXGIFactory passed to CreateSwapChain() in DX11Device");
		}
	}
	else
	{
		/* throw exception */
		throw NocturneDevice::Exception("Could not initialize swap chain using NULL D3D11 device in CreateSwapChain()");
	}

	/* return the result */
	return uiResult;
}

/**
 * Resize a swap chain's buffer.
 *
 * @param	uiIdentifier	The identifier of the swap chain
 * @param	uiWidth			The new width of the swap chain
 * @param	uiHeight		The new height of the swap chain
 */
void NocturneDeviceDX11::Device::ResizeSwapChain(PN_SWAPCHAIN_ID uiIdentifier, unsigned int uiWidth, unsigned int uiHeight)
{
	/* if there is a handle to the device */
	if(NULL != this->_pContext)
	{
		/* unbind the resources from the device */
		this->_pContext->OMSetRenderTargets(0, NULL, NULL);

		/* set the viewport to null */
		this->_pContext->RSSetViewports(0, NULL);

		/* get a reference to the swap chain */
		SwapChain* pSwapChain = static_cast<SwapChain*>(this->_GetSwapChain(uiIdentifier));

		/* if the swap chain exists */
		if(NULL != pSwapChain)
		{
			/* release the swap chain's depth stencil view */
			pSwapChain->SetDepthStencilView(NULL);

			/* release the swap chain's render target view */
			pSwapChain->SetRenderTargetView(NULL);

			/* declare buffer description */
			DXGI_SWAP_CHAIN_DESC swapChainDesc;

			/* get the description from the swap chain */
			pSwapChain->GetHandle()->GetDesc(&swapChainDesc);

			/* resize the swap chain */
			HRESULT hr = pSwapChain->GetHandle()->ResizeBuffers(swapChainDesc.BufferCount, uiWidth, uiHeight, swapChainDesc.BufferDesc.Format, swapChainDesc.Flags);

			/* if resizing the buffers was successful */
			if(SUCCEEDED(hr))
			{
				/* create a new render target view for the swap chain */
				ID3D11RenderTargetView* pRenderTargetView = this->_CreateRenderTargetView(this->_pHandle, pSwapChain->GetHandle());

				/* if the render target view is not null */
				if(NULL != pRenderTargetView)
				{
					/* create a new depth stencil view for the swap chain */
					ID3D11DepthStencilView* pDepthStencilView = this->_CreateDepthStencilView(this->_pHandle, uiWidth, uiHeight);

					/* if the depth stencil view is not null */
					if(NULL != pDepthStencilView)
					{
						/* create a new viewport for the swap chain */
						D3D11_VIEWPORT viewport = this->_CreateViewport(0, 0, uiWidth, uiHeight);

						/* set the new properties of the swap chain */
						pSwapChain->SetRenderTargetView(pRenderTargetView);
						pSwapChain->SetDepthStencilView(pDepthStencilView);
						pSwapChain->SetViewport(&viewport);
					}
					else
					{
						/* throw exception */
						throw NocturneDevice::Exception("Failed to create depth stencil view in ResizeSwapChain() in DX11Device");
					}
					
				}
				else
				{
					/* throw exception */
					throw NocturneDevice::Exception("Failed to create render target view in ResizeSwapChain() in DX11Device");
				}
			}
			else
			{
				/* throw exception */
				throw NocturneDevice::Exception("Resizing the buffers failed in ResizeSwapChain() in DX11Device");
			}
		}
		else
		{
			/* throw exception */
			throw NocturneDevice::Exception("Invalid swap chain identifier passed to ResizeSwapChain() in DX11Device");
		}
	}
	else
	{
		/* throw exception */
		throw NocturneDevice::Exception("No device initialized to resize swap chain in ResizeSwapChain() in DX11Device");
	}
}

/**
 * Set the swap chain that will be used in rendering.
 *
 * @param	uiIdentifier	The identifier of the swap chain
 */
void NocturneDeviceDX11::Device::SetActiveSwapChain(PN_SWAPCHAIN_ID uiIdentifier)
{
	/* call superclass method */
	NocturneDeviceDX::Device::SetActiveSwapChain(uiIdentifier);

	/* get reference to the swap chain */
	SwapChain* pSwapChain = static_cast<SwapChain*>(this->_GetActiveSwapChain());

	/* get a reference to the render target view */
	ID3D11RenderTargetView* pRenderTargetView = pSwapChain->GetRenderTargetView();

	/* if the swap chain and render target view are not null */
	if(NULL != pSwapChain && NULL != pRenderTargetView)
	{
		/* bind the render targets to the output merger */
		this->_pContext->OMSetRenderTargets(1, &pRenderTargetView, pSwapChain->GetDepthStencilView());

		/* set viewport */
		this->_pContext->RSSetViewports(1, pSwapChain->GetViewport());
	}
	else
	{
		/* throw exception */
		throw NocturneDevice::Exception("Unknown identifier of swap chain passed to set active in SetActiveSwapChain() in DX11Device");
	}
}

/**
 * Destroy a swap chain given its identifier.
 *
 * @param	uiIdentifier	The identifier of the swap chain
 */
void NocturneDeviceDX11::Device::DestroySwapChain(PN_SWAPCHAIN_ID uiIdentifier)
{
	/* unbind the resources from the device */
	this->_pContext->OMSetRenderTargets(0, NULL, NULL);

	/* set the viewport to null */
	this->_pContext->RSSetViewports(0, NULL);

	/* get a reference to the swap chain */
	SwapChain* pSwapChain = static_cast<SwapChain*>(this->_GetSwapChain(uiIdentifier));

	/* switch to windows mode */
	pSwapChain->GetHandle()->SetFullscreenState(FALSE, NULL);

	/* call superclass method */
	NocturneDeviceDX::Device::DestroySwapChain(uiIdentifier);
}

/**
 * Switch full-screen mode in the swap chain found by passing in 
 * the identifier.
 *
 * @param	uiIdentifier	The identifier of the swap chain
 */
void NocturneDeviceDX11::Device::SwitchFullScreen(PN_SWAPCHAIN_ID uiIdentifier)
{
	/* get the swap chain */
	SwapChain* pSwapChain = static_cast<SwapChain*>(this->_GetSwapChain(uiIdentifier));

	/* declare swap chain description */
	DXGI_SWAP_CHAIN_DESC swapChainDesc;

	/* get swap chain description */
	pSwapChain->GetHandle()->GetDesc(&swapChainDesc);

	/* declare most suitable mode */
	DXGI_MODE_DESC suitableMode = this->_pDXGIHandler->GetMostSuitableMode(this->_pHandle, swapChainDesc.BufferDesc);

	/* resize the target */
	pSwapChain->GetHandle()->ResizeTarget(&suitableMode);

	/* call superclass method */
	NocturneDeviceDX::Device::SwitchFullScreen(uiIdentifier);

	/* 
	* hack because of MS fail: resize buffers '
	* see: http://forums.create.msdn.com/forums/p/44234/278737.aspx
	* see: http://forums.create.msdn.com/forums/t/45287.aspx
	*/
	this->ResizeSwapChain(uiIdentifier, suitableMode.Width, suitableMode.Height);
}

/**
 * Begin drawing the scene.
 */
void NocturneDeviceDX11::Device::BeginScene()
{
	/* do nothing */
}

/**
 * Stop drawing the scene.
 */
void NocturneDeviceDX11::Device::EndScene()
{
	/* do nothing */
}

/**
 * Clear the targets defined by the uiTargets flag with the
 * given color.
 *
 * @param	uiTargets	The targets to clear
 * @param	uiRed		The red value to use
 * @param	uiGreen		The green value to use
 * @param	uiBlue		The blue value to use
 */
void NocturneDeviceDX11::Device::Clear(unsigned int uiTargets, unsigned int uiRed, unsigned int uiGreen, unsigned int uiBlue)
{
	/* get a reference to the active swap chain */
	SwapChain* pSwapChain = static_cast<SwapChain*>(this->_GetActiveSwapChain());

	/* if the back buffer should be cleared */
	if(uiTargets & this->TARGET)
	{
		/* define the clear color array */
		float clearColor[4] = { (float)uiRed / 255, (float)uiGreen / 255, (float)uiBlue / 255, 1.0f };

		/* clear the render target view */
		this->_pContext->ClearRenderTargetView(pSwapChain->GetRenderTargetView(), clearColor);
	}

	/* if the depth stencil buffer should be cleared */
	if(uiTargets & this->DEPTHSTENCIL)
	{
		/* clear depth stencil buffer */
		this->_pContext->ClearDepthStencilView(pSwapChain->GetDepthStencilView(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	}
}

/**
 * Create a Direct3D 11 device.
 *
 * @param	pAdapter	The IDXGIAdapter to use
 *
 * @return	Pointer to initialized device, null if it failed
 */
ID3D11Device* NocturneDeviceDX11::Device::_CreateDevice(IDXGIAdapter* pAdapter)
{
	/* declare device */
	ID3D11Device* pDevice = NULL;

	/* declare context */
	ID3D11DeviceContext* pContext = NULL;

	/* define create device flags */
	UINT createDeviceFlags = 0;
#ifdef _DEBUG_
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	/* create device and swap chain, using the first (default) adapter */
	HRESULT hr = D3D11CreateDevice(
		pAdapter,
		D3D_DRIVER_TYPE_UNKNOWN,
		NULL,
		createDeviceFlags,
		NULL,
		NULL,
		D3D11_SDK_VERSION,
		&pDevice,
		NULL,
		&pContext
	);

	/* if the result is invalid */
	if(hr == D3DERR_INVALIDCALL)
	{
		/* throw exception */
		throw NocturneDevice::Exception("Failed to initialize D3D11 device in _CreateDevice() in DX11Device");
	}

	/* set the context */
	this->_pContext = pContext;

	/* return the device */
	return pDevice;
}

/**
 * Create a render target view given a D3D 11 device handle and a swap chain.
 *
 * @param	pDevice		The device handle
 * @param	pSwapChain	The swap chain to create the render target view for
 *
 * @return	Pointer to initialized ID3D11RenderTargetView, null if it failed
 */
ID3D11RenderTargetView* NocturneDeviceDX11::Device::_CreateRenderTargetView(ID3D11Device* pDevice, IDXGISwapChain* pSwapChain)
{
	/* declare render target view */
	ID3D11RenderTargetView* pRenderTargetView = NULL;

	/* declare backbuffer */
	ID3D11Texture2D* pBackBuffer = NULL;

	/* get the buffer from the swap chain */
	pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&pBackBuffer));

	/* create render target view */
	pDevice->CreateRenderTargetView(pBackBuffer, 0, &pRenderTargetView);

	/* relase the back buffer */
	pBackBuffer->Release();

	/* return the render target view */
	return pRenderTargetView;
}

/**
 * Create a depth stencil view given an initialized ID3D11Device and a
 * width and height.
 *
 * @param	pDevice		The D3D11 device
 * @param	uiWidth		The width of the depth stencil view
 * @param	uiHeight	The height of the depth stencil view
 *
 * @return	Pointer to initialized ID3D11DepthStencilView, null if it failed
 */
ID3D11DepthStencilView* NocturneDeviceDX11::Device::_CreateDepthStencilView(ID3D11Device* pDevice, unsigned int uiWidth, unsigned int uiHeight)
{
	/* declare depth stencil view */
	ID3D11DepthStencilView* pDepthStencilView = NULL;

	/* if the device is not null */
	if(NULL != pDevice)
	{
		/* create depth stencil description */
		D3D11_TEXTURE2D_DESC depthStencilDesc;

		/* fill in all the properties */
		depthStencilDesc.Width = uiWidth;
		depthStencilDesc.Height = uiHeight;
		depthStencilDesc.MipLevels = 1;
		depthStencilDesc.ArraySize = 1;
		depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthStencilDesc.SampleDesc.Count = 1;
		depthStencilDesc.SampleDesc.Quality = 0;
		depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
		depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		depthStencilDesc.CPUAccessFlags = 0;
		depthStencilDesc.MiscFlags = 0;

		/* declare depth stencil buffer */
		ID3D11Texture2D* pDepthStencilBuffer = NULL;

		/* create a texture */
		pDevice->CreateTexture2D(&depthStencilDesc, 0, &pDepthStencilBuffer);

		/* create depth stencil view */
		pDevice->CreateDepthStencilView(pDepthStencilBuffer, 0, &pDepthStencilView);

		/* release the buffer */
		pDepthStencilBuffer->Release();
	}
	else
	{
#ifdef _DEBUG_
		LOGERRORALL("Cannot create depth stencil view with NULL ID3D11Device in DX11Device", "");
#endif
	}

	/* return the depth stencil view */
	return pDepthStencilView;
}

/**
 * Return a pointer to an initialized viewport struct.
 *
 * @param	uiTopLeftX		The X-coordinate of the top left corner
 * @param	uiTopLeftY		The Y-coordinate of the top left corner
 * @param	uiWidth			The width of the viewport
 * @param	uiHeight		The height of the viewport
 *
 * @return	The initialized viewport
 */
D3D11_VIEWPORT NocturneDeviceDX11::Device::_CreateViewport(unsigned int uiTopLeftX, unsigned int uiTopLeftY, unsigned int uiWidth, unsigned int uiHeight)
{
	/* declare viewport */
	D3D11_VIEWPORT viewport;

	/* set viewport properties */
	viewport.TopLeftX = (float)uiTopLeftX;
	viewport.TopLeftY = (float)uiTopLeftY;
	viewport.Width = (float)uiWidth;
	viewport.Height = (float)uiHeight;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;

	/* return the viewport */
	return viewport;
}