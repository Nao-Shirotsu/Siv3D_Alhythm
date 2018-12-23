#pragma once

#define NO_S3D_USING

#include <queue>
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
	// �eNote�ɓn�����߂ɕۊ�
	std::shared_ptr<Track> track;

	// 8���[���̋�`�A���胉�C���A���[��ID����
	std::unordered_map<LaneID, s3d::Rect> laneRects;
	s3d::Line judgeLineL;
	s3d::Line judgeLineR;
	s3d::Font letterA;
	s3d::Font letterS;
	s3d::Font letterD;
	s3d::Font letterF;
	s3d::Font letterJ;
	s3d::Font letterK;
	s3d::Font letterL;
	s3d::Font letterSmcl;

	// 1�Ȓ��e���[���ɗ���Ă���m�[�c��S�Ċi�[����
	std::unordered_map<LaneID, std::queue<Note>> notesQueue;
};

}
}