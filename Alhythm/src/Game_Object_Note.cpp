#include <unordered_map>

#include "Game_Object_Note.h"

namespace{

// �m�[�c��@�������̔���p
constexpr double GOOD_TIME{ 0.25 };
constexpr double GREAT_TIME{ 0.125 };
constexpr double PERFECT_TIME{ 0.0625 };

// �m�[�c�̌����ڂ̕�
constexpr int NOTE_WIDTH{ 70 };
constexpr int NOTE_HEIGHT{ 22 };

// �m�[�c���ǂ̃��[�����ɂ���Ĉʒu��ς��邽��
constexpr int POS_A{ 475 };
constexpr int POS_S{ 550 };
constexpr int POS_D{ 625 };
constexpr int POS_F{ 700 };
constexpr int POS_J{ 900 };
constexpr int POS_K{ 975 };
constexpr int POS_L{ 1050 };
constexpr int POS_Smcl{ 1125 };

// �m�[�c�̐F
constexpr s3d::Color NOTE_COLOR{ 200, 200, 200 };

// �m�[�c�����[����ɕ\������鎞��
constexpr double INDICATE_TIME{ 5.0 };

constexpr int LANE_HEIGHT{ 800 };

}

Game::Object::Note::Note( int barNum_, int beatNum_, LaneID lane_, const std::shared_ptr<Track>& track_ ):
	lane( static_cast<s3d::wchar>( lane_ ) ),
	track( track_ ),
	passed( false ),
	isPushable( false ){
	secOnMusic = track->SecOnBarBeat( barNum_, beatNum_ );

	// �m�[�c�̈ʒu���ߏ��� ���΂ɃN�\�R�[�h�Ȃ̂ŕύX���ׂ�
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
		rectPosX = 0; // �s���l
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

	// ���̃m�[�c���ʂ�߂��ĂȂ�&&���肳���b�����Ȃ��
	if( !passed && secOnMusic - GOOD_TIME < track->CurSec() && track->CurSec() < secOnMusic + GOOD_TIME ){
		isPushable = true;
		if( s3d::Key( lane ).clicked ){
			passed = true;
			track->PlayNote();
		}
	}

	else if( isPushable ){ // �m�[�c��������Ȃ��������ʂ�߂���
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