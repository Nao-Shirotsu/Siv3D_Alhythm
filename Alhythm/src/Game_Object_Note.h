#pragma once

#define NO_S3D_USING

#include <memory>

#include <Siv3D.hpp>

#include "Game_Object_Track.h"
#include "Game_Object_Enum.h"

namespace Game{
namespace Object{

// ���Q�[�v���C��ʂŎg���m�[�c�I�u�W�F�N�g�̍\����
class Note{
public:
	explicit Note( int barNum_, int beatNum_, LaneID lane_, const std::shared_ptr<Track>& track_ );

	// �������Ȃ� STL�R���e�i�̂��ߗp��
	Note();
	~Note();

	void Update();
	void Draw() const;

	// �m�[�c�����ꂽ�Ȃ�true
	bool Passed();

private:
	// ���̃m�[�g���Ȓ��ŗL���ɂȂ�b��(�ʒu)
	double secOnMusic;

	// �m�[�g�̕\�����Ԃ̌v�Z�ɗ��p
	double timeDiff;

	// �\�����̂ƈʒu
	int rectPosX;
	s3d::RoundRect noteRect;

	// �F�X�ƃg���b�N�̏����g������DI�œ��Ċi�[
	std::shared_ptr<Track> track;

	// �{����LaneID�̂܂܂��悢���A��������Ɖ��x���L���X�g����K�v�����邽��s3d::wchar
	s3d::wchar lane;

	// ���̃m�[�g�����[���𗬂�؂�����Ȃ�true
	bool passed;

	// ����L���ɂȂ������ǂ���
	// ���ꂪtrue�Ȃ�Δ��胉�C���ɋ߂Â�����ł���A
	// �{�^���������Ȃ��Ă����Ԍo�߂ŏ����Ȃ���΂Ȃ�Ȃ����ߌ̕ϐ����g��
	bool isPushable;
};

}
}