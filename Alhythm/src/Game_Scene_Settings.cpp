#include <memory>

#include "Game_Scene_Settings.h"

namespace Game{
namespace Scene{

Settings::Settings():
	returnToSelect( 50, 700, L"‚à‚Ç‚é", 20 ){}

Settings::~Settings(){}

void Settings::Update(){}

void Settings::Draw() const{
	returnToSelect.Draw();
}

bool Settings::NeedsTransition(){
	return returnToSelect.WasClicked();
}

std::unique_ptr<Base> Settings::TransitionToNext(){
	return nullptr;
}

}// namespace Scene
}// namespace Game