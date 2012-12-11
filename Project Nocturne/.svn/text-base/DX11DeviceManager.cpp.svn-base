#include "DX11DeviceManager.h"	/* include DX11DeviceManager header */

/**
 * Default constructor.
 */
NocturneDeviceDX11::DeviceManager::DeviceManager() : NocturneDeviceDX::DeviceManager()
{
#ifdef _DEBUG_
	LOGALL("DX11DeviceManager constructed", "");
#endif
}

/**
 * Destructor.
 */
NocturneDeviceDX11::DeviceManager::~DeviceManager()
{
#ifdef _DEBUG_
	LOGALL("DX11DeviceManager destroyed", "");
#endif
}

/**
 * Create a device suitable for DirectX 11.
 *
 * @param	pWindow		The window to associate the device for
 *
 * @return	The ID of the automatically created swap chain, 0 if initialization failed
 */
PN_SWAPCHAIN_ID NocturneDeviceDX11::DeviceManager::CreateDevice(NocturneCoreDX::Window* pWindow)
{
	/* declare the result as 0 */
	PN_SWAPCHAIN_ID uiResult = 0;

	/* try to create a device */
	Device* pDevice = new Device(pWindow);

	/* set the device */
	this->_SetDevice(pDevice);

	/* set the active swap chain's ID to the result */
	uiResult = this->GetDevice()->GetActiveSwapChainIdentifier();

	/* return the result */
	return uiResult;
}