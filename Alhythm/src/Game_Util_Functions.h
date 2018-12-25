#pragma once

#define NO_S3D_USING

#include <Siv3D.hpp>

namespace Game{
namespace Util{

bool LaneKeyClicked( wchar_t keycode );
bool LaneKeyPressed( wchar_t keycode );

s3d::String FullTrackName( const s3d::String& trackName );

}// namespace Util
}// namespace Game