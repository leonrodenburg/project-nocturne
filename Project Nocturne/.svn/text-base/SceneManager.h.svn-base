#pragma once

#ifndef _SCENEMANAGER_H_
#define _SCENEMANAGER_H_

#include "Resources.h"		/* include resource definitions */
#include <vector>			/* include vector header */
#include <string>			/* include string header */
#include "Scene.h"			/* include Scene header */

namespace NocturneScene
{
	class SceneManager
	{
	public:
		SceneManager();
		virtual ~SceneManager();

		bool Load(std::string sFilename);
	private:
		std::vector<Scene*> _scenesList;
	};
}

#endif