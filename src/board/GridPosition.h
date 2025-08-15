#pragma once

#include <functional>

struct GridPosition {
    unsigned row;
    unsigned column;

    friend bool operator==(const GridPosition& lhs, const GridPosition& rhs) {
        return lhs.row == rhs.row && lhs.column == rhs.column;
    }

    friend bool operator!=(const GridPosition& lhs, const GridPosition& rhs) { return !(lhs == rhs); }
};

template <> struct std::hash<GridPosition> {
    std::size_t operator()(const GridPosition& pos) const noexcept {
        return std::hash<unsigned>()(pos.row) ^ (std::hash<unsigned>()(pos.column) << 1);
    }
};
