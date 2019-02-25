#include <exception>

#include "Game_Singleton_SettingState.h"

namespace Game{
namespace Singleton{

// staticメンバ実体化
double SettingState::hispeedRate;
s3d::INIReader SettingState::ini;

SettingState::SettingState() = default;

SettingState::~SettingState(){
	s3d::INIWriter iniWriter( L"/1500" );
	iniWriter.write( L"Hispeed", L"rate", hispeedRate );
}

void SettingState::WriteHispeedRate( const double rate ){
	hispeedRate = rate;
}

double Game::Singleton::SettingState::HispeedRate() const{
	if( !ini ){
		Init();
	}
	return hispeedRate;
}


void SettingState::Init(){
	ini = s3d::INIReader( L"/1500" );
	if( !ini ){
		throw std::runtime_error( "[Game::Singleton::SettingState::Init()] setting file read error" );
	}
	hispeedRate = ini.get<double>( L"Hispeed.rate" );
}

}// namespace Singleton
}// namespace Game