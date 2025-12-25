#include "mvv_lva.hpp"


MVVLVA::MVVLVA(Bitboards& board): _board(board) {}

int MVVLVA::mvv_lva(Move& move, const Color side, const Color opponent) {
    if (!move.take) return 0;
    PieceType capturer = _board.get_piece_type(side, move.from);
    PieceType captured = _board.get_piece_type(opponent, move.to);
    return PIECE_VALUES[captured] * 10 - PIECE_VALUES[capturer];
}

void MVVLVA::sort_mvv_lva(std::vector<Move>& moves, const Color side) {
    const Color opponent = (side == Color::WHITE) ? Color::BLACK : Color::WHITE;
    sort(moves.begin(), moves.end(), [this, side, opponent](Move& m1, Move& m2) {
        return mvv_lva(m1, side, opponent) > mvv_lva(m2, side, opponent);
    });
}