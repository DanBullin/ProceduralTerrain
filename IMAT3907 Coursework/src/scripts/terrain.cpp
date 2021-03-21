/*! \file terrain.cpp
*
* \brief A terrain script class which will create a terrain
*
* \author: Daniel Bullin
*
*/
#include "scripts/terrain.h"
#include "independent/entities/entity.h"
#include "independent/systems/systems/log.h"
#include "independent/systems/components/scene.h"
#include "independent/rendering/renderers/renderer3D.h"

TerrainVertex Terrain::makeVertex(int x, int z, float xTotalLength, float zTotalLength)
{
	return { { x, 0.f, z} , { (float)x / xTotalLength, (float)z / zTotalLength } };
}

//! Terrain()
Terrain::Terrain()
{
	m_model = nullptr;
	m_width = 250;
	m_height = 250;
	m_stepSize = 30;
	m_drawWireframe = false;
	m_tessellationEquation = 1;
	m_generateY = true;
	m_scale = 100.f;
	m_octaves = 3;
	m_frequency = 0.005f;
	m_amplitude = 100.f;
	m_amplitudeDivisor = 3.f;
	m_frequencyMultiplier = 2.f;
}

//! ~Terrain()
Terrain::~Terrain()
{
	if (m_model) delete m_model;
}

//! onAttach()
void Terrain::onAttach()
{
	std::vector<TerrainVertex> vertices;
	std::vector<uint32_t> indices;

	// Generating the vertices
	for (int z = 0; z < m_height; z++)
	{
		int offsetZ = z * m_stepSize;
		float zLength = static_cast<float>(m_height) * static_cast<float>(m_stepSize);

		for (int x = 0; x < m_width; x++)
		{
			int offsetX = x * m_stepSize;
			float xLength = static_cast<float>(m_width) * static_cast<float>(m_stepSize);
			vertices.push_back(makeVertex(offsetX, offsetZ, xLength, zLength));
			vertices.push_back(makeVertex(offsetX + m_stepSize, offsetZ, xLength, zLength));
			vertices.push_back(makeVertex(offsetX + m_stepSize, offsetZ + m_stepSize, xLength, zLength));
			vertices.push_back(makeVertex(offsetX, offsetZ + m_stepSize, xLength, zLength));
		}
	}

	// Generating the indices
	uint32_t count = 0;
	for (int z = 0; z < m_height; z++)
	{
		for (int x = 0; x < m_width; x++)
		{
			indices.push_back(count);
			indices.push_back(count+1);
			indices.push_back(count+3);
			indices.push_back(count+1);
			indices.push_back(count+2);
			indices.push_back(count+3);
			count += 4;
		}
	}

	// Create a piece of geometry using local vertices and indices information
	Geometry3D geometry;
	geometry.VertexBuffer = ResourceManager::getResource<VertexBuffer>("TerrainVertexBuffer");
	Renderer3D::addGeometry(vertices, indices, geometry);

	Model3D* newTerrain = new Model3D("Terrain");
	newTerrain->getMeshes().push_back(Mesh3D(geometry));
	newTerrain->getMeshes().at(0).setMaterial(ResourceManager::getResource<Material>("TerrainMaterial"));
	m_model = newTerrain;
}

//! onRender
/*
\param renderer a const Renderers - The renderer to use
*/
void Terrain::onRender(const Renderers renderer)
{
	if (renderer == Renderers::Renderer3D)
	{
		auto tessUBO = ResourceManager::getResource<UniformBuffer>("TessellationUBO");
		tessUBO->uploadData("u_tessellationEquation", static_cast<void*>(&m_tessellationEquation));
		tessUBO->uploadData("u_generateY", static_cast<void*>(&m_generateY));
		tessUBO->uploadData("u_scale", static_cast<void*>(&m_scale));
		tessUBO->uploadData("u_octaves", static_cast<void*>(&m_octaves));
		tessUBO->uploadData("u_frequency", static_cast<void*>(&m_frequency));
		tessUBO->uploadData("u_amplitude", static_cast<void*>(&m_amplitude));
		tessUBO->uploadData("u_amplitudeDivisor", static_cast<void*>(&m_amplitudeDivisor));
		tessUBO->uploadData("u_frequencyMultiplier", static_cast<void*>(&m_frequencyMultiplier));

		if (m_drawWireframe) RenderUtils::enableWireframe(true);
		for (auto& mesh : m_model->getMeshes())
		{
			Renderer3D::submit("Terrain", mesh.getGeometry(), mesh.getMaterial(), getParent()->getComponent<Transform>()->getModelMatrix());
		}
	}
}

//! onKeyRelease()
/*!
\param e a KeyReleasedEvent& - A key release event
\param timestep a const float - The timestep
\param totalTime a const float - The total time of the application
*/
void Terrain::onKeyRelease(KeyReleasedEvent & e, const float timestep, const float totalTime)
{
	if (e.getKeyCode() == Keys::Z)
	{
		m_drawWireframe = !m_drawWireframe;
	}

	if (e.getKeyCode() == Keys::X)
	{
		m_tessellationEquation = !m_tessellationEquation;
	}

	if (e.getKeyCode() == Keys::C)
	{
		m_generateY = !m_generateY;
	}

	if (e.getKeyCode() == Keys::N)
	{
		m_scale += 10.f;
	}

	if (e.getKeyCode() == Keys::M)
	{
		m_scale -= 10.f;
	}
}