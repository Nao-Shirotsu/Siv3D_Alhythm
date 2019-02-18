#pragma once

#define NO_S3D_USING

#include <memory>

#include <Siv3D.hpp>

namespace Game{
namespace Singleton{

// クリック音オブジェクトのシングルトンクラス(複数回ロードを防ぐためFlyweightにする)
class ClickSound{
public:
	ClickSound();
	~ClickSound();

	void Play() const;

private:
	// シングルトン初期化
	static void Init();

	static s3d::Sound sound;
};

}// namespace Singleton
}// namespace Game