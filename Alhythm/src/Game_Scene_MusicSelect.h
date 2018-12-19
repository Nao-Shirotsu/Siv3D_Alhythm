#pragma once

#include <Siv3D.hpp>

#include "Game_Scene_Base.h"

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
};

}// namespace Scene
}// namespace Game#pragma once
