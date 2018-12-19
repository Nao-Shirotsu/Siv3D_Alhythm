#pragma once

#include <memory>

namespace Game{
namespace Scene{

// 全てのSceneクラスの基底クラス
class Base{
public:
	~Base();

	// メンバ変数等の状態のアップデート
	virtual void Update() = 0;

	// 画面へ描画する
	virtual void Draw() const = 0;

	// シーン遷移を行なうかどうか
	virtual bool NeedsTransition() = 0;

	// シーン遷移関数
	// 次のシーンの実体を生成して返すか、nullptrを返す
	// (nullptrが返されるのは、前のシーンへ戻る時)
	virtual std::unique_ptr<Base> TransitionToNext() = 0;
};

}// namespace Scene
}// namespace Game