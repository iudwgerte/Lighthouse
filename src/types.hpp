#ifndef TYPES_HPP
#define TYPES_HPP

#include <array>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

typedef uint64_t Bitboard;
typedef uint64_t Key;

constexpr int MAX_PLY = 128;
constexpr int MAX_MOVES = 256;

enum Color { WHITE, BLACK, COLOR_NB };
enum CastlingRights {
    NO_CASTLING,
    WHITE_OO,
    WHITE_OOO = WHITE_OO << 1,
    BLACK_OO = WHITE_OO << 2,
    BLACK_OOO = WHITE_OO << 3,

    KING_SIDE = WHITE_OO | BLACK_OO,
    QUEEN_SIDE = WHITE_OOO | BLACK_OOO,
    WHITE_CASTLING = WHITE_OO | WHITE_OOO,
    BLACK_CASTLING = BLACK_OO | BLACK_OOO,
    ANY_CASTLING = WHITE_CASTLING | BLACK_CASTLING,

    CASTLING_RIGHTS_NB = 16
};
enum Bound {
    BOUND_NONE,
    BOUND_UPPER,
    BOUND_LOWER,
    BOUND_EXACT = BOUND_UPPER | BOUND_LOWER
};

typedef int Value;

constexpr Value VALUE_ZERO = 0;
constexpr Value VALUE_DRAW = 0;
constexpr Value VALUE_MATE = 32000;
constexpr Value VALUE_INFINITE = 32001;
constexpr Value VALUE_NONE = 32002;

constexpr Value VALUE_MATE_IN_MAX_PLY = VALUE_MATE - MAX_PLY;
constexpr Value VALUE_MATED_IN_MAX_PLY = -VALUE_MATE_IN_MAX_PLY;

// clang-format off

enum PieceType {
    NO_PIECE_TYPE, PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING,
    ALL_TYPES = 0,
    PIECE_TYPE_NB = 8
};
enum Piece {
    NO_PIECE,
    W_PAWN = PAWN,     W_KNIGHT, W_BISHOP, W_ROOK, W_QUEEN, W_KING,
    B_PAWN = PAWN + 8, B_KNIGHT, B_BISHOP, B_ROOK, B_QUEEN, B_KING,
    PIECE_NB = 12
};

// clang-format on

typedef int Depth;

// clang-format off

enum Square : int {
    SQ_A1, SQ_B1, SQ_C1, SQ_D1, SQ_E1, SQ_F1, SQ_G1, SQ_H1,
    SQ_A2, SQ_B2, SQ_C2, SQ_D2, SQ_E2, SQ_F2, SQ_G2, SQ_H2,
    SQ_A3, SQ_B3, SQ_C3, SQ_D3, SQ_E3, SQ_F3, SQ_G3, SQ_H3,
    SQ_A4, SQ_B4, SQ_C4, SQ_D4, SQ_E4, SQ_F4, SQ_G4, SQ_H4,
    SQ_A5, SQ_B5, SQ_C5, SQ_D5, SQ_E5, SQ_F5, SQ_G5, SQ_H5,
    SQ_A6, SQ_B6, SQ_C6, SQ_D6, SQ_E6, SQ_F6, SQ_G6, SQ_H6,
    SQ_A7, SQ_B7, SQ_C7, SQ_D7, SQ_E7, SQ_F7, SQ_G7, SQ_H7,
    SQ_A8, SQ_B8, SQ_C8, SQ_D8, SQ_E8, SQ_F8, SQ_G8, SQ_H8,
    SQ_NONE,

    SQUARE_ZERO = 0,
    SQUARE_NB   = 64
};

// clang-format on

enum Direction : int {
    NORTH = 8,
    EAST = 1,
    SOUTH = -NORTH,
    WEST = -EAST,

    NORTH_EAST = NORTH + EAST,
    SOUTH_EAST = SOUTH + EAST,
    SOUTH_WEST = SOUTH + WEST,
    NORTH_WEST = NORTH + WEST
};
enum File : int {
    FILE_A,
    FILE_B,
    FILE_C,
    FILE_D,
    FILE_E,
    FILE_F,
    FILE_G,
    FILE_H,
    FILE_NB = 8
};
enum Rank : int {
    RANK_1,
    RANK_2,
    RANK_3,
    RANK_4,
    RANK_5,
    RANK_6,
    RANK_7,
    RANK_8,
    RANK_NB = 8
};

