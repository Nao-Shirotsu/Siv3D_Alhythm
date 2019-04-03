#pragma once

#define NO_S3D_USING

#include <memory>
#include <unordered_map>

#include <Siv3D.hpp>

#include "Game_Scene_Base.h"
#include "Game_Object_ClickButton.h"
#include "Game_Object_Track.h"
#include "Game_Object_NoteSound.h"
#include "Game_Object_RightAlignedFont.h"
#include "Game_Object_Lane.h"
#include "Game_Object_Gauge.h"
#include "Game_Util_TimeDuration.h"
#include "Game_FileID.h"

namespace Game{
namespace Scene{

// シーン：楽曲プレイ画面
class Gameplay: public Base{
public:
	Gameplay( const TrackFileID trackID, int bpm, int maxBar );

	Gameplay();
	~Gameplay();

	void Update() override;
	void Draw() const override;
	bool NeedsTransition() override;
	std::unique_ptr<Base> TransitionToNext() override;

private:
	// 描画処理の分割
	void DrawComboSegment() const;
	void DrawJudgeSegment() const;
	void DrawScoreSegment() const;
	void DrawClearedSegemnt() const;

	// Noteから受け取った判定値をクリアゲージ加算値に変換
	double JudgeToGaugeVal( Game::Object::NoteJudge judgeVal );

	// Noteから受け取った判定値をスコアに変換
	int JudgeToScore( Game::Object::NoteJudge judgeVal );

	// クリア後に表示する文字を更新
	void UpdateClearInfo();

	// 戻るボタン
	Game::Object::ClickButton returnToSelect;

	// プレイ楽曲オブジェクト
	std::shared_ptr<Game::Object::Track> track;

	// タップ音オブジェクト
	std::shared_ptr<Game::Object::NoteSound> noteSound;

	// 楽曲名表示用フォントとString
	s3d::Font trackNameText;
	s3d::String trackNameStr;
	bool musicPlaying;
	bool isReady;

	// トラック開始時の表示に使うストップウォッチ
	Game::Util::TimeDuration stopwatchTrackName;

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

	// 判定文字の処理で利用するストップウォッチ
	Game::Util::TimeDuration stopwatchJudgeState;

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

}// namespace Scene
}// namespace Game