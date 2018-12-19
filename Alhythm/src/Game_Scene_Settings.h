#pragma once

#include "Game_Scene_Base.h"
#include "Game_Object_ClickButton.h"

namespace Game{
namespace Scene{

// シーン：設定画面
class Settings: public Base{
public:
	Settings();
	~Settings();

	void Update() override;
	void Draw() const override;
	bool NeedsTransition() override;
	std::unique_ptr<Base> TransitionToNext() override;

private:
	// 選曲画面へもどる
	Game::Object::ClickButton returnToSelect;
};

}// namespace Scene
}// namespace Game