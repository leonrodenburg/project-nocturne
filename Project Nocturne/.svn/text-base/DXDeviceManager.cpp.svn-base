#include "DXDeviceManager.h"	/* include DXDeviceManager header */

/**
 * Default constructor.
 */
NocturneDeviceDX::DeviceManager::DeviceManager()
{
	/* set device to NULL */
	this->_pDevice = NULL;

#ifdef _DEBUG_
	LOGALL("DXDeviceManager constructed", "");
#endif
}

/**
 * Destructor.
 */
NocturneDeviceDX::DeviceManager::~DeviceManager()
{
	/* if the device is not NULL */
	if(NULL != this->_pDevice)
	{
		/* delete the device */
		delete this->_pDevice;
	}

#ifdef _DEBUG_
	LOGALL("DXDeviceManager destroyed", "");
#endif
}

/**
 * Return the DXDevice associated with the device manager.
 *
 * @return	Pointer to the DXDevice
 */
NocturneDeviceDX::Device* NocturneDeviceDX::DeviceManager::GetDevice()
{
	/* return the device */
	return this->_pDevice;
}

/**
 * Set the device associated with this device manager.
 *
 * @param	pDevice		The pointer to the device
 */
void NocturneDeviceDX::DeviceManager::_SetDevice(NocturneDeviceDX::Device* pDevice)
{
	/* set the device */
	this->_pDevice = pDevice;
}