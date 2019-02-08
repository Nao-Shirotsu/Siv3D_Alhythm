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

s3d::String Game::Util::FullTrackName( const Game::BinFileID id ){
	int num = static_cast<int>( id );
	if( num < 3000 || 4000 <= num ){
		return L"";
	}

	using ID = Game::BinFileID;
	switch( id ){
	case ID::Senkou:
		return L"閃光の足跡";

	case ID::Cassi:
		return L"Cassiopeia";

	case ID::Orion:
		return L"Orion";

	default:
		return L"";
	}
}

s3d::String Game::Util::EmbededFilePath( const Game::BinFileID id ){
	return L"/" + s3d::Format( static_cast<int>( id ) );
}

s3d::String Game::Util::EmbededNotesInfoPath( const Game::BinFileID id ){
	int num = static_cast<int>( id );
	if( 3000 <= num && num < 4000 ){
		return L"/" + s3d::Format( ( num + 1000 ) );
	}
	return L"/";
}
