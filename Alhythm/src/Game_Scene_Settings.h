#pragma once

#include "Game_Scene_Base.h"
#include "Game_Object_ClickButton.h"
#include "Game_Object_Lane.h"
#include "Game_Singleton_SettingState.h"
#include "Game_Object_NoteSound.h"

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
	// 設定の値を変えるスライダー
	s3d::GUI gui;

	// 選曲画面へもどる
	Game::Object::ClickButton returnToSelect;

	// ノーツを流すレーン
	Game::Object::Lane lane;

	// 設定の各値を取得
	Game::Singleton::SettingState settingState;
};

}// namespace Scene
}// namespace Game