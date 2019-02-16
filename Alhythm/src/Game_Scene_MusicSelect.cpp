﻿#include <memory>

#include "Game_Scene_MusicSelect.h"
#include "Game_Scene_Settings.h"
#include "Game_Scene_Gameplay.h"
#include "Game_Util_Functions.h"

namespace Game{
namespace Scene{

//cassiはたぶん89小節
//senkouはたぶん134小節

MusicSelect::MusicSelect():
	returnToTitle( 1050, 700, L"タイトルへ戻る", 20 ),
	goToSettings( 50, 700, L"ゲームプレイ設定", 20 ),
	goToSenkou( 650, 200, L"閃光の足跡          ", 40 ), // 長さ自動調節したいね
	bgm( Util::EmbeddedFilePath( SEBGMFileID::MusicSelectBGM ) ),
	isMusicPlaying( true ),
	nextSceneID( SceneID::Gameplay ){
	if( !bgm ){
		throw std::runtime_error( "sound file read error" );
	}
	bgm.setLoop( true );
	bgm.play();
}

MusicSelect::~MusicSelect(){}

void MusicSelect::Update(){
	if( !isMusicPlaying ){
		bgm.play();
	}
}

void MusicSelect::Draw() const{
	returnToTitle.Draw();
	goToSettings.Draw();
	goToSenkou.Draw();
}

bool MusicSelect::NeedsTransition(){
	if( goToSettings.WasClicked() ){
		nextSceneID = SceneID::Settings;
		return true;
	}

	if( goToSenkou.WasClicked() ){
		nextSceneID = SceneID::Gameplay;
		trackID = TrackFileID::Senkou;
		trackBPM = 210;
		trackMaxBar = 134;
		return true;
	}
	if( returnToTitle.WasClicked() ){
		nextSceneID = SceneID::Title;
		return true;
	}

	return false;
}

std::unique_ptr<Base> MusicSelect::TransitionToNext(){
	switch( nextSceneID ){
	case SceneID::Settings:
		return std::make_unique<Settings>();

	case SceneID::Gameplay:
		bgm.stop();
		isMusicPlaying = false;
		return std::make_unique<Gameplay>( trackID, trackBPM, trackMaxBar );

	default: // ここエラーハンドリングした方がいい
		bgm.stop();
		return nullptr;
	}
}

}// namespace Scene
}// namespace Game