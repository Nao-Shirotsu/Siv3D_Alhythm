#pragma once

namespace Game{
namespace Object{

// 1つのノーツの幅と高さ
constexpr int NOTE_WIDTH{ 70 };
constexpr int NOTE_HEIGHT{ 20 };

// レーン1列の幅と高さ
constexpr int LANE_WIDTH{ 80 };
constexpr int LANE_HEIGHT{ 700 };

// 判定ラインの中心のy座標
constexpr int JUDGELINE_HEGHT{ LANE_HEIGHT - NOTE_HEIGHT / 2 - 5 };

}// namespace Object
}// namespace Game