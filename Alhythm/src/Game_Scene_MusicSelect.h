﻿#pragma once

#define NO_S3D_USING

#include <Siv3D.hpp>

#include "Game_Scene_Base.h"
#include "Game_Object_ClickButton.h"

namespace Game{
namespace Scene{

enum class SceneID{
	Title,
	Settings,
	Gameplay,
};

// シーン：楽曲選択画面
class MusicSelect: public Base{
public:
	MusicSelect();
	~MusicSelect();

	void Update() override;
	void Draw() const override;
	bool NeedsTransition() override;
	std::unique_ptr<Base> TransitionToNext() override;

private:
	// タイトルへもどるボタン
	Game::Object::ClickButton returnToTitle;

	// 設定画面へ遷移するボタン
	Game::Object::ClickButton goToSettings;

	// 楽曲プレイ画面に遷移するボタン 後々曲増えるから拡張しよう
	Game::Object::ClickButton goToGameplay;

	// 音声ファイルオブジェクト
	const s3d::Sound bgm;
	bool isMusicPlaying;

	// 次のシーンが何のシーンか判定
	SceneID nextSceneID;
};

}// namespace Scene
}// namespace Game#pragma once