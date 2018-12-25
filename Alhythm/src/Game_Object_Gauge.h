#pragma once

#define NO_S3D_USING

#include <Siv3D.hpp>

namespace Game{
namespace Object{

// ゲームプレイ画面のクリアゲージ(縦棒)
class Gauge{
public:
	Gauge();

	// パーセンテージを加減算
	void Update( double persentDiff );
	void Draw() const;

	// ゲージがクリアライン(70%)以上か
	bool IsOverClearPersent() const noexcept;

private:
	// 増減するゲージの高さと位置
	int height;
	int posY;

	// 現在のクリアゲージの値(0.0~100.0)
	double persentage;

	// クリアゲージの値の表示
	s3d::Font persentText;
	s3d::String persentStr;

	// クリアゲージの70%ライン
	s3d::Line clearLine;

	// ゲージ本体の表示 枠(不変)と増減する方
	s3d::RoundRect backGaugeRect;
	s3d::RoundRect frontGaugeRect;

	// 増減ゲージの色
	s3d::Color frontColor;
};

}// namespace Object
}// namespace Game