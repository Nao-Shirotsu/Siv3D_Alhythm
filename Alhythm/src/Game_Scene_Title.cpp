#include <memory>
#include <exception>

#include "Game_Scene_Title.h"
#include "Game_Scene_MusicSelect.h"
#include "Game_Scene_Credit.h"
#include "Game_Util_Functions.h"

namespace Game{
namespace Scene{

Title::Title():
	gamestart( 855, 650, L"Game Start", 45 ),
	gameend( 50, 700, L"ゲーム終了", 20 ),
	goToCredit( 300, 700, L"クレジット", 20 ),
	titleStr( Util::EmbeddedFilePath( ImageFileID::TitleStringImage ) ),
	bgm( Util::EmbeddedFilePath( SEBGMFileID::TitleBGM ) ),
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
	titleStr.draw( 70, 70 );
	gamestart.Draw();
	gameend.Draw();
	goToCredit.Draw();
}

bool Title::NeedsTransition(){
	if( goToCredit.WasClicked() ){
		nextSceneID = SceneID::Credit;
		return true;
	}

	if( gamestart.WasClicked() ){
		nextSceneID = SceneID::MusicSelect;
		return true;
	}

	return false;
}

std::unique_ptr<Base> Title::TransitionToNext(){
	switch( nextSceneID ){
	case SceneID::Credit:
		return std::make_unique<Credit>();

	case SceneID::MusicSelect:
		bgm.stop();
		isMusicPlaying = false;
		return std::make_unique<MusicSelect>();

	default: // ここエラーハンドリングした方がいい
		bgm.stop();
		return nullptr;
	}
}

}// namespace Scene
}// namespace Game