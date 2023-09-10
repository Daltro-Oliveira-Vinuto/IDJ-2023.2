#include "Music.h"


Music::Music() {
	music = NULL;;
}

Music::Music(std::string file) {
	Open(file);
}

void Music::Open(std::string file) {
	
}