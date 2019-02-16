#pragma once
#pragma once
#pragma once

#define NO_S3D_USING

#include <deque>
#include <unordered_map>

#include <Siv3D.hpp>

#include "Game_Object_Enum.h"
#include "Game_Object_Note.h"
#include "Game_FileID.h"

namespace Game{
namespace Object{

// 音ゲープレイ画面に出るノーツが流れるレーンのクラス
class Lane{
public:
	explicit Lane( std::shared_ptr<Track>& track_ );

	// 何もしない
	Lane();
	~Lane();

	std::deque<NoteJudge> Update();
	void Draw() const;

	int FullCombo() const;
	
private:
	// とりあえずおいてる
	void DrawNotesSegment() const;
	void DrawLaneSegment() const;

	// 楽曲のノーツデータを追加する( LoadNotesInfoFile内で使用 )
	// どのレーンの何小節何拍目かを指定
	void AddNoteToLane( LaneID laneID, int bar, int beat );

	// トラックの譜面情報(ノーツ配置)が載ったファイルを読みこむ 
	void LoadNotesInfoFile();

	int fullCombo;

	// 各Noteに渡すために保管
	std::shared_ptr<Track> track;

	// 8レーンの矩形、判定ライン、レーンID文字
	std::unordered_map<LaneID, s3d::Rect> laneRects;
	s3d::Rect judgeLineL;
	s3d::Rect judgeLineR;
	s3d::Font letterA;
	s3d::Font letterS;
	s3d::Font letterD;
	s3d::Font letterF;
	s3d::Font letterJ;
	s3d::Font letterK;
	s3d::Font letterL;
	s3d::Font letterSmcl;

	// 1曲中各レーンに流れてくるノーツを全て格納する
	std::unordered_map<LaneID, std::deque<Note>> noteLines;
};

}// namespace Object
}// namespace Game