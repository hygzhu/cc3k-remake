#include "game.h"


int main( int argc, char* args[] )
{
	Game game;
	bool play = true;
	while(play)
	{
		play = game.start();
	}
	return 0;
}