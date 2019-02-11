#include <chrono>

#include "Game_Object_UI.h"
#include "Game_Util_Functions.h"
#include "Game_Object_Enum.h"
#include "Game_Object_Constant.h"

namespace{

// レーン枠の色など
constexpr s3d::Color LANE_BG_COLOR{ 64, 64, 64, 224 };
constexpr s3d::Color LANE_BG_COLOR_PUSHED{ 96, 96, 96, 224 };
constexpr s3d::Color FRAME_COLOR{ 128, 128, 128 };
constexpr s3d::Color JUDGELINE_COLOR{ 224, 224, 224, 128 };

// レーン枠の左上頂点の位置
constexpr int LANE_A_POS_X{ 470 };
constexpr int LANE_S_POS_X{ 545 };
constexpr int LANE_D_POS_X{ 620 };
constexpr int LANE_F_POS_X{ 695 };
constexpr int LANE_J_POS_X{ 895 };
constexpr int LANE_K_POS_X{ 970 };
constexpr int LANE_L_POS_X{ 1045 };
constexpr int LANE_Smcl_POS_X{ 1120 };
constexpr int LANE_POS_Y{ 0 };

// レーン枠の幅
constexpr int LANE_FRAME_WIDTH{ 5 };

// レーン下部に表示するASDFなどの値
constexpr int LANE_LETTER_SIZE{ 35 };
constexpr int LANE_LETTER_POS_Y{ Game::Object::LANE_HEIGHT - 90 };
constexpr int LANE_LETTER_A_POS_X{ LANE_A_POS_X + 25 };
constexpr int LANE_LETTER_S_POS_X{ LANE_S_POS_X + 30 };
constexpr int LANE_LETTER_D_POS_X{ LANE_D_POS_X + 30 };
constexpr int LANE_LETTER_F_POS_X{ LANE_F_POS_X + 30 };
constexpr int LANE_LETTER_J_POS_X{ LANE_J_POS_X + 25 };
constexpr int LANE_LETTER_K_POS_X{ LANE_K_POS_X + 30 };
constexpr int LANE_LETTER_L_POS_X{ LANE_L_POS_X + 30 };
constexpr int LANE_LETTER_Smcl_POS_X{ LANE_Smcl_POS_X + 30 };
constexpr s3d::Color LANE_LETTER_COLOR{ 85, 85, 85, 224 };

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
constexpr double GAUGE_JUST_FACTOR{ 2.0 };
constexpr double GAUGE_FINE_FACTOR{ 1.0 };
constexpr double GAUGE_GOOD_FACTOR{ 0.5 };
constexpr double GAUGE_MISS_NUM{ -3.0 }; // ミスは定数でゲージ減少

// スコアの最大値と増加割合 fullcomboで満点にするのでJUSTは無し MISSも0にするので無し
constexpr double SCORE_FULL{ 100000.0 }; // この値÷fullcomboで1ノーツの増加量
constexpr double SCORE_FINE_FACTOR{ 0.5 };
constexpr double SCORE_GOOD_FACTOR{ 0.25 };

}

Game::Object::UI::UI( std::shared_ptr<Track>& track_, const BinFileID trackID ):
	track( track_ ),
	judgeLineL( LANE_A_POS_X + 5, JUDGELINE_HEGHT - NOTE_HEIGHT / 2, LANE_WIDTH * 4 - 25, NOTE_HEIGHT ), // +5とか-25は枠の分
	judgeLineR( LANE_J_POS_X + 5, JUDGELINE_HEGHT - NOTE_HEIGHT / 2, LANE_WIDTH * 4 - 25, NOTE_HEIGHT ),
	letterA( LANE_LETTER_SIZE ),
	letterS( LANE_LETTER_SIZE ),
	letterD( LANE_LETTER_SIZE ),
	letterF( LANE_LETTER_SIZE ),
	letterJ( LANE_LETTER_SIZE ),
	letterK( LANE_LETTER_SIZE ),
	letterL( LANE_LETTER_SIZE ),
	letterSmcl( LANE_LETTER_SIZE ),
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
	stopwatch(),
	cleared( false ),
	clearText( CLEAR_TEXT_SIZE, s3d::Typeface::Bold, s3d::FontStyle::Outline ),
	clearStr( L"" ),
	clearColor( 0, 0, 0 ),
	gauge(){
	// mapの実体を作る
	using namespace Game::Object;
	notesLanes[LaneID::A];
	notesLanes[LaneID::S];
	notesLanes[LaneID::D];
	notesLanes[LaneID::F];
	notesLanes[LaneID::J];
	notesLanes[LaneID::K];
	notesLanes[LaneID::L];
	notesLanes[LaneID::Smcl];

	laneRects[LaneID::A] = s3d::Rect( LANE_A_POS_X, LANE_POS_Y, LANE_WIDTH, LANE_HEIGHT );
	laneRects[LaneID::S] = s3d::Rect( LANE_S_POS_X, LANE_POS_Y, LANE_WIDTH, LANE_HEIGHT );
	laneRects[LaneID::D] = s3d::Rect( LANE_D_POS_X, LANE_POS_Y, LANE_WIDTH, LANE_HEIGHT );
	laneRects[LaneID::F] = s3d::Rect( LANE_F_POS_X, LANE_POS_Y, LANE_WIDTH, LANE_HEIGHT );
	laneRects[LaneID::J] = s3d::Rect( LANE_J_POS_X, LANE_POS_Y, LANE_WIDTH, LANE_HEIGHT );
	laneRects[LaneID::K] = s3d::Rect( LANE_K_POS_X, LANE_POS_Y, LANE_WIDTH, LANE_HEIGHT );
	laneRects[LaneID::L] = s3d::Rect( LANE_L_POS_X, LANE_POS_Y, LANE_WIDTH, LANE_HEIGHT );
	laneRects[LaneID::Smcl] = s3d::Rect( LANE_Smcl_POS_X, LANE_POS_Y, LANE_WIDTH, LANE_HEIGHT );

	LoadNotesInfoFile( trackID );

	scorePerNote = SCORE_FULL / static_cast<double>( fullCombo );
	gaugeValPerNote = GAUGE_FULL / static_cast<double>( fullCombo );
}

