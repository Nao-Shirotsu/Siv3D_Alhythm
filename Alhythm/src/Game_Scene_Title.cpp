#include <memory>
#include <exception>

#include "Game_Scene_Title.h"
#include "Game_Scene_MusicSelect.h"

namespace Game{
namespace Scene{

Title::Title():
	gamestart( 765, 600, L"Game Start", 60 ),
	gameend( 50, 700, L"ゲーム終了", 20 ),
	titleStr( L"Resource/Title_string.png" ),
	bgm( L"Resource/bgm_title.mp3" ),
	isMusicPlaying( true ){
	if( !bgm ){
		throw std::runtime_error( "[Scene::Title] sound file read error" );
	}
	bgm.setLoop( true );
	bgm.play();
}

Title::~Title(){}

void Title::Update(){
	if( !isMusicPlaying ){
		bgm.play();
	}
	if( gameend.WasClicked() ){
		s3d::System::Exit();
	}
}

void Title::Draw() const{
	titleStr.draw( 20, 20 );
	gamestart.Draw();
	gameend.Draw();
}

bool Title::NeedsTransition(){
	return gamestart.WasClicked();
}

std::unique_ptr<Base> Title::TransitionToNext(){
	bgm.stop();
	isMusicPlaying = false;
	return std::make_unique<MusicSelect>();
}

}// namespace Scene
}// namespace Game