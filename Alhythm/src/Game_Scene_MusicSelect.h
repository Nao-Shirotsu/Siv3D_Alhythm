#pragma once

#define NO_S3D_USING

#include <Siv3D.hpp>

#include "Game_Scene_Base.h"
#include "Game_Object_ClickButton.h"
#include "Game_FileID.h"
#include "Game_SceneID.h"

namespace Game{
namespace Scene{

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
	Game::Object::ClickButton goToSenkou;
	Game::Object::ClickButton senkouMedium;

	Game::Object::ClickButton goToCassi;
	Game::Object::ClickButton cassiExtreme;

	Game::Object::ClickButton goToOrion;
	Game::Object::ClickButton orionEasy;

	// 音声ファイルオブジェクト
	const s3d::Sound bgm;
	bool isMusicPlaying;

	// 次のシーンが何のシーンか判定
	SceneID nextSceneID;

	// 左上に表示するMusicSelectの文字
	s3d::Font musicSelectText;

	// プレイしたい楽曲の情報
	TrackFileID trackID;
	int trackBPM;
	int trackMaxBar; // 一番最後の小説番号
};

}// namespace Scene
}// namespace Game
