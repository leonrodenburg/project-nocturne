#include "DX10DeviceManager.h"	/* include DX10DeviceManager header */

/**
 * Default constructor.
 */
NocturneDeviceDX10::DeviceManager::DeviceManager() : NocturneDeviceDX::DeviceManager()
{
#ifdef _DEBUG_
	LOGALL("DX10DeviceManager constructed", "");
#endif
}

/**
 * Destructor.
 */
NocturneDeviceDX10::DeviceManager::~DeviceManager()
{
#ifdef _DEBUG_
	LOGALL("DX10DeviceManager destroyed", "");
#endif
}

/**
 * Create a device suitable for DirectX 10.
 *
 * @param	pWindow		The window to associate the device for
 *
 * @return	The ID of the automatically created swap chain, 0 if initialization failed
 */
PN_SWAPCHAIN_ID NocturneDeviceDX10::DeviceManager::CreateDevice(NocturneCoreDX::Window* pWindow)
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