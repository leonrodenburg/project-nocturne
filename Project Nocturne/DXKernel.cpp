#include "DXKernel.h"			/* include DXKernel header */
#include "DX9DeviceManager.h"	/* include DX9DeviceManager header */
//#include "DX10DeviceManager.h"	/* include DX10DeviceManager header */
//#include "DX11DeviceManager.h"	/* include DX11DeviceManager header */
	
/* map Window to Kernel objects */
std::map<NocturneCore::Window*, NocturneCoreDX::Kernel*> NocturneCoreDX::Kernel::_windowList;

/**
 * Constructor. Uses the application handle and show command
 * to initialize a window manager
 */
NocturneCoreDX::Kernel::Kernel() : NocturneCore::Kernel()
{
	/* initialize a window manager */
	WindowManager* pWindowManager = new WindowManager();

	/* initialize a device manager */
	this->_pDeviceManager = new NocturneDeviceDX9::DeviceManager();

	/* set the window manager as a local member */
	this->SetWindowManager(pWindowManager);

	/* initialize resizing bool */
	this->_bResizing = false;

#ifdef _DEBUG_
	LOGALL("DXKernel constructed", "");
#endif
}

/**
 * Destructor.
 */
NocturneCoreDX::Kernel::~Kernel()
{
	/* release the device manager if there is one */
	if(NULL != this->_pDeviceManager)
	{
		/* delete the device manager */
		delete this->_pDeviceManager;
	}

#ifdef _DEBUG_
	LOGALL("DXKernel destroyed", "");
#endif
}

/**
 * Fire up the engine.
 */
void NocturneCoreDX::Kernel::Run()
{
	/* enter message loop */
	this->_MessageLoop();
}

/**
 * Register a window in the window list so the corresponding
 * kernel can be found.
 *
 * @param	pWindow		The window to register
 */
void NocturneCoreDX::Kernel::RegisterWindow(NocturneCore::Window* pWindow)
{
	/* if the window is not null */
	if(NULL != pWindow)
	{
		/* if the window has not yet been registered */
		if(Kernel::_windowList.find(pWindow) == Kernel::_windowList.end())
		{
			/* insert the window to the window list */
			Kernel::_windowList[pWindow] = this;

			/* if the device manager already has a device */
			if(NULL != this->_pDeviceManager->GetDevice())
			{
				/* register an additional swap chain with the device */
				this->_pDeviceManager->GetDevice()->CreateSwapChain(static_cast<NocturneCoreDX::Window*>(pWindow));
			}
			else
			{
				/* try to create a DirectX device for this window */
				this->_pDeviceManager->CreateDevice(static_cast<NocturneCoreDX::Window*>(pWindow));
			}

#ifdef _DEBUG_
			LOGALL("Window registered with DXKernel", "");
#endif
		}
		else
		{
			/* throw exception */
			throw NocturneCore::Exception("Window already registered with RegisterWindow() in DXKernel");
		}
	}
	else
	{
		/* throw exception */
		throw NocturneCore::Exception("Null window passed to RegisterWindow() in DXKernel");
	}
}

/**
 * Return the device manager used by the DirectX kernel.
 *
 * @return	Pointer to the device manager
 */
NocturneDeviceDX::DeviceManager* NocturneCoreDX::Kernel::GetDeviceManager()
{
	/* return the device manager */
	return this->_pDeviceManager;
}

/**
 * Set the device manager used by the DirectX kernel.
 *
 * @param	pDeviceManager		Pointer to device manager instance
 */
void NocturneCoreDX::Kernel::SetDeviceManager(NocturneDeviceDX::DeviceManager* pDeviceManager)
{
	/* set the device manager */
	this->_pDeviceManager = pDeviceManager;
}

/**
 * Handle incoming window messages.
 *
 * @param	hWnd	The window handle
 * @param	uiMsg	The message sent
 * @param	wParam	The window parameters
 * @param	lParam	User-defined parameters
 *
 * @return	Whether or not the message was handled
 */
LRESULT CALLBACK NocturneCoreDX::Kernel::WndProc(HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam)
{
	/* if the message is of the CREATE type */
	if(WM_CREATE == uiMsg)
	{
		/* persist the data in the lParams */
		SetWindowLongPtr(hWnd,
						 GWLP_USERDATA,
						 reinterpret_cast<LONG_PTR>(
							reinterpret_cast<LPCREATESTRUCT>(lParam)->lpCreateParams
						 )
		);
	}

	/* retrieve the window from the window list */
	Window* pWindow = reinterpret_cast<Window*>(
		GetWindowLongPtr(hWnd, GWLP_USERDATA)	
	);

	/* declare iterator for window list */
	std::map<NocturneCore::Window*, Kernel*>::iterator iterator;

	/* find the element */
	iterator = Kernel::_windowList.find(pWindow);

	/* if an element was found */
	if(iterator != Kernel::_windowList.end())
	{
		/* dispatch the window procedure to local version */
		return iterator->second->_WndProc(hWnd, uiMsg, wParam, lParam, pWindow);
	}
	else
	{
		/* return default handler */
		return DefWindowProc(hWnd, uiMsg, wParam, lParam);
	}
}

/**
 * Enter the message loop and dispatch incoming messages.
 */
