﻿#include "Game_Util_Functions.h"

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

s3d::String Game::Util::FullTrackName( const Game::TrackFileID id ){
	int num = static_cast<int>( id );
	if( num < 3000 || 4000 <= num ){
		return L"";
	}

	using ID = Game::TrackFileID;
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

s3d::String Game::Util::EmbeddedFilePath( const Game::SEBGMFileID id ){
	return L"/" + s3d::Format( static_cast<int>( id ) );
}

s3d::String Game::Util::EmbeddedFilePath( const Game::TrackFileID id ){
	if( id == TrackFileID::CassiEmp ){
		return L"/" + s3d::Format( static_cast<int>( TrackFileID::Cassi ) );
	}
	return L"/" + s3d::Format( static_cast<int>( id ) );
}

s3d::String Game::Util::EmbeddedFilePath( const Game::ImageFileID id ){
	return L"/" + s3d::Format( static_cast<int>( id ) );
}

s3d::String Game::Util::EmbeddedNotesInfoFilePath( const Game::TrackFileID id ){
#ifndef NOTESINFODEBUG
	int num = static_cast< int >( id );
	if( num < 3000 || 4000 <= num ){
		return L"";
	}
	return L"/" + s3d::Format( ( num + 1000 ) );
#else
	switch( id ){
	case Game::TrackFileID::Senkou:
		return L"NotesInfo/senkou.csv";

	case Game::TrackFileID::Cassi:
		return L"NotesInfo/cassi.csv";

	case Game::TrackFileID::Orion:
		return L"NotesInfo/orion.csv";

	case Game::TrackFileID::CassiEmp:
		return L"NotesInfo/cassi_emp.csv";

	default:
		return L"";
}
#endif
}
