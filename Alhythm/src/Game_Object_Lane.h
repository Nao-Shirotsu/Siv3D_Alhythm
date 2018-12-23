#pragma once

#define NO_S3D_USING

#include <queue>
#include <array>
#include <unordered_map>

#include <Siv3D.hpp>

#include "Game_Object_Enum.h"
#include "Game_Object_Note.h"

namespace Game{
namespace Object{

// ���Q�[�v���C��ʂɏo�郌�[����1��
class Lane{
public:
	Lane( std::shared_ptr<Track>& track_ );

	// �������Ȃ�
	Lane();
	~Lane();

	void Update();

	void Draw() const;

	// �y�Ȃ̃m�[�c�f�[�^��ǉ�����
	// �ǂ̃��[���̉����߉����ڂ����w��
	void AddNote( LaneID laneID, int bar, int beat );

private:
	// 8���[���̋�`�Ɣ��胉�C��
	std::array<s3d::Rect, 8> laneRects;
	s3d::Line judgeLineL;
	s3d::Line judgeLineR;

	// 1�Ȓ��e���[���ɗ���Ă���m�[�c��S�Ċi�[����
	std::unordered_map<LaneID, std::queue<Note>> notesQueue;

	// �eNote�ɓn�����߂ɕۊ�
	std::shared_ptr<Track> track;
};

}
}