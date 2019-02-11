#pragma once

#define NO_S3D_USING

#include <Siv3D.hpp>

#include "Game_Scene_Base.h"
#include "Game_Object_ClickButton.h"

namespace Game{
namespace Scene{

// シーン：タイトル画面
class Credit: public Base{
public:
	Credit();
	~Credit();

	void Update() override;
	void Draw() const override;
	bool NeedsTransition() override;
	std::unique_ptr<Base> TransitionToNext() override;

private:
	// タイトルに戻るボタン
	Game::Object::ClickButton returnToTitle;

	s3d::Font bgmseText;
	s3d::Font bgmseNameText;
	s3d::Font composerText;
	s3d::Font composerNameText;
};

}// namespace Scene
}// namespace Game