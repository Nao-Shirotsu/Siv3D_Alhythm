#pragma once

namespace Game{
namespace Object{

// プレイ画面で、どのレーンかを識別する列挙型
enum class LaneID{
	// 後々処理で使う(主にGame::Object::Note)ためs3d::wchar型を利用する
	A = static_cast< int >( L'A' ),
	S = static_cast< int >( L'S' ),
	D = static_cast< int >( L'D' ),
	F = static_cast< int >( L'F' ),
	J = static_cast< int >( L'J' ),
	K = static_cast< int >( L'K' ),
	L = static_cast< int >( L'L' ),
	Smcl = static_cast< int >( L';' ),
};

//enum class Difficulty{
//	Easy,
//	Medium,
//	Expert,
//};

}// namespace Game
}// namespace Object