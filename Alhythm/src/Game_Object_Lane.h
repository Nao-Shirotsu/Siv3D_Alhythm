#pragma once

#define NO_S3D_USING

#include <Siv3D.hpp>

#include <queue>

#include "Game_Object_Enum.h"
#include "Game_Object_Note.h"

namespace Game{
namespace Object{

// 音ゲープレイ画面に出るレーンの1列
class Lane{
public:
	Lane( LaneID laneID_ );

	// 何もしない
	Lane();
	~Lane();

	void Update();

	void Draw() const;

	// 1曲中にこのレーンに流れてくるノーツを全て格納する
	std::queue<Note> notes;

private:
	// このレーンがどのキー(鍵盤)のレーンか
	LaneID laneID;

	// このレーンの矩形と判定ライン
	s3d::Rect laneRect;
	s3d::Line judgeLineL;
	s3d::Line judgeLineR;
};

}
}