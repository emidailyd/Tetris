#pragma once

namespace GameConfig
{
    constexpr int ROW_COUNT = 20;
    constexpr int COLUMN_COUNT = 10;

    constexpr int CELL_SIZE = 28;
    constexpr int STATUS_PANEL_WIDTH = 150;

    constexpr int BOARD_WIDTH = COLUMN_COUNT * CELL_SIZE;
    constexpr int BOARD_HEIGHT = ROW_COUNT * CELL_SIZE;
}
