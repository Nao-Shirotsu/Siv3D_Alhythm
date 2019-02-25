#include "Game_Object_Lane.h"
#include "Game_Util_Functions.h"
#include "Game_Object_Constant.h"

namespace Game{
namespace Object{

namespace{

// レーン枠の色など
constexpr s3d::Color LANE_BG_COLOR{ 64, 64, 64, 224 };
constexpr s3d::Color LANE_BG_COLOR_PUSHED{ 96, 96, 96, 224 };
constexpr s3d::Color FRAME_COLOR{ 128, 128, 128 };

// レーン枠の幅
constexpr int LANE_FRAME_WIDTH{ 5 };

// レーン下部に表示するASDFなどの値
constexpr int LANE_LETTER_SIZE{ 35 };
constexpr int LANE_LETTER_POS_Y{ LANE_HEIGHT - 90 };
constexpr int LANE_LETTER_A_POS_X{ LANE_A_POS_X + 25 };
constexpr int LANE_LETTER_S_POS_X{ LANE_S_POS_X + 30 };
constexpr int LANE_LETTER_D_POS_X{ LANE_D_POS_X + 30 };
constexpr int LANE_LETTER_F_POS_X{ LANE_F_POS_X + 30 };
constexpr int LANE_LETTER_J_POS_X{ LANE_J_POS_X + 25 };
constexpr int LANE_LETTER_K_POS_X{ LANE_K_POS_X + 30 };
constexpr int LANE_LETTER_L_POS_X{ LANE_L_POS_X + 30 };
constexpr int LANE_LETTER_Smcl_POS_X{ LANE_Smcl_POS_X + 30 };
constexpr s3d::Color LANE_LETTER_COLOR{ 85, 85, 85, 224 };

}

Lane::Lane( std::shared_ptr<Track>& track_, std::shared_ptr<NoteSound>& noteSound_, int maxbar ):
	track( track_ ),
	noteSound( noteSound_ ),
	judgeLineL( L_JUDGELINE_POS_X, JUDGELINE_HEGHT - NOTE_HEIGHT / 2, JUDGELINE_LENGTH, NOTE_HEIGHT ), // +5とか-25は枠の分
	judgeLineR( R_JUDGELINE_POS_X, JUDGELINE_HEGHT - NOTE_HEIGHT / 2, JUDGELINE_LENGTH, NOTE_HEIGHT ),
	letterA( LANE_LETTER_SIZE ),
	letterS( LANE_LETTER_SIZE ),
	letterD( LANE_LETTER_SIZE ),
	letterF( LANE_LETTER_SIZE ),
	letterJ( LANE_LETTER_SIZE ),
	letterK( LANE_LETTER_SIZE ),
	letterL( LANE_LETTER_SIZE ),
	letterSmcl( LANE_LETTER_SIZE ){
	using namespace Game::Object;
	noteLines[LaneID::A];
	noteLines[LaneID::S];
	noteLines[LaneID::D];
	noteLines[LaneID::F];
	noteLines[LaneID::J];
	noteLines[LaneID::K];
	noteLines[LaneID::L];
	noteLines[LaneID::Smcl];

	laneRects[LaneID::A] = s3d::Rect( LANE_A_POS_X, LANE_POS_Y, LANE_WIDTH, LANE_HEIGHT );
	laneRects[LaneID::S] = s3d::Rect( LANE_S_POS_X, LANE_POS_Y, LANE_WIDTH, LANE_HEIGHT );
	laneRects[LaneID::D] = s3d::Rect( LANE_D_POS_X, LANE_POS_Y, LANE_WIDTH, LANE_HEIGHT );
	laneRects[LaneID::F] = s3d::Rect( LANE_F_POS_X, LANE_POS_Y, LANE_WIDTH, LANE_HEIGHT );
	laneRects[LaneID::J] = s3d::Rect( LANE_J_POS_X, LANE_POS_Y, LANE_WIDTH, LANE_HEIGHT );
	laneRects[LaneID::K] = s3d::Rect( LANE_K_POS_X, LANE_POS_Y, LANE_WIDTH, LANE_HEIGHT );
	laneRects[LaneID::L] = s3d::Rect( LANE_L_POS_X, LANE_POS_Y, LANE_WIDTH, LANE_HEIGHT );
	laneRects[LaneID::Smcl] = s3d::Rect( LANE_Smcl_POS_X, LANE_POS_Y, LANE_WIDTH, LANE_HEIGHT );

	LoadNotesInfoFile();
	AddAllBarLineToLane( maxbar );
}

Lane::Lane(){}

Lane::~Lane(){}

std::deque<NoteJudge> Lane::Update(){
	std::deque<NoteJudge> judgeVal;
	for( auto& line : noteLines ){
		if( line.second.empty() ){ // ノーツのdequeが空なら何もしない
			continue;
		}

		for( auto& note : line.second ){
			if( !note.IsValidToIndicate() ){
				break;
			}
			note.UpdatePos();
		}

		// 処理終わったノーツをポップ
		line.second.front().UpdateJudging();
		NoteJudge res = line.second.front().Result();
		if( res != NoteJudge::Undone ){
			line.second.pop_front();
			judgeVal.emplace_back( res );
		}
	}

	for( auto& barline : barLines ){
		if( !barline.IsValidToIndicate() ){
			break;
		}
		barline.Update();
	}

	if( !barLines.front().IsValidToIndicate() ){
		barLines.pop_front();
	}

	return judgeVal;
}

void Lane::Draw() const{
	DrawLaneSegment();
	DrawBarLineSegment();
	DrawNotesSegment();
}

int Lane::FullCombo() const{
	return fullCombo;
}



void Lane::AddNoteToLane( LaneID laneID, int bar, int beat ){
	noteLines[laneID].emplace_back( bar, beat, laneID, track, noteSound );
}

void Lane::AddAllBarLineToLane( const int maxbar ){
	for( int i = 0; i < maxbar; ++i ){
		barLines.emplace_back( i, track );
	}
}

void Lane::LoadNotesInfoFile(){
	const s3d::CSVReader csv( Util::EmbeddedNotesInfoFilePath( track->trackID ) );
	if( !csv || csv.isEmpty() ){
		throw std::runtime_error( "notesinfo file read error" );
	}

	fullCombo = static_cast< int >( csv._get_rows() );
	for( int i = 0; i < fullCombo; ++i ){
		AddNoteToLane( static_cast<LaneID>( csv.get<wchar_t>( i, 0 ) ), csv.get<int>( i, 1 ), csv.get<int>( i, 2 ) );
	}
}

void Lane::DrawNotesSegment() const{
	for( const auto &lane : noteLines ) {
		if( lane.second.empty() ) {
			continue;
		}
		for( const auto &note : lane.second ) {
			if( !note.IsValidToIndicate() ) {
				break;
			}
			note.Draw();
		}
	}
}

void Lane::DrawLaneSegment() const {
	for( const auto &laneRect : laneRects ) {
		if( Game::Util::LaneKeyPressed( static_cast< wchar_t >( laneRect.first ) ) ) {
			laneRect.second.draw( LANE_BG_COLOR_PUSHED );
		}
		else {
			laneRect.second.draw( LANE_BG_COLOR );
		}
		laneRect.second.drawFrame( LANE_FRAME_WIDTH, 0, FRAME_COLOR );
	}
	judgeLineL.draw( JUDGELINE_COLOR );
	judgeLineR.draw( JUDGELINE_COLOR );
	letterA( L'A' ).draw( LANE_LETTER_A_POS_X, LANE_LETTER_POS_Y, LANE_LETTER_COLOR );
	letterS( L'S' ).draw( LANE_LETTER_S_POS_X, LANE_LETTER_POS_Y, LANE_LETTER_COLOR );
	letterD( L'D' ).draw( LANE_LETTER_D_POS_X, LANE_LETTER_POS_Y, LANE_LETTER_COLOR );
	letterF( L'F' ).draw( LANE_LETTER_F_POS_X, LANE_LETTER_POS_Y, LANE_LETTER_COLOR );
	letterJ( L'J' ).draw( LANE_LETTER_J_POS_X, LANE_LETTER_POS_Y, LANE_LETTER_COLOR );
	letterK( L'K' ).draw( LANE_LETTER_K_POS_X, LANE_LETTER_POS_Y, LANE_LETTER_COLOR );
	letterL( L'L' ).draw( LANE_LETTER_L_POS_X, LANE_LETTER_POS_Y, LANE_LETTER_COLOR );
	letterSmcl( L';' ).draw( LANE_LETTER_Smcl_POS_X, LANE_LETTER_POS_Y, LANE_LETTER_COLOR );
}

void Lane::DrawBarLineSegment() const{
	for( const auto& barline : barLines ) {
		if( !barline.IsValidToIndicate() ) {
			break;
		}
		barline.Draw();
	}
}

}// namespace Object
}// namespace Game