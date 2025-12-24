#include "mvv_lva.hpp"


int MVVLVA::mvv_lva(Bitboards& board, Move& move, const Color side) {
    PieceType capturer = board.get_piece_type(side, move.from);
    PieceType captured = board.get_piece_type(side, move.to);
    return PIECE_VALUES[captured] * 10 - PIECE_VALUES[capturer];
}