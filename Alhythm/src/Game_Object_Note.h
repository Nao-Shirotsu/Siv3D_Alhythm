#pragma once
#pragma once

#define NO_S3D_USING

#include <Siv3D.hpp>

#include "Game_Object_Enum.h"

namespace Game{
namespace Object{

// 音ゲープレイ画面で使うノーツオブジェクトの構造体
class Note{
public:
	Note( int barNum_, int beatNum_, LaneID lane_ );

	// 何もしない STLコンテナのため用意
	Note();
	~Note();

	// Getterメンバ
	int BarNum();
	int BeatNum();
	LaneID Lane();

private:
	int barNum;
	int beatNum;
	LaneID lane;
};

}
}