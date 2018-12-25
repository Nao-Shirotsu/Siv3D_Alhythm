#pragma once

#define NO_S3D_USING

#include <memory>
#include <unordered_map>

#include <Siv3D.hpp>

#include "Game_Scene_Base.h"
#include "Game_Object_ClickButton.h"
#include "Game_Object_Track.h"
#include "Game_Object_UI.h"
#include "Game_Util_TimeDuration.h"

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

	// プレイ楽曲オブジェクト
	std::shared_ptr<Game::Object::Track> track;

	// 楽曲名表示用フォントとString
	s3d::Font trackNameText;
	s3d::String trackNameStr;
	bool musicPlaying;
	bool isReady;

	// 処理に使うストップウォッチ
	Game::Util::TimeDuration stopwatch;

	// UIとその内部処理
	Game::Object::UI ui;
};

}// namespace Scene
}// namespace Game