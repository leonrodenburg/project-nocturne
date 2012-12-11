#include "Kernel.h"				/* include Kernel header */

#ifdef PN_DIRECTX_SUPPORT
	#include "DXKernel.h"		/* include DXKernel header */
#endif

#include "GLKernel.h"			/* include GLKernel header */

/**
 * Default constructor.
 */
NocturneCore::Kernel::Kernel()
{
	/* construct a new scene manager */
	this->_pSceneManager = new NocturneScene::SceneManager();

#ifdef _DEBUG_
	LOGALL("Kernel constructed", "");
#endif
}

/**
 * Destructor.
 */
NocturneCore::Kernel::~Kernel()
{
	/* if the scene manager is initialized */
	if(NULL != this->_pSceneManager)
	{
		/* delete the scene manager */
		delete this->_pSceneManager;
	}

	/* if the window manager is initialized */
	if(NULL != this->_pWindowManager) 
	{
		/* delete the window manager */
		delete this->_pWindowManager;
	}

#ifdef _DEBUG_
	LOGALL("Kernel destroyed", "");
#endif
}

/**
 * Return a kernel object based on the type that should be 
 * loaded.
 */
NocturneCore::Kernel* NocturneCore::Kernel::GetKernel(PN_KERNEL_TYPE iType)
{
	/* define Kernel* as NULL */
	Kernel* pKernel = NULL;

	/* switch over the type */
	switch(iType)
	{
#ifdef PN_DIRECTX_SUPPORT
	/* if it's a DirectX kernel */
	case PN_DIRECTX_KERNEL:
		/* create a new DirectX kernel */
		pKernel = new NocturneCoreDX::Kernel();

		/* break the case */
		break;
#endif
	/* if it's an OpenGL kernel */
	case PN_OPENGL_KERNEL:
		/* create a new OpenGL kernel */
		pKernel = new NocturneCoreGL::Kernel();
    
        /* break the case */
        break;
    /* default case, exception */
    default:
		/* throw exception */
        throw NocturneCore::Exception("Unknown kernel type passed, cannot initialize engine");

		/* break */
		break;
	}

	/* return the kernel */
	return pKernel;
}

/**
 * Return pointer to the window manager.
 *
 * @return	Pointer to window manager
 */
NocturneCore::WindowManager* NocturneCore::Kernel::GetWindowManager()
{
	/* return the window manager */
	return this->_pWindowManager;
}

/**
 * Set the window manager used by the kernel.
 *
 * @param	pWindowManager	Pointer to window manager
 */
void NocturneCore::Kernel::SetWindowManager(WindowManager* pWindowManager)
{
	/* set the window manager */
	this->_pWindowManager = pWindowManager;
}

/**
 * Return pointer to the scene manager.
 *
 * @return	Pointer to scene manager
 */
NocturneScene::SceneManager* NocturneCore::Kernel::GetSceneManager()
{
	/* return the scene manager */
	return this->_pSceneManager;
}

/**
 * Set the scene manager used by the kernel.
 *
 * @param	pSceneManager	Pointer to the scene manager
 */
void NocturneCore::Kernel::SetSceneManager(NocturneScene::SceneManager* pSceneManager)
{
	/* set the scene manager */
	this->_pSceneManager = pSceneManager;
}