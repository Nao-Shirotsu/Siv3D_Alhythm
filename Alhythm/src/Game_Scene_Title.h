#pragma once

#define NO_S3D_USING

#include <Siv3D.hpp>

#include "Game_Scene_Base.h"
#include "Game_Object_ClickButton.h"
#include "Game_SceneID.h"

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
	s3d::Texture titleStr;

	// ゲーム開始ボタンっぽいの
	Game::Object::ClickButton gamestart;
	Game::Object::ClickButton gameend;

	// クレジット表記
	Game::Object::ClickButton goToCredit;

	// 音声ファイルオブジェクト
	const s3d::Sound bgm;
	bool isMusicPlaying;

	// 次のシーンが何のシーンか判定
	SceneID nextSceneID;
};

}// namespace Scene
}// namespace Game