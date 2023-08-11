#pragma once
#include <raylib.h>
#include <vector>

namespace Colors {

static const std::vector<Color> GetCellColors() {
    Color CYAN{21, 204, 209, 255};
    return {DARKBLUE, GREEN, RED, ORANGE, YELLOW, PURPLE, CYAN, PINK};
}

}  // namespace Colors