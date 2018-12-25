#define NO_S3D_USING

#include <Siv3D.hpp>

#include "Game_Util_Functions.h"

bool Game::Util::LaneKeyClicked( wchar_t keycode ){
	if( s3d::IsAlnum( keycode ) ){
		return s3d::Key( keycode ).clicked;
	}
	else if( keycode == L';' ){
		return s3d::Input::KeySemicolon.clicked;
	}
	return false;
}

bool Game::Util::LaneKeyPressed( wchar_t keycode ){
	if( s3d::IsAlnum( keycode ) ){
		return s3d::Key( keycode ).pressed;
	}
	else if( keycode == L';' ){
		return s3d::Input::KeySemicolon.pressed;
	}
	return false;
}
