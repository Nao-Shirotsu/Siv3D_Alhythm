#pragma once

#define NO_S3D_USING

#include <memory>

#include <Siv3D.hpp>

#include "Game_Object_Track.h"
#include "Game_Object_Enum.h"

namespace Game{
namespace Object{

// 音ゲープレイ画面で使うノーツオブジェクトの構造体
class Note{
public:
	explicit Note( int barNum_, int beatNum_, LaneID lane_, const std::shared_ptr<Track>& track_ );

	// 何もしない STLコンテナのため用意
	Note();
	~Note();

	void Update();
	void Draw();

	// ノーツが流れたならtrue
	bool Passed();

private:
	// このノートが曲中で有効になる秒数(位置)
	double secOnMusic;

	// 色々とトラックの情報を使うためDIで得て格納
	std::shared_ptr<Track> track;

	// 本当はLaneIDのままがよいが、そうすると何度もキャストする必要があるためs3d::wchar
	s3d::wchar lane;

	// このノートがレーンを流れ切った後ならtrue
	bool passed;

	// 打鍵音
	s3d::Sound tapSound;
};

}
}