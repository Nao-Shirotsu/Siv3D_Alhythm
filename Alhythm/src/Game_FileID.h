#pragma once

namespace Game{

// Resource.rcに記述する埋め込みファイルの識別番号(画像)
enum class ImageFileID{
	BackgroundImage = 1000,
	TitleStringImage = 1001,
};

// Resource.rcに記述する埋め込みファイルの識別番号(トラック以外のSEやBGMなどのサウンド)
enum class SEBGMFileID{
	// SoundEffects
	NoteTapSound = 2000,
	DecideSound = 2001,

	// BGM
	MusicSelectBGM = 2500,
	TitleBGM = 2501,
};

// Resource.rcに記述する埋め込みファイルの識別番号(トラック)
enum class TrackFileID{
	Senkou = 3000,
	Cassi = 3001,
	Orion = 3002,
};

}// namespace Game