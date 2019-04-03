#pragma once

#define NO_S3D_USING

#include <Siv3D.hpp>

namespace Game{
namespace Object{

// 右揃えフォント
class RightAlignedFont{
public:
	RightAlignedFont( int size, int posX_, int posY_ );

	RightAlignedFont();
	~RightAlignedFont();

	void Draw( const s3d::String& text ) const;

private:
	// 表示したい座標(フォントの右上頂点)
	int posX, posY;

	// フォント本体
	s3d::Font font;
};

}// namespace Object
}// namespace Game