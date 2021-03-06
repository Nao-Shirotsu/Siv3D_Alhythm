﻿#include <unordered_map>
#include <cmath>

#include "Game_Object_Note.h"
#include "Game_Util_Functions.h"
#include "Game_Object_Constant.h"

namespace{

// ノーツを叩いた時の判定秒数 1/60 = 0.01666
constexpr double MISS_TIME{ 0.1875 };    // 0b0.0011
constexpr double GOOD_TIME{ 0.09375 };  //  0b0.00011
constexpr double FINE_TIME{ 0.046875 }; //  0b0.000011
constexpr double JUST_TIME{ 0.0234375 };//  0b0.0000011

// レーンごとのノーツの左上頂点のX座標
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

}

Game::Object::Note::Note( int barNum_, int beatNum_, LaneID lane_, const std::shared_ptr<Track>& track_, const std::shared_ptr<NoteSound>& noteSound_ ):
	lane( static_cast<s3d::wchar>( lane_ ) ),
	track( track_ ),
	noteSound( noteSound_ ),
	tapResult( NoteJudge::Undone ),
	isPushable( false ),
	settingState(){
	noteIndicateTime = NOTE_INDICATE_TIME / settingState.HispeedRate();
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

	default: // 不正値
		throw std::runtime_error( "csvファイルのノーツ情報が不正です。" );
		break;
	}
	noteRect = s3d::RoundRect( rectPosX, 0, NOTE_WIDTH, NOTE_HEIGHT, 4 );
}

Game::Object::Note::Note(){}

Game::Object::Note::~Note(){}

void Game::Object::Note::UpdateJudging(){
	// このノーツが通り過ぎてない&&判定される秒数内ならば
	if( tapResult == NoteJudge::Undone && secOnMusic - MISS_TIME < track->CurSec() && track->CurSec() < secOnMusic + MISS_TIME ){
		isPushable = true;
		// 判定が有効な時
		if( Game::Util::LaneKeyClicked( static_cast<wchar_t>( lane ) ) ){
			// timeDiffによって判定結果を算出してtapResultに格納
			double judgeTime = std::fabs( timeDiff );
			if( judgeTime < JUST_TIME ){
				tapResult = NoteJudge::Just;
			}
			else if( judgeTime < FINE_TIME ){
				tapResult = NoteJudge::Fine;
			}
			else if( judgeTime < GOOD_TIME ){
				tapResult = NoteJudge::Good;
			}
			else{
				tapResult = NoteJudge::Miss;
			}
			noteSound->Play( tapResult );
			return;
		}
	}
	else if( isPushable && timeDiff < -MISS_TIME ){ // ノーツが押されなかったが通り過ぎた
		tapResult = NoteJudge::Miss;
	}
}

void Game::Object::Note::UpdatePos(){
	timeDiff = secOnMusic - track->CurSec();
	noteIndicateTime = NOTE_INDICATE_TIME / settingState.HispeedRate();
	if( 0.0 < timeDiff && timeDiff < noteIndicateTime ){
		noteRect.setPos( { rectPosX, JUDGELINE_HEGHT - static_cast< int >( ( timeDiff / noteIndicateTime ) * JUDGELINE_HEGHT ) } );
	}
}

void Game::Object::Note::Draw() const{
	if( 0.0 < timeDiff && timeDiff < noteIndicateTime ){
		noteRect.draw( NOTE_COLOR );
		noteRect.drawFrame( 1, 0, s3d::Palette::Black );
	}
}

Game::Object::NoteJudge Game::Object::Note::Result(){
	return tapResult;
}

bool Game::Object::Note::IsValidToIndicate() const noexcept{
	return secOnMusic - track->CurSec() < noteIndicateTime;
}
