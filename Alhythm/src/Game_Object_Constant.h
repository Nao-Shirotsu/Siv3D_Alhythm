#pragma once

namespace Game{
namespace Object{

// 1つのノーツの幅と高さ
constexpr int NOTE_WIDTH{ 70 };
constexpr int NOTE_HEIGHT{ 20 };

// レーン1列の幅と高さ
constexpr int LANE_WIDTH{ 80 };
constexpr int LANE_HEIGHT{ 700 };

// レーン枠の左上頂点の位置
constexpr int LANE_A_POS_X{ 470 };
constexpr int LANE_S_POS_X{ 545 };
constexpr int LANE_D_POS_X{ 620 };
constexpr int LANE_F_POS_X{ 695 };
constexpr int LANE_J_POS_X{ 895 };
constexpr int LANE_K_POS_X{ 970 };
constexpr int LANE_L_POS_X{ 1045 };
constexpr int LANE_Smcl_POS_X{ 1120 };
constexpr int LANE_POS_Y{ 0 };

// 判定ラインのX座標
constexpr int L_JUDGELINE_POS_X{ LANE_A_POS_X + 5 };
constexpr int R_JUDGELINE_POS_X{ LANE_J_POS_X + 5 };

// 判定ラインの長さ
constexpr int JUDGELINE_LENGTH{ LANE_WIDTH * 4 - 25 };

// 判定ラインの中心のy座標
constexpr int JUDGELINE_HEGHT{ LANE_HEIGHT - NOTE_HEIGHT / 2 - 5 };

// 判定ラインの色
constexpr s3d::Color JUDGELINE_COLOR{ 224, 224, 224, 128 };

// ノーツ, 小節線がレーン上に表示される秒数
constexpr double NOTE_INDICATE_TIME{ 1.2 };

}// namespace Object
}// namespace Game