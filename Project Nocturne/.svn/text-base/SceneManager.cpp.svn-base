#include "SceneManager.h"	/* include SceneManager header */

/**
 * Default constructor.
 */
NocturneScene::SceneManager::SceneManager() : _scenesList()
{
#ifdef _DEBUG_
	LOGALL("SceneManager constructed", "");
#endif
}

/**
 * Destructor.
 */
NocturneScene::SceneManager::~SceneManager()
{
	/* loop over the scenes in the list */
	for(std::vector<Scene*>::iterator it = _scenesList.begin(); it != _scenesList.end(); ++it)
	{
		/* delete the scene */
		delete *it;
	}

#ifdef _DEBUG_
	LOGALL("SceneManager destroyed", "");
#endif
}