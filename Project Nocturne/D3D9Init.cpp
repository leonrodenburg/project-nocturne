#define _DEBUG_

#include <Windows.h>		/* Windows header */
#include <mmsystem.h>		/* mmsystem header */
#include <d3dx9.h>			/* Direct3DX header */
#include <stdio.h>			/* stdio header */
#include <io.h>				/* io header */
#include <fcntl.h>			/* fcntl header */
#include "Resources.h"		/* include resource definitions */
#include "Kernel.h"			/* include Kernel header */
#include "DXKernel.h"		/* include DXKernel header */

#ifdef _DEBUG_
	#include "Logger.h"		/* Logger header */
#endif

/* globals */
LPDIRECT3D9			g_pD3D		=   NULL;
LPDIRECT3DDEVICE9   g_pDevice   =   NULL;
LPD3DXMESH			g_pMesh		=   NULL;
D3DXMATRIX			g_view;
D3DXMATRIX			g_projection;
D3DXMATRIX			g_world;

/* forward declarations */
HRESULT Setup();
VOID Render(float timeDelta);
VOID Cleanup();
HWND InitializeWindow(LPCTSTR windowClassName, UINT width, UINT height, HINSTANCE hInstance, int nShowCmd);
HRESULT InitializeDirect3D(HWND hWnd);
HRESULT InitializeMatrices(HWND hWnd);
VOID MessageLoop();
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd);

/**
 * Set up the application's resources
 *
 * @return  S_OK if successful, E_FAIL if not
 */
HRESULT Setup()
{
	/* create the mesh */
	D3DXCreateTeapot(g_pDevice, &g_pMesh, NULL);

	/* turn on wireframe mode */
	g_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

#ifdef _DEBUG_
	LOGALL("Teapot mesh loaded");
#endif

	/* return S_OK */
	return S_OK;
}

/**
 * Render the scene
 */
VOID Render(float timeDelta)
{
	/* if a device is defined */
	if(NULL != g_pDevice)
	{
		/* clear the backbuffer */
		g_pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0);

		/* define static Y-axis rotation */
		static float y = 0.00f;
		
		/* define static Z-axis rotation */
		static float z = 0.00f;

		/* rotate the world matrix */
		D3DXMatrixRotationYawPitchRoll(&g_world, 0.0f, y, z);

		/* increment the Y-axis rotation */
		y += (timeDelta * 0.001f);

		/* increment the Z-axis rotation */
		z += (timeDelta * 0.001f);

		/* set world transform */
		g_pDevice->SetTransform(D3DTS_WORLD, &g_world);

		/* begin the scene */
		if(SUCCEEDED(g_pDevice->BeginScene()))
		{
			/* draw first subset of teapot */
			g_pMesh->DrawSubset(0);

			/* end the scene */
			g_pDevice->EndScene();
		}

		/* present the backbuffer */
		g_pDevice->Present(0, 0, 0, 0);
	}
}

/**
 * Clean up all the resources
 */
VOID Cleanup()
{
	/* unload resources if defined */
	if(NULL != g_pMesh)	 g_pMesh->Release();
	if(NULL != g_pDevice)   g_pDevice->Release();
	if(NULL != g_pD3D)	  g_pD3D->Release();

#ifdef _DEBUG_
	LOGALL("Cleaned up resources");
#endif
}

/**
 * Initialize a window and show it
 *
 * @param	windowClassName		The name of the window class
 * @param	width				Width of the window
 * @param	height				Height of the window
 * @param	hInstance			The application handle
 * @param	nShowCmd			The show command
 *
 * @return	Handle to initialized window
 */
