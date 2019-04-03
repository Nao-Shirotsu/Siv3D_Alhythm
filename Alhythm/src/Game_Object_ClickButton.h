#pragma once

#define NO_S3D_USING

#include <Siv3D.hpp>

#include "Game_Singleton_ClickSound.h"

namespace Game{
namespace Object{

// 長方形の上にテキストが描かれていて、クリックできるオブジェクト
class ClickButton{
public:
	// 何もしない
	ClickButton();

	// クリックボックス生成(枠のpixel幅と色 指定)
	ClickButton( int x_, int y_, const s3d::wchar* text_, const int fontsize, const int frameWidth_, s3d::Color rectColor_, s3d::Color frameColor_ );

	// クリックボックス生成(デフォルト)
	ClickButton( int x_, int y_, const s3d::wchar* text_, const int fontsize );

	// クリックボックス生成(枠pixel幅 指定)
	ClickButton( int x_, int y_, const s3d::wchar* text_, const int fontsize, const int frameWidth_ );

	// クリックボックス生成(色 指定)
	ClickButton( int x_, int y_, const s3d::wchar* text_, const int fontsize, s3d::Color rectColor_, s3d::Color frameColor_ );

	// 横幅が固定なクリックボックス生成(矩形の横幅, 枠のpixel幅, 色 指定)
	ClickButton( int x_, int y_, const s3d::wchar* text_, const int fontsize, const int rectWidth, const int frameWidth_, s3d::Color rectColor_, s3d::Color frameColor_ );

	// 横幅が固定なクリックボックス生成(矩形の横幅, 枠pixel幅 指定)
	ClickButton( int x_, int y_, const s3d::wchar* text_, const int fontsize, const int rectWidth, const int frameWidth_ );

	void Draw() const;

	// クリック検知
	bool WasClicked() const;

private:
	// マウスオーバーで色変わるか否か
	bool colorChangeable;

	// ボックスの左上座標
	int x, y;

	// ボックスの矩形
	s3d::Rect rect;

	// ボックスの背景色
	s3d::Color rectColor;

	// ボックスの枠の太さ
	int frameWidth;
	
	// ボックスの枠の色
	s3d::Color frameColor;

	// 表示するテキスト
	s3d::Font text;
	const s3d::wchar* textStr;

	// サウンドオブジェクト
	Singleton::ClickSound clickSound;
};

}// namespace Object
}// namespace Game