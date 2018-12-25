#include <memory>
#include <exception>

#include "Game_Scene_Gameplay.h"
#include "Game_Scene_Gameplay.h"
#include "Game_Util_Functions.h"

namespace Game{
namespace Scene{

Gameplay::Gameplay( const s3d::String& trackName_, int bpm, int maxBar ):
	returnToSelect( 20, 380, L"選曲へ", 20 ),
	track( std::make_shared<Game::Object::Track>( L"Resource/" + trackName_ + L".mp3", bpm, maxBar ) ),
	trackNameText( 60, s3d::Typeface::Default, s3d::FontStyle::Italic ),
	trackNameStr( Util::FullTrackName( trackName_ ) ),
	musicPlaying( false ),
	isReady( false ),
	stopwatch(),
	ui( track, trackName_ ){
	stopwatch.Start();
}

Gameplay::Gameplay(){}

Gameplay::~Gameplay(){}

void Gameplay::Update(){
	if( !isReady && stopwatch.MilliDur() > 3000 ){
		isReady = true;
		trackNameStr = L"Ready?";
	}

	if( !musicPlaying && stopwatch.MilliDur() > 5500 ){
		musicPlaying = true;
		track->Play();
	}

	if( musicPlaying ){
		ui.Update();
	}
}

void Gameplay::Draw() const{
	ui.Draw();
	if( !musicPlaying ){
		trackNameText( trackNameStr ).drawCenter( 835, 420 );
	}
	returnToSelect.Draw();
}

bool Gameplay::NeedsTransition(){
	return returnToSelect.WasClicked();
}

std::unique_ptr<Base> Gameplay::TransitionToNext(){
	return nullptr;
}

}// namespace Scene
}// namespace Game