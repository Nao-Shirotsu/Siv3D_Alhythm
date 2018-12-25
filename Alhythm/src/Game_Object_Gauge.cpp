#include "Game_Object_Gauge.h"

namespace{

// 増減ゲージの左上座標の初期位置
constexpr int POS_X{ 394 };
constexpr int POS_Y{ 105 };

// 増減ゲージの幅と最大の高さ
constexpr int WIDTH{ 45 };
constexpr int MAX_HEIGHT{ 590 };

// ゲージ枠の枠の色と背景色
constexpr s3d::Color FRAME_COLOR{ s3d::Palette::Black };
constexpr s3d::Color FRAME_BG_COLOR{ 50, 50, 50, 192 };

// 増減ゲージがクリアパーセント未満と以上の時の色
constexpr s3d::Color UNDER_COLOR{ 64, 128, 64 };
constexpr s3d::Color OVER_COLOR{ 156, 40, 96 };

}

Game::Object::Gauge::Gauge():
	height( 0 ),
	posY( POS_Y + MAX_HEIGHT ),
	persentage( 0.0 ),
	persentText( 25 ),
	persentStr( L"" ),
	clearLine( POS_X, POS_Y + MAX_HEIGHT * 0.31, POS_X + WIDTH, POS_Y + MAX_HEIGHT * 0.31 ),
	backGaugeRect( POS_X - 5, POS_Y - 5, 55, 600, 35 ),
	frontGaugeRect( POS_X, POS_Y + MAX_HEIGHT, WIDTH, 0, 5 ),
	frontColor( UNDER_COLOR ){}

void Game::Object::Gauge::Update( double persentDiff ){
	// ゲージ値更新=============
	persentage += persentDiff;
	if( persentage > 100.0 ){
		persentage = 100.0;
	}
	else if( persentage < 0.0 ){
		persentage = 0;
	}

	if( IsOverClearPersent() ){
		frontColor = OVER_COLOR;
	}
	else{
		frontColor = UNDER_COLOR;
	}
	persentStr = s3d::Format( static_cast<int>( persentage ), L"%" );
	// ========================

	// ゲージ位置更新============
	height = static_cast<int>( MAX_HEIGHT * persentage / 100.0 );
	posY = MAX_HEIGHT + POS_Y - height;
	frontGaugeRect.set( POS_X, posY, WIDTH, height, 10 );
	// ========================
}

void Game::Object::Gauge::Draw() const{
	backGaugeRect.draw( FRAME_BG_COLOR );
	frontGaugeRect.draw( frontColor );
	backGaugeRect.drawFrame( 5, 0, FRAME_COLOR );
	persentText( persentStr ).drawCenter( POS_X + 22, posY - 18 );
	clearLine.draw();
}

bool Game::Object::Gauge::IsOverClearPersent() const noexcept{
	return persentage >= 70.0;
}