Game::Object::UI::UI() = default;

Game::Object::UI::~UI() = default;

void Game::Object::UI::Update(){
	using namespace std::chrono;

	for( auto& lane : notesLanes ){
		if( lane.second.empty() ){ // ノーツのdequeが空なら何もしない
			continue;
		}

		for( auto& note : lane.second ){
			if( !note.IsValidtoIndicate() ){
				break;
			}
			note.Update();
		}

		NoteJudge res = lane.second.front().Result();
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

			// 処理終わったノーツをポップ
			lane.second.pop_front();
			

			// 判定文字を消す計測開始
			stopwatch.Start();
			continue;
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
	DrawLaneSegment();
	DrawNotesSegment();
	DrawGaugeSegment();
	DrawComboSegment();
	DrawJudgeSegment();
	DrawScoreSegment();
	DrawClearedSegemnt();
}

void Game::Object::UI::DrawLaneSegment() const{
	for( const auto &laneRect : laneRects ) {
		if( Game::Util::LaneKeyPressed( static_cast< wchar_t >( laneRect.first ) ) ) {
			laneRect.second.draw( LANE_BG_COLOR_PUSHED );
		}
		else {
			laneRect.second.draw( LANE_BG_COLOR );
		}
		laneRect.second.drawFrame( LANE_FRAME_WIDTH, 0, FRAME_COLOR );
	}
	judgeLineL.draw( JUDGELINE_COLOR );
	judgeLineR.draw( JUDGELINE_COLOR );
	letterA( L'A' ).draw( LANE_LETTER_A_POS_X, LANE_LETTER_POS_Y, LANE_LETTER_COLOR );
	letterS( L'S' ).draw( LANE_LETTER_S_POS_X, LANE_LETTER_POS_Y, LANE_LETTER_COLOR );
	letterD( L'D' ).draw( LANE_LETTER_D_POS_X, LANE_LETTER_POS_Y, LANE_LETTER_COLOR );
	letterF( L'F' ).draw( LANE_LETTER_F_POS_X, LANE_LETTER_POS_Y, LANE_LETTER_COLOR );
	letterJ( L'J' ).draw( LANE_LETTER_J_POS_X, LANE_LETTER_POS_Y, LANE_LETTER_COLOR );
	letterK( L'K' ).draw( LANE_LETTER_K_POS_X, LANE_LETTER_POS_Y, LANE_LETTER_COLOR );
	letterL( L'L' ).draw( LANE_LETTER_L_POS_X, LANE_LETTER_POS_Y, LANE_LETTER_COLOR );
	letterSmcl( L';' ).draw( LANE_LETTER_Smcl_POS_X, LANE_LETTER_POS_Y, LANE_LETTER_COLOR );
}

void Game::Object::UI::DrawNotesSegment() const{
	for( const auto &lane : notesLanes ) {
		if( lane.second.empty() ) {
			continue;
		}
		for( const auto &note : lane.second ) {
			if( !note.IsValidtoIndicate() ) {
				break;
			}
			note.Draw();
		}
	}
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

void Game::Object::UI::AddNoteToLane( LaneID laneID, int bar, int beat ){
	notesLanes[laneID].emplace_back( bar, beat, laneID, track );
}

void Game::Object::UI::LoadNotesInfoFile( const BinFileID trackID ) noexcept( false ){
	const s3d::CSVReader csv( Util::EmbededNotesInfoPath( trackID ) );
	if( !csv || csv.isEmpty() ){
		throw std::runtime_error( "notesinfo file read error" );
	}

	fullCombo = static_cast< int >( csv._get_rows() );
	for( int i = 0; i < fullCombo; ++i ){
		AddNoteToLane( static_cast< LaneID >( csv.get<wchar_t>( i, 0 ) ), csv.get<int>( i, 1 ), csv.get<int>( i, 2 ) );
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


