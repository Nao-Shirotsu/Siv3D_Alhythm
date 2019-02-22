#include <unordered_map>
#include <cmath>

#include "Game_Object_BarLine.h"
#include "Game_Object_Constant.h"

namespace{

// 小節線の色
constexpr s3d::Color NOTE_COLOR{ 200, 200, 200 };

// 1小節のどの拍で小節線が判定ラインまで落ちてくるか
constexpr int BARLINE_VALID_BEAT{ 1 };

}

Game::Object::BarLine::BarLine( int barNum_, const std::shared_ptr<Track>& track_ ):
	track( track_ ),
	lineL( L_JUDGELINE_POS_X, 0, L_JUDGELINE_POS_X + JUDGELINE_LENGTH, 0 ),
	lineR( R_JUDGELINE_POS_X, 0, R_JUDGELINE_POS_X + JUDGELINE_LENGTH, 0 ){
	secOnMusic = track->SecOnBarBeat( barNum_, BARLINE_VALID_BEAT );
	timeDiff = secOnMusic - track->CurSec();
}

Game::Object::BarLine::BarLine(){}

Game::Object::BarLine::~BarLine(){}

void Game::Object::BarLine::Update(){
	// posYの更新
	timeDiff = secOnMusic - track->CurSec();

	// この小節線が判定される秒数内ならば
	if( 0.0 < timeDiff && timeDiff < NOTE_INDICATE_TIME ){
		int posY = JUDGELINE_HEGHT - static_cast<int>( ( timeDiff / NOTE_INDICATE_TIME ) * JUDGELINE_HEGHT ) + NOTE_HEIGHT;
		lineL.set( L_JUDGELINE_POS_X, posY, L_JUDGELINE_POS_X + JUDGELINE_LENGTH, posY );
		lineR.set( R_JUDGELINE_POS_X, posY, R_JUDGELINE_POS_X + JUDGELINE_LENGTH, posY );
	}
}

void Game::Object::BarLine::Draw() const{
	if( 0.0 < timeDiff && timeDiff < NOTE_INDICATE_TIME ){
		lineL.draw();
		lineR.draw();
	}
}

bool Game::Object::BarLine::IsValidToIndicate() const{
	return secOnMusic - track->CurSec() < NOTE_INDICATE_TIME;
}
