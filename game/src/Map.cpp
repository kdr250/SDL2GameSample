#include <string>
#include <fstream>

#include "Map.h"
#include "TextureManager.h"
#include "ecs/EntityComponentSystem.h"
#include "ecs/Components.h"

extern Manager manager;

Map::Map(const char* mpf, int ms, int ts) : mapFilePath(mpf), mapScale(ms), tileSize(ts)
{
	scaledSize = ms * ts;
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
			sourceY = atoi(&tile) * tileSize;
			mapFile.get(tile);
			sourceX = atoi(&tile) * tileSize;
			AddTile(sourceX, sourceY, x * scaledSize, y * scaledSize);
			mapFile.ignore();
		}
	}

	mapFile.ignore();

	for (int y = 0; y < sizeY; y++) {
		for (int x = 0; x < sizeX; x++) {
			mapFile.get(tile);
			if (tile == '1') {
				auto& tileCollider(manager.AddEntity());
				tileCollider.AddComponent<ColliderComponent>("terrain", x * scaledSize, y * scaledSize, scaledSize);
				tileCollider.AddGroup(Game::GroupCollider);
			}
			mapFile.ignore();
		}
	}

	mapFile.close();
}

void Map::AddTile(int sourceX, int sourceY, int xpos, int ypos)
{
	auto& tile(manager.AddEntity());
	tile.AddComponent<TileComponent>(sourceX, sourceY, xpos, ypos, tileSize, mapScale, mapFilePath);
	tile.AddGroup(Game::GroupMap);
}

