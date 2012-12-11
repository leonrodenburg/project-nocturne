Project Nocturne
================

A cross-platform, open-source 3D gaming engine written in C++.

Will support OpenGL, DirectX 9, 10 and 11 with full support for HLSL (DirectX only), GLSL (OpenGL only) and Cg (DirectX and OpenGL) shaders.

To build the project from the source code on any platform, clone the source code and make sure you have the following prerequisites available:

- CMake 2.8.6 (http://www.cmake.org)
- GLFW (http://www.glfw.org)
- DirectX June 2010 SDK (Windows only) (http://www.microsoft.com/download/en/details.aspx?id=6812)
- Windows SDK for the Windows version you are building on (Windows only)

Then make sure the following environment variables are available:

- ${GLFW_INCLUDE_PATH} = Path to GLFW include folder
- ${GLFW_LIB_PATH} = Path to the GLFW libraries
- ${WINDOWSSDK_DIR} = Path to the Windows SDK you'd like to build with (Windows only)

To start building the project, point CMake to the Project Nocturne/Project Nocturne directory and follow the steps.