void NocturneCoreDX::Kernel::_MessageLoop()
{
	/* declare message */
	MSG msg;

	/* zero out the memory */
	ZeroMemory(&msg, sizeof(msg));

	/* define static float for time management */
	static float fLastTime = (float)timeGetTime();

	/* while the message is not a QUIT message */
	while(WM_QUIT != msg.message)
	{
		/* peek for a message */
		if(::PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			/* translate the message */
			::TranslateMessage(&msg);

			/* dispatch the message */
			::DispatchMessage(&msg);
		}
		else
		{
			/* get current time */
			float fCurrentTime = (float)timeGetTime();

			/* calculate time delta */
			float fTimeDelta = (fCurrentTime - fLastTime) / 1000.0f;

			/* if the kernel is not busy resizing */
			if(!this->_bResizing)
			{
				/* render! */
				this->_Render(fTimeDelta);
			}
			
			/* set last time to current time */
			fLastTime = fCurrentTime;
		}
	}
}

/**
 * Local version of window procedure.
 *
 * @param	hWnd	The window handle
 * @param	uiMsg	The message sent
 * @param	wParam	The window parameters
 * @param	lParam	User-defined parameters
 *
 * @return	Whether or not the message was handled
 */
LRESULT NocturneCoreDX::Kernel::_WndProc(HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam, NocturneCore::Window* pWindow)
{
	/* define rectangle */
	RECT rect;

	/* define width and height */
	unsigned int uiWidth = 0;
	unsigned int uiHeight = 0;
	
	/* switch over the message types */
	switch(uiMsg)
	{
	/* if a key is pressed */
	case WM_KEYDOWN:
		/* if the key is the Escape-key */
		if(wParam == VK_ESCAPE)
		{
			/* destroy the window */
			DestroyWindow(hWnd);
		}

		/* if the key is the F-key */
		if(wParam == 0x46)
		{
			/* if the window is not full-screen already */
			if(!pWindow->IsFullScreen())
			{
				/* if there is only 1 initialized window (no support for multiple full-screen windows) */
				if(this->GetWindowManager()->GetWindowCount() == 1)
				{
					/* switch full-screen */
					this->GetDeviceManager()->GetDevice()->SwitchFullScreen(pWindow->GetIdentifier());
				}
			}
		}

		/* return 0 */
		return 0;
	/* if a window is resized */
	case WM_SIZE:
		/* if the message is not a minimize message */
		if(wParam != SIZE_MINIMIZED)
		{
			/* set resizing to true */
			this->_bResizing = true;

			/* get the window rectangle */
			GetClientRect(hWnd, &rect);

			/* calculate the width and height */
			uiWidth = rect.right - rect.left;
			uiHeight = rect.bottom - rect.top;

			/* set the new widt in the window */
			pWindow->SetWidth(uiWidth);

			/* set the new height in the window */
			pWindow->SetHeight(uiHeight);

			/* resize the buffers in the swap chain for this window */
			this->GetDeviceManager()->GetDevice()->ResizeSwapChain(pWindow->GetIdentifier(), uiWidth, uiHeight);

			/* set resizing to false */
			this->_bResizing = false;
		}

		/* return 0 */
		return 0;
		
	/* if it is a destroy message */
	case WM_DESTROY:
		/* unregister the window */
		this->_UnregisterWindow(pWindow);

		/* destroy the window in the window manager */
		this->GetWindowManager()->DestroyWindow(pWindow);

		/* if there are no more open windows */
		if(this->GetWindowManager()->GetWindowCount() == 0)
		{
			/* post a quit message */
			PostQuitMessage(0);
		}
		
		/* return 0 */
		return 0;
	}

	/* return default window procedure return value */
	return DefWindowProc(hWnd, uiMsg, wParam, lParam);
}

/**
 * Unregister a window from the window list.
 *
 * @param	pWindow		The window to unregister
 */
void NocturneCoreDX::Kernel::_UnregisterWindow(NocturneCore::Window* pWindow)
{
	/* delete the swap chain */
	this->GetDeviceManager()->GetDevice()->DestroySwapChain(pWindow->GetIdentifier());

	/* declare iterator for window list */
	std::map<NocturneCore::Window*, Kernel*>::iterator iterator;

	/* find the element */
	iterator = Kernel::_windowList.find(pWindow);

	/* erase the element */
	Kernel::_windowList.erase(iterator);

#ifdef _DEBUG_
	LOGALL("Window unregistered from DXKernel", "");
#endif
}

/**
 * Render!
 */
void NocturneCoreDX::Kernel::_Render(float fTimeDelta)
{
	/* get a reference to the device */
	NocturneDeviceDX::Device* pDevice = this->GetDeviceManager()->GetDevice();

	/* loop over the swap chains */
	for each(PN_SWAPCHAIN_ID i in pDevice->GetSwapChainIdentifiers())
	{
		/* set the active swap chain */
		pDevice->SetActiveSwapChain(i);

		/* clear the device */
		pDevice->Clear(pDevice->TARGET | pDevice->DEPTHSTENCIL, (i * 100), (i * 100), (i * 100));

		/* begin the scene */
		pDevice->BeginScene();

		/* end the scene */
		pDevice->EndScene();

		/* present the swap chain */
		pDevice->Present();
	}
}
