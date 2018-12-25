#include "Game_Object_RightAlignedFont.h"

Game::Object::RightAlignedFont::RightAlignedFont( int size, int posX_, int posY_ ):
	posX( posX_ ),
	posY( posY_ ),
	font( size ){}

Game::Object::RightAlignedFont::RightAlignedFont(){}

Game::Object::RightAlignedFont::~RightAlignedFont(){}

void Game::Object::RightAlignedFont::Draw( const s3d::String& text ) const{
	const int w = font( text ).region().w;
	font( text ).draw( posX - w, posY );
}
