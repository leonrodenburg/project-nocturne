#include "Resources.h"			/* include resource definitions */
#include "Kernel.h"				/* include Kernel header */
#include "Window.h"				/* include Window header */
//#include <vld.h>				/* include Visual Leak Detector header */

#ifdef _DEBUG_
	#include "Logger.h"			/* Logger header */
#endif

/**
 * Main entry point for application.
 *
 * @param	argc	The number of command-line arguments
 * @param	argv	Array of command-line arguments
 *
 * @return	Application exit code
 */
int main(int argc, char** argv)
{
	/* create a kernel */
	NocturneCore::Kernel* pKernel = NocturneCore::Kernel::GetKernel(PN_DIRECTX_KERNEL);

	/* create a window object */
	NocturneCore::Window* pWindow = pKernel->GetWindowManager()->InitializeWindow("Project Nocturne - First window", 800, 600, false);

	/* register the window with the kernel */
	pKernel->RegisterWindow(pWindow);

	/* show the window */
	pWindow->Show();

	/* start the engine with default settings */
	pKernel->Run();

	/* delete the kernel */
	delete pKernel;

	/* return 1 */
	return 1;
}