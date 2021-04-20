/*! \file dirLightScript.h
*
* \brief A directional light script
*
* \author: Daniel Bullin
*
*/
#ifndef DIRLIGHTSCRIPT_H
#define DIRLIGHTSCRIPT_H

#include "independent/entities/components/nativeScript.h"

using namespace Engine;

/*! \class DirLightScript
* \brief A script for the directional light
*/
class DirLightScript : public NativeScript
{
private:
	float m_distance = 0.f;
	float m_increment = 0.03f;
	glm::vec3 m_originalPos;
	bool m_first = true;
public:
	DirLightScript(); //!< Constructor
	~DirLightScript(); //!< Destructor
	void onPreUpdate(const float timestep, const float totalTime) override; //!< Call before game update
};
#endif