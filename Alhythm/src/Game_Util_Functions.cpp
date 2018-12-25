#include "Game_Util_Functions.h"

bool Game::Util::LaneKeyClicked( s3d::wchar keycode ){
	if( s3d::IsAlnum( keycode ) ){
		return s3d::Key( keycode ).clicked;
	}
	else if( keycode == L';' ){
		return s3d::Input::KeySemicolon.clicked;
	}
	return false;
}

bool Game::Util::LaneKeyPressed( s3d::wchar keycode ){
	if( s3d::IsAlnum( keycode ) ){
		return s3d::Key( keycode ).pressed;
	}
	else if( keycode == L';' ){
		return s3d::Input::KeySemicolon.pressed;
	}
	return false;
}
