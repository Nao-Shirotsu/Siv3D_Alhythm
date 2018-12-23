#include "Game_Object_Track.h"

Game::Object::Track::Track( s3d::wchar* filename, int bpm, int maxBar_ ) noexcept( false ):
	beatSec( 60.0 / static_cast<double>( bpm ) ),
	curBar( 0 ),
	curBaet( 0 ),
	file( filename ),
	tapSound( L"Resource/note_sound.mp3" ),
	maxBar( maxBar_ ){
	if( !file ){
		throw std::runtime_error( "sound file read error" );
	}
}

Game::Object::Track::Track() = default;

Game::Object::Track::~Track(){
	file.stop();
}

double Game::Object::Track::SecOnBarBeat( int bar, int beat ) const noexcept{
	if( bar > maxBar ){
		return 0; // 不正値として、ノーツを無効にするために0を返す
	}
	return beatSec * static_cast<double>( 4 * ( bar - 1 ) + beat / 8 );
}

double Game::Object::Track::CurSec() const noexcept{
	return file.streamPosSec();
}

void Game::Object::Track::Play(){
	file.play();
}

void Game::Object::Track::PlayNote(){
	tapSound.playMulti();
}