#ifndef BITBOARDS_HPP
#define BITBOARDS_HPP

#include "types.hpp"

constexpr Bitboard FileABB = 0x0101010101010101ULL;
constexpr Bitboard FileBBB = FileABB << 1;
constexpr Bitboard FileCBB = FileABB << 2;
constexpr Bitboard FileDBB = FileABB << 3;
constexpr Bitboard FileEBB = FileABB << 4;
constexpr Bitboard FileFBB = FileABB << 5;
constexpr Bitboard FileGBB = FileABB << 6;
constexpr Bitboard FileHBB = FileABB << 7;

constexpr Bitboard FilesBB[FILE_NB] = {FileABB, FileBBB, FileCBB, FileDBB,
                                       FileEBB, FileFBB, FileGBB, FileHBB};

constexpr Bitboard Rank1BB = 0xFF;
constexpr Bitboard Rank2BB = Rank1BB << (8 * 1);
constexpr Bitboard Rank3BB = Rank1BB << (8 * 2);
constexpr Bitboard Rank4BB = Rank1BB << (8 * 3);
constexpr Bitboard Rank5BB = Rank1BB << (8 * 4);
constexpr Bitboard Rank6BB = Rank1BB << (8 * 5);
constexpr Bitboard Rank7BB = Rank1BB << (8 * 6);
constexpr Bitboard Rank8BB = Rank1BB << (8 * 7);

constexpr Bitboard RanksBB[RANK_NB] = {Rank1BB, Rank2BB, Rank3BB, Rank4BB,
                                       Rank5BB, Rank6BB, Rank7BB, Rank8BB};

constexpr Bitboard square_bb(Square s) { return 1ull << s; }

inline Bitboard operator&(Bitboard b, Square s) { return b & square_bb(s); }
inline Bitboard operator|(Bitboard b, Square s) { return b | square_bb(s); }
inline Bitboard operator^(Bitboard b, Square s) { return b ^ square_bb(s); }
inline Bitboard &operator&=(Bitboard &b, Square s) { return b &= square_bb(s); }
inline Bitboard &operator|=(Bitboard &b, Square s) { return b |= square_bb(s); }
inline Bitboard &operator^=(Bitboard &b, Square s) { return b ^= square_bb(s); }

inline Bitboard operator&(Square s, Bitboard b) { return b & s; }
inline Bitboard operator|(Square s, Bitboard b) { return b | s; }
inline Bitboard operator^(Square s, Bitboard b) { return b ^ s; }

inline Bitboard operator|(Square s1, Square s2) { return square_bb(s1) | s2; }

constexpr bool more_than_one(Bitboard b) { return b & (b - 1); }

constexpr Bitboard file_bb(File f) { return FilesBB[f]; }
constexpr Bitboard rank_bb(Rank r) { return RanksBB[r]; }
constexpr Bitboard file_bb(Square s) { return file_bb(file_of(s)); }
constexpr Bitboard rank_bb(Square s) { return rank_bb(rank_of(s)); }

template <Direction D> constexpr Bitboard shift(Bitboard b) {
    return D == NORTH           ? b << 8
           : D == SOUTH         ? b >> 8
           : D == NORTH + NORTH ? b << 16
           : D == SOUTH + SOUTH ? b >> 16
           : D == EAST          ? (b & ~FileHBB) << 1
           : D == WEST          ? (b & ~FileABB) >> 1
           : D == NORTH_EAST    ? (b & ~FileHBB) << 9
           : D == NORTH_WEST    ? (b & ~FileABB) << 7
           : D == SOUTH_EAST    ? (b & ~FileHBB) >> 7
           : D == SOUTH_WEST    ? (b & ~FileABB) >> 9
                                : b;
}

inline int popcount(Bitboard b) { return __builtin_popcountll(b); }
inline Square lsb(Bitboard b) {
    assert(b);
    return Square(__builtin_ctzll(b));
}
inline Square msb(Bitboard b) {
    assert(b);
    return Square(__builtin_clzll(b) ^ 63);
}
inline Square poplsb(Bitboard &b) {
    assert(b);
    const Square s = lsb(b);
    b &= b - 1;
    return s;
}

#endif
