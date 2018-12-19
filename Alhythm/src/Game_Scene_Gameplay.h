#pragma once

#define NO_S3D_USING

#include <Siv3D.hpp>

#include "Game_Scene_Base.h"
#include "Game_Object_ClickButton.h"

namespace Game{
namespace Scene{

// シーン：楽曲プレイ画面
class Gameplay: public Base{
public:
	Gameplay();
	~Gameplay();

	void Update() override;
	void Draw() const override;
	bool NeedsTransition() override;
	std::unique_ptr<Base> TransitionToNext() override;

private:
	// 戻るボタン
	Game::Object::ClickButton returnToSelect;

	// 音声ファイルオブジェクト
	const s3d::Sound track;
	bool musicBegan;
};

}// namespace Scene
}// namespace Game