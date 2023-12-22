#include <stdio.h>
#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include "Game.h"

#include "Rect.h"
#include "Vec2.h"

//#define DEBUG_MODE


int main(int argc, char **argv) {
	const int SCREEN_WIDTH = 1024, SCREEN_HEIGHT = 600;
    //const int SCREEN_WIDTH = 1920, SCREEN_HEIGHT = 1080;

    #ifdef DEBUG_MODE // ----------------------------------------------------------------
	Vec2 v1(3, -2), v2(1, 7	);

	std::cout << "v1: " << v1 << std::endl;

	std::cout << "v2: " << v2 << std::endl;

	std::cout << "v1+v2: " << v1 + v2 << std::endl;
	std::cout << "v1-v2: " << v1 - v2 << std::endl;
	std::cout << "v1*5: " << v1*5 << std::endl;
	std::cout << "|v1|: " << v1.mod << std::endl;
	std::cout << "v1 normalized: " << v1.GetNormalized() << std::endl;
	std::cout << "distance between v1 and v2: " << v1.DistanceTo(v2) << std::endl;
	std::cout << "angle from ox of v1: " << v1.angle << std::endl;

	std::cout << "angle from ox of v1(in degrees): " << 
	Vec2::ConvertRadianToDegree( v1.angle ) << std::endl;
	std::cout << "v1 rotated in -90 degrees: " << 
	v1.Rotate(Vec2::ConvertDegreeToRadian(-90)) << std::endl;

	Rect r1(0,0,10,10), r2;
	r2 = r1;

	std::cout << "distance r1 to r2: "<< r1.DistanceTo(r2) << std::endl;
	std::cout << "contains : " << r1.ContainVec2(v1) << std::endl;
	std::cout << "angle between v1 and v2: " << Vec2::ConvertRadianToDegree(v1.AngleBetween(v2)) 
	<< std::endl;
	std::cout << "v1 * v2 : " << v1.DotProduct(v2) << std::endl; 


	#endif // -------------------------------------------------------------------------------
	



	Game game = Game::GetInstance("Daltro 160025966", SCREEN_WIDTH, SCREEN_HEIGHT);		
	game.Run();

	return 0;

}