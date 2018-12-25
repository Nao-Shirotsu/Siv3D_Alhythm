#pragma once

#define NO_S3D_USING

#include <Siv3D.hpp>

namespace Game{
namespace Object{

// 長方形の上にテキストが描かれていて、クリックできるオブジェクト
class ClickButton{
public:
	// 何もしない
	ClickButton();

	// デフォルト色のクリックボックスを生成する
	ClickButton( int x_, int y_, const s3d::wchar* text_, const int fontsize );

	void Draw() const;

	// クリック検知
	bool WasClicked() const;

private:
	int x, y;
	s3d::Rect rect;
	s3d::Color colorRect;
	s3d::Rect rectShade;
	s3d::Font text;
	const s3d::wchar* textStr;
	const s3d::Sound decideSound;
};

}// namespace Object
}// namespace Game