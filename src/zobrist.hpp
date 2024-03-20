#ifndef ZOBRIST_HPP
#define ZOBRIST_HPP

#include "helpers.hpp"
#include "types.hpp"

Key ZobristPieceKeys[PIECE_NB][SQUARE_NB];
Key ZobristEnPassantKeys[FILE_NB];
Key ZobristCastlingKeys[CASTLING_RIGHTS_NB];
Key ZobristTurnKey;

void initZobrist() {
    PRNG rng(1070372);

    for (Color c = WHITE; c <= BLACK; ++c)
        for (PieceType pt = PAWN; pt <= KING; ++pt)
            for (Square sq = SQ_A1; sq <= SQ_H8; ++sq)
                ZobristPieceKeys[make_piece(c, pt)][sq] = rng.rand<Key>();

    for (File f = FILE_A; f <= FILE_H; ++f)
        ZobristEnPassantKeys[f] = rng.rand<Key>();

    for (int cr = NO_CASTLING; cr <= ANY_CASTLING; ++cr)
        ZobristCastlingKeys[cr] = rng.rand<Key>();

    ZobristTurnKey = rng.rand<Key>();
}

#endif
