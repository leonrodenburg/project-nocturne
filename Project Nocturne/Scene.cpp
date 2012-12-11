#include "Scene.h"	/* include Scene header file */

/**
 * Constructor, setting the name of the scene.
 *
 * @param	sSceneName	The name of the scene
 */
NocturneScene::Scene::Scene(std::string sSceneName)
{
	/* call other constructor */
	Scene::Scene(sSceneName, "");
}

/**
 * Constructor, setting the name of the scene and attaching
 * it to the specified file name.
 *
 * @param	sSceneName		The name of the scene
 * @param	sSceneFilename	The filename to attach to
 */
NocturneScene::Scene::Scene(std::string sSceneName, std::string sSceneFilename)
{
	/* set the scene name */
	this->_sSceneName = sSceneName;

	/* if the scene filename is not empty */
	if(sSceneName.length() > 0)
	{
		/* attach to the specified file name */
		this->AttachToFile(sSceneFilename);
	}

#ifdef _DEBUG_
	LOGALL("Scene constructed", "");
#endif
}

/**
 * Destructor.
 */
NocturneScene::Scene::~Scene()
{
#ifdef _DEBUG_
	LOGALL("Scene destroyed", "");
#endif
}

/**
 * Return the name of the scene.
 *
 * @return	The name of the scene
 */
std::string NocturneScene::Scene::GetSceneName()
{
	/* return the name of the scene */
	return this->_sSceneName;
}

/**
 * Set the name of the scene.
 *
 * @param	sSceneName	The name of the scene
 */
void NocturneScene::Scene::SetSceneName(std::string sSceneName)
{
	/* set the name of the scene */
	this->_sSceneName = sSceneName;
}

/**
 * Attach to the given filename. An attached file can be used to
 * load scene info from, or save the current scene state to the
 * file in XML-format.
 *
 * @param	sSceneFilename	The filename of the scene XML-file
 */
void NocturneScene::Scene::AttachToFile(std::string sSceneFilename)
{
	/* set the filename of the scene */
	this->_sSceneFilename = sSceneFilename;
}

/**
 * Load the currently attached scene file and parse the elements
 * from it.
 */
void NocturneScene::Scene::Load()
{

}

/**
 * Save the state of the scene to the currently attached filename.
 */
void NocturneScene::Scene::Save()
{

}

