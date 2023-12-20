
#include <string>
#include "GameObject.h"
#include "TileSet.h"

#ifndef TILEMAP_H
#define TILEMAP_H

class TileMap : public Component {
public:
	TileMap(GameObject&, std::string, TileSet*);
	~TileMap();

	void Load(std::string);

	void SetTileSet(TileSet*);

	int At(int x, int y, int z); 

	void RenderLayer(int, int, int);

	void Update(float);
	void Render();
	bool Is(std::string);

	int GetWidth();
	int GetHeight();
	int GetDepth();

private:
	std::vector<int> tileMatrix;
	TileSet* tileSet = NULL;
	int mapWidth;
	int mapHeight;
	int mapDepth;
};

#endif