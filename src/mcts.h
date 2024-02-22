#ifndef MCTS_H
#define MCTS_H

#include <vector>
#include <tuple>
#include <cmath>
#include <limits>
#include <random>
#include "Hex_Environement.h"
#include <algorithm> // For std::shuffle
#include <chrono>    // For std::chrono::system_clock

// Forward declaration to make MCTSNode aware of MCTS class
class MCTS;

class MCTSNode {
public:
    MCTSNode* parent;
    std::vector<MCTSNode*> children;
    int wins;
    int visits;
    std::tuple<int, int> move;
    std::vector<std::tuple<int, int>> untriedMoves;

    MCTSNode(MCTSNode* parent, std::tuple<int, int> move, std::vector<std::tuple<int, int>> possibleMoves)
        : parent(parent), wins(0), visits(0), move(move), untriedMoves(possibleMoves) {}

    bool isLeafNode() const { return children.empty(); }
    MCTSNode* selectChildUCT();
    void expand(MCTS& mcts); // Change to accept MCTS reference
    void update(bool win);


    ~MCTSNode() { 
        // Recursively delete children
        for (MCTSNode* child : children) {
            delete child;
        }
    }
};

class MCTS {
private:
    friend class MCTSNode; // Make MCTSNode a friend of MCTS
    Hex_Environement* hexEnv;
    MCTSNode* root ;

public:
    // MCTS(Hex_Environement* env) : hexEnv(env) {} // Constructor to initialize hexEnv
    // //MCTS(Hex_Environement* env);
   

    MCTS(Hex_Environement* env) : hexEnv(env), root(nullptr) {
//        assert(env != nullptr); // Ensure env is not null
        root = new MCTSNode(nullptr, std::make_tuple(-1, -1), generatePossibleMoves());
    }

    ~MCTS() {
        delete root; // Ensure to clean up root to prevent memory leaks
    }

    std::tuple<int, int> runMCTS();
    bool simulateGame(MCTSNode* node);
    std::vector<std::tuple<int, int>> generatePossibleMoves() const;

};

// Implementation of selectChildUCT remains the same
MCTSNode* MCTSNode::selectChildUCT() {
    if (children.empty()) return nullptr; // Check for empty before accessing

    MCTSNode* bestChild = nullptr;
    double bestValue = std::numeric_limits<double>::lowest();
    for (auto& child : children) {
        if (child != nullptr && child->visits > 0 && parent != nullptr && parent->visits > 0) {
            double winRate = static_cast<double>(child->wins) / static_cast<double>(child->visits);
            double explorationFactor = sqrt(2.0) * sqrt(log(static_cast<double>(parent->visits)) / static_cast<double>(child->visits));
            double uctValue = winRate + explorationFactor;
            if (uctValue > bestValue) {
                bestValue = uctValue;
                bestChild = child;
            }
        }
    }
    return bestChild;
}

void MCTSNode::expand(MCTS& mcts) {
    if (untriedMoves.empty()) return; // Check for empty before accessing

    auto move = untriedMoves.back();
    untriedMoves.pop_back();
    auto possibleMoves = mcts.generatePossibleMoves();
    if (!possibleMoves.empty()) { // Check for empty before creating a child
        MCTSNode* child = new MCTSNode(this, move, possibleMoves);
        children.push_back(child);
    }
}
void MCTSNode::update(bool win) {
    visits++;
    if (win) wins++;
    if (parent != nullptr) parent->update(!win); // Check parent is not null
}
// Use this to seed the random number generator
unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
std::default_random_engine generator(seed);

std::vector<std::tuple<int, int>> MCTS::generatePossibleMoves() const {
    std::vector<std::tuple<int, int>> moves;
    // Assuming Hex_Environement has a method to check if a move is valid
    for (unsigned int row = 0; row < hexEnv->getSize(); ++row) {
        for (unsigned int col = 0; col < hexEnv->getSize(); ++col) {
            if (hexEnv->isValidMove(row, col)) {
                moves.emplace_back(row, col);
            }
        }
    }
    return moves;
}
std::tuple<int, int> MCTS::runMCTS() {
    if (!root) { // Make sure root is valid
        return std::make_tuple(-1, -1);
    }

    int iterations = 1000;
    while (iterations--) {
        MCTSNode* node = root; // Already checked for null

        // Selection - Ensure node selection is valid
        while (node && !node->isLeafNode() && !node->untriedMoves.empty()) {
            MCTSNode* selectedNode = node->selectChildUCT();
            if (!selectedNode) {
                break; // Avoid proceeding with a null selected node
            }
            node = selectedNode;
        }

        // Expansion - Safely expand the node
        if (node && !node->untriedMoves.empty()) {
            node->expand(*this);
            // Ensure there's at least one child before accessing
            if (!node->children.empty()) {
                node = node->children.back();
            }
        }

        // Simulation - Perform only if node is valid
        if (node) {
            bool win = simulateGame(node);
            node->update(win);
        }
    }

    // Selection of the best move
    if (root && !root->children.empty()) {
        auto bestChildIt = std::max_element(root->children.begin(), root->children.end(), [](const MCTSNode* a, const MCTSNode* b) {
            return (a->wins / static_cast<double>(a->visits)) < (b->wins / static_cast<double>(b->visits));
        });

        if (bestChildIt != root->children.end()) {
            return (*bestChildIt)->move;
        }
    }

    return std::make_tuple(-1, -1); // Handle error or uninitialized state
}


bool MCTS::simulateGame(MCTSNode* node) {
    // Simplified simulation: randomly choose a winner
    std::vector<int> outcomes = {0, 1}; // 0 for loss, 1 for win
    std::shuffle(outcomes.begin(), outcomes.end(), generator);
    return outcomes.front(); // Randomly return true (win) or false (loss)
}

#endif // MCTS_H
