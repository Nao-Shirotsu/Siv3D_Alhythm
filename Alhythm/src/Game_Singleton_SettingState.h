#pragma once

#define NO_S3D_USING

#include <Siv3D.hpp>

namespace Game{
namespace Singleton{

// ゲーム内設定の各値を管理するシングルトンクラス(設定の値はiniファイルに保存してロードする)
class SettingState{
public:
	SettingState();
	~SettingState();

	void WriteHispeedRate( const double rate );
	double HispeedRate() const;

private:
	// シングルトン初期化
	static void Init();

	static s3d::INIReader ini;
	static double hispeedRate;
};

}// namespace Singleton
}// namesp