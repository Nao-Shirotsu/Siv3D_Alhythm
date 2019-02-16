﻿#include <chrono>
#include <deque>

#include "Game_Object_UI.h"
#include "Game_Util_Functions.h"
#include "Game_Object_Enum.h"
#include "Game_Object_Constant.h"

namespace{

// スコア関連の表示位置
constexpr int SCORE_POS_X{ 30 };
constexpr int SCORE_POS_Y{ 0 };
constexpr int SCORE_TEXT_SIZE{ 20 };
constexpr int SCORE_NUM_SIZE{ 28 };

// 判定文字の色
constexpr s3d::Color MISS_COLOR{ 48, 48, 48, 192 };
constexpr s3d::Color GOOD_COLOR{ 128, 224, 224, 192 };
constexpr s3d::Color FINE_COLOR{ 224, 224, 32, 192 };
constexpr s3d::Color JUST_COLOR{ 255, 160, 0, 192 };

// 判定文字の位置(左上頂点)
constexpr int JUDGE_TEXT_POS_X{ 835 };
constexpr int JUDGE_TEXT_POS_Y{ 400 };
constexpr int JUDGE_TEXT_SIZE{ 55 };

// ノーツが一度叩かれた後の判定文字の表示秒数(ミリ秒)
constexpr int JUDGE_TEXT_VALID_TIME{ 2500 };

// クリア文字の位置など
constexpr int CLEAR_TEXT_POS_X{ 835 };
constexpr int CLEAR_TEXT_POS_Y{ 420 };
constexpr int CLEAR_TEXT_SIZE{ 60 };

// コンボ文字の位置など
constexpr int COMBO_TEXT_POS_X{ 835 };
constexpr int COMBO_TEXT_POS_Y{ 290 };
constexpr int COMBO_NUM_POS_X{ 835 };
constexpr int COMBO_NUM_POS_Y{ 340 };
constexpr int COMBO_TEXT_SIZE{ 20 };
constexpr int COMBO_NUM_SIZE{ 40 };

// スコア値を表示する四角形の色
constexpr s3d::Color SCORE_BG_COLOR{ 0x2d, 0x38, 0x59 };

// クリアゲージの最大値と増加割合(判定ごとの割合)など
constexpr double GAUGE_FULL{ 100.0 }; // この値÷fullcomboで1ノーツの増加量
constexpr double GAUGE_JUST_FACTOR{ 4.0 };
constexpr double GAUGE_FINE_FACTOR{ 2.0 };
constexpr double GAUGE_GOOD_FACTOR{ 1.0 };
constexpr double GAUGE_MISS_NUM{ -3.0 }; // ミスは定数でゲージ減少

// スコアの最大値と増加割合 fullcomboで満点にするのでJUSTは無し MISSも0にするので無し
constexpr double SCORE_FULL{ 100000.0 }; // この値÷fullcomboで1ノーツの増加量
constexpr double SCORE_FINE_FACTOR{ 0.5 };
constexpr double SCORE_GOOD_FACTOR{ 0.25 };

}

Game::Object::UI::UI( std::shared_ptr<Track>& track_ ):
	track( track_ ),
	comboText( COMBO_TEXT_SIZE ),
	comboNumText( COMBO_NUM_SIZE ),
	combo( 0 ),
	score( 0 ),
	scoreRect( SCORE_POS_X, SCORE_POS_Y + 35, s3d::Font( 28 )( L"1234567" ).region().w, s3d::Font( 32 )( L"1" ).region().h, 5 ),
	scoreText( SCORE_TEXT_SIZE ),
	scoreNumText( SCORE_NUM_SIZE, 196, 48 ),
	noteJudgeText( JUDGE_TEXT_SIZE, s3d::Typeface::Heavy, s3d::FontStyle::Outline ),
	noteJudgeStr( L"" ),
	noteJudge( NoteJudge::Undone ),
	lane( track_ ),
	stopwatch(),
	cleared( false ),
	clearText( CLEAR_TEXT_SIZE, s3d::Typeface::Bold, s3d::FontStyle::Outline ),
	clearStr( L"" ),
	clearColor( 0, 0, 0 ),
	gauge(){
	fullCombo = lane.FullCombo();
	scorePerNote = SCORE_FULL / static_cast<double>( fullCombo );
	gaugeValPerNote = GAUGE_FULL / static_cast<double>( fullCombo );
}

Game::Object::UI::UI() = default;

Game::Object::UI::~UI() = default;

