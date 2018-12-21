#include "Game_Object_Note.h"

Game::Object::Note::Note( int barNum_, int beatNum_, LaneID lane_ ):
	barNum( barNum_ ),
	beatNum( beatNum_ ),
	lane( lane_ ){}

Game::Object::Note::Note(){}

Game::Object::Note::~Note(){}

int Game::Object::Note::BarNum(){
	return barNum;
}

int Game::Object::Note::BeatNum(){
	return beatNum;
}

Game::Object::LaneID Game::Object::Note::Lane(){
	return lane;
}