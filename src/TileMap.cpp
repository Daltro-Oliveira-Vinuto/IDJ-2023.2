#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "TileMap.h"


TileMap::~TileMap() {
	delete tileSet;
	tileSet = NULL;
}

TileMap::TileMap(GameObject& associated, std::string file, TileSet* tileSet): Component(associated) {
	this->tileSet = tileSet;
	Load(file);
}

void TileMap::Load(std::string file) {
	
	std::vector<std::string> lines;
	std::fstream fileMap;
	fileMap.open(file.c_str(), std::ios::in);

	if (fileMap.is_open()) {
		std::string new_line;
		while(getline(fileMap, new_line)) {
			lines.push_back(new_line);
		}
	}

	fileMap.close();
	
	/*
	printf("lines size: %d\n", (int)lines.size()); 
	
	for(unsigned i= 0; i < lines.size(); i++) {
		std::string line = lines[i];
		std::cout << line << std::endl;

	}
	*/

	std::vector<int> first_line_vector = {};
	std::string first_line = lines[0];
	std::stringstream first_stream(first_line);
	std::string first_string;
	while(getline(first_stream, first_string,',')) {
		if (first_string != "\r")
			first_line_vector.push_back(atoi(first_string.c_str()));
	}


	this->mapHeight = first_line_vector[0];
	this->mapWidth = first_line_vector[1];
	this->mapDepth = first_line_vector[2];

	//printf("%d, %d, %d\n", mapHeight, mapWidth, mapDepth);
	
	for(unsigned i = 1; i < lines.size(); i++) {
		std::string line = lines[i];
		if (line != "\r") {
			std::stringstream line_stream(line);
			std::string string_aux;
			while(getline(line_stream, string_aux, ',')) {
				if (string_aux != "\r") {
					tileMatrix.push_back(atoi(string_aux.c_str())-1);
				}
			}
		}
	}

	/*
	for(unsigned i = 0; i < tileMatrix.size(); i++) {
		printf("%d ", tileMatrix[i]);
	}
	printf("\n");
	*/
}

void TileMap::SetTileSet(TileSet* tileSet) {
	if (this->tileSet != NULL) {
		delete this->tileSet;
	}

	this->tileSet = tileSet;
}

int TileMap::At(int x, int y, int z = 0) {
	int position;

	position = z*(mapWidth*mapHeight) + y*(mapWidth) + x;

	return this->tileMatrix[position]; 
}
  
void TileMap::RenderLayer(int layer, int cameraX =0, int cameraY=0) {

	for(int i = 0; i < this->mapHeight; i++) {
		for(int j = 0; j < this->mapWidth; j++) {
			int index;
			int x;
			int y;
			x = j+cameraX;
			y = i+cameraY;
			index = this->At(x, y, layer);
			//printf("%d ", index);
			int pos_x, pos_y;
			pos_x = j*(tileSet->GetTileWidth());
			pos_y = i*(tileSet->GetTileHeight());
			if (index != -1) {

				tileSet->RenderTile(index,pos_x, pos_y);
			}
		}
	}
	//exit(0);
}


void TileMap::Render() {
		//tileSet->RenderTile(15,100,200);
	for(int layer = 0; layer < this->mapDepth; layer++) {
		int cameraX = 0; int cameraY = 0;
		this->RenderLayer(layer, cameraX, cameraY);
	}
}	

void TileMap::Update(float dt) {

}

bool TileMap::Is(std::string type) {
	bool is = false;
	if (type == "TileMap") {
		is = true;
	}

	return is;
}


int TileMap::GetWidth() {
	return mapWidth;
}

int TileMap::GetHeight() {
	return mapHeight;
}

int TileMap::GetDepth() {
	return mapDepth;
}