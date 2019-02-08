#define NO_S3D_USING

#include <exception>

#include <Siv3D.hpp>

#include "Game_Object_ClickButton.h"
#include "Game_Util_Functions.h"

namespace Game{
namespace Object{

ClickButton::ClickButton(){}

ClickButton::ClickButton( int x_, int y_, const s3d::wchar* text_, const int fontsize_ ):
	x( x_ ),
	y( y_ ),
	rectColor( 20, 20, 40 ),
	text( fontsize_, s3d::Typeface::Medium, s3d::FontStyle::Outline ),
	textStr( text_ ),
	decideSound( Util::EmbededFilePath( BinFileID::DecideSound ) ){
	//test
	auto str = Util::EmbededFilePath( BinFileID::DecideSound );
	//----
	using namespace s3d;
	if( !decideSound ){
		throw std::runtime_error( "[Game::Object::ClickButton::ClickButton()] sound file read error" );
	}
	text.changeOutlineStyle( TextOutlineStyle( TextOutlineStyle( Color( 80, 80, 130 ), Color( 100, 100, 150 ), 2.0 ) ) );
	Rect tmp = text( text_ ).region( x, y );
	rect = Rect( tmp.x - 10, tmp.y - 5, tmp.w + 20, tmp.h + 10 );
}

void ClickButton::Draw() const{
	rect.drawShadow( { 6, 4 }, 13, 7 );
	rect.draw( rectColor );
	text( textStr ).draw( x, y );
}

bool ClickButton::WasClicked() const{
	using namespace s3d;
	const Point cursolPos = Mouse::Pos();
	if( rect.x <= cursolPos.x && cursolPos.x <= rect.x + rect.w && 
		rect.y <= cursolPos.y && cursolPos.y <= rect.y + rect.h &&
		Input::MouseL.clicked ){
		decideSound.play();
		return true;
	}
	return false;
}

}// namespace Object
}// namespace Game