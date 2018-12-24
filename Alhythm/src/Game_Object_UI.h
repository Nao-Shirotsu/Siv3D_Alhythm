#pragma once

#define NO_S3D_USING

#include <queue>
#include <unordered_map>

#include <Siv3D.hpp>

#include "Game_Object_Enum.h"
#include "Game_Object_Note.h"
#include "Game_Object_Gauge.h"
#include "Game_Util_TimeDuration.h"

namespace Game{
namespace Object{

// 音ゲープレイ画面に出るUIとそのための処理をするクラス
class UI{
public:
	UI( std::shared_ptr<Track>& track_ );

	// 何もしない
	UI();
	~UI();

	void Update();

	void Draw() const;

	// 楽曲のノーツデータを追加する
	// どのレーンの何小節何拍目かを指定
	void AddNoteToLane( LaneID laneID, int bar, int beat );

private:
	// Noteから受け取った判定値をクリアゲージ加算値に変換
	double JudgeToGaugeVal( NoteJudge judgeVal );

	// 各Noteに渡すために保管
	std::shared_ptr<Track> track;

	// 8レーンの矩形、判定ライン、レーンID文字
	std::unordered_map<LaneID, s3d::Rect> laneRects;
	s3d::Line judgeLineL;
	s3d::Line judgeLineR;
	s3d::Font letterA;
	s3d::Font letterS;
	s3d::Font letterD;
	s3d::Font letterF;
	s3d::Font letterJ;
	s3d::Font letterK;
	s3d::Font letterL;
	s3d::Font letterSmcl;

	// コンボ数表示
	s3d::Font comboText;
	s3d::Font comboNumText;

	// コンボ数
	int combo;
	int fullCombo;

	// 判定値表示
	s3d::Font noteJudgeText;
	s3d::String noteJudgeStr;

	// 最も直近に処理されたノーツの判定値
	Game::Object::NoteJudge noteJudge;

	// 処理で利用するストップウォッチ
	Game::Util::TimeDuration stopwatch;

	// 1曲中各レーンに流れてくるノーツを全て格納する
	std::unordered_map<LaneID, std::queue<Note>> notesQueue;

	// クリアゲージ
	Game::Object::Gauge gauge;
};

}// namespace Object
}// namespace Game