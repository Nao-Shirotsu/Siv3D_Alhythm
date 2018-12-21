#pragma once

namespace Game{
namespace Object{

enum class LaneID{
	A = static_cast< int >( 'A' ),
	S = static_cast< int >( 'S' ),
	D = static_cast< int >( 'D' ),
	F = static_cast< int >( 'F' ),
	J = static_cast< int >( 'J' ),
	K = static_cast< int >( 'K' ),
	L = static_cast< int >( 'L' ),
	Smcl = static_cast< int >( ';' ),
};

//enum class Difficulty{
//	Easy,
//	Medium,
//	Expert,
//};

}// namespace Game
}// namespace Object