#include "DX9Device.h"		/* include DX9Device header */

/**
 * Constructor, creates a DirectX 9 device using the passed in
 * window and interface.
 *
 * @param	pWindow		The window to associate with
 * @param	pInterface	The Direct3D 9 interface to use
 */
NocturneDeviceDX9::Device::Device(NocturneCoreDX::Window* pWindow, IDirect3D9* pInterface) : NocturneDeviceDX::Device()
{
	/* store device capabilities */
	pInterface->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &(this->_deviceCaps));

	/* initialize the device */
	this->_pHandle = this->_CreateDevice(pInterface, D3DADAPTER_DEFAULT, pWindow);

	/* if the window is not full-screen */
	if(!pWindow->IsFullScreen())
	{
		/* create new swap chain for window */
		this->CreateSwapChain(pWindow);
	}
	else
	{
		/* create swap chain from device */
		this->_CreateSwapChainFromDevice(pWindow->GetIdentifier(), this->_pHandle, pWindow->IsFullScreen());
	}
	
#ifdef _DEBUG_
	LOGALL("DX9Device constructed", "");
#endif
}

/**
 * Release the device
 */
NocturneDeviceDX9::Device::~Device()
{
	/* if the handle is initialized */
	if(NULL != this->_pHandle)
	{
		/* release the handle */
		this->_pHandle->Release();
	}

#ifdef _DEBUG_
	LOGALL("DX9Device destroyed", "");
#endif
}

/**
 * Create another swap chain for the present parameters passed in.
 *
 * @param	uiIdentifier		The identifier of the swap chain
 * @param	pPresentParameters	The present parameters
 *
 * @return	The identifier of the swap chain, 0 if initialization failed
 */
PN_SWAPCHAIN_ID NocturneDeviceDX9::Device::CreateSwapChain(PN_SWAPCHAIN_ID uiIdentifier, D3DPRESENT_PARAMETERS* pPresentParameters)
{
	/* set the result to 0 */
	PN_SWAPCHAIN_ID uiResult = 0;

	/* if the handle is initialized */
	if(NULL != this->_pHandle)
	{
		/* declare swap chain */
		IDirect3DSwapChain9* pSwapChain = NULL;

		/* create additional swap chain */
		this->_pHandle->CreateAdditionalSwapChain(pPresentParameters, &pSwapChain);

		/* if the swap chain is not null */
		if(NULL != pSwapChain)
		{
			/* create a depth stencil surface */
			IDirect3DSurface9* pDepthStencilSurface = this->_CreateDepthStencilSurface(this->_pHandle, pSwapChain, pPresentParameters->BackBufferWidth, pPresentParameters->BackBufferHeight);

			/* if the depth stencil surface is not null */
			if(NULL != pDepthStencilSurface)
			{
				/* create a new swap chain */
				SwapChain* pNewSwapChain = new SwapChain(uiIdentifier, pSwapChain, pDepthStencilSurface, !pPresentParameters->Windowed);

				/* add the swap chain to the list */
				this->_AddSwapChainToList(pNewSwapChain);

				/* set the result to the swap chain identifier */
				uiResult = pNewSwapChain->GetIdentifier();
			}
			else
			{
				/* throw exception */
				throw NocturneDevice::Exception("Failed to create depth stencil surface in CreateSwapChain() in DX9Device");
			}
		}
		else
		{
			/* throw exception */
			throw NocturneDevice::Exception("Failed to create additional swap chain in CreateSwapChain() in DX9Device");
		}

	}
	else
	{
		/* throw exception */
		throw NocturneDevice::Exception("Failed to create swap chain with NULL handle in CreateSwapChain() in DX9Device");
	}

	/* return the result */
	return uiResult;
}

/**
 * Create another swap chain for the window passed in.
 *
 * @param	pWindow		The window to create a swap chain for
 *
 * @return	The identifier of the new swap chain, 0 if initialization failed
 */
