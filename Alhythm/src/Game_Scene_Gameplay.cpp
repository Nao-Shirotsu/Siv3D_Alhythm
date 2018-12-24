#include <memory>
#include <exception>

#include "Game_Scene_Gameplay.h"
#include "Game_Scene_Gameplay.h"

namespace Game{
namespace Scene{

Gameplay::Gameplay():
	track( std::make_shared<Game::Object::Track>( static_cast<s3d::wchar*>( L"Resource/senkou.mp3" ), 210, 133 ) ),
	lanes( track ),
	returnToSelect( 20, 380, L"選曲へ", 20 ),
	playMusic( 20, 310, L"再生する", 20 ),
	musicBegan( false ){
	using namespace Game::Object;
	lanes.AddNote( LaneID::D, 3, 1 );
	lanes.AddNote( LaneID::F, 3, 9 );
	lanes.AddNote( LaneID::D, 3, 17 );
	lanes.AddNote( LaneID::F, 3, 25 );

	lanes.AddNote( LaneID::D, 4, 1 );
	lanes.AddNote( LaneID::F, 4, 9 );
	lanes.AddNote( LaneID::D, 4, 17 );
	lanes.AddNote( LaneID::F, 4, 25 );

	lanes.AddNote( LaneID::D, 5, 1 );
	lanes.AddNote( LaneID::F, 5, 9 );
	lanes.AddNote( LaneID::D, 5, 17 );
	lanes.AddNote( LaneID::F, 5, 25 );

	lanes.AddNote( LaneID::D, 6, 1 );
	lanes.AddNote( LaneID::F, 6, 9 );
	lanes.AddNote( LaneID::D, 6, 17 );
	lanes.AddNote( LaneID::F, 6, 25 );
}

Gameplay::~Gameplay(){}

void Gameplay::Update(){
	if( !musicBegan ){
		if( playMusic.WasClicked() ){
			musicBegan = true;
			track->Play();
		}
	}

	lanes.Update();
}

void Gameplay::Draw() const{
	returnToSelect.Draw();
	lanes.Draw();

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