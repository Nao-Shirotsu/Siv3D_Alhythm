#include <chrono>

#include "Game_Object_UI.h"
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

constexpr s3d::Color MISS_COLOR{ 48, 48, 48, 192 };
constexpr s3d::Color GOOD_COLOR{ 128, 224, 224, 192 };
constexpr s3d::Color FINE_COLOR{ 224, 224, 32, 192 };
constexpr s3d::Color JUST_COLOR{ 255, 160, 0, 192 };

}

Game::Object::UI::UI( std::shared_ptr<Track>& track_, const s3d::String& trackName ):
	track( track_ ),
	judgeLineL( 475, 680, 770, 680 ),
	judgeLineR( 900, 680, 1195, 680 ),
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
	stopwatch(),
	gauge(){
	// mapの実体を作る
	using namespace Game::Object;
	notesLaneDeque[LaneID::A];
	notesLaneDeque[LaneID::S];
	notesLaneDeque[LaneID::D];
	notesLaneDeque[LaneID::F];
	notesLaneDeque[LaneID::J];
	notesLaneDeque[LaneID::K];
	notesLaneDeque[LaneID::L];
	notesLaneDeque[LaneID::Smcl];

	laneRects[LaneID::A] = s3d::Rect( 470, 0, 80, 800 );
	laneRects[LaneID::S] = s3d::Rect( 545, 0, 80, 800 );
	laneRects[LaneID::D] = s3d::Rect( 620, 0, 80, 800 );
	laneRects[LaneID::F] = s3d::Rect( 695, 0, 80, 800 );
	laneRects[LaneID::J] = s3d::Rect( 895, 0, 80, 800 );
	laneRects[LaneID::K] = s3d::Rect( 970, 0, 80, 800 );
	laneRects[LaneID::L] = s3d::Rect( 1045, 0, 80, 800 );
	laneRects[LaneID::Smcl] = s3d::Rect( 1120, 0, 80, 800 );

	LoadNotesInfoFile( trackName );
}

Game::Object::UI::UI() = default;

Game::Object::UI::~UI() = default;

void Game::Object::UI::Update(){
	using namespace std::chrono;

	// ----debug----
	s3d::ClearPrint();
	// -------------

	for( auto& lane : notesLaneDeque ){
		// ----debug----
		s3d::Println( s3d::Format( L"[ ", static_cast< s3d::wchar >( lane.first ), L" ] 残 ", lane.second.size() ) );
		// -------------

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

			// 処理終わったノーツをポップ
			lane.second.pop_front();

			// 判定文字を消す計測開始
			stopwatch.Start();
			continue;
		}

		// ノーツのqueueの先頭が未処理だったらUpdate
		//lane.second.front().Update();
	}

	// ノーツが2.5秒間無い時判定文字を消す
	if( stopwatch.MilliDur() > 2500 ){
		// 何もない区間で何度も代入を避けるためstart
		stopwatch.Start();
		noteJudgeStr = L"";
	}
}

void Game::Object::UI::Draw() const{
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
	letterSmcl( L';' ).draw( 1150, 710, LETTER_COLOR );
	// ===========================

	// 落ちてくるノーツを描く=========
	for( const auto& lane : notesLaneDeque ){
		if( !lane.second.empty() ){
			for( const auto& note : lane.second ){
				if( !note.IsValidtoIndicate() ){
					break;
				}
				note.Draw();
			}
		}
	}
	// ============================

	gauge.Draw();

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

void Game::Object::UI::AddNoteToLane( LaneID laneID, int bar, int beat ){
	notesLaneDeque[laneID].emplace_back( bar, beat, laneID, track );
}

void Game::Object::UI::LoadNotesInfoFile( const s3d::String& trackName ) noexcept( false ){
	const s3d::CSVReader csv( L"NotesInfo/" + trackName + L".csv" );
	if( !csv || csv.isEmpty() ){
		throw std::runtime_error( "notesinfo file read error" );
	}
	
	fullCombo = static_cast<int>( csv._get_rows() );
	for( int i = 0; i < fullCombo; ++i ){
		AddNoteToLane( static_cast<LaneID>( csv.get<wchar_t>( i, 0 ) ), csv.get<int>( i, 1 ), csv.get<int>( i, 2 ) );
	}
}

//int Game::Object::UI::RestNotesNum(){
//	int count = 0;
//	for( const auto& lane : notesLaneDeque ){
//		count += lane.second.size();
//	}
//	return count;
//}
//
double Game::Object::UI::JudgeToGaugeVal( Game::Object::NoteJudge judgeVal ){
	switch( judgeVal ){
	case NoteJudge::Just:
		return  200.0 / static_cast<double>( fullCombo );

	case NoteJudge::Fine:
		return 100.0 / static_cast< double >( fullCombo );

	case NoteJudge::Good:
		return 50.0 / static_cast< double >( fullCombo );

	case NoteJudge::Miss:
		return -3.0;

	default:
		return 0.0;
	}
}