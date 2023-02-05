#include <string>
#include <fstream>
#include "Map.h"
#include "TextureManager.h"

Map::Map()
{
}

Map::~Map()
{
}

void Map::LoadMap(std::string path, int sizeX, int sizeY)
{
	char tile;
	std::fstream mapFile;
	mapFile.open(path);

	int sourceX, sourceY;

	for (int y = 0; y < sizeY; y++) {
		for (int x = 0; x < sizeX; x++) {
			mapFile.get(tile);
			sourceY = atoi(&tile) * 32;
			mapFile.get(tile);
			sourceX = atoi(&tile) * 32;
			Game::AddTile(sourceX, sourceY, x * 64, y * 64);
			mapFile.ignore();
		}
	}

	mapFile.close();
}

