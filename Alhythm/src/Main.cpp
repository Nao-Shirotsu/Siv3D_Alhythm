#include "Game_Core.h"

// そのうちシングルトンにしとけ

void Main(){
	Game::Core gamecore;

	while( gamecore.IsGameEnd() ){
		gamecore.Update();
		gamecore.Draw();
	}

	return;
}
