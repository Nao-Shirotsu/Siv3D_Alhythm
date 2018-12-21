#pragma once

#define NO_S3D_USING

#include <Siv3D.hpp>

namespace Game{
namespace Object{

// 音ゲープレイ画面で使う曲オブジェクト
// 小節数や拍数などを保持して処理する
class Track{
public:
	explicit Track( s3d::wchar* filename, int bpm, int maxBar_ ) noexcept(false);

	// 何もしない STLコンテナのため用意
	Track();
	~Track();

	// 小節数、拍数を受け取り秒数を返す
	double SecOnBarBeat( int bar, int beat ) const noexcept;

	// 再生中の曲の現在の秒数を返す
	double SecCur() const noexcept;

	// サウンド再生/停止
	void Play();
	void Stop();

private:
	/*
	秒数でのノーツ判定につき、intだと大量にキャストすることになるため、初めからdoubleで保持して処理を軽くする。
	このクラスのインスタンスの個数は非常に少なくなるはずなので、メモリリソースはdoubleでも問題にならない。
	*/
	double beatSec; // 1拍で経過する秒数 = 60/BPM
	double curBar;  // 現在の小節数 1-origin
	double curBaet; // 現在の小節内の拍数 1-origin 32分音符で表現 5/32など
	s3d::Sound file;
	int maxBar; // このトラックの最終小節番号
};

}
}