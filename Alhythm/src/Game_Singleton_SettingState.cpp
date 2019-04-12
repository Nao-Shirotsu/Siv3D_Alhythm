#include <exception>

#include "Game_Singleton_SettingState.h"

namespace Game{
namespace Singleton{

// staticメンバ実体化
double SettingState::hispeedRate;
s3d::INIReader SettingState::ini;

SettingState::SettingState(){
	if( !ini ){
		Init();
	}
}

SettingState::~SettingState(){}

void SettingState::WriteHispeedRate( const double rate ){
	hispeedRate = rate;
	s3d::INIWriter iniWriter( L"./Engine/SystemData.ini" );
	iniWriter.write( L"Hispeed", L"rate", hispeedRate );
	iniWriter.close();
}

double Game::Singleton::SettingState::HispeedRate() const{
	return hispeedRate;
}


void SettingState::Init(){
	ini = s3d::INIReader( L"./Engine/SystemData.ini" );
	if( !ini ){
		throw std::runtime_error( "[Game::Singleton::SettingState::Init()] setting file read error" );
	}
	hispeedRate = ini.getOr<double>( L"Hispeed.rate", 1.0 );
}

}// namespace Singleton
}// namespace Game