PN_SWAPCHAIN_ID NocturneDeviceDX9::Device::CreateSwapChain(NocturneCoreDX::Window* pWindow)
{
	/* set the result to 0 */
	PN_SWAPCHAIN_ID uiResult = 0;

	/* if the handle is initialized */
	if(NULL != this->_pHandle)
	{
		/* create present parameters structure */
		D3DPRESENT_PARAMETERS presentParameters;

		/* zero out the memory */
		ZeroMemory(&presentParameters, sizeof(presentParameters));

		/* set the present parameter properties */
		presentParameters.BackBufferWidth = pWindow->GetWidth();
		presentParameters.BackBufferHeight = pWindow->GetHeight();
		presentParameters.BackBufferFormat = D3DFMT_A8R8G8B8;
		presentParameters.BackBufferCount = 1;
		presentParameters.MultiSampleType = D3DMULTISAMPLE_NONE;
		presentParameters.MultiSampleQuality = 0;
		presentParameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
		presentParameters.hDeviceWindow = pWindow->GetWindowHandle();
		presentParameters.Windowed = !pWindow->IsFullScreen();
		presentParameters.EnableAutoDepthStencil = true;
		presentParameters.AutoDepthStencilFormat = D3DFMT_D24S8;
		presentParameters.Flags = 0;
		presentParameters.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
		presentParameters.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

		/* set vertex processing to software */
		int iVertexProc = D3DCREATE_SOFTWARE_VERTEXPROCESSING;

		/* if the device supports hardware vertex processing */
		if(this->_deviceCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		{
			/* set the vertex processing to hardware */
			iVertexProc = D3DCREATE_HARDWARE_VERTEXPROCESSING;
		}

		/* call the overloaded method with the present parameters */
		uiResult = this->CreateSwapChain(pWindow->GetIdentifier(), &presentParameters);
	}
	else
	{
		/* throw exception */
		throw NocturneDevice::Exception("Failed to create swap chain with NULL handle in CreateSwapChain() in DX9Device");
	}

	/* return the result */
	return uiResult;
}

/**
 * Resize the swap chain with the given identifier to a new width
 * and height.
 *
 * @param	uiIdentifier	The identifier of the swap chain
 * @param	uiWidth			The new width
 * @param	uiHeight		The new height
 */
void NocturneDeviceDX9::Device::ResizeSwapChain(PN_SWAPCHAIN_ID uiIdentifier, unsigned int uiWidth, unsigned int uiHeight)
{
	/* if the handle is not null */
	if(NULL != this->_pHandle)
	{
		/* get a list of swap chain identifiers */
		std::vector<PN_SWAPCHAIN_ID> vIdentifierList = this->GetSwapChainIdentifiers();

		/* declare present parameters of device */
		D3DPRESENT_PARAMETERS devicePresentParameters;

		/* declare swap chain */
		IDirect3DSwapChain9* pDeviceSwapChain = NULL;

		/* get the swap chain from the device */
		this->_pHandle->GetSwapChain(0, &pDeviceSwapChain);

		/* get the swap chain's present parameters */
		pDeviceSwapChain->GetPresentParameters(&devicePresentParameters);

		/* if the first swap chain is full-screen */
		if(!devicePresentParameters.Windowed)
		{
 			/* if the passed in identifier equals the device's swap chain */
 			if(uiIdentifier == vIdentifierList[0])
 			{
 				/* update the device present parameters with new dimensions */
 				devicePresentParameters.BackBufferWidth = uiWidth;
 				devicePresentParameters.BackBufferHeight = uiHeight;
 			}

			/* get the swap chain object from the device */
			SwapChain* pDeviceSwapChainObject = static_cast<SwapChain*>(this->_GetSwapChain(vIdentifierList[0]));

			/* release the swap chain */
			this->DestroySwapChain(pDeviceSwapChainObject->GetIdentifier());

			/* remove the first identifier from the list */
			vIdentifierList.erase(vIdentifierList.begin());
		}

		/* declare a map for the present parameters */
		std::map<PN_SWAPCHAIN_ID, D3DPRESENT_PARAMETERS> mPresentParametersList;

		/* declare an empty swap chain */
		SwapChain* pSwapChain = NULL;

		/* loop over the swap chains */
		for(std::vector<PN_SWAPCHAIN_ID>::iterator it = vIdentifierList.begin(); it != vIdentifierList.end(); ++it)
		{
			/* get the swap chain with the current ID */
			pSwapChain = static_cast<SwapChain*>(this->_GetSwapChain(*it));

			/* declare present parameters */
			D3DPRESENT_PARAMETERS presentParameters;

			/* get the present parameters from the swap chain */
			pSwapChain->GetHandle()->GetPresentParameters(&presentParameters);

			/* if the current ID equals the passed in ID */
			if(uiIdentifier == *it)
			{
				/* update the present parameters */
				presentParameters.BackBufferWidth = uiWidth;
				presentParameters.BackBufferHeight = uiHeight;
			}

			/* store the present parameters in the map */
			mPresentParametersList[*it] = presentParameters;

			/* release the swap chain */
			this->DestroySwapChain(pSwapChain->GetIdentifier());

			/* set the swap chain pointer to null */
			pSwapChain = NULL;
		}

		/* reset the device */
		HRESULT hr = this->_pHandle->Reset(&devicePresentParameters);

		/* if resetting the device failed */
		if(hr == D3DERR_INVALIDCALL)
		{
			/* throw exception */
			throw NocturneDevice::Exception("Failed to reset the device in ResetSwapChain() in DX9Device");
		}

		/* if the device is in full-screen mode */
		if(!devicePresentParameters.Windowed)
		{
			/* create a swap chain from the device */
			this->_CreateSwapChainFromDevice(uiIdentifier, this->_pHandle, !devicePresentParameters.Windowed);
		}

		/* loop over the other swap chain identifiers */
		for(std::map<PN_SWAPCHAIN_ID, D3DPRESENT_PARAMETERS>::iterator it = mPresentParametersList.begin(); it != mPresentParametersList.end(); ++it)
		{
			/* create an additional swap chain */
			this->CreateSwapChain(it->first, &it->second);
		}
	}
	else
	{
		/* throw exception */
		throw NocturneDevice::Exception("Cannot resize swap chain using NULL device handle in ResizeSwapChain() in DX9Device");
	}
}

/**
 * Set the active swap chain.
 *
 * @param	uiIdentifier	The identifier of the swap chain
 */
void NocturneDeviceDX9::Device::SetActiveSwapChain(PN_SWAPCHAIN_ID uiIdentifier)
{
	/* call superclass method */
	NocturneDeviceDX::Device::SetActiveSwapChain(uiIdentifier);

	/* get reference to the swap chain */
	SwapChain* pSwapChain = static_cast<SwapChain*>(this->_GetActiveSwapChain());

	/* set the render target to the backbuffer of the active swap chain */
	this->_pHandle->SetRenderTarget(0, pSwapChain->GetBackBufferSurface());

	/* set the depth stencil surface */
	this->_pHandle->SetDepthStencilSurface(pSwapChain->GetDepthStencilSurface());
}

/**
 * Switch the swap chain with the given ID to full-screen.
 *
 * @param	uiIdentifier	The identifier of the swap chain
 */
void NocturneDeviceDX9::Device::SwitchFullScreen(PN_SWAPCHAIN_ID uiIdentifier)
{
	/* call superclass method */
	NocturneDeviceDX::Device::SwitchFullScreen(uiIdentifier);

	/* for now, do nothing */

// 	/* declare swap chain object */
// 	SwapChain* pSwapChain = NULL;
// 	
// 	/* get swap chain object from the list */
// 	pSwapChain = static_cast<SwapChain*>(this->_GetSwapChain(uiIdentifier));
// 
// 	/* if the swap chain object is not null */
// 	if(NULL != pSwapChain)
// 	{
// 		/* if the device handle is not null */
// 		if(NULL != this->_pHandle)
// 		{
// 			/* if the swap chain is not full-screen */
// 			if(!pSwapChain->IsFullScreen())
// 			{
// 				/* declare present parameters */
// 				D3DPRESENT_PARAMETERS newPresentParameters;
// 
// 				/* get the parameters from the swap chain */
// 				pSwapChain->GetHandle()->GetPresentParameters(&newPresentParameters);
// 
// 				/* set new  present parameters properties */
// 				newPresentParameters.Windowed = true;
// 
// 				/* copy the present parameters to the device parameters */
// 				D3DPRESENT_PARAMETERS devicePresentParameters = newPresentParameters;
// 
// 				/* set the device present parameters' properties */
// 				devicePresentParameters.BackBufferWidth = 16;
// 				devicePresentParameters.BackBufferHeight = 16;
// 
// 				/* release the swap chain */
// 				this->DestroySwapChain(pSwapChain->GetIdentifier());
// 
// 				/* reset the device */
// 				HRESULT result = this->_pHandle->Reset(&devicePresentParameters);
// 			
// 				/* if the result is an invalid call */
// 				if(result == D3DERR_INVALIDCALL)
// 				{
// 					/* throw exception */
// 					throw NocturneDevice::Exception("Failed to reset device to windowed state in SwitchFullScreen() in DX9Device");
// 				}
// 
// 				/* create additional swap chain */
// 				this->CreateSwapChain(uiIdentifier, &newPresentParameters);
// 			}
// 			else
// 			{
// 				/* declare present parameters */
// 				D3DPRESENT_PARAMETERS devicePresentParameters;
// 
// 				/* get the parameters from the swap chain */
// 				pSwapChain->GetHandle()->GetPresentParameters(&devicePresentParameters);
// 
// 				/* set device parameters properties */
// 				devicePresentParameters.Windowed = false;
// 
// 				/* release the swap chain */
// 				this->DestroySwapChain(uiIdentifier);
// 
// 				/* reset the device */
// 				HRESULT hr = this->_pHandle->Reset(&devicePresentParameters);
// 
// 				/* if the device reset failed */
// 				if(hr == D3DERR_INVALIDCALL)
// 				{
// 					/* throw exception */
// 					throw NocturneDevice::Exception("Failed to reset device to full-screen state in SwitchFullScreen() in DX9Device");
// 				}
// 
// 				/* create swap chain from device */
// 				this->_CreateSwapChainFromDevice(uiIdentifier, this->_pHandle, !devicePresentParameters.Windowed);
// 			}
// 		}
// 		else
// 		{
// 			/* throw exception */
// 			throw NocturneDevice::Exception("Cannot switch full-screen mode with null device handle in SwitchFullScreen() in DX9Device");
// 		}
// 	}
// 	else
// 	{
// 		/* throw exception */
// 		throw NocturneDevice::Exception("Failed to get swap chain with given identifier in SwitchFullScreen() in DX9Device");
// 	}
}

/**
 * Begin drawing the scene.
 */
void NocturneDeviceDX9::Device::BeginScene()
{
	/* begin drawing the scene */
	this->_pHandle->BeginScene();
}

/**
 * Stop drawing the scene.
 */
void NocturneDeviceDX9::Device::EndScene()
{
	/* stop drawing the scene */
	this->_pHandle->EndScene();
}

/**
 * Clear the specified buffers with a given red, green and blue
 * value.
 *
 * @param	uiTargets	The buffers to clear
 * @param	uiRed		The red color value (0-255)
 * @param	uiGreen		The green color value (0-255)
 * @param	uiBlue		The blue color value (0-255)
 */
void NocturneDeviceDX9::Device::Clear(unsigned int uiTargets, unsigned int uiRed, 
	unsigned int uiGreen, unsigned int uiBlue)
{
	/* initialize the clear flags to 0 */
	DWORD uiFlags = 0;

	/* if the backbuffer should be cleared */
	if(uiTargets & this->TARGET)
	{
		/* add the backbuffer target to the flags */
		uiFlags |= D3DCLEAR_TARGET;
	}

	/* if the stencil buffer should be cleared */
	if(uiTargets & this->DEPTHSTENCIL)
	{
		/* add the depth buffer to the flags */
		uiFlags |= D3DCLEAR_ZBUFFER;

		/* add the stencil buffer to the flags */
		uiFlags |= D3DCLEAR_STENCIL;
	}

	/* clear the buffers */
	this->_pHandle->Clear(0, 0, uiFlags, D3DCOLOR_XRGB(uiRed, uiGreen, uiBlue), 1.0f, 0);
}

/**
 * Create a device given a Direct3D 9 interface and a dummy swap chain
 * and render target view. This makes it easier to reset the device
 * upon resizing of a window or when the device is lost.
 *
 * @param	pInterface	Pointer to the initialized interface
 * @param	uiAdapter	The number of the adapter to use
 * @param	pWindow		The first window to associate the device with
 *
 * @return	Pointer to initialized device, false if it failed
 */
IDirect3DDevice9* NocturneDeviceDX9::Device::_CreateDevice(IDirect3D9* pInterface, UINT uiAdapter, NocturneCoreDX::Window* pWindow)
{
	/* declare device */
	IDirect3DDevice9* pDevice = NULL;

	/* create present parameters structure */
	D3DPRESENT_PARAMETERS presentParameters;

	/* zero out the memory */
	ZeroMemory(&presentParameters, sizeof(presentParameters));

	/* if the window is windowed */
	if(!pWindow->IsFullScreen())
	{
		/* set the present parameter properties */
		presentParameters.BackBufferWidth = 16;
		presentParameters.BackBufferHeight = 16;
		presentParameters.Windowed = true;
	}
	else
	{
		/* set the present parameter properties */
		presentParameters.BackBufferWidth = pWindow->GetWidth();
		presentParameters.BackBufferHeight = pWindow->GetHeight();
		presentParameters.Windowed = false;
	}
	
	/* set other present parameter properties */
	presentParameters.BackBufferFormat = D3DFMT_A8R8G8B8;
	presentParameters.BackBufferCount = 1;
	presentParameters.MultiSampleType = D3DMULTISAMPLE_NONE;
	presentParameters.MultiSampleQuality = 0;
	presentParameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
	presentParameters.hDeviceWindow = pWindow->GetWindowHandle();
	
	presentParameters.EnableAutoDepthStencil = true;
	presentParameters.AutoDepthStencilFormat = D3DFMT_D24S8;
	presentParameters.Flags = 0;
	presentParameters.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	presentParameters.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	/* set vertex processing to software */
	int iVertexProc = D3DCREATE_SOFTWARE_VERTEXPROCESSING;

	/* if the device supports hardware vertex processing */
	if(this->_deviceCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
	{
		/* set the vertex processing to hardware */
		iVertexProc = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	}

	/* create the device */
	pInterface->CreateDevice(
		uiAdapter,
		D3DDEVTYPE_HAL,
		pWindow->GetWindowHandle(),
		iVertexProc,
		&presentParameters,
		&pDevice
	);

	/* return the device */
	return pDevice;
}

/**
 * Create a SwapChain object from the device passed in (used if
 * the device is initialized in full-screen).
 *
 * @param	uiIdentifier	The identifier of the swap chain
 * @param	pDevice			The device to get the swap chain from
 * @param	bIsFullScreen	Whether or not the device is in full-screen mode
 *
 * @return	The new swap chain ID, 0 if initialization failed
 */
PN_SWAPCHAIN_ID NocturneDeviceDX9::Device::_CreateSwapChainFromDevice(PN_SWAPCHAIN_ID uiIdentifier, IDirect3DDevice9* pDevice, bool bIsFullScreen)
{
	/* define the result */
	PN_SWAPCHAIN_ID uiResult = 0;

	/* declare swap chain */
	IDirect3DSwapChain9* pSwapChain = NULL;

	/* declare depth stencil buffer */
	IDirect3DSurface9* pDepthStencilSurface = NULL;

	/* if the device is not null */
	if(NULL != pDevice)
	{
		/* get the swap chain from the device */
		pDevice->GetSwapChain(0, &pSwapChain);

		/* if the swap chain is not null */
		if(NULL != pSwapChain)
		{
			/* get the depth stencil surface from the device */
			pDevice->GetDepthStencilSurface(&pDepthStencilSurface);

			/* if the depth stencil surface is not null */
			if(NULL != pDepthStencilSurface)
			{
				/* declare a new swap chain object */
				SwapChain* pNewSwapChain = NULL;
				
				/* create a new swap chain object */
				pNewSwapChain = new SwapChain(
					uiIdentifier,
					pSwapChain,
					pDepthStencilSurface,
					bIsFullScreen
				);

				/* if the swap chain object is not null */
				if(NULL != pNewSwapChain)
				{
					/* add the swap chain to the list */
					this->_AddSwapChainToList(pNewSwapChain);

					/* set the result */
					uiResult = pNewSwapChain->GetIdentifier();
				}
				else
				{
					/* throw exception */
					throw NocturneDevice::Exception("Failed to create swap chain object in _CreateSwapChainFromDevice() in DX9Device");
				}
			}
			else
			{
				/* throw exception */
				throw NocturneDevice::Exception("Failed to get depth stencil surface from device handle in _CreateSwapChainFromDevice() in DX9Device");
			}
		}
		else
		{
			/* throw exception */
			throw NocturneDevice::Exception("Failed to get swap chain from device handle in _CreateSwapChainFromDevice() in DX9Device");
		}
	}
	else
	{
		/* throw exception */
		throw NocturneDevice::Exception("Cannot get swap chain from NULL device handle in _CreateSwapChainFromDevice() in DX9Device");
	}

	/* return the result */
	return uiResult;
}

/**
 * Create a depth stencil surface for a given swap chain with the given
 * width and height.
 *
 * @param	pDevice		The device used to create the surface
 * @param	pSwapChain	The swap chain to create the depth stencil surface for
 * @param	uiWidth		The width of the surface
 * @param	uiHeight	The height of the surface
 *
 * @return	Pointer to initialized IDirect3DSurface9, null if it failed
 */
IDirect3DSurface9* NocturneDeviceDX9::Device::_CreateDepthStencilSurface(IDirect3DDevice9* pDevice, IDirect3DSwapChain9* pSwapChain, unsigned int uiWidth, unsigned int uiHeight)
{
	/* declare a depth stencil surface */
	IDirect3DSurface9* pDepthStencilSurface = NULL;

	/* if the device is not null */
	if(NULL != pDevice)
	{
		/* declare present parameters */
		D3DPRESENT_PARAMETERS presentParameters;

		/* get the present parameters from the swap chain */
		pSwapChain->GetPresentParameters(&presentParameters);

		/* create a depth stencil surface */
		pDevice->CreateDepthStencilSurface(
			uiWidth,
			uiHeight,
			presentParameters.AutoDepthStencilFormat,
			presentParameters.MultiSampleType,
			presentParameters.MultiSampleQuality,
			true,
			&pDepthStencilSurface,
			NULL
			);
	}
	else
	{
		/* throw exception */
		throw NocturneDevice::Exception("Cannot create a depth stencil view with a NULL IDirect3DDevice9 in _CreateDepthStencilSurface() in DX9Device");
	}

	/* return result */
	return pDepthStencilSurface;
}