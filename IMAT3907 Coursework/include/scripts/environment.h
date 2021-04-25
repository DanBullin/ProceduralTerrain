/*! \file environment.h
*
* \brief A script for all the objects in the environment
*
* \author: Daniel Bullin
*
*/
#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "independent/entities/components/nativeScript.h"
#include "independent/entities/components/transform.h"

using namespace Engine;

/*! \class Environment
* \brief A script for all the objects in the environment
*/
class Environment : public NativeScript
{
private:
	Model3D* m_treeModel;;
	std::vector<std::pair<glm::vec3, bool>> m_treePositions;
public:
	Environment(); //!< Constructor
	~Environment(); //!< Destructor

	void onAttach() override; //!< Called when attached to the entity
	void onPostUpdate(const float timestep, const float totalTime) override; //!< Call after game update
	void onKeyRelease(KeyReleasedEvent& e, const float timestep, const float totalTime) override; //!< Call upon key release
	void onRender(const Renderers renderer, const std::string& renderState) override; //!< Call upon render
	void onMousePress(MousePressedEvent& e, const float timestep, const float totalTime) override;

	glm::vec3 generatePoint();
};
#endif