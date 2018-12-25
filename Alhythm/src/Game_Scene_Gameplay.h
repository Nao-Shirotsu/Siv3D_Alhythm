#pragma once

#define NO_S3D_USING

#include <memory>
#include <unordered_map>

#include <Siv3D.hpp>

#include "Game_Scene_Base.h"
#include "Game_Object_ClickButton.h"
#include "Game_Object_Track.h"
#include "Game_Object_UI.h"

namespace Game{
namespace Scene{

// シーン：楽曲プレイ画面
class Gameplay: public Base{
public:
	Gameplay( const s3d::String& trackName_, int bpm, int maxBar );

	Gameplay();
	~Gameplay();

	void Update() override;
	void Draw() const override;
	bool NeedsTransition() override;
	std::unique_ptr<Base> TransitionToNext() override;

private:
	// 戻るボタン
	Game::Object::ClickButton returnToSelect;

	// デバッグ用ボタン
	Game::Object::ClickButton playMusic;

	// 楽曲情報と曲名の一部
	std::shared_ptr<Game::Object::Track> track;
	s3d::String trackName;

	// 音声ファイルオブジェクト musicBeganで再生済か否か判定する
	bool musicBegan;

	// レーン
	Game::Object::UI ui;
};

}// namespace Scene
}// namespace Game