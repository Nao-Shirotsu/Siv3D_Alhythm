#pragma once

#define NO_S3D_USING

#include <memory>

#include <Siv3D.hpp>

#include "Game_Object_Track.h"
#include "Game_Singleton_SettingState.h"

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

	// 色々とトラックの情報を使うためDIで得て格納
	std::shared_ptr<Track> track;

	// 実体の位置(高さ)
	int posY;

	// 表示する実体
	s3d::Line lineL;
	s3d::Line lineR;

	// 小節番号
	s3d::Font barNumFont;
	s3d::String barNumStr;

	// ハイスピなどの設定の値を取得するために持つ
	Singleton::SettingState settingState;

	// ハイスピ倍率 x NOTE_INDICATE_TIME
	double noteIndicateTime;
};

}// namespace Object
}// namespace Game