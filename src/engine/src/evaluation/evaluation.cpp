// evaluation.cpp

#include "evaluation.hpp"


int Evaluation::evaluate_board(Bitboards& board, Color player) {
    int score = 0;
    for (int i=0; i < 64; i++) {
        PieceType piece_type = board.get_piece_type(player, i);
        if (piece_type != PieceType::NONE_PIECE) score += PIECE_VALUES[piece_type];
    }
    return score;
}