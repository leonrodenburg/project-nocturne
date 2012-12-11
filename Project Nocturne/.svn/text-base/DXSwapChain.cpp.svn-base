#include "DXSwapChain.h"	/* include DXSwapChain header */

/**
 * Constructor, setting the identifier.
 *
 * @param	uiIdentifier	The identifier of the swap chain
 * @param	bIsFullScreen	Whether or not the swap chain is presented full-screen
 */
NocturneDeviceDX::SwapChain::SwapChain(PN_SWAPCHAIN_ID uiIdentifier, bool bIsFullScreen)
{
	/* set the identifier */
	this->_uiIdentifier = uiIdentifier;

	/* set full-screen value */
	this->_bIsFullScreen = bIsFullScreen;

#ifdef _DEBUG_
	LOGALL("DXSwapChain constructed");
#endif
}

/**
 * Destructor.
 */
NocturneDeviceDX::SwapChain::~SwapChain()
{
#ifdef _DEBUG_
	LOGALL("DXSwapChain destroyed");
#endif
}

/**
 * Return the identifier of the swap chain.
 *
 * @return	The identifier
 */
PN_SWAPCHAIN_ID NocturneDeviceDX::SwapChain::GetIdentifier()
{
	/* return the identifier */
	return this->_uiIdentifier;
}

/**
 * Switch the full-screen mode of this swap chain.
 */
void NocturneDeviceDX::SwapChain::SwitchFullScreen()
{
	/* if the swap chain is full-screen */
	if(this->_bIsFullScreen)
	{
		/* set full-screen to false */
		this->_bIsFullScreen = false;
	}
	else
	{
		/* set full-screen to true */
		this->_bIsFullScreen = true;
	}
}

/**
 * Return whether or not the swap chain is full-screen.
 *
 * @return	True if full-screen, false if not
 */
bool NocturneDeviceDX::SwapChain::IsFullScreen()
{
	/* return whether or not it's full-screen */
	return this->_bIsFullScreen;
}