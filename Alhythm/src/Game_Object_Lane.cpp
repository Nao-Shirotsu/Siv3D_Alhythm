#include "Game_Object_Lane.h"

namespace{

constexpr int LANE_WIDTH{ 80 };
constexpr int LANE_HEIGHT{ 800 };

constexpr s3d::Color BG_COLOR{ 64, 64, 64, 224 };
constexpr s3d::Color FRAME_COLOR{ 128, 128, 128 };
constexpr s3d::Color JUDGE_COLOR{ 224, 224, 224 };

}

Game::Object::Lane::Lane( std::shared_ptr<Track>& track_ ):
	track( track_ ),
	judgeLineL( 475, 680, 770, 680 ),
	judgeLineR( 900, 680, 1195, 680 ){
	
	using namespace Game::Object;
	// queue�̎��̂�������Ă���
	notesQueue[LaneID::A];
	notesQueue[LaneID::S];
	notesQueue[LaneID::D];
	notesQueue[LaneID::F];
	notesQueue[LaneID::J];
	notesQueue[LaneID::K];
	notesQueue[LaneID::L];
	notesQueue[LaneID::Smcl];

	// ���[���̕`��p��`�̏ꏊ���w��
	laneRects[0] = s3d::Rect( 470, 0, 80, 800 );
	laneRects[1] = s3d::Rect( 545, 0, 80, 800 );
	laneRects[2] = s3d::Rect( 620, 0, 80, 800 );
	laneRects[3] = s3d::Rect( 695, 0, 80, 800 );
	laneRects[4] = s3d::Rect( 895, 0, 80, 800 );
	laneRects[5] = s3d::Rect( 970, 0, 80, 800 );
	laneRects[6] = s3d::Rect( 1045, 0, 80, 800 );
	laneRects[7] = s3d::Rect( 1120, 0, 80, 800 );
}

Game::Object::Lane::Lane() = default;

Game::Object::Lane::~Lane() = default;

void Game::Object::Lane::Update(){

	// ----debug----
	s3d::ClearPrint();
	// -------------

	for( auto& notes : notesQueue ){
		// ----debug----
		s3d::Println( s3d::Format( L"[ ", static_cast< s3d::wchar >( notes.first ), L" ] �c ", notes.second.size() ) );
		// -------------

		if( notes.second.empty() ){ // �m�[�c��queue����Ȃ牽�����Ȃ�
			continue;
		}
		if( notes.second.front().Passed() ){ // �m�[�c��queue�̐擪�������ゾ������|�b�v�������Ď���
			notes.second.pop();
			continue;
		}
		notes.second.front().Update(); // �m�[�c��queue�̐擪����������������Update
	}
}

void Game::Object::Lane::Draw() const{
	// ���[����`��
	for( const auto& laneRect : laneRects ){
		laneRect.draw( BG_COLOR );
		laneRect.drawFrame( 5, 0, FRAME_COLOR );
	}
	judgeLineL.draw( JUDGE_COLOR );
	judgeLineR.draw( JUDGE_COLOR );

	// �����Ă���m�[�c��`��
	for( const auto& notes : notesQueue ){
		if( !notes.second.empty() ){
			notes.second.front().Draw();
		}
	}
}

void Game::Object::Lane::AddNote( LaneID laneID, int bar, int beat ){
	notesQueue[laneID].emplace( bar, beat, laneID, track );
}
