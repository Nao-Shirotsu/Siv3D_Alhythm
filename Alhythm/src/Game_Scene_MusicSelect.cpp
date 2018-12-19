#include <memory>

#include "Game_Scene_MusicSelect.h"

namespace Game{
namespace Scene{

MusicSelect::MusicSelect(){}

MusicSelect::~MusicSelect(){}

void MusicSelect::Update(){}

void MusicSelect::Draw() const{}

bool MusicSelect::NeedsTransition(){
	return false;
}

std::unique_ptr<Base> MusicSelect::TransitionToNext(){
	return nullptr;
}

}// namespace Scene
}// namespace Game