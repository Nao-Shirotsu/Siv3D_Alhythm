#pragma once
#define NO_S3D_USING

#include <memory>
#include <stack>

#include <Siv3D.hpp>

#include "Game_Scene_Base.h"

namespace Game{

// ゲームコア シーンなどのインスタンスを所有して管理
class Core{
public:
	Core();
	~Core();

	// trueならウィンドウを閉じてゲーム終了
	bool IsGameEnd() const;

	// 毎フレーム必要な処理
	void Update();

	// 毎フレーム ゲームを画面に描画
	void Draw() const;

	// Coreインスタンスは複数存在しないほうがよいため、使用しない
	Core( const Core& core ) = delete;
	Core& operator=( const Core& core ) = delete;
	Core( const Core&& core ) = delete;
	Core& operator=( const Core&& core ) = delete;

private:
	// sceneStackに積まれているすべてのリソースを解放
	void DestructAllSceneObjects();

	std::stack<std::unique_ptr<Game::Scene::Base>> sceneStack;

	// 常に表示する背景画像 1280x800 の 16:10
	s3d::Texture background;
};

}// namespace Game