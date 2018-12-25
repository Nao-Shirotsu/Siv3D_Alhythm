#pragma once

#include <chrono>

namespace Game{
namespace Util{

// 時間計測クラス(ストップウォッチ)
class TimeDuration{
public:
	TimeDuration();

	// 計測開始
	// もし計測中であってもそれをabortして新たに計測する
	void Start() noexcept;

	// 計測開始時からのミリ秒単位のdurationを得る 停止はしない
	int MilliDur() const noexcept;

private:
	std::chrono::system_clock::time_point start;
};

}// namespace Util
}// namespace Game