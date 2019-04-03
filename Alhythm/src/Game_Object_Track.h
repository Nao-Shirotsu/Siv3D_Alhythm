#pragma once
#pragma once

#define NO_S3D_USING

#include <Siv3D.hpp>

#include "Game_FileID.h"

namespace Game{
namespace Object{

// 音ゲープレイ画面で使う曲オブジェクト
// 小節数や拍数などを保持して処理する
class Track{
public:
	explicit Track( const TrackFileID trackID_, int bpm, int maxBar_ ) noexcept(false);

	// 何もしない STLコンテナのため用意
	Track();
	~Track();

	// 小節数と拍数を受け取り、トラック中での秒数を返す
	double SecOnBarBeat( int bar, int beat ) const noexcept;

	// 再生中の曲の現在の秒数を返す
	double CurSec() const noexcept;

	// 楽曲再生
	void Play();

	// 無音で再生
	void PlayZeroSound();

	// 曲が終わったかどうか
	bool IsEnd();

	const TrackFileID trackID;

private:
	double beatSec; // 1拍で経過する秒数 = 60/BPM  (小数点な秒数でのノーツ判定につき多量キャスト防止のためdoubleで保持)
	s3d::Sound file; // 楽曲
	int maxBar; // このトラックの最終小節番号
};

}
}