#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>


class Board {
private:
    char raw[3][3];
public:
    Board() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                raw[i][j] = ' ';
            }
        }
    }

    bool hasNoEmptyCells() const {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (isEmpty(i, j)) {
                    return false;
                }
            }
        }

        return true;
    }

    bool isEmpty(int i, int j) const {
        return raw[i][j] == ' ';
    }

    char* operator[](int i) {
        return raw[i];
    }

    const char* operator[](int i) const {
        return raw[i];
    }

    std::string getRow(int row) const {
        std::string value = std::string() + raw[row][0] + raw[row][1] + raw[row][2];
        return value;
    }

    std::string getCol(int col) const {
        std::string value = std::string() + raw[0][col] + raw[1][col] + raw[2][col];
        return value;
    }

    std::string getMainDiagonal() const {
        std::string value = std::string() + raw[0][0] + raw[1][1] + raw[2][2];
        return value;
    }

    std::string getSecondaryDiagonal() const {
        std::string value = std::string() + raw[0][2] + raw[1][1] + raw[2][0];
        return value;
    }

    friend std::ostream& operator<<(std::ostream& os, const Board& board) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                os << board[i][j] << "|";
            }
            std::cout << std::endl;
        }

        return os;
    }
};

// Alpha-beta algorithm
const int MAX = INT_MAX;
const int MIN = INT_MIN;
Board AlphaBetaDecision(const Board& board);
int MaxValue(const Board& board, int alpha, int beta, int &depth);
int MinValue(const Board& board, int alpha, int beta, int &depth);
// Helper functions
std::vector<Board> getChildren(const Board &board, char player);
int getTerminalStateValue(const Board& board);
bool isFinalState(const Board &board);


Board AlphaBetaDecision(const Board& board) {
    int maxValue = -1;
    int bestDepth = MAX;
    Board bestBoard = board;

    std::vector<Board> children = getChildren(board, 'x');

    for (auto child : children) {
        int depth = 0;
        int value = MinValue(child, MIN, MAX, depth);

        if (value > maxValue) {
            maxValue = value;
            bestBoard = child;
            bestDepth = depth;
        }
        else if (value == maxValue && depth < bestDepth) {
            bestDepth = depth;
            bestBoard = child;
        }
    }

    return bestBoard; // returns bets possible move for the AI
}

int MaxValue(const Board& board, int alpha, int beta, int &depth) {
    depth++;
    if (isFinalState(board)) {
        return getTerminalStateValue(board);
    }

    int best = MIN;
    std::vector<Board> children = getChildren(board, 'x');

    for (auto child : children) {
        best = std::max(best, MinValue(child, alpha, beta, depth));

        if (best >= beta) {
            return best;
        }

        alpha = std::max(alpha, best);
    }

    return best;
}

int MinValue(const Board& board, int alpha, int beta, int &depth) {
    depth++;
    if (isFinalState(board)) {
        return getTerminalStateValue(board);
    }

    int best = MAX;
    std::vector<Board> children = getChildren(board, 'o');

    for (auto child : children) {
        best = std::min(best, MaxValue(child, alpha, beta, depth));

        if (best <= alpha) {
            return best;
        }

        beta = std::min(beta, best);
    }

    return best;
}

std::vector<Board> getChildren(const Board &board, char player) {
    std::vector<Board> children;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (!board.isEmpty(i, j)) {
                continue;
            }
            Board nextState = board;
            nextState[i][j] = player;
            children.push_back(nextState);
        }
    }

    return children;
}

int getTerminalStateValue(const Board& board) {

    std::string mainDiagonal = board.getMainDiagonal();
    std::string secondaryDiagonal = board.getSecondaryDiagonal();

    if (mainDiagonal == "xxx" ||
        secondaryDiagonal == "xxx") {
        return 1;
    }

    if (mainDiagonal == "ooo" ||
        secondaryDiagonal == "ooo") {
        return -1;
    }

    for (int i = 0; i < 3; i++) {
        std::string row = board.getRow(i);
        std::string col = board.getCol(i);
        if (row == "xxx" ||
            col == "xxx") {
            return 1;
        }
        if (row == "ooo" ||
            col == "ooo") {
            return -1;
        }
    }

    return 0;
}

bool isFinalState(const Board &board) {

    if (board.hasNoEmptyCells()) {
        return true;
    }

    std::string mainDiagonal = board.getMainDiagonal();
    std::string secondaryDiagonal = board.getSecondaryDiagonal();

    if (mainDiagonal == "xxx" ||
        secondaryDiagonal == "xxx" ||
        mainDiagonal == "ooo" ||
        secondaryDiagonal == "ooo") {
        return true;
    }

    for (int i = 0; i < 3; i++) {
        std::string row = board.getRow(i);
        std::string col = board.getCol(i);
        if (row == "xxx" ||
            col == "xxx" ||
            row == "ooo" ||
            col == "ooo") {
            return true;
        }
    }

    return false;
}

class Game {
    Board board;
    enum {Player, CPU} firstPlayer;

    std::pair<int, int> getPlayerMove() {
        int i, j;
        std::cout << "Row Col: ";
        std::cin >> i >> j;

        while(i < 0 || j < 0 ||
              i > 2 || j > 2 ||
            !board.isEmpty(i, j)) {
            std::cout << "Not a valid move. Try again!" << std::endl;
            std::cout << "Row Col: ";
            std::cin >> i >> j;
        }

        return std::make_pair(i, j);
    }

    void printResult() {
        if (getTerminalStateValue(board) == 1) {
            std::cout << "AI WINS!" << std::endl;
        }
        else if (getTerminalStateValue(board) == -1) {
            std::cout << "Player WINS!" << std::endl;
        }
        else {
            std::cout << "Draw!" << std::endl;
        }
    }
public:
    Game() {
        firstPlayer = CPU;
     
        std::cout << " - Human plays with O" << std::endl;
        std::cout << " - AI plays with X" << std::endl;
        std::cout << '\n';
    }

    void choosePlayer() {
        std::cout << "Who should go first? 1 for player, 0 for CPU: ";
        bool choice;
        std::cin >> choice;
        firstPlayer = (choice == true) ? Player : CPU;
    }

    void start() {
        if (firstPlayer == Player) {
            std::cout << board << std::endl;
            std::pair<int, int> pos = getPlayerMove();
            board[pos.first][pos.second] = 'o';
            std::cout << board << std::endl;
        }

        while (!isFinalState(board)) {
            std::cout<<"AI move"<<std::endl;
            board = AlphaBetaDecision(board);
            std::cout << board << std::endl;
            if (isFinalState(board)) {
                break;
            }
            std::pair<int, int> pos = getPlayerMove();
            board[pos.first][pos.second] = 'o';
            std::cout << board << std::endl;
        }

        printResult();
    }
};

int main() {

    Game game;
    game.choosePlayer();
    game.start();

    return 0;
}
