#pragma once

#include <Siv3D.hpp>

#include "Game_Scene_Base.h"
#include "Game_Object_ClickButton.h"

namespace Game{
namespace Scene{

// シーン：タイトル画面
class Title: public Base{
public:
	Title();
	~Title();

	void Update() override;
	void Draw() const override;
	bool NeedsTransition() override;
	std::unique_ptr<Base> TransitionToNext() override;

private:
	// タイトル文字の画像
	Texture titleStr;

	// ゲーム開始ボタンっぽいの
	Game::Object::ClickButton gamestart;
};

}// namespace Scene
}// namespace Game