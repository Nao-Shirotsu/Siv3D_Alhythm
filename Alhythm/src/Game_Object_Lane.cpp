#include "Game_Object_Lane.h"

namespace{

constexpr int LANE_WIDTH = 80;
constexpr int LANE_HEIGHT = 800;

}

Game::Object::Lane::Lane( LaneID laneID_ ):
	laneID( laneID_ ){
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

void Game::Object::Lane::Update( double secCur ){}

void Game::Object::Lane::Draw() const{
	laneRect.draw( s3d::Color( 64, 64, 64, 224 ) );
	laneRect.drawFrame( 5, 0, s3d::Color( 128, 128, 128 ) );
}
