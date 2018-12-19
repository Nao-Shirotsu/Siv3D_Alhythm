#include <memory>

#include "Game_Scene_Title.h"
#include "Game_Scene_MusicSelect.h"

namespace Game{
namespace Scene{

Title::Title():
	gamestart( 765, 600, L"Game Start", 60 ),
	titleStr( L"Resource/Title_string.png" ){}

Title::~Title(){}

void Title::Update(){
	
}

void Title::Draw() const{
	titleStr.draw( 20, 20 );
	gamestart.Draw();
}

bool Title::NeedsTransition(){
	return gamestart.WasClicked();
}

std::unique_ptr<Base> Title::TransitionToNext(){
	return std::make_unique<MusicSelect>();
}

}// namespace Scene
}// namespace Game