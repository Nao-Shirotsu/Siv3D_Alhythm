#include "Game_Object_NoteSound.h"
#include "Game_Util_Functions.h"
#include "Game_FileID.h"

Game::Object::NoteSound::NoteSound():
	goodfineSound( Util::EmbeddedFilePath( Game::SEBGMFileID::NoteTapSound ) ),
	justSound( Util::EmbeddedFilePath( Game::SEBGMFileID::NoteTapSoundJust ) ),
	missSound( Util::EmbeddedFilePath( Game::SEBGMFileID::NoteTapSoundMiss ) ){
}

Game::Object::NoteSound::~NoteSound(){}

void Game::Object::NoteSound::Play( NoteJudge judge ) const{
	switch( judge ){
	case NoteJudge::Just:
		justSound.playMulti();
		break;

	case NoteJudge::Miss:
		missSound.playMulti();
		break;

	default:
		goodfineSound.playMulti();
		break;
	}
}
