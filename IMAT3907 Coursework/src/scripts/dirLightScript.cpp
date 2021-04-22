/*! \file dirLightScript.cpp
*
* \brief A directional light script
*
* \author: Daniel Bullin
*
*/
#include "scripts/dirLightScript.h"
#include "independent/systems/systems/sceneManager.h"

DirLightScript::DirLightScript()
{
}

DirLightScript::~DirLightScript()
{
}

void DirLightScript::onPreUpdate(const float timestep, const float totalTime)
{
	Transform* trans = getParent()->getComponent<Transform>();

	if (m_first)
	{
		m_originalPos = trans->getPosition();
		m_first = false;
	}

	if (getParent()->getName() == "DirLight") trans->setPosition(m_originalPos + glm::vec3(m_distance, 0.f, m_distance));

	if (m_distance > 250.f)
		m_increment = -25.f;
	else if (m_distance < -250.f)
		m_increment = 25.f;

	m_distance += m_increment;
}

void DirLightScript::onKeyRelease(KeyReleasedEvent & e, const float timestep, const float totalTime)
{
	if (e.getKeyCode() == Keys::U)
	{
		getParent()->getComponent<DirectionalLight>()->setDirection({ 0.f, 1.f, 0.f });
	}

	if (e.getKeyCode() == Keys::I)
	{
		getParent()->getComponent<DirectionalLight>()->setDirection({ 0.4f, 0.2f, -0.1f });
	}
}
