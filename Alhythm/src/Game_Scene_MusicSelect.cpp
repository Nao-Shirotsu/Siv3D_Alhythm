﻿#include <memory>

#include "Game_Scene_MusicSelect.h"
#include "Game_Scene_Settings.h"
#include "Game_Scene_Gameplay.h"
#include "Game_Util_Functions.h"

namespace{

constexpr s3d::Color EASY_BG_COLOR{ 160, 200, 60 };
constexpr s3d::Color EASY_FRAME_COLOR{ 130, 160, 50 };

constexpr s3d::Color MEDIUM_BG_COLOR{ 200, 120, 50 };
constexpr s3d::Color MEDIUM_FRAME_COLOR{ 160, 160, 0 };

constexpr s3d::Color EXTREME_BG_COLOR{ 185, 30, 40 };
constexpr s3d::Color EXTREME_FRAME_COLOR{ 150, 20, 35 };

}

namespace Game{
namespace Scene{

//cassiはたぶん89小節
//senkouはたぶん134小節

MusicSelect::MusicSelect():
	returnToTitle( 1050, 700, L"タイトルへ戻る", 20 ),
	goToSettings( 50, 700, L"ハイスピード設定", 20 ),
	goToSenkou( 650, 200, L"閃光の足跡", 40, 550, 3 ),
	senkouMedium( 1000, 250, L"Medium", 25, 190, 2, MEDIUM_BG_COLOR, MEDIUM_FRAME_COLOR ),
	goToCassi( 650, 330, L"Cassiopeia", 40, 550, 3 ),
	cassiExtreme( 1000, 380, L"Extreme", 25, 190, 2, EXTREME_BG_COLOR, EXTREME_FRAME_COLOR ),
	goToOrion( 650, 460, L"Orion", 40, 550, 3 ),
	orionEasy( 1000, 510, L"Easy", 25, 190, 2, EASY_BG_COLOR, EASY_FRAME_COLOR ),
	bgm( Util::EmbeddedFilePath( SEBGMFileID::MusicSelectBGM ) ),
	isMusicPlaying( true ),
	nextSceneID( SceneID::Gameplay ),
	musicSelectText( 55, s3d::Typeface::Medium, s3d::FontStyle::Outline ){
	using namespace s3d;
	if( !bgm ){
		throw std::runtime_error( "sound file read error" );
	}
	bgm.setLoop( true );
	bgm.play();
	musicSelectText.changeOutlineStyle( TextOutlineStyle( TextOutlineStyle( { 60, 60, 120 }, { 50, 50, 75 }, 2.0 ) ) );
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
	goToCassi.Draw();
	goToOrion.Draw();
	senkouMedium.Draw();
	cassiExtreme.Draw();
	orionEasy.Draw();
	musicSelectText( L"Music Select" ).draw( 60, 30 );
}

bool MusicSelect::NeedsTransition(){
	if( goToSettings.WasClicked() ){
		nextSceneID = SceneID::Settings;
		trackID = TrackFileID::CassiEmp;
		return true;
	}

	if( goToSenkou.WasClicked() ){
		nextSceneID = SceneID::Gameplay;
		trackID = TrackFileID::Senkou;
		trackBPM = 210;
		trackMaxBar = 134;
		return true;
	}

	if( goToCassi.WasClicked() ){
		nextSceneID = SceneID::Gameplay;
		trackID = TrackFileID::Cassi;
		trackBPM = 152;
		trackMaxBar = 86;
		return true;
	}

	if( goToOrion.WasClicked() ){
		nextSceneID = SceneID::Gameplay;
		trackID = TrackFileID::Orion;
		trackBPM = 120;
		trackMaxBar = 76;
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