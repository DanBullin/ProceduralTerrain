/*! \file terrain.h
*
* \brief A terrain script class which will create a terrain
*
* \author: Daniel Bullin
*
*/
#ifndef TERRAIN_H
#define TERRAIN_H

#include "independent/entities/components/nativeScript.h"

using namespace Engine;

/*! \class Terrain
* \brief A terrain script
*/
class Terrain : public NativeScript
{
private:
	int m_width; //!< The total number of tiles in the x axis
	int m_height; //!< The total number of tiles in the z axis
	int m_stepSize; //!< The size of a tile in width
	Model3D* m_model; //!< The model of the terrain

	bool m_drawWireframe; //!< Draw the terrain in wireframe
	uint32_t m_tessellationEquation; //!< The equation to use for tessellation
	bool m_generateY; //!< Generate the y valus for generation
	int m_octaves; //!< The number of octaves
	float m_scale; //!< The scale factor for the terrain
	float m_frequency; //!< The frequency
	float m_amplitude; //!< The amplitude
	float m_amplitudeDivisor; //!< The amplitude divisor
	float m_frequencyMultiplier; //!< The frequency multiplier

	TerrainVertex makeVertex(int x, int z, float xTotalLength, float zTotalLength);
public:
	Terrain(); //!< Constructor
	~Terrain(); //!< Destructor

	void onAttach() override; //!< Called when attached to the entity
	void onRender(const Renderers renderer); //!< On Render
	void onKeyRelease(KeyReleasedEvent& e, const float timestep, const float totalTime) override; //!< Call upon key release
};
#endif