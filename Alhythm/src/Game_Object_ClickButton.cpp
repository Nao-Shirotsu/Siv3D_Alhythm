#define NO_S3D_USING

#include <exception>

#include <Siv3D.hpp>

#include "Game_Object_ClickButton.h"
#include "Game_Util_Functions.h"

namespace{

constexpr s3d::Color RECT_BG_COLOR{ 20, 20, 40 };
constexpr s3d::Color RECT_FRAME_COLOR{ 50, 50, 100 };

constexpr s3d::Color TEXT_BG_COLOR{ 80, 80, 130 };
constexpr s3d::Color TEXT_FRAME_COLOR{ 100, 100, 150 };

}

namespace Game{
namespace Object{

ClickButton::ClickButton(){}

ClickButton::ClickButton( int x_, int y_, const s3d::wchar * text_, const int fontsize, const int frameWidth_, s3d::Color rectColor_, s3d::Color frameColor_ ):
	x( x_ ),
	y( y_ ),
	rectColor( rectColor_ ),
	frameWidth( frameWidth_ ),
	frameColor( frameColor_ ),
	text( fontsize, s3d::Typeface::Medium, s3d::FontStyle::Outline ),
	textStr( text_ ),
	clickSound(){
	using namespace s3d;
	text.changeOutlineStyle( TextOutlineStyle( TextOutlineStyle( TEXT_BG_COLOR, TEXT_FRAME_COLOR, 2.0 ) ) );
	Rect tmp = text( text_ ).region( x, y );
	rect = Rect( tmp.x - 10, tmp.y - 5, tmp.w + 20, tmp.h + 10 );
}

ClickButton::ClickButton( int x_, int y_, const s3d::wchar* text_, const int fontsize ):
	ClickButton( x_, y_, text_, fontsize, 2, RECT_BG_COLOR, RECT_FRAME_COLOR ){}

ClickButton::ClickButton( int x_, int y_, const s3d::wchar* text_, const int fontsize, const int frameWidth_ ):
	ClickButton( x_, y_, text_, fontsize, frameWidth_, RECT_BG_COLOR, RECT_FRAME_COLOR ){}

ClickButton::ClickButton( int x_, int y_, const s3d::wchar* text_, const int fontsize, s3d::Color rectColor_, s3d::Color frameColor_ ) :
	ClickButton( x_, y_, text_, fontsize, 2, rectColor_, frameColor_ ){}


ClickButton::ClickButton( int x_, int y_, const s3d::wchar* text_, const int fontsize, const int rectWidth, const int frameWidth_, s3d::Color rectColor_, s3d::Color frameColor_ ):
	x( x_ ),
	y( y_ ),
	rectColor( rectColor_ ),
	frameWidth( frameWidth_ ),
	frameColor( frameColor_ ),
	text( fontsize, s3d::Typeface::Medium, s3d::FontStyle::Outline ),
	textStr( text_ ),
	clickSound(){
	using namespace s3d;
	text.changeOutlineStyle( TextOutlineStyle( TextOutlineStyle( Color( 80, 80, 130 ), Color( 100, 100, 150 ), 2.0 ) ) );
	Rect tmp = text( text_ ).region( x, y );
	rect = Rect( tmp.x - 10, tmp.y - 5, rectWidth, tmp.h + 10 );
}

ClickButton::ClickButton( int x_, int y_, const s3d::wchar * text_, const int fontsize, const int rectWidth, const int frameWidth_ ):
	ClickButton( x_, y_, text_, fontsize, rectWidth, frameWidth_, RECT_BG_COLOR, RECT_FRAME_COLOR ){}

void ClickButton::Draw() const{
	rect.drawShadow( { 6, 4 }, 13, 7 );
	rect.draw( rectColor );
	rect.drawFrame( frameWidth, 0, frameColor );
	text( textStr ).draw( x, y );
}

bool ClickButton::WasClicked() const{
	using namespace s3d;
	const Point cursolPos = Mouse::Pos();
	if( rect.x <= cursolPos.x && cursolPos.x <= rect.x + rect.w && 
		rect.y <= cursolPos.y && cursolPos.y <= rect.y + rect.h &&
		Input::MouseL.clicked ){
		clickSound.Play();
		return true;
	}
	return false;
}

}// namespace Object
}// namespace Game
