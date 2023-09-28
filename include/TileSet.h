#include <string>
#include "Sprite.h"

#ifndef TILESET_H
#define TILESET_H

class TileSet {
public:
	TileSet(int, int, std::string);
	void RenderTile(unsigned, int, int);

	int GetTileWidth();
	int GetTileHeight();

private:
	std::unique_ptr<Sprite> tileSet;

	int rows;
	int cols;
	unsigned numberOfTiles;

	int tileWidth;
	int tileHeight;

};



#endif 