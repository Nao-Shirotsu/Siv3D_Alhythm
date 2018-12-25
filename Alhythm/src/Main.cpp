#include <Siv3D.hpp>

//#include "Game_Core.h"

void Main(){
	const Font font( 30 );

	while( System::Update() ){
		font( L"ようこそ、Siv3D の世界へ！" ).draw();

		if( Input::KeySemicolon.pressed ){
			Circle( Mouse::Pos(), 50 ).draw( { 255, 0, 0, 127 } );
		}
	}
	/*Game::Core gamecore;

	while( gamecore.IsGameEnd() ){
		gamecore.Update();
		gamecore.Draw();
	}

	return;*/
}
