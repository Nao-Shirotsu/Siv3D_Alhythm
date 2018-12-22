#pragma once

#define NO_S3D_USING

#include <queue>
#include <array>
#include <unordered_map>

#include <Siv3D.hpp>

#include "Game_Object_Enum.h"
#include "Game_Object_Note.h"

namespace Game{
namespace Object{

// 音ゲープレイ画面に出るレーンの1列
class Lane{
public:
	Lane( std::shared_ptr<Track>& track_ );

	// 何もしない
	Lane();
	~Lane();

	void Update();

	void Draw() const;

	// 楽曲のノーツデータを追加する
	// どのレーンの何小節何拍目かを指定
	void AddNote( LaneID laneID, int bar, int beat );

private:
	// 8レーンの矩形と判定ライン
	std::array<s3d::Rect, 8> laneRects;
	s3d::Line judgeLineL;
	s3d::Line judgeLineR;

	// 1曲中各レーンに流れてくるノーツを全て格納する
	std::unordered_map<LaneID, std::queue<Note>> notesQueue;

	// 各Noteに渡すために保管
	std::shared_ptr<Track> track;
};

}
}