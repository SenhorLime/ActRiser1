
#include "TileMap.hpp"

#include <SFML/Graphics/Sprite.hpp>


TileMap::TileMap():world(nullptr){

	std::string ldtk_filename = "Assets/Maps/ActRaiser_Map.ldtk";
		try {
			project.loadFromFile(ldtk_filename);
			std::cout << "\nLDtk World \"" << project.getFilePath()
					<< "\" was loaded successfully." << std::endl;
		} catch (std::exception &ex) {
			std::cerr << ex.what() << std::endl;
		}
		world = &(project.getWorld());

		TileMap::path = project.getFilePath().directory();

}

auto TileMap::Textures::instance() -> Textures& {
	static Textures instance;
	return instance;
}

auto TileMap::Textures::Get(const std::string &name) -> sf::Texture& {
	auto &data = instance().data;
	if (data.count(name) == 0) {
		data[name].loadFromFile(TileMap::path + name);
	}

	return instance().data.at(name);
}

TileMap::Layer::Layer(const ldtk::Layer &layer,
		sf::RenderTexture &render_texture) :
		m_render_texture(render_texture) {
	m_tileset_texture = &Textures::Get(layer.getTileset().path);
	m_vertex_array.resize(layer.allTiles().size() * 4);
	m_vertex_array.setPrimitiveType(sf::PrimitiveType::Quads);
	int i = 0;
	for (const auto &tile : layer.allTiles()) {
		for (int j = 0; j < 4; ++j) {
			auto vertices = tile.getVertices();
			m_vertex_array[i * 4 + j].position.x = vertices[j].pos.x;
			m_vertex_array[i * 4 + j].position.y = vertices[j].pos.y;
			m_vertex_array[i * 4 + j].texCoords.x =
					static_cast<float>(vertices[j].tex.x);
			m_vertex_array[i * 4 + j].texCoords.y =
					static_cast<float>(vertices[j].tex.y);
		}
		i++;
	}
}

void TileMap::Layer::draw(sf::RenderTarget &target,
		sf::RenderStates states) const {
	states.texture = m_tileset_texture;
	m_render_texture.clear(sf::Color::Transparent);
	m_render_texture.draw(m_vertex_array, states);
	m_render_texture.display();
	target.draw(sf::Sprite(m_render_texture.getTexture()), states);
}

std::string TileMap::path;

void TileMap::Load(const ldtk::Level &level) {
	m_renderTexture.create(level.size.x, level.size.y);
	layers.clear();
	for (const auto &layer : level.allLayers()) {
		if (layer.getType() == ldtk::LayerType::Tiles) {
			layers.insert( { layer.getName(), { layer, m_renderTexture } });
		}
	}
}

auto TileMap::GetLayer(const std::string &name) const -> const Layer& {
	return layers.at(name);
}
