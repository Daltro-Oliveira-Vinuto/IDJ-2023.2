#include <string>
#include <memory>
#include "TileSet.h"
#include "GameObject.h"
#include "Rect.h"



TileSet::TileSet(int tileWidth, int tileHeight, std::string file) {
	this->tileWidth = tileWidth;
	this->tileHeight = tileHeight;
	std::unique_ptr<GameObject> newGameObject(new GameObject());

	std::unique_ptr<Sprite> newSprite(new Sprite(*newGameObject, file));
	//Rect clip(0,0, newSprite->GetWidth(), newSprite->GetHeight());
	tileSet = std::move(newSprite);

	rows = tileSet->GetHeight()/tileHeight;
	cols = tileSet->GetWidth()/tileWidth;
	numberOfTiles = rows*cols;

	//printf("(rows, cols)= (%d, %d)\n", rows, cols);
	//printf("tile_width: %d, tile_height: %d\n",this->tileWidth, this->tileHeight);
}


void TileSet::RenderTile(unsigned index, float x, float y) {
	if (index < 0 ||  index >= numberOfTiles) {
		//printf("Error! Index invalid!\n");
	} else {
		//int clip_x = (index-(index/cols)*cols)*tileWidth;
		//int clip_y = (index/cols)*tileHeight;
		int tileSetRow, tileSetCol;

		tileSetCol = (index % this->cols);
		tileSetRow = (index / this->cols);
		int clip_x = tileSetCol*(this->tileWidth);
		int clip_y = tileSetRow*(this->tileHeight);
		Rect clip(clip_x, clip_y, tileWidth, tileHeight);
		tileSet->SetClip(clip);
		tileSet->Render(x, y);

	}
}


int TileSet::GetTileWidth() {

	return tileWidth;
}

int TileSet::GetTileHeight() {

	return tileHeight;
}