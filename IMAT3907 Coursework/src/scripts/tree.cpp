/*! \file tree.cpp
*
* \brief A tree script
*
* \author: Daniel Bullin
*
*/
#include "scripts/tree.h"
#include "loaders/sceneLoader.h"
#include "independent/systems/systems/sceneManager.h"
#include "independent/rendering/renderers/renderer3D.h"
#include "independent/utils/mathUtils.h"

Tree::Tree()
{
}

Tree::~Tree()
{
}

void Tree::onAttach()
{
	m_treeModel = ResourceManager::getResource<Model3D>("tree");
}

void Tree::onPostUpdate(const float timestep, const float totalTime)
{
}

void Tree::onKeyRelease(KeyReleasedEvent& e, const float timestep, const float totalTime)
{
}

void Tree::onRender(const Renderers renderer, const std::string& renderState)
{
	if (renderer == Renderers::Renderer3D)
	{
		for (auto& pos : m_positions)
		{
			for (auto& mesh : m_treeModel->getMeshes())
			{
				Renderer3D::submit("Tree", mesh.getGeometry(), mesh.getMaterial(), MathUtils::getModelMatrix(pos));
			}
		}
	}
}