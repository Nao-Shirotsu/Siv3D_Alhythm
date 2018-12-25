#include <memory>
#include <exception>

#include "Game_Scene_Gameplay.h"
#include "Game_Scene_Gameplay.h"

namespace Game{
namespace Scene{

Gameplay::Gameplay( const s3d::String& trackName_, int bpm, int maxBar ):
	track( std::make_shared<Game::Object::Track>( L"Resource/" + trackName_ + L".mp3", bpm, maxBar ) ),
	ui( track, trackName_ ),
	returnToSelect( 20, 380, L"選曲へ", 20 ),
	playMusic( 20, 310, L"再生する", 20 ),
	musicBegan( false ){}

Gameplay::Gameplay(){}

Gameplay::~Gameplay(){}

void Gameplay::Update(){
	if( !musicBegan ){
		if( playMusic.WasClicked() ){
			musicBegan = true;
			track->Play();
		}
	}

	ui.Update();
}

void Gameplay::Draw() const{
	returnToSelect.Draw();
	ui.Draw();

	//----debug----
	playMusic.Draw();
	//-------------
}

bool Gameplay::NeedsTransition(){
	return returnToSelect.WasClicked();
}

std::unique_ptr<Base> Gameplay::TransitionToNext(){
	return nullptr;
}

}// namespace Scene
}// namespace Game