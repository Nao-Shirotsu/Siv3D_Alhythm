#include "Game_Object_Track.h"

Game::Object::Track::Track( s3d::wchar* filename, int bpm, int maxBar_ ) noexcept( false ):
	beatSec( 60.0 / static_cast< double >( bpm ) ),
	curBar( 0 ),
	curBaet( 0 ),
	file( filename ),
	maxBar( maxBar_ ){
	if( !file ){
		throw std::runtime_error( "sound file read error" );
	}
}

Game::Object::Track::Track(){}

Game::Object::Track::~Track(){
	// よばれてない？おかしい
	file.stop();
}

double Game::Object::Track::SecOnBarBeat( int bar, int curBeat ) const noexcept{
	if( bar > maxBar ){
		return 0; // 不正値として、ノーツを無効にするために0を返す
	}
	return 32.0 * ( beatSec * ( bar - 1 ) + 32.0 * curBaet );
}

double Game::Object::Track::SecCur() const noexcept{
	return file.streamPosSec();
}

void Game::Object::Track::Play(){
	file.play();
}

void Game::Object::Track::Stop(){
	file.stop();
}