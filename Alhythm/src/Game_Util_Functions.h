#pragma once

#define NO_S3D_USING

#include <Siv3D.hpp>

namespace Game{
namespace Util{

bool LaneKeyClicked( s3d::wchar keycode );
bool LaneKeyPressed( s3d::wchar keycode );

}// namespace Util
}// namespace Game