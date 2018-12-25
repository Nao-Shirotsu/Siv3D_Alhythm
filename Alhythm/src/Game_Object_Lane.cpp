#include "Game_Object_Lane.h"
#include "Game_Util_Functions.h"

namespace{

constexpr int LANE_WIDTH{ 80 };
constexpr int LANE_HEIGHT{ 800 };

constexpr s3d::Color BG_COLOR{ 64, 64, 64, 224 };
constexpr s3d::Color BG_COLOR_PUSHED{ 96, 96, 96, 224 };
constexpr s3d::Color FRAME_COLOR{ 128, 128, 128 };
constexpr s3d::Color JUDGE_COLOR{ 224, 224, 224 };
constexpr s3d::Color LETTER_COLOR{ 85, 85, 85, 224 };

}

Game::Object::Lane::Lane( std::shared_ptr<Track>& track_ ):
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
	letterSmcl( 35 ){
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

	// ----debug----
	s3d::ClearPrint();
	// -------------

	for( auto& notes : notesQueue ){
		// ----debug----
		s3d::Println( s3d::Format( L"[ ", static_cast<s3d::wchar>( notes.first ), L" ] 残 ", notes.second.size() ) );
		// -------------

		if( notes.second.empty() ){ // ノーツのqueueが空なら何もしない
			continue;
		}
		if( notes.second.front().Passed() ){ // ノーツのqueueの先頭が処理後だったらポップだけして次へ
			notes.second.pop();
			continue;
		}
		notes.second.front().Update(); // ノーツのqueueの先頭が未処理だったらUpdate
	}
}

void Game::Object::Lane::Draw() const{
	// レーンを描く
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

	// 落ちてくるノーツを描く
	for( const auto& notes : notesQueue ){
		if( !notes.second.empty() ){
			notes.second.front().Draw();
		}
	}
}

void Game::Object::Lane::AddNote( LaneID laneID, int bar, int beat ){
	notesQueue[laneID].emplace( bar, beat, laneID, track );
}
