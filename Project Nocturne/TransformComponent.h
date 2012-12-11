#pragma once

#ifndef _TRANSFORMCOMPONENT_H_
#define _TRANSFORMCOMPONENT_H_

#include "Component.h"			/* include Component header */

namespace NocturneRenderer
{
	class TransformComponent : public Component
	{
	public:
		TransformComponent();
		virtual ~TransformComponent();
	private:
	};
}

#endif