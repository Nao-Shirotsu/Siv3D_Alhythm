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

s3d::String Game::Util::FullTrackName( const s3d::String& trackName ){
	if( trackName == L"senkou" ){
		return L"閃光の足跡";
	}

	if( trackName == L"orion" ){
		return L"Orion";
	}

	if( trackName == L"cassi" ){
		return L"Cassiopeia";
	}

	return L"";
}
