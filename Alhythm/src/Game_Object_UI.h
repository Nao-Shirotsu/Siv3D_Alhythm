#pragma once

#define NO_S3D_USING

#include <Siv3D.hpp>

#include "Game_Object_Enum.h"
#include "Game_Object_Note.h"
#include "Game_Object_Gauge.h"
#include "Game_Util_TimeDuration.h"
#include "Game_Object_RightAlignedFont.h"
#include "Game_Object_Lane.h"
#include "Game_FileID.h"

namespace Game{
namespace Object{

// 音ゲープレイ画面に出るUIとそのための処理をするクラス
class UI{
public:
	explicit UI( std::shared_ptr<Track>& track_ );

	// 何もしない
	UI();
	~UI();

	void Update();
	void Draw() const;

private:
	// 描画処理の分割
	void DrawGaugeSegment() const;
	void DrawComboSegment() const;
	void DrawJudgeSegment() const;
	void DrawScoreSegment() const;
	void DrawClearedSegemnt() const;

	// Noteから受け取った判定値をクリアゲージ加算値に変換
	double JudgeToGaugeVal( NoteJudge judgeVal );

	// Noteから受け取った判定値をスコアに変換
	int JudgeToScore( NoteJudge judgeVal );

	// クリア後に表示する文字を更新
	void UpdateClearInfo();

	// とりあえず
	std::shared_ptr<Track> track;

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

	// ノーツを流すレーン
	Game::Object::Lane lane;

	// 処理で利用するストップウォッチ
	Game::Util::TimeDuration stopwatch;

	// プレイ終了後のClear, failed等の表示
	bool cleared;
	s3d::Font clearText;
	s3d::String clearStr;
	s3d::Color clearColor;

	// クリアゲージ
	Game::Object::Gauge gauge;

	// スコア満点÷fullcomboな値
	double scorePerNote;

	// ゲージマックス÷fullcomboな値
	double gaugeValPerNote;

};

}// namespace Object
}// namespace Game