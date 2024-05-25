// File: gui.cpp
// This is quick, ugly, pragmatic, temporary.

#include <iostream>
#include <cctype>
#include <map>
#include "gui.h"



namespace Chess {

    using namespace std;

    static const std::map<Piece, char> sprites = { 
        { Piece::pawn,      'P' },
        { Piece::pawn_en_passant,   'E' },
        { Piece::rook,      'R' },
        { Piece::rook_castle,   'R' },
        { Piece::knight,        'N' },
        { Piece::bishop,        'B' },
        { Piece::king,      'K' },
        { Piece::king_castle,   'K' },
        { Piece::king_in_check,      'K' },
        { Piece::none,      '+' },
        { Piece::none_b,      '+' },
        { Piece::out_of_board,      '#' },
        { Piece::queen,         'Q' }
    };

    void print_board(const Board& b, Move last_move) {
        cout<<"\n   a b c d e f g h";
        for(ssize_t i=20; i < (ssize_t)board_size; ++i){
            if(i%10 == 9)
                continue;
            if(i/10 == 10)
                break;
            if(i%10 == 0) {
                cout<<"\n "<< 10 - i/10 <<" ";
                continue;
            }
            char s = sprites.at(b.get(i).piece);
            if(b.get(i).piece_color == Color::black)
                s = tolower(s);
            cout<<s;
            if(last_move.from == i || last_move.to == i)
                cout<<'<';
            else
                cout<<' ';          
        }
        cout<<"\n"<<endl;
    }

    Move read_move(const MoveSet& valid_moves, Color turn) {
        if(cin.fail()) {
            cin.clear();
            string dummy;
            cin >> dummy;
        }

        string on;
        int in;
        Move ret;
        cout<<"Your move, "<<( turn == Color::white ? "white" : "black" )<<": ";
        cin >> on;

        // Command to undo 1 or 2 moves (2 to revert AI+own)
        if(on == "0" || on == "1" || on == "2"){
            ret.from = on[0]-48;
            return ret;
        }

        in = (((58 - on[1])*10 + (on[0] - 96))*10 + (58 - on[3]))*10 + (on[2] - 96);

        ret.to  = in%10+in/10%10*10;
        in /= 100;
        ret.from  = in%10+in/10%10*10;

        for(const auto m : valid_moves)
            if(m.from == ret.from && m.to == ret.to)
                return ret;
        cout<<"Invalid move\n";
        return read_move(valid_moves, turn);
    }

}