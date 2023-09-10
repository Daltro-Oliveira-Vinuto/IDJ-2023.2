

#ifndef __MUSIC_H__
#define __MUSIC_H__


class Music {
public:
	Music();
	Music(std::string);

	void Open(std::string);
	
private:
	Mix_Music* music;

};


#endif