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
	s3d::Font text;
	s3d::String str;

	// 音声ファイルオブジェクト
	std::shared_ptr<Game::Object::Track> track;
	bool musicBegan;

	// レーン
	std::unordered_map<Game::Object::LaneID, Game::Object::Lane> lanes;

	//test
	static s3d::Sound test;
};

}// namespace Scene
}// namespace Game