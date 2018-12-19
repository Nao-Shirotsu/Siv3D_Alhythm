#include <Siv3D.hpp>

#include "Game_Object_ClickButton.h"

namespace Game{
namespace Object{

ClickButton::ClickButton(){}

ClickButton::ClickButton( int x_, int y_, const wchar* text_, const int fontsize_ ):
	x( x_ ),
	y( y_ ),
	textStr( text_ ),
	colorRect( 20, 20, 40 ),
	colorShade( 5, 5, 15 ),
	text( fontsize_, Typeface::Medium, FontStyle::Outline ){
	text.changeOutlineStyle( TextOutlineStyle( TextOutlineStyle( Color( 80, 80, 130 ), Color( 100, 100, 150 ), 1.0 ) ) );
	Rect tmp = text( text_ ).region( x, y );
	rect = Rect( tmp.x - 10, tmp.y - 10, tmp.w + 10, tmp.h + 10 );
	rectShade = Rect( tmp.x - 9, tmp.y - 9, tmp.w + 15, tmp.h + 15 );
}

void ClickButton::Draw() const{
	rectShade.draw( colorShade );
	rect.draw( colorRect );
	text( textStr ).draw( x, y );
}

bool ClickButton::WasClicked() const{
	const Point cursolPos = Mouse::Pos();
	if( rect.x <= cursolPos.x && cursolPos.x <= rect.x + rect.w && 
		rect.y <= cursolPos.y && cursolPos.y <= rect.y + rect.h ){

		return Input::MouseL.clicked;
	}
	return false;
}

}// namespace Object
}// namespace Game