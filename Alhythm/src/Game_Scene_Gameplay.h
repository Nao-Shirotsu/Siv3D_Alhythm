#pragma once

#define NO_S3D_USING

#include <memory>
#include <unordered_map>

#include <Siv3D.hpp>

#include "Game_Scene_Base.h"
#include "Game_Object_ClickButton.h"
#include "Game_Object_Track.h"
#include "Game_Object_Lane.h"

namespace Game{
namespace Scene{

// �V�[���F�y�ȃv���C���
class Gameplay: public Base{
public:
	Gameplay();
	~Gameplay();

	void Update() override;
	void Draw() const override;
	bool NeedsTransition() override;
	std::unique_ptr<Base> TransitionToNext() override;

private:
	// �߂�{�^��
	Game::Object::ClickButton returnToSelect;

	// �f�o�b�O�p�{�^���ƕ�����
	Game::Object::ClickButton button;
	Game::Object::ClickButton playMusic;
	s3d::Font text;
	s3d::String str;

	// �����t�@�C���I�u�W�F�N�g musicBegan�ōĐ��ς��ۂ����肷��
	std::shared_ptr<Game::Object::Track> track;
	bool musicBegan;

	// ���[��
	Game::Object::Lane lanes;
};

}// namespace Scene
}// namespace Game