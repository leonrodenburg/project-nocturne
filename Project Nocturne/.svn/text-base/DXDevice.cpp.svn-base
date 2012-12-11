#include "DXDevice.h"	/* include DXDevice header */

/**
 * Default constructor.
 */
NocturneDeviceDX::Device::Device() : _swapChainList()
{
	/* set the active swap chain to NULL */
	this->_pActiveSwapChain = NULL;

#ifdef _DEBUG_
	LOGALL("DXDevice constructed", "");
#endif
}

/**
 * Destructor.
 */
NocturneDeviceDX::Device::~Device()
{
	/* get an iterator */
	std::map<PN_SWAPCHAIN_ID, SwapChain*>::iterator iterator;

	/* loop over the map */
	for(iterator = this->_swapChainList.begin(); iterator != this->_swapChainList.end(); ++iterator)
	{
		/* release the swap chain */
		delete iterator->second;
	}

	/* clear the swap chain list */
	this->_swapChainList.clear();

#ifdef _DEBUG_
	LOGALL("DXDevice destroyed", "");
#endif
}

/**
 * Present the content of the active swap chain's back buffer.
 */
void NocturneDeviceDX::Device::Present()
{
	/* if the active swap chain is not NULL */
	if(NULL != this->_pActiveSwapChain)
	{
		/* present the swap chain's buffer */
		this->_pActiveSwapChain->Present();
	}
}

/**
 * Return the number of swap chains managed by this
 * device.
 *
 * @return	The number of swap chains
 */
unsigned int NocturneDeviceDX::Device::GetSwapChainCount()
{
	/* return the number of items in the list */
	return this->_swapChainList.size();
}

/**
 * Return a list of all the registered swap chain identifiers.
 *
 * @return	A vector with the registered identifiers
 */
std::vector<PN_SWAPCHAIN_ID> NocturneDeviceDX::Device::GetSwapChainIdentifiers()
{
	/* create a new vector */
	std::vector<PN_SWAPCHAIN_ID> vIdentifiers;

	/* loop over all elements */
	for(std::map<PN_SWAPCHAIN_ID, SwapChain*>::iterator iterator = this->_swapChainList.begin(); iterator != this->_swapChainList.end(); ++iterator)
	{
		/* add the identifier to the vector */
		vIdentifiers.push_back(iterator->first);
	}

	/* return the vector */
	return vIdentifiers;
}

/**
 * Set the active swap chain.
 *
 * @param	uiIdentifier	The identifier of the swap chain
 */
void NocturneDeviceDX::Device::SetActiveSwapChain(PN_SWAPCHAIN_ID uiIdentifier)
{
	/* declare swap chain and set to NULL */
	SwapChain* pFoundSwapChain = NULL;

	/* find the swap chain */
	pFoundSwapChain = this->_swapChainList[uiIdentifier];

	/* if the swap chain is not NULL */
	if(NULL != pFoundSwapChain) 
	{
		/* set the active swap chain to the found swap chain */
		this->_pActiveSwapChain = pFoundSwapChain;
	}
	else
	{
		/* throw exception */
		throw NocturneDevice::Exception("Invalid swap chain ID passed to SetActiveSwapChain() in DXDevice");
	}
}

/**
 * Return the currently active swap chain identifier.
 *
 * @return	The active swap chain's identifier, 0 if no swap chain is active
 */
PN_SWAPCHAIN_ID NocturneDeviceDX::Device::GetActiveSwapChainIdentifier()
{
	/* if there is an active swap chain */
	if(NULL != this->_pActiveSwapChain)
	{
		/* return the currently active swap chain */
		return this->_pActiveSwapChain->GetIdentifier();
	}
	else
	{
		/* return 0 */
		return 0;
	}
}

/**
 * Destroy the swap chain with the given identifier.
 *
 * @param	uiIdentifier	The identifier of the swap chain
 */
void NocturneDeviceDX::Device::DestroySwapChain(PN_SWAPCHAIN_ID uiIdentifier)
{
	/* delete the swap chain */
	delete this->_swapChainList[uiIdentifier];

	/* erase the item from the list */
	this->_swapChainList.erase(this->_swapChainList.find(uiIdentifier));

#ifdef _DEBUG_
	LOGALL("Swap chain removed from list", "");
#endif
}

/**
 * Switch the specified swap chain in full-screen mode.
 *
 * @param	uiIdentifier	The identifier of the swap chain
 */
void NocturneDeviceDX::Device::SwitchFullScreen(PN_SWAPCHAIN_ID uiIdentifier)
{
	/* get a reference to the swap chain */
	SwapChain* pSwapChain = this->_swapChainList[uiIdentifier];

	/* if the swap chain is not null */
	if(NULL != pSwapChain)
	{
		/* switch the mode of the swap chain */
		pSwapChain->SwitchFullScreen();
	}
	else
	{
		/* throw exception */
		throw NocturneDevice::Exception("Unknown swap chain ID passed to SwitchFullScreen() in DXDevice");
	}
}

/**
 * Add a swap chain to the list.
 *
 * @param	pSwapChain		The swap chain to add
 */
void NocturneDeviceDX::Device::_AddSwapChainToList(SwapChain* pSwapChain)
{
	/* add the swap chain to the list */
	this->_swapChainList[pSwapChain->GetIdentifier()] = pSwapChain;
}

/**
 * Return the active swap chain.
 *
 * @return	The active swap chain
 */
NocturneDeviceDX::SwapChain* NocturneDeviceDX::Device::_GetActiveSwapChain()
{
	/* return the active swap chain */
	return this->_pActiveSwapChain;
}

/**
 * Return a swap chain given its ID.
 *
 * @return	The swap chain with the given identifier, NULL if not found
 */
NocturneDeviceDX::SwapChain* NocturneDeviceDX::Device::_GetSwapChain(PN_SWAPCHAIN_ID uiIdentifier)
{
	/* declare swap chain */
	SwapChain* pSwapChain = NULL;

	/* get the swap chain from the map */
	pSwapChain = this->_swapChainList[uiIdentifier];

	/* return the swap chain */
	return pSwapChain;
}