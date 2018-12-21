#include <memory>
#include <exception>

#include "Game_Scene_Gameplay.h"
#include "Game_Scene_Gameplay.h"

namespace Game{
namespace Scene{

//----test----
s3d::Sound Gameplay::test = s3d::Sound( L"Resource/decide.mp3" );
//------------

Gameplay::Gameplay():
	returnToSelect( 20, 380, L"選曲へ", 20 ),
	button( 20, 450, L"クリック", 20 ),
	track( std::make_shared<Game::Object::Track>( static_cast<s3d::wchar*>( L"Resource/senkou.mp3"), 210, 133 ) ),
	text( 30 ),
	str( L"initial" ),
	musicBegan( false ){
	using namespace Game::Object;
	lanes[LaneID::A] = Lane( LaneID::A );
	lanes[LaneID::S] = Lane( LaneID::S );
	lanes[LaneID::D] = Lane( LaneID::D );
	lanes[LaneID::F] = Lane( LaneID::F );
	lanes[LaneID::J] = Lane( LaneID::J );
	lanes[LaneID::K] = Lane( LaneID::K );
	lanes[LaneID::L] = Lane( LaneID::L );
	lanes[LaneID::Smcl] = Lane( LaneID::Smcl );

	lanes[LaneID::F].notes.emplace( 1, 1, LaneID::F, track );
	lanes[LaneID::F].notes.emplace( 2, 1, LaneID::F, track );
	lanes[LaneID::F].notes.emplace( 3, 1, LaneID::F, track );
	lanes[LaneID::F].notes.emplace( 4, 1, LaneID::F, track );
	lanes[LaneID::F].notes.emplace( 5, 1, LaneID::F, track );
	lanes[LaneID::F].notes.emplace( 6, 1, LaneID::F, track );
	lanes[LaneID::F].notes.emplace( 7, 1, LaneID::F, track );
}

Gameplay::~Gameplay(){}

void Gameplay::Update(){
	if( !musicBegan ){
		if( s3d::Input::KeyEnter.clicked ){
			musicBegan = true;
			track->Play();
		}
	}
	if( button.WasClicked() ){
		str = s3d::Format( track->SecCur() );
	}

	for( auto& lane : lanes ){
		lane.second.Update();
	}
}

void Gameplay::Draw() const{
	returnToSelect.Draw();
	for( const auto& lane : lanes ){
		lane.second.Draw();
	}
	
	//----debug----
	button.Draw();
	text( str ).draw( 20, 470 );
	//-------------
}

bool Gameplay::NeedsTransition(){
	return returnToSelect.WasClicked();
}

std::unique_ptr<Base> Gameplay::TransitionToNext(){
	track->Stop();
	return nullptr;
}

}// namespace Scene
}// namespace Game