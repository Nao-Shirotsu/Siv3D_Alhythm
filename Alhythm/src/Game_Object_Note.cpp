#include <unordered_map>

#include "Game_Object_Note.h"

namespace{

// ノーツを叩いた時の判定用
constexpr double GOOD_TIME{ 0.25 };
constexpr double GREAT_TIME{ 0.125 };
constexpr double PERFECT_TIME{ 0.0625 };

// ノーツの見た目の幅
constexpr int NOTE_WIDTH{ 70 };
constexpr int NOTE_HEIGHT{ 22 };

// ノーツがどのレーンかによって位置を変えるため
constexpr int POS_A{ 475 };
constexpr int POS_S{ 550 };
constexpr int POS_D{ 625 };
constexpr int POS_F{ 700 };
constexpr int POS_J{ 900 };
constexpr int POS_K{ 975 };
constexpr int POS_L{ 1050 };
constexpr int POS_Smcl{ 1125 };

// ノーツの色
constexpr s3d::Color NOTE_COLOR{ 200, 200, 200 };

// ノーツがレーン上に表示される時間
constexpr double INDICATE_TIME{ 5.0 };

constexpr int LANE_HEIGHT{ 800 };

}

Game::Object::Note::Note( int barNum_, int beatNum_, LaneID lane_, const std::shared_ptr<Track>& track_ ):
	lane( static_cast<s3d::wchar>( lane_ ) ),
	track( track_ ),
	passed( false ),
	isPushable( false ){
	secOnMusic = track->SecOnBarBeat( barNum_, beatNum_ );

	// ノーツの位置決め処理 流石にクソコードなので変更すべき
	switch( lane_ ){
	case LaneID::A:
		rectPosX = POS_A;
		break;

	case LaneID::S:
		rectPosX = POS_S;
		break;

	case LaneID::D:
		rectPosX = POS_D;
		break;

	case LaneID::F:
		rectPosX = POS_F;
		break;

	case LaneID::J:
		rectPosX = POS_J;
		break;

	case LaneID::K:
		rectPosX = POS_K;
		break;

	case LaneID::L:
		rectPosX = POS_L;
		break;

	case LaneID::Smcl:
		rectPosX = POS_Smcl;
		break;

	default:
		rectPosX = 0; // 不正値
		break;
	}
	noteRect = s3d::RoundRect( rectPosX, 0, NOTE_WIDTH, NOTE_HEIGHT, 4 );
}

Game::Object::Note::Note(){}

Game::Object::Note::~Note(){}

void Game::Object::Note::Update(){
	timeDiff = secOnMusic - track->CurSec();
	if( 0.0 < timeDiff && timeDiff < INDICATE_TIME  ){
		noteRect.setPos( { rectPosX, LANE_HEIGHT - static_cast<int>( LANE_HEIGHT * timeDiff ) } );
	}

	// このノーツが通り過ぎてない&&判定される秒数内ならば
	if( !passed && secOnMusic - GOOD_TIME < track->CurSec() && track->CurSec() < secOnMusic + GOOD_TIME ){
		isPushable = true;
		if( s3d::Key( lane ).clicked ){
			passed = true;
			track->PlayNote();
		}
	}

	else if( isPushable ){ // ノーツが押されなかったが通り過ぎた
		passed = true;
	}
}

void Game::Object::Note::Draw() const{
	if( 0.0 < timeDiff && timeDiff < INDICATE_TIME ){
		noteRect.draw( NOTE_COLOR );
		noteRect.drawFrame( 1, 0, s3d::Palette::Black );
	}
}

bool Game::Object::Note::Passed(){
	return passed;
}