#include "bapch.h"
#include "LayerList.h"

LayerList::~LayerList()
{
	for (const auto& layer : m_Layers)
	{
		layer->OnDetach();
	}
}

void LayerList::AddLayer(std::shared_ptr<Layer> layer)
{
	m_Layers.emplace(m_Layers.begin() + m_InsertIndex, layer);
	++m_InsertIndex;
	layer->OnAttach();
}

void LayerList::RemoveLayer(std::shared_ptr<Layer> layer)
{
	auto it = std::find(m_Layers.begin() + m_InsertIndex, m_Layers.end(), layer);
	if (it != m_Layers.begin() + m_InsertIndex)
	{
		layer->OnDetach();
		m_Layers.erase(it);
		--m_InsertIndex;
	}
}
