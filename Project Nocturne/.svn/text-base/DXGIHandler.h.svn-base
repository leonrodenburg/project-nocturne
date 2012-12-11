#pragma once

#ifndef _DXGIHANDLER_H_
#define _DXGIHANDLER_H_

#include "Resources.h"			/* include resource definitions */
#include <DXGI.h>				/* include DXGI header */
#include <vector>				/* include vector header */

namespace NocturneDeviceDX
{
	class DXGIHandler
	{
	public:
		DXGIHandler();
		virtual ~DXGIHandler();

		IDXGIFactory* CreateFactory();
		std::vector<IDXGIAdapter*> EnumerateAdapters(IDXGIFactory* pFactory);
		DXGI_MODE_DESC GetMostSuitableMode(IUnknown* pDevice, DXGI_MODE_DESC mode);
		DXGI_MODE_DESC GetMostSuitableMode(IDXGIOutput* pOutput, DXGI_MODE_DESC mode, IUnknown* pDevice);
	private:
	};
}


#endif