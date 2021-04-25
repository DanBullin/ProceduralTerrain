/*! \file environment.cpp
*
* \brief A script for all the objects in the environment
*
* \author: Daniel Bullin
*
*/
#include "scripts/environment.h"
#include "independent/rendering/renderers/renderer3D.h"
#include "independent/utils/mathUtils.h"
#include "scripts/terrain.h"
#include "independent/systems/systems/sceneManager.h"
#include "independent/systems/systems/randomiser.h"

Environment::Environment()
{
}

Environment::~Environment()
{
}

void Environment::onAttach()
{
	m_treeModel = ResourceManager::getResource<Model3D>("tree");

	for (int i = 0; i < 50; i++)
	{
		glm::vec3 generatedPos = { 0.f, -10.f, 0.f };
		while (generatedPos.y < 50.f)
		{
			generatedPos = generatePoint();
		}
		m_treePositions.push_back({ generatedPos, false });
	}
}

void Environment::onPostUpdate(const float timestep, const float totalTime)
{
}

void Environment::onKeyRelease(KeyReleasedEvent& e, const float timestep, const float totalTime)
{
}

void Environment::onRender(const Renderers renderer, const std::string& renderState)
{
	if (renderer == Renderers::Renderer3D)
	{
		for (auto& pos : m_treePositions)
		{
			for (auto& mesh : m_treeModel->getMeshes())
			{
				Renderer3D::submit("Tree", mesh.getGeometry(), mesh.getMaterial(), MathUtils::getModelMatrix(pos.first, { 6.f, 6.f, 6.f }));
			}
		}
	}
}

void Environment::onMousePress(MousePressedEvent & e, const float timestep, const float totalTime)
{
}

glm::vec3 Environment::generatePoint()
{
	Terrain* terrain = static_cast<Terrain*>(getParent()->getParentScene()->getEntity("Terrain1")->getComponent<NativeScript>());
	float x = Randomiser::uniformFloatBetween(-500.f, 500.f);
	float z = Randomiser::uniformFloatBetween(-500.f, 500.f);
	float posX = Randomiser::uniformIntBetween(0, 1);
	float posZ = Randomiser::uniformIntBetween(0, 1);
	if (posX == 0) x = -x;
	if (posZ == 0) z = -z;
	return { x, terrain->getYCoord(x, z), z };
}