# set up project
cmake_minimum_required (VERSION 2.6)
project (project-nocturne)

# version number
set (PN_VERSION_MAJOR 0)
set (PN_VERSION_MINOR 1)

# if the generator is Xcode or Unix
if (CMAKE_GENERATOR MATCHES Xcode OR CMAKE_GENERATOR MATCHES Unix)
    	option (PN_DIRECTX_SUPPORT "Link DirectX library" OFF)
    	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wno-write-strings")
# the generator is Win32
else()
	option (PN_DIRECTX_SUPPORT "Link DirectX library" ON)
endif()

# if the generator is Xcode
if (CMAKE_GENERATOR MATCHES Xcode)
	# set platform number to 2
	set (PN_PLATFORM 2)

	# find Cocoa library
	find_library (COCOA_LIBRARY NAMES Cocoa)

	# include Cocoa library
	set (EXTRA_LIBS ${EXTRA_LIBS} ${COCOA_LIBRARY})
# if the generator is Unix
elseif (CMAKE_GENERATOR MATCHES Unix)
	# set platform number to 3
	set (PN_PLATFORM 3)
# if the generator is Win32
else () 
	# set platform number to 1
	set (PN_PLATFORM 1)
endif()



# if there should be DirectX support
if (PN_DIRECTX_SUPPORT)
	# include DirectX directory
	include_directories ("$ENV{DXSDK_DIR}/Include")
	
	# find DirectX libraries
	find_library (DIRECTX_LIBRARIES_9 NAMES d3d9.lib PATHS "$ENV{DXSDK_DIR}/Lib/x86")
	find_library (DIRECTX_LIBRARIES_X9 NAMES d3dx9.lib PATHS "$ENV{DXSDK_DIR}/Lib/x86")
	find_library (DIRECTX_LIBRARIES_10 NAMES d3d10.lib PATHS "$ENV{DXSDK_DIR}/Lib/x86")
	find_library (DIRECTX_LIBRARIES_X10 NAMES d3dx10.lib PATHS "$ENV{DXSDK_DIR}/Lib/x86")
	find_library (DIRECTX_LIBRARIES_INPUT NAMES dinput8.lib PATHS "$ENV{DXSDK_DIR}/Lib/x86")
	find_library (DIRECTX_LIBRARIES_DXGI NAMES dxgi.lib PATHS "$ENV{DXSDK_DIR}/Lib/x86")
	find_library (WINMM NAMES winmm.lib PATHS "$ENV{WINDOWSSDK_DIR}/lib")
				 
	# link with the libraries
	set (EXTRA_LIBS ${EXTRA_LIBS} ${DIRECTX_LIBRARIES_9})
	set (EXTRA_LIBS ${EXTRA_LIBS} ${DIRECTX_LIBRARIES_X9})
	set (EXTRA_LIBS ${EXTRA_LIBS} ${DIRECTX_LIBRARIES_10})
	set (EXTRA_LIBS ${EXTRA_LIBS} ${DIRECTX_LIBRARIES_X10})
	set (EXTRA_LIBS ${EXTRA_LIBS} ${DIRECTX_LIBRARIES_INPUT})
	set (EXTRA_LIBS ${EXTRA_LIBS} ${DIRECTX_LIBRARIES_DXGI})
	set (EXTRA_LIBS ${EXTRA_LIBS} ${WINMM})
	
	# add Project Nocturne DirectX library
	add_library (project-nocturne-dx STATIC 
				DXKernel.cpp
				DXWindow.cpp
				DXWindowManager.cpp
				DXDevice.cpp
				DXDeviceManager.cpp
				DXSwapChain.cpp
				DX9Device.cpp
				DX9DeviceManager.cpp
				DX9SwapChain.cpp
				DX10Device.cpp
				DX10DeviceManager.cpp
				DX10SwapChain.cpp
				DXGIHandler.cpp
   	 )
	
	# link with project-nocturne-dx library
	set (EXTRA_LIBS ${EXTRA_LIBS} project-nocturne-dx)
endif (PN_DIRECTX_SUPPORT)

# add Project Nocturne OpenGL library
add_library (project-nocturne-gl STATIC 
             GLKernel.cpp
             GLWindow.cpp
             GLWindowManager.cpp
)
set (EXTRA_LIBS ${EXTRA_LIBS} project-nocturne-gl)

# find OpenGL packages
find_package (OpenGL REQUIRED)

# find GLFW library
find_library (GLFW_LIBRARY NAMES GLFW PATHS $ENV{GLFW_LIB_PATH})

# include GLFW directory
include_directories ($ENV{GLFW_INCLUDE_PATH})

# include OpenGL and GLFW libraries
set (EXTRA_LIBS ${EXTRA_LIBS} ${OPENGL_LIBRARIES})
set (EXTRA_LIBS ${EXTRA_LIBS} ${GLFW_LIBRARY})

# configure a header file
configure_file (
    "${PROJECT_SOURCE_DIR}/Resources.h.in"
    "${PROJECT_SOURCE_DIR}/Resources.h"
)

# add executable
add_executable (project-nocturne
                DXKernel.h
                DXWindow.h
                DXWindowManager.h
				DXDeviceManager.h
				DXDevice.h
				DXSwapChain.h
				DX9Device.h
				DX9DeviceManager.h
				DX9SwapChain.h
				DX10Device.h
				DX10DeviceManager.h
				DX10SwapChain.h
				DXGIHandler.h
                GLKernel.h
                GLWindow.h
                GLWindowManager.h
                Kernel.h
                Kernel.cpp
                Logger.h
                Logger.cpp
                Main.cpp
                Resources.h
                Window.h
                Window.cpp
                WindowManager.h
                WindowManager.cpp
				BaseException.h
				CoreException.h
				GraphicsException.h
				Scene.h
				Scene.cpp
				SceneManager.h
				SceneManager.cpp
				tinystr.h
				tinystr.cpp
				tinyxml.h
				tinyxml.cpp
				tinyxmlerror.cpp
				tinyxmlparser.cpp
)

# link with libraries
target_link_libraries (project-nocturne ${EXTRA_LIBS})
                
            