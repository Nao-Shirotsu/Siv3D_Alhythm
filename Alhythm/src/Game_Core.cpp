#define NO_S3D_USING

#include <memory>

#include <Siv3D.hpp>

#include "Game_Core.h"
#include "Game_Scene_Title.h"
#include "Game_BinFileID.h"
#include "Game_Util_Functions.h"

namespace Game{

Core::Core():
	background( Util::EmbededFilePath( BinFileID::BackgroundImage ) ){
	sceneStack.push( std::make_unique<Scene::Title>() );
	s3d::Window::SetTitle( L"Alhythm" );
	s3d::Window::Resize( 1280, 800 );
}

Core::~Core(){
	DestructAllSceneObjects();
}

bool Core::IsGameEnd() const{
	 // Siv3Dの更新時にエラーがあったらfalseが返るためここでUpdateを実行
	return s3d::System::Update();
}

void Core::Update(){
	if( sceneStack.top()->NeedsTransition() ){
		// auto&&ではなくautoで良いか？ 要検証
		auto&& nextScene = sceneStack.top()->TransitionToNext();
		if( nextScene ){
			sceneStack.push( std::move( nextScene ) );
		}
		else{
			sceneStack.pop();
		}
		return;
	}
	sceneStack.top()->Update();
}

void Core::Draw() const{
	background.draw( 0, 0 );
	sceneStack.top()->Draw();
}

void Core::DestructAllSceneObjects(){
	while( !sceneStack.empty() ){
		sceneStack.pop();
	}
}
	
}// namespace Game