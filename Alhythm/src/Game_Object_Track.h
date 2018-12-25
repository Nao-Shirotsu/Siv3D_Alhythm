#pragma once

#define NO_S3D_USING

#include <Siv3D.hpp>

namespace Game{
namespace Object{

// ���Q�[�v���C��ʂŎg���ȃI�u�W�F�N�g
// ���ߐ��┏���Ȃǂ�ێ����ď�������
class Track{
public:
	explicit Track( s3d::wchar* filename, int bpm, int maxBar_ ) noexcept(false);

	// �������Ȃ� STL�R���e�i�̂��ߗp��
	Track();
	~Track();

	// ���ߐ��A�������󂯎��b����Ԃ�
	double SecOnBarBeat( int bar, int beat ) const noexcept;

	// �Đ����̋Ȃ̌��݂̕b����Ԃ�
	double CurSec() const noexcept;

	// �y�ȍĐ�
	void Play();

	// �m�[�c�^�b�v���Đ�
	void PlayNote();

private:
	/*
	�b���ł̃m�[�c����ɂ��Aint���Ƒ�ʂɃL���X�g���邱�ƂɂȂ邽�߁A���߂���double�ŕێ����ď������y������B
	���̃N���X�̃C���X�^���X�̌��͔��ɏ��Ȃ��Ȃ�͂��Ȃ̂ŁA���������\�[�X��double�ł����ɂȂ�Ȃ��B
	*/
	double beatSec; // 1���Ōo�߂���b�� = 60/BPM
	double curBar;  // ���݂̏��ߐ� 1-origin
	double curBaet; // ���݂̏��ߓ��̔��� 1-origin 32�������ŕ\�� 5/32�Ȃ�
	s3d::Sound file; // �y��
	s3d::Sound tapSound; // �^�b�v��
	int maxBar; // ���̃g���b�N�̍ŏI���ߔԍ�
};

}
}