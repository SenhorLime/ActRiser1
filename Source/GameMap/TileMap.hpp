#pragma once

#include <vector>
#include <map>
#include <string>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/VertexArray.hpp>

#include <LDtkLoader/Level.hpp>
#include <LDtkLoader/Project.hpp>

class TileMap {
public:
	static std::string path;

	const ldtk::World * world;

	TileMap();

	class Textures {
		Textures() = default;
		std::map<std::string, sf::Texture> data;
		static auto instance() -> Textures&;
	public:
		Textures(const Textures&) = delete;
		static auto Get(const std::string &name) -> sf::Texture&;
	};

	class Layer: public sf::Drawable {
		friend TileMap;
		Layer(const ldtk::Layer &layer, sf::RenderTexture &render_texture);
		sf::Texture *m_tileset_texture;
		sf::RenderTexture &m_render_texture;
		sf::VertexArray m_vertex_array;
		void draw(sf::RenderTarget &target, sf::RenderStates states) const
				override;
	};

	//TileMap() = default;
	void Load(const ldtk::Level &level);
	auto GetLayer(const std::string &name) const -> const Layer&;

private:
	mutable sf::RenderTexture m_renderTexture;
	std::map<std::string, Layer> layers;

	ldtk::Project project;

};