HWND InitializeWindow(LPCTSTR windowClassName, UINT width, UINT height, HINSTANCE hInstance, int nShowCmd)
{
	/* create window class */
	WNDCLASSEX wcex;

	/* configure window class */
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;	
	wcex.lpfnWndProc = ::WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = ::LoadIcon(hInstance, (LPCTSTR)IDI_APPLICATION);
	wcex.hCursor = ::LoadCursor(hInstance, (LPCTSTR)IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_BACKGROUND + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = windowClassName;
	wcex.hIconSm = NULL;

	/* register window class */
	if(!::RegisterClassEx(&wcex))
	{
		/* return failure */
		return NULL;
	}

	/* create window */
	HWND hWnd = ::CreateWindow("NocturneWindow",				/* window class name */
							   "Project Nocturne - Test",	   /* window name */
							   WS_OVERLAPPEDWINDOW,			 /* window type */
							   CW_USEDEFAULT,				   /* x-position */
							   CW_USEDEFAULT,				   /* y-position */
							   width,						   /* width */
							   height,						  /* height */
							   NULL,							/* parent window */
							   NULL,							/* menu name */
							   hInstance,					   /* application handle */
							   NULL);						   /* user-defined parameters */

	/* if creation failed */
	if(NULL == hWnd) 
	{
		/* return failure */
		return NULL;
	}

	/* show the window */
	::ShowWindow(hWnd, nShowCmd);

	/* update the window */
	::UpdateWindow(hWnd);

#ifdef _DEBUG_
	LOGALL("Window created and shown");
#endif

	/* return success */
	return hWnd;
}

/**
 * Initialize a Direct3D interface and device
 *
 * @param   hWnd	The window handle
 *
 * @return  S_OK if successful, false if not
 */
HRESULT InitializeDirect3D(HWND hWnd)
{
	/* initialize Direct3D interface */
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	/* if the initialization failed */
	if(NULL == g_pD3D)
	{
		/* return a failed result */
		return E_FAIL;
	}

	/* define rectangle */
	RECT rect;

	/* get window rectangle */
	::GetWindowRect(hWnd, &rect);

	/* create present parameters structure */
	D3DPRESENT_PARAMETERS pp;

	/* configure present parameters */
	pp.hDeviceWindow = hWnd;
	pp.Windowed = TRUE;
	pp.BackBufferWidth = rect.right - rect.left;
	pp.BackBufferHeight = rect.bottom - rect.top;
	pp.BackBufferCount = 1;
	pp.BackBufferFormat = D3DFMT_A8R8G8B8;
	pp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	pp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	pp.EnableAutoDepthStencil = TRUE;
	pp.AutoDepthStencilFormat = D3DFMT_D16;
	pp.Flags = 0;
	pp.FullScreen_RefreshRateInHz = 0;
	pp.MultiSampleType = D3DMULTISAMPLE_NONE;
	pp.MultiSampleQuality = 0;
	
	/* create device */
	g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
						   D3DDEVTYPE_HAL,
						   hWnd,
						   D3DCREATE_HARDWARE_VERTEXPROCESSING,
						   &pp,
						   &g_pDevice);

	/* if the device initialization failed */
	if(NULL == g_pDevice)
	{
		/* return a failed result */
		return E_FAIL;
	}

#ifdef _DEBUG_
	LOGALL("Direct3D interface and device initialized");
#endif

	/* return OK */
	return S_OK;
}

/**
 * Initialize the view and projection matrix
 *
 * @param   hWnd	The window handle
 *
 * @return  S_OK if successful, false if not
 */
HRESULT InitializeMatrices(HWND hWnd)
{
	/* define position, target and up vector for camera */
	D3DXVECTOR3 position(0.0f, 2.0f, -3.0f);
	D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);

	/* calculate view matrix */
	D3DXMatrixLookAtLH(&g_view, &position, &target, &up);

	/* declare rectangle */
	RECT rect;

	/* get window rectangle */
	::GetWindowRect(hWnd, &rect);

	/* calculate projection matrix */
	D3DXMatrixPerspectiveFovLH(&g_projection,
		D3DX_PI * 0.5f,
		((rect.right - rect.left) / (float)(rect.bottom - rect.top)),
		1.0f,
		1000.0f);

	/* set matrices */
	g_pDevice->SetTransform(D3DTS_VIEW, &g_view);
	g_pDevice->SetTransform(D3DTS_PROJECTION, &g_projection);

	/* initialize world matrix to identity */
	D3DXMatrixIdentity(&g_world);

