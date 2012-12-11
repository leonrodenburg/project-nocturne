#include "DX9DeviceManager.h"	/* include DX9DeviceManager header */

/**
 * Default constructor.
 */
NocturneDeviceDX9::DeviceManager::DeviceManager() : NocturneDeviceDX::DeviceManager()
{
	/* set the interface to NULL */
	this->_pInterface = NULL;

	/* initialize a graphics interface */
	this->_pInterface = Direct3DCreate9(D3D_SDK_VERSION);

	/* if the interface is NULL */
	if(NULL == this->_pInterface)
	{
		/* throw exception */
		throw NocturneDevice::Exception("DX9DeviceManager creation failed: unable to get D3D9 interface");
	}

#ifdef _DEBUG_
	LOGALL("DX9DeviceManager constructed", "");
#endif
}

/**
 * Destructor.
 */
NocturneDeviceDX9::DeviceManager::~DeviceManager()
{
	/* if the interface is not null */
	if(NULL != this->_pInterface)
	{
		/* release the interface */
		this->_pInterface->Release();
	}

#ifdef _DEBUG_
	LOGALL("DX9DeviceManager destroyed", "");
#endif
}

/**
 * Create a device suitable for DirectX 9.
 *
 * @param	pWindow		The window to associate the device for
 *
 * @return	The ID of the automatically created swap chain, 0 if initialization failed
 */
PN_SWAPCHAIN_ID NocturneDeviceDX9::DeviceManager::CreateDevice(NocturneCoreDX::Window* pWindow)
{
	/* declare the result as 0 */
	PN_SWAPCHAIN_ID uiResult = 0;

	/* if the interface is not NULL */
	if(NULL != this->_pInterface)
	{
		/* try to create a device */
		Device* pDevice = new Device(pWindow, this->_pInterface);

		/* set the device */
		this->_SetDevice(pDevice);

		/* set the active swap chain's ID to the result */
		uiResult = this->GetDevice()->GetActiveSwapChainIdentifier();
	}
	
	/* return the result */
	return uiResult;
}