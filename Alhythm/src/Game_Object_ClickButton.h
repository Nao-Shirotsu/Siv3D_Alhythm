#pragma once
#pragma once

#include <Siv3D.hpp>

namespace Game{
namespace Object{

// 長方形の上にテキストが描かれていて、クリックできるオブジェクト
class ClickButton{
public:
	// 何もしない
	ClickButton();

	// デフォルト色のクリックボックスを生成する
	ClickButton( int x_, int y_, const wchar* text_, const int fontsize );

	void Draw() const;

	// クリック検知
	bool WasClicked() const;

private:
	int x, y;
	Rect rect;
	Color colorRect;
	Rect rectShade;
	Color colorShade;
	Font text;
	const wchar* textStr;
};

}// namespace Object
}// namespace Game