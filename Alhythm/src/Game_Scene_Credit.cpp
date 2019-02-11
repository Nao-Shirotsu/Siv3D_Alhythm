#include <memory>
#include <exception>

#include "Game_Scene_Credit.h"
#include "Game_Scene_MusicSelect.h"
#include "Game_Util_Functions.h"

namespace Game{
namespace Scene{

Credit::Credit():
	returnToTitle( 50, 700, L"もどる", 20 ),
	bgmseText( 20 ),
	bgmseNameText( 20 ),
	composerText( 20 ),
	composerNameText( 20 ){}

Credit::~Credit(){}

void Credit::Update(){}

void Credit::Draw() const{
	returnToTitle.Draw();
	bgmseText( L"BGM&SE" ).draw( 500, 350 );
	bgmseNameText( L"魔王魂" ).draw( 500, 380 );
	composerText( L"楽曲提供" ).draw( 500, 440 );
	composerNameText( L"きぐまP,  れーじくん" ).draw( 500, 470 );
}

bool Credit::NeedsTransition(){
	if( returnToTitle.WasClicked() ){
		return true;
	}
	return false;
}

std::unique_ptr<Base> Credit::TransitionToNext(){
	return nullptr;
}

}// namespace Scene
}// namespace Game