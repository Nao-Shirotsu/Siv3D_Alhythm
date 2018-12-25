#include "Game_Util_TimeDuration.h"

Game::Util::TimeDuration::TimeDuration():
	start( std::chrono::system_clock::now() ){}

void Game::Util::TimeDuration::Start() noexcept{
	start = std::chrono::system_clock::now();
}

int Game::Util::TimeDuration::MilliDur() const noexcept{
	using namespace std::chrono;
	return static_cast<int>( duration_cast<milliseconds>( system_clock::now() - start ).count() );
}
