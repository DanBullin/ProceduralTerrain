/*! \file depthPass.h
*
* \brief A depth render pass
*
* \author Daniel Bullin
*
*/
#ifndef DEPTHPASS_H
#define DEPTHPASS_H

#include "independent/rendering/renderPasses/renderPass.h"

namespace Engine
{
	/*! \class DepthPass
	* \brief A depth render pass
	*/
	class DepthPass : public RenderPass
	{
	private:
		static bool s_initialised; //!< Has the pass been initialised
		FrameBuffer* m_frameBuffer; //!< A framebuffer
		UniformBuffer* m_cameraUBO; //!< The camera UBO
		UniformBuffer* m_lightSpaceUBO; //!< The light space UBO

		void setupPass(); //!< Set up the pass by setting the settings
	public:
		DepthPass(); //!< Constructor
		~DepthPass(); //!< Destructor

		void onRender(std::vector<Entity*>& entities) override; //!< The rendering to perform for this pass
		FrameBuffer* getFrameBuffer() override; //!< Get the framebuffer of this render pass
	};
}
#endif