#include <exception>

#include "Game_Singleton_ClickSound.h"
#include "Game_Util_Functions.h"

namespace Game{
namespace Singleton{

// staticメンバ実体化
s3d::Sound ClickSound::sound;

ClickSound::ClickSound() = default;

ClickSound::~ClickSound() = default;

void ClickSound::Init(){
	sound = s3d::Sound( Util::EmbeddedFilePath( SEBGMFileID::DecideSound ) );
	if( !sound ){
		throw std::runtime_error( "[Game::Singleton::ClickSound::ClickSound()] sound file read error" );
	}
}

void ClickSound::Play() const{
	if( !sound ){
		Init();
	}
	sound.play();
}

}// namespace Singleton
}// namespace Game
