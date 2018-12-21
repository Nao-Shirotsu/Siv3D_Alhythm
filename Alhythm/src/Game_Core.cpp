#define NO_S3D_USING

#include <memory>

#include <Siv3D.hpp>

#include "Game_Core.h"
#include "Game_Scene_Title.h"

namespace Game{

Core::Core():
	background( L"Resource/Title_resized.jpg" ),
	testout( 20 ){

	sceneStack.push( std::make_unique<Scene::Title>() );
	s3d::Window::SetTitle( L"Alhythm" );
	s3d::Window::Resize( 1280, 800 );
}

Core::~Core(){}

bool Core::IsGameEnd() const{
	 // Siv3Dの更新時にエラーがあったらfalseが返るためここで実行
	return s3d::System::Update();
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
	testout( s3d::Format( sceneStack.size() ) ).draw();
}

void Core::DestructAllSceneObjects(){
	while( !sceneStack.empty() ){
		sceneStack.pop();
	}
}
	
}// namespace Game