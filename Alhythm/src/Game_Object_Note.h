#pragma once
#pragma once

#define NO_S3D_USING

#include <memory>

#include <Siv3D.hpp>

#include "Game_Object_Track.h"
#include "Game_Object_Enum.h"
#include "Game_Object_NoteSound.h"

namespace Game{
namespace Object{

// 音ゲープレイ画面で使うノーツオブジェクトの構造体
class Note{
public:
	explicit Note( int barNum_, int beatNum_, LaneID lane_, const std::shared_ptr<Track>& track_, const std::shared_ptr<NoteSound>& noteSound_ );

	// 何もしない STLコンテナのため用意
	Note();
	~Note();

	void UpdateJudging();
	void UpdatePos();
	void Draw() const;

	// ノーツの判定を返す
	NoteJudge Result();

	// レーンに表示される期間内か否か返す
	bool IsValidToIndicate() const noexcept;

private:
	// 判定ラインと重なる瞬間
	double secOnMusic;

	// ノートの表示時間の計算に利用
	double timeDiff;

	// 表示実体と位置
	int rectPosX;
	s3d::RoundRect noteRect;

	// 色々とトラックの情報を使うためDIで得て格納
	std::shared_ptr<Track> track;

	// タップ音クラスの実体をDIで得て格納
	std::shared_ptr<NoteSound> noteSound;

	// 本当はLaneIDのままがよいが、そうすると何度もキャストする必要があるためs3d::wchar
	s3d::wchar lane;

	// このノートのタップ判定値 Good, Fineなど
	NoteJudge tapResult;

	// 判定有効になったかどうか
	// これがtrueならば判定ラインに近づいた後であり、
	// ボタンを押さなくても時間経過で消さなければならないため個の変数を使う
	bool isPushable;
};

}// namespace Object
}// namespace Game