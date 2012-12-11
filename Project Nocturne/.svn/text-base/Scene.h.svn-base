#pragma once

#ifndef _SCENE_H_
#define _SCENE_H_

#include "Resources.h"		/* include resource definitions */
#include <string>			/* include string header */

namespace NocturneScene
{
	class Scene
	{
	public:
		Scene(std::string sSceneName);
		Scene(std::string sSceneName, std::string sSceneFilename);
		virtual ~Scene();

		std::string GetSceneName();
		void SetSceneName(std::string sSceneName);

		void AttachToFile(std::string sSceneFilename);
		void Load();
		void Save();
	private:
		std::string _sSceneName;
		std::string _sSceneFilename;
	};
}

#endif