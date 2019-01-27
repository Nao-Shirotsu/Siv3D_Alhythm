#pragma once
#pragma once

#define NO_S3D_USING

#include <deque>
#include <unordered_map>

#include <Siv3D.hpp>

#include "Game_Object_Enum.h"
#include "Game_Object_Note.h"
#include "Game_Object_Gauge.h"
#include "Game_Util_TimeDuration.h"
#include "Game_Object_RightAlignedFont.h"

namespace Game{
namespace Object{

// 音ゲープレイ画面に出るUIとそのための処理をするクラス
class UI{
public:
	explicit UI( std::shared_ptr<Track>& track_, const s3d::String& trackName );

	// 何もしない
	UI();
	~UI();

	void Update();

	void Draw() const;

private:
	// 描画処理の分割
	void DrawLaneSegment() const;
	void DrawNotesSegment() const;
	void DrawGaugeSegment() const;
	void DrawComboSegment() const;
	void DrawJudgeSegment() const;
	void DrawScoreSegment() const;
	void DrawClearedSegemnt() const;

	// 楽曲のノーツデータを追加する
	// どのレーンの何小節何拍目かを指定
	void AddNoteToLane( LaneID laneID, int bar, int beat );

	// トラックの譜面情報(ノーツ配置)が載ったファイルを読みこむ 
	void LoadNotesInfoFile( const s3d::String& trackName ) noexcept(false);

	// Noteから受け取った判定値をクリアゲージ加算値に変換
	double JudgeToGaugeVal( NoteJudge judgeVal );

	// Noteから受け取った判定値をスコアに変換
	int JudgeToScore( NoteJudge judgeVal );

	// クリア後に表示する文字を更新
	void UpdateClearInfo();

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

	// コンボ数表示
	s3d::Font comboText;
	s3d::Font comboNumText;

	// コンボ数
	int combo;
	int fullCombo;

	// スコア full = 100000
	int score;
	s3d::RoundRect scoreRect;
	s3d::Font scoreText;
	Game::Object::RightAlignedFont scoreNumText;

	// 判定値表示
	s3d::Font noteJudgeText;
	s3d::String noteJudgeStr;

	// 最も直近に処理されたノーツの判定値
	Game::Object::NoteJudge noteJudge;

	// 処理で利用するストップウォッチ
	Game::Util::TimeDuration stopwatch;

	// プレイ終了後のClear, failed等の表示
	bool cleared;
	s3d::Font clearText;
	s3d::String clearStr;
	s3d::Color clearColor;

	// 1曲中各レーンに流れてくるノーツを全て格納する
	std::unordered_map<LaneID, std::deque<Note>> notesLanes;

	// クリアゲージ
	Game::Object::Gauge gauge;

	// スコア満点÷fullcomboな値
	double scorePerNote;

	// ゲージマックス÷fullcomboな値
	double gaugeValPerNote;

};

}// namespace Object
}// namespace Game