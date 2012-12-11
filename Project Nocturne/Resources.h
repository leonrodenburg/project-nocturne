#pragma once

#ifndef _RESOURCES_H_
	#define _RESOURCES_H_
	#define _DEBUG_

	/* definitions */
	#define PN_DIRECTX_SUPPORT
	#define PN_PLATFORM 1

	/* platform definitions */
	#define PN_PLATFORM_WIN 1
	#define PN_PLATFORM_OSX 2
    #define PN_PLATFORM_UNIX 3

	/* type definitions */
	typedef unsigned int PN_WINDOW_ID;
	typedef unsigned int PN_KERNEL_TYPE;
	typedef unsigned int PN_SWAPCHAIN_ID;

	/* constant definitions */
	#ifdef PN_DIRECTX_SUPPORT
		#define PN_DIRECTX_KERNEL 1
	#endif
	#define PN_OPENGL_KERNEL 2

	/* include logger (if in debug mode) */
	#ifdef _DEBUG_
		#include "Logger.h"			/* Logger header */
	#endif

	/* include exception classes */
	#include "CoreException.h"
	#include "GraphicsException.h"
#endif
