#pragma once

#define NO_S3D_USING

#include <Siv3D.hpp>

#include "Game_FileID.h"

namespace Game{
namespace Util{

bool LaneKeyClicked( wchar_t keycode );
bool LaneKeyPressed( wchar_t keycode );

s3d::String FullTrackName( const Game::TrackFileID id );

s3d::String EmbeddedFilePath( const Game::ImageFileID id );
s3d::String EmbeddedFilePath( const Game::SEBGMFileID id );
s3d::String EmbeddedFilePath( const Game::TrackFileID id );

s3d::String EmbeddedNotesInfoFilePath( const Game::TrackFileID id );

}// namespace Util
}// namespace Game