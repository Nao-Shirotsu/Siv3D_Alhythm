#include "Game_Object_Gauge.h"

namespace{

// ゲージの角丸の半径
constexpr int GAUGE_EDGE_RADIUS{ 30 };

// ゲージの枠の幅
constexpr int FRAME_WIDTH{ 5 };

// 増減ゲージの左上座標の初期位置
constexpr int POS_X{ 394 };
constexpr int POS_Y{ 50 };

// 増減ゲージの幅と最大の高さ
constexpr int WIDTH{ 45 };
constexpr int MAX_HEIGHT{ 590 };

// クリアと判定するパーセント値
constexpr double CLEAR_PERSENT{ 0.7 };

// ゲージのクリアボーダーラインの高さ
constexpr int CLEAR_LINE_POS{ POS_Y + static_cast<int>( MAX_HEIGHT * ( 1.0 - CLEAR_PERSENT + 0.01 ) ) }; // 0.01はゲージの見た目のための補正

// ゲージ枠の枠の色と背景色
constexpr s3d::Color FRAME_COLOR{ s3d::Palette::Black };
constexpr s3d::Color FRAME_BG_COLOR{ 50, 50, 50, 192 };

// 増減ゲージがクリアパーセント未満と以上の時の色
constexpr s3d::Color UNDER_COLOR{ 0x38, 0x84, 0x7f };
constexpr s3d::Color OVER_COLOR{ 0x9c, 0x28, 0x60 };

}

Game::Object::Gauge::Gauge():
	height( 0 ),
	posY( POS_Y + MAX_HEIGHT ),
	persentage( 0.0 ),
	persentText( 25 ),
	persentStr( L"" ),
	clearLine( POS_X, CLEAR_LINE_POS, POS_X + WIDTH, CLEAR_LINE_POS ),
	backGaugeRect( POS_X - FRAME_WIDTH, POS_Y - FRAME_WIDTH, WIDTH + FRAME_WIDTH * 2, MAX_HEIGHT + FRAME_WIDTH * 2, GAUGE_EDGE_RADIUS ),
	frontGaugeRect( POS_X, POS_Y + MAX_HEIGHT, WIDTH, 0, GAUGE_EDGE_RADIUS ),
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
	return persentage >= CLEAR_PERSENT * 100.0;
}
