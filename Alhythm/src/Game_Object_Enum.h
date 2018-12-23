#pragma once

#include <Siv3D.hpp>

namespace Game{
namespace Object{

// プレイ画面で、どのレーンかを識別する列挙型
enum class LaneID : wchar_t{
	// 後々処理で使う(主にGame::Object::Note)ためs3d::wchar型を利用する
	A = L'A',
	S = L'S',
	D = L'D',
	F = L'F',
	J = L'J',
	K = L'K',
	L = L'L',
	Smcl = L';',
};

//enum class Difficulty{
//	Easy,
//	Medium,
//	Expert,
//};

}// namespace Game
}// namespace Object