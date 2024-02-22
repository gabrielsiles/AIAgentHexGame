#ifndef IA_PLAYER__H
#define IA_PLAYER__H

#include <tuple>
#include <vector>
#include <memory>
#include <map>
#include <cassert>
#include <limits>
#include <cmath>

#include "Hex_Environement.h"
#include "mcts.h"

class IA_Player : public Player_Interface {
    char _player;
    unsigned int _taille;
public:
    IA_Player(char player, unsigned int taille=10) : _player(player), _taille(taille) {
        assert(player == 'X' || player == 'O');

    }

    void otherPlayerMove(int row, int col) override {
        // l'autre joueur à joué (row, col)
    }

    std::tuple<int, int> getMove(Hex_Environement& hex) override {
       // int row, col; // TODO : choisir le coups row, col a jouer

        // ///// Exemple d'un choix aléatoire ////////////
        // do {
        //     row = rand()%_taille; 	// Choix aléatoire
        //     col = rand()%_taille; 	// Choix aléatoire
        // } while( hex.isValidMove(row, col) == false );
        // //////////////////////////////////////////////

        // return {row, col};
        MCTS mcts(&hex);
        return mcts.runMCTS();
       
    }
};


#endif

