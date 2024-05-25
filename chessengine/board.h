/*
    File: board.h
*/

#pragma once

#include <array>

namespace Chess{

    const size_t board_size = 10*12;

    enum class Color { white, black, none };

    enum class Piece {
        king,       // a king without castle potential
        king_castle,
        king_in_check,    // a king in check
        queen,
        pawn,       // a pawn without en passant potential
        pawn_en_passant, // a pawn with en passant potential
        rook,
        rook_castle,
        knight,
        bishop,
        none,
        none_b,
        out_of_board    // Illegal position
    };

    

    struct Square {
        Color piece_color;
        Piece piece;
        Square(Piece, Color);
        Square();
    };

    class Board {
        private:
            std::array<Square, board_size> squares;
        public:
            void set(const size_t where, Square);
            Square get(const size_t where) const;
    };
    
    Square Board::get(const size_t where) const {
        if (where >= board_size)
            return Square (Piece::out_of_board, Color::none);
        return squares[where];
    }

    void Board::set(const size_t where, Square s) {
        if (where >= board_size)
            return;
        squares[where] = s;
    }

    void init_classic_board(Board&);

}