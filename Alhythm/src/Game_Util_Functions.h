#pragma once
#pragma once

#define NO_S3D_USING

#include <Siv3D.hpp>

#include "Game_BinFileID.h"

namespace Game{
namespace Util{

bool LaneKeyClicked( wchar_t keycode );
bool LaneKeyPressed( wchar_t keycode );

s3d::String FullTrackName( const Game::BinFileID id );

s3d::String EmbededFilePath( const Game::BinFileID id );
s3d::String EmbededNotesInfoPath( const Game::BinFileID id );

}// namespace Util
}// namespace Game