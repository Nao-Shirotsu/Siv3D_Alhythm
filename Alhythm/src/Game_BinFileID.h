#pragma once

namespace Game{

// Resource.rcに記述する埋め込みファイルの識別番号
enum class BinFileID{
	// Images
	BackgroundImage = 1000,
	TitleStringImage = 1001,

	// SoundEffects
	NoteTapSound = 2000,
	DecideSound = 2001,

	// BGM
	MusicSelectBGM = 2500,
	TitleBGM = 2501,

	// Tracks
	Senkou = 3000,
	Cassi = 3001,
	Orion = 3002,

	// NotesFiles
	// 各トラックに対応する譜面ファイルは+1000する( 曲3000なら譜面4000 )
};

}// namespace Game