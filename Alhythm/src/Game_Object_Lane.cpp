#include "Game_Object_Lane.h"

namespace{

constexpr int LANE_WIDTH{ 80 };
constexpr int LANE_HEIGHT{ 800 };

constexpr s3d::Color BG_COLOR{ 64, 64, 64, 224 };
constexpr s3d::Color FRAME_COLOR{ 128, 128, 128 };
constexpr s3d::Color JUDGE_COLOR{ 224, 224, 224 };

}

Game::Object::Lane::Lane( std::shared_ptr<Track>& track_ ):
	track( track_ ),
	judgeLineL( 475, 680, 770, 680 ),
	judgeLineR( 900, 680, 1195, 680 ){
	
	using namespace Game::Object;
	// queueの実体だけ作っておく
	notesQueue[LaneID::A];
	notesQueue[LaneID::S];
	notesQueue[LaneID::D];
	notesQueue[LaneID::F];
	notesQueue[LaneID::J];
	notesQueue[LaneID::K];
	notesQueue[LaneID::L];
	notesQueue[LaneID::Smcl];

	// レーンの描画用矩形の場所を指定
	laneRects[0] = s3d::Rect( 470, 0, 80, 800 );
	laneRects[1] = s3d::Rect( 545, 0, 80, 800 );
	laneRects[2] = s3d::Rect( 620, 0, 80, 800 );
	laneRects[3] = s3d::Rect( 695, 0, 80, 800 );
	laneRects[4] = s3d::Rect( 895, 0, 80, 800 );
	laneRects[5] = s3d::Rect( 970, 0, 80, 800 );
	laneRects[6] = s3d::Rect( 1045, 0, 80, 800 );
	laneRects[7] = s3d::Rect( 1120, 0, 80, 800 );
}

Game::Object::Lane::Lane() = default;

Game::Object::Lane::~Lane() = default;

void Game::Object::Lane::Update(){

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
		laneRect.draw( BG_COLOR );
		laneRect.drawFrame( 5, 0, FRAME_COLOR );
	}
	judgeLineL.draw( JUDGE_COLOR );
	judgeLineR.draw( JUDGE_COLOR );

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