#ifdef _DEBUG_
	LOGALL("Matrices initialized");
#endif

	/* return S_OK */
	return S_OK;
}

/**
 * Listen for incoming messages
 */
VOID MessageLoop()
{
	/* declare a message */
	MSG msg;

	/* zero out the memory */
	::ZeroMemory(&msg, sizeof(msg));

	/* define static float to keep track of time */
	static float lastTime = (float) timeGetTime();

	/* while the received message is not a quit message */
	while(msg.message != WM_QUIT)
	{
		/* peek for a new message */
		if(::PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			/* translate the message */
			::TranslateMessage(&msg);

			/* dispatch the message */
			::DispatchMessage(&msg);
		}
		else
		{
			/* get current time */
			float currTime = (float) timeGetTime();

			/* calculate time delta */
			float timeDelta = (currTime - lastTime);

			/* render */
			::Render(timeDelta);

			/* set last time to the current time */
			lastTime = currTime;
		}
	}
}

/**
 * Callback for messages sent to our windows
 *
 * @param	hWnd	The window handle
 * @param	msg		The message sent
 * @param	wParam	Window parameters
 * @param	lParam	Window parameters
 *
 * @return	Whether or not the message was handled
 */
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	/* switch over the message */
	switch(msg)
	{
		/* if a key was pressed */
		case WM_KEYDOWN:
			/* if the key pressed was the Escape key */
			if(wParam == VK_ESCAPE)
			{
				/* destroy the window */
				::DestroyWindow(hWnd);
			}

			/* return 0 */
			return 0;
		/* if the message is a destroy message */
		case WM_DESTROY:
			/* clean up */
			::Cleanup();

			/* post quit message */
			::PostQuitMessage(0);

			/* return 0 */
			return 0;
	}

	/* dispatch to default handler */
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

/**
 * Main entry point for application
 *
 * @param	hInstance		The application handle
 * @param	hPrevInstance	Not used
 * @param	lpCmdLine		Command-line arguments
 * @param	nShowCmd		Show command
 *
 * @return	Application exit code
 */
int WINAPI WinMain2(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
 {
  	/* define window class name */
  	LPCSTR windowClassName = "NocturneWindow";
  
  	/* initialize a window */
  	HWND hWnd = InitializeWindow(windowClassName, 1024, 768, hInstance, nShowCmd);
  
  	/* if initialization failed */
  	if(NULL == hWnd)
  	{
  		/* show a message box indicating the error */
  		::MessageBox(NULL, "Window creation failed", "Project Nocturne - Error", MB_OK);
  
  		/* return 0 to exit the application */
  		return 0;
  	}
  
  	/* initialize Direct 3D */
  	if(FAILED(::InitializeDirect3D(hWnd)))
  	{
  		/* show a message box indicating the error */
  		::MessageBox(NULL, "Direct3D initialization failed", "Project Nocturne - Error", MB_OK);
  
  		/* return 0 to exit the application */
  		return 0;
  	}
  
  	/* initialize matrices */
  	if(FAILED(::InitializeMatrices(hWnd)))
  	{
  		/* show a message box indicating the error */
  		::MessageBox(NULL, "Matrix initialization failed", "Project Nocturne - Error", MB_OK);
  
  		/* return 0 to exit the application */
  		return 0;
  	}
  
  	/* set up resources */
  	if(FAILED(::Setup()))
  	{
  		/* show a message box indicating the error */
  		::MessageBox(NULL, "Setup of resources failed", "Project Nocturne - Error", MB_OK);
  
  		/* return 0 to exit the application */
  		return 0;
  	}
  
  #ifdef _DEBUG_
  	LOGALL("Entering message loop...");
  #endif
  
  	/* enter the message loop */
  	::MessageLoop();
  
  	/* unregister window class */
  	UnregisterClass(windowClassName, hInstance);
  
  #ifdef _DEBUG_
  	LOGALL("Closing application");
  #endif
  
  	/* return 0 */
  	return 0;
}