void Game::Object::UI::Update(){
	using namespace std::chrono;

	// 右辺をlane.なんとか()にする
	for( const auto& res : lane.Update() ){
		if( res != NoteJudge::Undone ){ // ノーツのdequeの先頭が処理後だったらポップして次へ
			// 表示する判定文字の更新
			noteJudge = res;
			switch( noteJudge ){
			case NoteJudge::Miss:
				noteJudgeStr = L"MISS";
				break;

			case NoteJudge::Good:
				noteJudgeStr = L"GOOD";
				break;

			case NoteJudge::Fine:
				noteJudgeStr = L"FINE";
				break;

			case NoteJudge::Just:
				noteJudgeStr = L"JUST";
				break;

			default:
				noteJudgeStr = L"";
				break;
			}

			// コンボ加算
			if( noteJudge != NoteJudge::Miss ){
				combo += 1;
			}
			else{ // ミスでコンボ0
				combo = 0;
			}

			// ゲージ増減処理
			gauge.Update( JudgeToGaugeVal( res ) );
			score += JudgeToScore( res );

			// 判定文字を消す計測開始
			stopwatch.Start();
		}
	}

	// ノーツが2.5秒間無い時判定文字を消す
	if( stopwatch.MilliDur() > JUDGE_TEXT_VALID_TIME ){
		// 何もない区間で何度も代入を避けるためstart
		stopwatch.Start();
		noteJudgeStr = L"";
	}

	if( !cleared && track->IsEnd() ){
		cleared = true;
		UpdateClearInfo();
	}
}

void Game::Object::UI::Draw() const{
	lane.Draw();
	DrawGaugeSegment();
	DrawComboSegment();
	DrawJudgeSegment();
	DrawScoreSegment();
	DrawClearedSegemnt();
}

void Game::Object::UI::DrawGaugeSegment() const{
	gauge.Draw();
}

void Game::Object::UI::DrawComboSegment() const{
	comboText( L"COMBO" ).drawCenter( COMBO_TEXT_POS_X, COMBO_TEXT_POS_Y );
	comboNumText( s3d::Format( combo ) ).drawCenter( COMBO_NUM_POS_X, COMBO_NUM_POS_Y );
}

void Game::Object::UI::DrawJudgeSegment() const{
	switch( noteJudge ){
	case NoteJudge::Miss:
		noteJudgeText( noteJudgeStr ).drawCenter( JUDGE_TEXT_POS_X, JUDGE_TEXT_POS_Y, MISS_COLOR );
		break;

	case NoteJudge::Good:
		noteJudgeText( noteJudgeStr ).drawCenter( JUDGE_TEXT_POS_X, JUDGE_TEXT_POS_Y, GOOD_COLOR );
		break;

	case NoteJudge::Fine:
		noteJudgeText( noteJudgeStr ).drawCenter( JUDGE_TEXT_POS_X, JUDGE_TEXT_POS_Y, FINE_COLOR );
		break;

	case NoteJudge::Just:
		noteJudgeText( noteJudgeStr ).drawCenter( JUDGE_TEXT_POS_X, JUDGE_TEXT_POS_Y, JUST_COLOR );
		break;

	default:
		break;
	}
}

void Game::Object::UI::DrawScoreSegment() const{
	scoreText( L"SCORE" ).draw( SCORE_POS_X, SCORE_POS_Y );
	scoreRect.draw( SCORE_BG_COLOR );
	scoreRect.drawFrame( 2, 0, s3d::Palette::Midnightblue );
	scoreNumText.Draw( s3d::Format( score ) );
}

void Game::Object::UI::DrawClearedSegemnt() const {
	if( cleared ){
		clearText( clearStr ).drawCenter( CLEAR_TEXT_POS_X, CLEAR_TEXT_POS_Y, clearColor );
	}
}

double Game::Object::UI::JudgeToGaugeVal( Game::Object::NoteJudge judgeVal ){
	switch( judgeVal ){
	case NoteJudge::Just:
		return gaugeValPerNote * GAUGE_JUST_FACTOR;

	case NoteJudge::Fine:
		return gaugeValPerNote * GAUGE_FINE_FACTOR;

	case NoteJudge::Good:
		return gaugeValPerNote * GAUGE_GOOD_FACTOR;

	case NoteJudge::Miss:
		return GAUGE_MISS_NUM;

	default:
		return 0.0;
	}
}

int Game::Object::UI::JudgeToScore( Game::Object::NoteJudge judgeVal ){
	switch( judgeVal ){
	case NoteJudge::Just:
		return static_cast<int>( scorePerNote );

	case NoteJudge::Fine:
		return static_cast<int>( scorePerNote * SCORE_FINE_FACTOR );

	case NoteJudge::Good:
		return static_cast<int>( scorePerNote * SCORE_GOOD_FACTOR );

	case NoteJudge::Miss:
		return 0;

	default:
		return 0;
	}
}

void Game::Object::UI::UpdateClearInfo(){
	if( gauge.IsOverClearPersent() && combo == fullCombo ){
		clearStr = L"FULL COMBO";
		clearColor = s3d::Palette::Mediumvioletred;
	}
	else if( gauge.IsOverClearPersent() ){
		clearStr = L"CLEARED";
		clearColor = s3d::Palette::Orangered;
	}
	else{
		clearStr = L"FAILED";
		clearColor = s3d::Palette::Darkslateblue;
	}
}


