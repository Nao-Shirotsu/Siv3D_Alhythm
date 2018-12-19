#pragma once

#include "Game_Scene_Base.h"
#include "Game_Object_ClickButton.h"

namespace Game{
namespace Scene{

// �V�[���F�ݒ���
class Settings: public Base{
public:
	Settings();
	~Settings();

	void Update() override;
	void Draw() const override;
	bool NeedsTransition() override;
	std::unique_ptr<Base> TransitionToNext() override;

private:
	// �I�ȉ�ʂւ��ǂ�
	Game::Object::ClickButton returnToSelect;
};

}// namespace Scene
}// namespace Game