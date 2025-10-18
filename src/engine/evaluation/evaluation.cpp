// evaluation.cpp

#include "evaluation.hpp"


int Evaluation::evaluate_board_for(Bitboards& board, Color player) {
    int player_score = Evaluation::evaluate_player(board, player);
    Color opponent = (player == Color::WHITE) ? Color::BLACK : Color::WHITE;
    int opponent_score = Evaluation::evaluate_player(board, opponent);
    return (player_score - opponent_score);
}

int Evaluation::evaluate_player(Bitboards& board, Color player) {
    int score = 0;
    for (int i=0; i < 64; i++) {
        PieceType piece_type = board.get_piece_type(player, i);
        if (piece_type != PieceType::NONE_PIECE) score += PIECE_VALUES[piece_type];
    }
    return score;
}