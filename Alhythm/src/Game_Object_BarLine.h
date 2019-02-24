﻿#pragma once
#pragma once

#define NO_S3D_USING

#include <memory>

#include <Siv3D.hpp>

#include "Game_Object_Track.h"

namespace Game{
namespace Object{

// 音ゲープレイ画面のレーンに流れる小節線
class BarLine{
public:
	explicit BarLine( int barNum, const std::shared_ptr<Track>& track_ );

	// 何もしない STLコンテナのため用意
	BarLine();
	~BarLine();

	void Update();
	void Draw() const;

	// レーンに表示される期間内か否か返す
	bool IsValidToIndicate() const;

private:
	// 判定ラインと重なる瞬間
	double secOnMusic;

	// 表示時間の計算に利用
	double timeDiff;

	// 表示する実体
	s3d::Line lineL;
	s3d::Line lineR;

	// 色々とトラックの情報を使うためDIで得て格納
	std::shared_ptr<Track> track;
};

}// namespace Object
}// namespace Game