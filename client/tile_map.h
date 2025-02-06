#pragma once

#include "tile.h"

#include <vector>
#include <string>

class TileMap
{
public:
	TileMap(const std::string& name)
		:name(name)
	{
	}

	~TileMap()
	{
		for (std::vector<Tile*> j : tile_list)
			for (Tile* i : j)
				delete i;
	}

	const std::string& get_name() const
	{
		return name;
	}

private:
	std::vector<std::vector<Tile*>> tile_list;
	std::string name;
};
