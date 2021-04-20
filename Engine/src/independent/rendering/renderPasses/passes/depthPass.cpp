/*! \file depthPass.cpp
*
* \brief A depth render pass
*
* \author Daniel Bullin
*
*/
#include "independent/rendering/renderPasses/passes/depthPass.h"
#include "independent/systems/components/scene.h"
#include "independent/rendering/renderUtils.h"
#include "independent/systems/systems/resourceManager.h"
#include "independent/systems/systems/windowManager.h"
#include "independent/rendering/renderers/renderer3D.h"

namespace Engine
{
	bool DepthPass::s_initialised = false; //!< Initialise to false

	//! DepthPass()
	DepthPass::DepthPass()
	{
		m_frameBuffer = ResourceManager::getResource<FrameBuffer>("shadowMapFBO");
		m_cameraUBO = ResourceManager::getResource<UniformBuffer>("CameraUBO");
		m_lightSpaceUBO = ResourceManager::getResource<UniformBuffer>("LightSpaceUBO");
		s_initialised = true;
	}

	//! ~DepthPass()
	DepthPass::~DepthPass()
	{
		m_frameBuffer = nullptr;
		m_cameraUBO = nullptr;
		m_lightSpaceUBO = nullptr;
		s_initialised = false;
	}

	//! setupPass()
	void DepthPass::setupPass()
	{
		RenderUtils::clearBuffers(RenderParameter::DEPTH_BUFFER_BIT, m_attachedScene->getMainCamera()->getClearColour());

		// Set some rendering settings
		RenderUtils::setDepthComparison(RenderParameter::LESS_THAN_OR_EQUAL);
		RenderUtils::enableDepthTesting(true);

		std::vector<DirectionalLight*> dirLights = m_attachedScene->getClosestDirectionalLights();
		Camera* cam = m_attachedScene->getMainCamera();

		glm::mat4 lightProjection, lightView, lightSpaceMatrix;
		float near_plane = cam->getProjection().NearPlane, far_plane = cam->getProjection().FarPlane;

		lightProjection = glm::ortho(-1000.0f, 1000.0f, -1000.0f, 1000.0f, near_plane, far_plane);
		lightView = glm::lookAt(dirLights[0]->getParent()->getComponent<Transform>()->getPosition(), glm::vec3(0.f, 30.f, 0.f), glm::vec3(0.0, 1.0, 0.0));
		lightSpaceMatrix = lightProjection * lightView;

		m_lightSpaceUBO->uploadData("u_lightSpaceMatrix", static_cast<void*>(&lightSpaceMatrix));
		m_lightSpaceUBO->uploadData("u_nearPlane", static_cast<void*>(&near_plane));
		m_lightSpaceUBO->uploadData("u_farPlane", static_cast<void*>(&far_plane));

		// Upload camera perspective data to UBO
		m_cameraUBO->uploadData("u_viewPos", static_cast<void*>(&cam->getWorldPosition()));
	}

	//! onRender()
	/*!
	\param entities a std::vector<Entity*>& - The list of entities to render
	*/
	void DepthPass::onRender(std::vector<Entity*>& entities)
	{
		// Bind FBO
		m_frameBuffer->bind();

		// Set settings
		setupPass();

		// Draw terrain

		RenderUtils::enablePatchDrawing(true);

		Renderer3D::begin();

		for (auto& entity : entities)
		{
			if (entity->getLayer()->getDisplayed() && entity->getDisplay())
			{
				if (entity->containsComponent<NativeScript>())
					entity->getComponent<NativeScript>()->onRender(Renderers::Renderer3D, "TerrainDepth");
			}
		}

		Renderer3D::end();

		RenderUtils::enablePatchDrawing(false);
		RenderUtils::enableWireframe(false);

	}

	//! getFrameBuffer()
	/*!
	\return a FrameBuffer* - The framebuffer
	*/
	FrameBuffer* DepthPass::getFrameBuffer()
	{
		return m_frameBuffer;
	}
}