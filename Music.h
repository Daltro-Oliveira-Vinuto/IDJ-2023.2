

#ifndef __MUSIC_H__
#define __MUSIC_H__


class Music {
public:
	Music();
	~Music();
	Music(std::string);

	void Open(std::string);
	void Play(int);
	void Stop(int);
	bool IsOpen();
private:
	Mix_Music* music;

};


#endif