#include "Game_Object_Note.h"

namespace{

constexpr double MISS_TIME = 0.375;
constexpr double GOOD_TIME = 0.25;
constexpr double GREAT_TIME = 0.125;
constexpr double PERFECT_TIME = 0.0625;

}

Game::Object::Note::Note( int barNum_, int beatNum_, LaneID lane_, const std::shared_ptr<Track>& track_ ):
	lane( static_cast<s3d::wchar>( lane_ ) ),
	track( track_ ),
	passed( false ),
	tapSound( L"Resource/note_sound.mp3" ){
	secOnMusic = track->SecOnBarBeat( barNum_, beatNum_ );
}

Game::Object::Note::Note(){}

Game::Object::Note::~Note(){}

void Game::Object::Note::Update(){
	
	// ‚±‚Ìƒm[ƒc‚ª’Ê‚è‰ß‚¬‚Ä‚È‚¢&&”»’è‚³‚ê‚é•b”“à‚È‚ç‚Î
	if( !passed && secOnMusic - MISS_TIME < track->SecCur() && track->SecCur() < secOnMusic + MISS_TIME ){
		if( s3d::Key( lane ).clicked ){
			passed = true;
			tapSound.playMulti();
		}
	}
}

void Game::Object::Note::Draw(){}

bool Game::Object::Note::Passed(){
	return passed;
}