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

	// デバッグ用ボタンと文字列
	Game::Object::ClickButton button;
	Game::Object::ClickButton playMusic;
	s3d::Font text;
	s3d::String str;

	// 音声ファイルオブジェクト musicBeganで再生済か否か判定する
	std::shared_ptr<Game::Object::Track> track;
	bool musicBegan;

	// レーン
	Game::Object::Lane lanes;
};

}// namespace Scene
}// namespace Game