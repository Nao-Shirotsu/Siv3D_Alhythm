#include <chrono>

#include "Game_Object_Lane.h"
#include "Game_Util_Functions.h"
#include "Game_Object_Enum.h"

namespace{

constexpr int LANE_WIDTH{ 80 };
constexpr int LANE_HEIGHT{ 800 };

constexpr s3d::Color BG_COLOR{ 64, 64, 64, 224 };
constexpr s3d::Color BG_COLOR_PUSHED{ 96, 96, 96, 224 };
constexpr s3d::Color FRAME_COLOR{ 128, 128, 128 };
constexpr s3d::Color JUDGE_COLOR{ 224, 224, 224 };
constexpr s3d::Color LETTER_COLOR{ 85, 85, 85, 224 };

constexpr s3d::Color MISS_COLOR{ 48, 48, 48, 224 };

constexpr s3d::Color GOOD_COLOR{ 128, 224, 224, 224 };
constexpr s3d::Color FINE_COLOR{ 224, 224, 32, 224 };
constexpr s3d::Color JUST_COLOR{ 255, 160, 0, 224 };

}

Game::Object::Lane::Lane( std::shared_ptr<Track>& track_ ):
	track( track_ ),
	judgeLineL( 475, 690, 770, 690 ),
	judgeLineR( 900, 690, 1195, 690 ),
	letterA( 35 ),
	letterS( 35 ),
	letterD( 35 ),
	letterF( 35 ),
	letterJ( 35 ),
	letterK( 35 ),
	letterL( 35 ),
	letterSmcl( 35 ),
	comboText( 20 ),
	comboNumText( 40 ),
	combo( 0 ),
	noteJudgeText( 55, s3d::Typeface::Heavy, s3d::FontStyle::Outline ),
	noteJudgeStr( L"" ),
	noteJudge( NoteJudge::Undone ),
	stopwatch(){
	// mapの実体を作る
	using namespace Game::Object;
	notesQueue[LaneID::A];
	notesQueue[LaneID::S];
	notesQueue[LaneID::D];
	notesQueue[LaneID::F];
	notesQueue[LaneID::J];
	notesQueue[LaneID::K];
	notesQueue[LaneID::L];
	notesQueue[LaneID::Smcl];

	laneRects[LaneID::A] = s3d::Rect( 470, 0, 80, 800 );
	laneRects[LaneID::S] = s3d::Rect( 545, 0, 80, 800 );
	laneRects[LaneID::D] = s3d::Rect( 620, 0, 80, 800 );
	laneRects[LaneID::F] = s3d::Rect( 695, 0, 80, 800 );
	laneRects[LaneID::J] = s3d::Rect( 895, 0, 80, 800 );
	laneRects[LaneID::K] = s3d::Rect( 970, 0, 80, 800 );
	laneRects[LaneID::L] = s3d::Rect( 1045, 0, 80, 800 );
	laneRects[LaneID::Smcl] = s3d::Rect( 1120, 0, 80, 800 );
}

Game::Object::Lane::Lane() = default;

Game::Object::Lane::~Lane() = default;

void Game::Object::Lane::Update(){
	using namespace std::chrono;

	// ----debug----
	s3d::ClearPrint();
	// -------------

	for( auto& notes : notesQueue ){
		// ----debug----
		s3d::Println( s3d::Format( L"[ ", static_cast< s3d::wchar >( notes.first ), L" ] 残 ", notes.second.size() ) );
		// -------------

		if( notes.second.empty() ){ // ノーツのqueueが空なら何もしない
			continue;
		}

		NoteJudge res = notes.second.front().Result();
		if( res != NoteJudge::Undone ){ // ノーツのqueueの先頭が処理後だったらポップして次へ
			// 表示する判定文字の更新とコンボ加算
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

			if( noteJudge != NoteJudge::Miss ){
				combo += 1;
			}
			else{ // ミスでコンボ0
				combo = 0;
			}
			notes.second.pop();
			stopwatch.Start();
			continue;
		}

		// ノーツのqueueの先頭が未処理だったらUpdate
		notes.second.front().Update();
	}

	// ノーツが2.5秒間無い時判定文字を消す
	if( stopwatch.MilliDur() > 2500 ){
		// 何もない区間で何度も代入を避けるためstart
		stopwatch.Start();
		noteJudgeStr = L"";
	}
}

void Game::Object::Lane::Draw() const{
	// レーンを描く==================
	for( const auto& laneRect : laneRects ){
		if( Game::Util::LaneKeyPressed( static_cast<wchar_t>( laneRect.first ) ) ){
			laneRect.second.draw( BG_COLOR_PUSHED );
		}
		else{
			laneRect.second.draw( BG_COLOR );
		}
		laneRect.second.drawFrame( 5, 0, FRAME_COLOR );
	}
	judgeLineL.draw( JUDGE_COLOR );
	judgeLineR.draw( JUDGE_COLOR );
	letterA( L'A' ).draw( 495, 710, LETTER_COLOR );
	letterS( L'S' ).draw( 575, 710, LETTER_COLOR );
	letterD( L'D' ).draw( 645, 710, LETTER_COLOR );
	letterF( L'F' ).draw( 725, 710, LETTER_COLOR );
	letterJ( L'J' ).draw( 920, 710, LETTER_COLOR );
	letterK( L'K' ).draw( 1000, 710, LETTER_COLOR );
	letterL( L'L' ).draw( 1075, 710, LETTER_COLOR );
	letterSmcl( L';' ).draw( 1160, 710, LETTER_COLOR );
	// ===========================

	// 落ちてくるノーツを描く=========
	for( const auto& notes : notesQueue ){
		if( !notes.second.empty() ){
			notes.second.front().Draw();
		}
	}
	// ============================

	// コンボ周りを描く===============
	comboText( L"COMBO" ).drawCenter( 835, 290 );
	comboNumText( s3d::Format( combo ) ).drawCenter( 835, 340 );
	// =============================

	// 判定文字を描く=================
	switch( noteJudge ){
	case NoteJudge::Miss:
		noteJudgeText( noteJudgeStr ).drawCenter( 835, 400, MISS_COLOR );
		break;

	case NoteJudge::Good:
		noteJudgeText( noteJudgeStr ).drawCenter( 835, 400, GOOD_COLOR );
		break;

	case NoteJudge::Fine:
		noteJudgeText( noteJudgeStr ).drawCenter( 835, 400, FINE_COLOR );
		break;

	case NoteJudge::Just:
		noteJudgeText( noteJudgeStr ).drawCenter( 835, 400, JUST_COLOR );
		break;

	default:
		break;
	}
	// =============================
}

void Game::Object::Lane::AddNote( LaneID laneID, int bar, int beat ){
	notesQueue[laneID].emplace( bar, beat, laneID, track );
}
