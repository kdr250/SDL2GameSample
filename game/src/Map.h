#pragma once

class Map
{
public:
	Map(std::string texID, int ms, int ts);
	~Map();

	void LoadMap(std::string path, int sizeX, int sizeY);
	void AddTile(int sourceX, int sourceY, int xpos, int ypos);

private:
	std::string textureID;
	int mapScale;
	int tileSize;
	int scaledSize;
};

