#include "DXGIHandler.h"	/* include DXGIHandler header */

/**
 * Default constructor.
 */
NocturneDeviceDX::DXGIHandler::DXGIHandler()
{
#ifdef _DEBUG_
	LOGALL("DXGIHandler constructed", "");
#endif
}

/**
 * Destructor.
 */
NocturneDeviceDX::DXGIHandler::~DXGIHandler()
{
#ifdef _DEBUG_
	LOGALL("DXGIHandler destroyed", "");
#endif
}

/**
 * Create an IDXGIFactory object.
 *
 * @return	Pointer to initialized IDXGIFactory, false if failed
 */
IDXGIFactory* NocturneDeviceDX::DXGIHandler::CreateFactory()
{
	/* declare factory */
	IDXGIFactory* pFactory = NULL;

	/* create a factory */
	CreateDXGIFactory(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&pFactory));

	/* if the factory is null */
	if(NULL == pFactory)
	{
		/* throw exception */
		throw NocturneDevice::Exception("Unable to create IDXGIFactory in CreateFactory() in DXGIHandler");
	}

	/* return the factory */
	return pFactory;
}

/**
 * Enumerate over the adapters of the given IDXGIFactory.
 *
 * @param	pFactory	The IDXGIFactory to enumerate
 *
 * @return	A vector containing the IDXGIFactory's IDXGIAdapters
 */
std::vector<IDXGIAdapter*> NocturneDeviceDX::DXGIHandler::EnumerateAdapters(IDXGIFactory* pFactory)
{
	/* define vector */
	std::vector<IDXGIAdapter*> vAdapterList;

	/* if the factory is not null */
	if(NULL != pFactory)
	{
		/* define sentinel value */
		UINT i = 0;

		/* declare adapter */
		IDXGIAdapter* pAdapter;

		/* enumerate over the adapters */
		while(pFactory->EnumAdapters(i, &pAdapter) != DXGI_ERROR_NOT_FOUND)
		{
			/* add the adapter to the vector */
			vAdapterList.push_back(pAdapter);

			/* increment the sentinel value */
			++i;
		}
	}
	else
	{
		/* throw exception */
		throw NocturneDevice::Exception("Cannot enumerate adapters of NULL IDXGIFactory in EnumarateAdapters() in DXGIHandler");
	}

	/* if the adapter list is empty */
	if(vAdapterList.size() == 0)
	{
		/* throw exception */
		throw NocturneDevice::Exception("No adapters found for given IDXGIFactory in EnumerateAdapters() in DXGIHandler");
	}

	/* return the vector */
	return vAdapterList;
}

/**
 * Get the most suitable mode from an initialized device (DirectX 10 or 11).
 *
 * @param	pDevice		The initialized device
 * @param	mode		The mode to match
 *
 * @return	The most suitable mode
 */
DXGI_MODE_DESC NocturneDeviceDX::DXGIHandler::GetMostSuitableMode(IUnknown* pDevice, DXGI_MODE_DESC mode)
{
	/* declare device */
	IDXGIDevice* pDXGIDevice = NULL;

	/* get the device from the handle */
	pDevice->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&pDXGIDevice));

	/* if the device is null */
	if(NULL == pDXGIDevice)
	{
		/* throw exception */
		throw NocturneDevice::Exception("Failed to get IDXGIDevice from device handle in GetMostSuitableMode() in DXGIHandler");
	}

	/* declare adapter */
	IDXGIAdapter* pAdapter = NULL;

	/* get the adapter from the IDXGIDevice */
	pDXGIDevice->GetAdapter(&pAdapter);

	/* if the adapter is null */
	if(NULL == pAdapter)
	{
		/* throw exception */
		throw NocturneDevice::Exception("Failed to get IDXGIAdapter from IDXGIDevice in GetMostSuitableMode() in DXGIHandler");
	}

	/* define sentinel value */
	UINT i = 0;

	/* declare output */
	IDXGIOutput* pOutput;

	/* declare vector for outputs */
	std::vector<IDXGIOutput*> vOutputList;

	/* while an output is found */
	while(pAdapter->EnumOutputs(i, &pOutput) != DXGI_ERROR_NOT_FOUND)
	{
		/* add the output to the list */
		vOutputList.push_back(pOutput);

		/* increment the sentinel value */
		++i;
	}

	/* if the output list is empty or the first output is null */
	if(vOutputList.size() == 0 || NULL == vOutputList[0])
	{
		/* throw exception */
		throw NocturneDevice::Exception("Failed to retrieve first output of IDXGIAdapter in GetMostSuitableMode() in DXGIHandler");
	}

	/* get value of overloaded method */
	DXGI_MODE_DESC output = this->GetMostSuitableMode(vOutputList[0], mode, pDevice);

	/* declare iterator */
	std::vector<IDXGIOutput*>::iterator it;

	/* loop over all outputs */
	for(it = vOutputList.begin(); it != vOutputList.end(); ++it)
	{
		/* release the output */
		(*it)->Release();
	}

	/* release the adapter */
	pAdapter->Release();

	/* release the device */
	pDXGIDevice->Release();

	/* return the output */
	return output;
}

/**
 * Get the most suitable mode from an output by passing in a mode
 * to compare with.
 *
 * @param	pOutput		The output to get the mode from
 * @param	mode		The mode to compare with
 * @param	pDevice		The device to test
 *
 * @return	The most suitable mode
 */
DXGI_MODE_DESC NocturneDeviceDX::DXGIHandler::GetMostSuitableMode(IDXGIOutput* pOutput, DXGI_MODE_DESC mode, IUnknown* pDevice)
{
	/* declare result */
	DXGI_MODE_DESC result;

	/* if the output is not null */
	if(NULL != pOutput)
	{
		/* get the most suitable mode */
		pOutput->FindClosestMatchingMode(&mode, &result, pDevice);
	}
	else
	{
		/* throw exception */
		throw NocturneDevice::Exception("Cannot find match for NULL IDXGIOutput in GetMostSuitableMode() in DXGIHandler");
	}

	/* return the output */
	return result;
}