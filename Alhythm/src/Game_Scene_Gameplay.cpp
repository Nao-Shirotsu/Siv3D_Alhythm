#include <memory>
#include <exception>

#include "Game_Scene_Gameplay.h"
#include "Game_Scene_Gameplay.h"

namespace Game{
namespace Scene{

Gameplay::Gameplay():
	returnToSelect( 570, 380, L"‘I‹È‚Ö", 20 ),
	track( L"Resource/senkou.mp3" ),
	musicBegan( false ){
	if( !track ){
		throw std::runtime_error( "sound file read error" );
	}
}

Gameplay::~Gameplay(){}

void Gameplay::Update(){
	if( !musicBegan ){
		if( s3d::Input::KeyEnter.clicked ){
			musicBegan = true;
			track.play();
		}
	}
}

void Gameplay::Draw() const{
	returnToSelect.Draw();
}

bool Gameplay::NeedsTransition(){
	return returnToSelect.WasClicked();
}

std::unique_ptr<Base> Gameplay::TransitionToNext(){
	track.stop();
	return nullptr;
}

}// namespace Scene
}// namespace Game