#pragma once

#ifndef _WINDOW_H_
#define _WINDOW_H_

#include "Resources.h"		/* include resource definitions */
#include <string>			/* include string header */

namespace NocturneCore
{
	class Window
	{
	public:
		Window(PN_WINDOW_ID uiIdentifier, std::string sTitle, unsigned int uiWidth, unsigned int uiHeight, bool bFullScreen);	
		virtual ~Window();										

		PN_WINDOW_ID GetIdentifier();

		std::string GetTitle();
		virtual void SetTitle(std::string sTitle);
		unsigned int GetWidth();
		void SetWidth(unsigned int uiWidth);
		unsigned int GetHeight();
		void SetHeight(unsigned int uiHeight);

		bool IsFullScreen();
		virtual void Show() = 0;
		virtual void Close() = 0;
	private:
		PN_WINDOW_ID _uiIdentifier;
		std::string _sTitle;
		unsigned int _uiWidth;
		unsigned int _uiHeight;
		bool _bFullScreen;
	};
}

#endif