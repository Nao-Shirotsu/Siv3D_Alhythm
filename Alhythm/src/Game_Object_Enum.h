#pragma once

namespace Game{
namespace Object{

// �v���C��ʂŁA�ǂ̃��[���������ʂ���񋓌^
enum class LaneID{
	// ��X�����Ŏg��(���Game::Object::Note)����s3d::wchar�^�𗘗p����
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