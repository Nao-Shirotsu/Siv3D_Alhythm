#include "Game_Object_Lane.h"

namespace{

constexpr int LANE_WIDTH = 80;
constexpr int LANE_HEIGHT = 800;

constexpr s3d::Color BG_COLOR{ 64, 64, 64, 224 };
constexpr s3d::Color FRAME_COLOR{ 128, 128, 128 };
constexpr s3d::Color JUDGE_COLOR{ 224, 224, 224 };

}

Game::Object::Lane::Lane( LaneID laneID_ ):
	laneID( laneID_ ),
	judgeLineL( 280, 680, 575, 680 ),
	judgeLineR( 705, 680, 1000, 680 ){
	switch( laneID_ ){
	case LaneID::A:
		laneRect = s3d::Rect( 275, 0, LANE_WIDTH, LANE_HEIGHT );
		break;

	case LaneID::S:
		laneRect = s3d::Rect( 350, 0, LANE_WIDTH, LANE_HEIGHT );
		break;

	case LaneID::D:
		laneRect = s3d::Rect( 425, 0, LANE_WIDTH, LANE_HEIGHT );
		break;

	case LaneID::F:
		laneRect = s3d::Rect( 500, 0, LANE_WIDTH, LANE_HEIGHT );
		break;

	case LaneID::J:
		laneRect = s3d::Rect( 700, 0, LANE_WIDTH, LANE_HEIGHT );
		break;

	case LaneID::K:
		laneRect = s3d::Rect( 775, 0, LANE_WIDTH, LANE_HEIGHT );
		break;

	case LaneID::L:
		laneRect = s3d::Rect( 850, 0, LANE_WIDTH, LANE_HEIGHT );
		break;

	case LaneID::Smcl:
		laneRect = s3d::Rect( 925, 0, LANE_WIDTH, LANE_HEIGHT );
		break;

	default:
		laneRect = s3d::Rect( 0, 0, 0, 0 );
		break;
	}
}

Game::Object::Lane::Lane() = default;

Game::Object::Lane::~Lane() = default;

void Game::Object::Lane::Update(){
	if( notes.empty() ){
		return;
	}
	if( notes.front().Passed() ){
		notes.pop();
	}
	notes.front().Update();
}

void Game::Object::Lane::Draw() const{
	laneRect.draw( BG_COLOR );
	laneRect.drawFrame( 5, 0, FRAME_COLOR );
	judgeLineL.draw( JUDGE_COLOR );
	judgeLineR.draw( JUDGE_COLOR );
}
