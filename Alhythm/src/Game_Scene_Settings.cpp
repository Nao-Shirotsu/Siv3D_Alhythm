#include <memory>

#include "Game_Scene_Settings.h"

namespace Game{
namespace Scene{

Settings::Settings():
	gui( s3d::GUIStyle::Default ),
	returnToSelect( 50, 700, L"もどる", 20 ),
	settingState(){
	gui.setTitle( L"ハイスピード設定" );
	gui.addln( L"hispeedRate", s3d::GUIText::Create( L"" ) );
	gui.add( L"hispeed", s3d::GUISlider::Create( 0.5, 5.0, settingState.HispeedRate() , 400 ) );
	gui.setPos( { 50, 150 } );
}

Settings::~Settings(){}

void Settings::Update(){
	settingState.WriteHispeedRate( gui.slider( L"hispeed" ).value );
	gui.text( L"hispeedRate" ).text = L"x" + s3d::Format( settingState.HispeedRate() );
}

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