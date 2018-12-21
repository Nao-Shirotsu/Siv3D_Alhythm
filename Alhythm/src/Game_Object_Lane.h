#pragma once

#define NO_S3D_USING

#include <Siv3D.hpp>

#include <queue>

#include "Game_Object_Enum.h"
#include "Game_Object_Note.h"

namespace Game{
namespace Object{

// ���Q�[�v���C��ʂɏo�郌�[����1��
class Lane{
public:
	Lane( LaneID laneID_ );

	// �������Ȃ�
	Lane();
	~Lane();

	void Update();

	void Draw() const;

	// 1�Ȓ��ɂ��̃��[���ɗ���Ă���m�[�c��S�Ċi�[����
	std::queue<Note> notes;

private:
	// ���̃��[�����ǂ̃L�[(����)�̃��[����
	LaneID laneID;

	// ���̃��[���̋�`�Ɣ��胉�C��
	s3d::Rect laneRect;
	s3d::Line judgeLineL;
	s3d::Line judgeLineR;
};

}
}