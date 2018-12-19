#include <memory>

#include <Siv3D.hpp>

#include "Game_Core.h"
#include "Game_Scene_Title.h"

namespace Game{

Core::Core():
	background( L"Resource/Title_resized.jpg" ){

	sceneStack.push( std::make_unique<Scene::Title>() );
	Window::SetTitle( L"Alhythm" );
	Window::Resize( 1280, 800 );
}

Core::~Core(){}

bool Core::IsGameEnd() const{
	 // Siv3Dの更新時にエラーがあったらfalseが返るためここで実行
	return System::Update();
}

void Core::Update(){
	if( sceneStack.top()->NeedsTransition() ){
		auto&& nextScene = sceneStack.top()->TransitionToNext();
		if( nextScene ){
			sceneStack.push( std::move( nextScene ) );
		}
		else{
			sceneStack.pop();
		}
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