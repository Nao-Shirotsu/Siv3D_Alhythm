#include <Siv3D.hpp>

#include "Game_Core.h"

void Main(){
	Game::Core gamecore;

	while( gamecore.IsGameEnd() ){
		gamecore.Update();
		gamecore.Draw();
	}

	return;
}
