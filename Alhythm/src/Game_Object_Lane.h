#pragma once

#define NO_S3D_USING

#include <deque>
#include <unordered_map>

#include <Siv3D.hpp>

#include "Game_Object_Enum.h"
#include "Game_Object_Note.h"
#include "Game_Object_BarLine.h"
#include "Game_FileID.h"
#include "Game_Util_TimeDuration.h"

namespace Game{
namespace Object{

// 音ゲープレイ画面に出るノーツが流れるレーンのクラス
class Lane{
public:
	explicit Lane( std::shared_ptr<Track>& track_, std::shared_ptr<NoteSound>& noteSound_, int maxbar );

	// 設定画面で使う時のコンストラクタ
	Lane( std::shared_ptr<NoteSound>& noteSound_ );

	// 何もしない
    Lane();
	~Lane();

	std::deque<NoteJudge> Update();
	void Draw() const;

	int FullCombo() const;
	
private:
	void DrawNotesSegment() const;
	void DrawLaneSegment() const;
	void DrawBarLineSegment() const;

	// 楽曲のノーツデータを追加する( LoadNotesInfoFile内で使用 )
	// どのレーンの何小節何拍目かを指定
	void AddNoteToLane( LaneID laneID, int bar, int beat );

	// 小節線を全て追加
	void AddAllBarLineToLane( const int maxbar ); // コンストラクタでmaxbarを渡してここで受け取っているのはクソ, 変えるべき

	// トラックの譜面情報(ノーツ配置)が載ったファイルを読みこむ 
	void LoadNotesInfoFile();

	// 設定画面で使われているか否か
	bool isSettingLane;

	// フルコンボ時のノーツ数
	int fullCombo;

	// 各Noteに渡すために保管
	std::shared_ptr<Track> track;
	std::shared_ptr<NoteSound> noteSound;

	// 8レーンの矩形、判定ライン、レーンID文字
	std::unordered_map<LaneID, s3d::Rect> laneRects;
	s3d::Rect judgeLineL;
	s3d::Rect judgeLineR;
	s3d::Font letterA;
	s3d::Font letterS;
	s3d::Font letterD;
	s3d::Font letterF;
	s3d::Font letterJ;
	s3d::Font letterK;
	s3d::Font letterL;
	s3d::Font letterSmcl;

	// 1曲中各レーンに流れてくるノーツを全て格納する
	std::unordered_map<LaneID, std::deque<Note>> noteLines;

	// 上同様、小節線を全て格納する
	std::deque<BarLine> barLines;
};

}// namespace Object
}// namespace Game