#define ENABLE_INCR_OPERATORS(T)                                               \
    inline T &operator++(T &d) { return d = T(int(d) + 1); }                   \
    inline T &operator--(T &d) { return d = T(int(d) - 1); }

ENABLE_INCR_OPERATORS(Color)
ENABLE_INCR_OPERATORS(PieceType)
ENABLE_INCR_OPERATORS(Square)
ENABLE_INCR_OPERATORS(File)
ENABLE_INCR_OPERATORS(Rank)

#undef ENABLE_INCR_OPERATORS

constexpr Direction operator+(Direction d1, Direction d2) {
    return Direction(int(d1) + int(d2));
}
constexpr Direction operator*(Direction d, int i) {
    return Direction(int(d) * i);
}

constexpr Square operator+(Square s, Direction d) {
    return Square(int(s) + int(d));
}
constexpr Square operator-(Square s, Direction d) {
    return Square(int(s) - int(d));
}
inline Square &operator+=(Square &s, Direction d) { return s = s + d; }
inline Square &operator-=(Square &s, Direction d) { return s = s - d; }

constexpr Color operator~(Color c) { return Color(c ^ BLACK); }
constexpr Square operator~(Square s) { return Square(s ^ SQ_A8); }
constexpr Piece operator~(Piece p) { return Piece(p ^ 8); }

constexpr CastlingRights operator&(Color c, CastlingRights cr) {
    return CastlingRights((c == WHITE ? WHITE_CASTLING : BLACK_CASTLING) & cr);
}

constexpr Value mate_in(int ply) { return VALUE_MATE - ply; }
constexpr Value mated_in(int ply) { return -VALUE_MATE + ply; }
constexpr Square make_square(File f, Rank r) { return Square((r << 3) + f); }
constexpr Piece make_piece(Color c, PieceType pt) {
    return Piece((c << 3) + pt);
}

constexpr Color color_of(Piece p) { return Color(p >> 3); }
constexpr PieceType type_of(Piece p) { return PieceType(p & 7); }

constexpr File file_of(Square s) { return File(s & 7); }
constexpr Rank rank_of(Square s) { return Rank(s >> 3); }

constexpr Direction pawn_push(Color c) { return c == WHITE ? NORTH : SOUTH; }

constexpr Key make_key(uint64_t seed) {
    return seed * 6364136223846793005ull + 1442695040888963407ull;
}

enum MoveType {
    NORMAL,
    PROMOTION = 1 << 14,
    ENPASSANT = 2 << 14,
    CASTLING = 3 << 14
};

class Move {
public:
    Move() = default;
    constexpr Move(std::uint16_t d) : data(d) {}
    constexpr Move(Square from, Square to) : data((to << 6) + from) {}

    template <MoveType T>
    constexpr Move make(Square from, Square to, PieceType pt = KNIGHT) {
        return Move(T + ((pt - KNIGHT) << 12) + (to << 6) + from);
    }

    constexpr Square from_sq() { return Square(data & 0x3F); }
    constexpr Square to_sq() { return Square((data >> 6) & 0x3F); }
    constexpr int from_to() { return data & 0xFFF; }
    constexpr MoveType type_of() { return MoveType(data & (3 << 14)); }
    constexpr PieceType promotion_type() {
        return PieceType(((data >> 12) & 3) + KNIGHT);
    }

    constexpr bool is_ok() { return from_sq() != to_sq(); }

    constexpr Move none() { return Move(0); }
    constexpr Move null() { return Move(65); }

    constexpr bool operator==(const Move &m) { return data == m.data; }
    constexpr bool operator!=(const Move &m) { return data != m.data; }

    constexpr operator bool() { return data != 0; }

    constexpr std::uint16_t raw() { return data; }

    struct MoveHash {
        std::size_t operator()(const Move &m) { return make_key(m.data); }
    };

protected:
    std::uint16_t data;
};

#endif
