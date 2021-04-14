/*! \file tree.h
*
* \brief A tree script
*
* \author: Daniel Bullin
*
*/
#ifndef TREE_H
#define TREE_H

#include "independent/entities/components/nativeScript.h"

using namespace Engine;

/*! \class Tree
* \brief A script for the trees
*/
class Tree : public NativeScript
{
private:
	Model3D* m_treeModel;
	std::vector<glm::vec3> m_positions;
public:
	Tree(); //!< Constructor
	~Tree(); //!< Destructor

	void onAttach() override; //!< Called when attached to the entity
	void onPostUpdate(const float timestep, const float totalTime) override; //!< Call after game update
	void onKeyRelease(KeyReleasedEvent& e, const float timestep, const float totalTime) override; //!< Call upon key release
	void onRender(const Renderers renderer, const std::string& renderState) override; //!< Call upon render
};
#endif