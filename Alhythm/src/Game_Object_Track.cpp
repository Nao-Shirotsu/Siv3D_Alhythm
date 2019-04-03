#include "Game_Object_Track.h"
#include "Game_Util_Functions.h"

Game::Object::Track::Track( const TrackFileID trackID_, int bpm, int maxBar_ ) noexcept( false ):
	trackID( trackID_ ),
	beatSec( 60.0 / static_cast<double>( bpm ) ),
	file( Util::EmbeddedFilePath( trackID_ ) ),
	maxBar( maxBar_ ){
	if( !file ){
		throw std::runtime_error( "sound file read error" );
	}
}

Game::Object::Track::Track():
	trackID( TrackFileID::Senkou ){}

Game::Object::Track::~Track(){
	file.stop();
}

double Game::Object::Track::SecOnBarBeat( int bar, int beat ) const noexcept{
	if( bar > maxBar ){
		return -1; // 不正値として、ノーツを無効にするために-1を返す  クソなのでoptionalにしろ
	}
	return beatSec * static_cast<double>( 4 * ( bar - 1 ) + beat / 8.0 );
}

double Game::Object::Track::CurSec() const noexcept{
	return file.streamPosSec();
}

void Game::Object::Track::Play(){
	file.play();
}

bool Game::Object::Track::IsEnd(){
	return !file.isPlaying();
}

void Game::Object::Track::PlayZeroSound(){
	file.setVolume( 0.0 );
	file.play();
}
