#pragma once
#pragma once

#define NO_S3D_USING

#include <Siv3D.hpp>

#include "Game_Object_Enum.h"

namespace Game{
namespace Object{

// ���Q�[�v���C��ʂŎg���m�[�c�I�u�W�F�N�g�̍\����
class Note{
public:
	Note( int barNum_, int beatNum_, LaneID lane_ );

	// �������Ȃ� STL�R���e�i�̂��ߗp��
	Note();
	~Note();

	// Getter�����o
	int BarNum();
	int BeatNum();
	LaneID Lane();

private:
	int barNum;
	int beatNum;
	LaneID lane;
};

}
}