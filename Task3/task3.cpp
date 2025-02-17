#include <iostream>
#include <vector>
using namespace std;
class TicTacToe {
private:
    vector<vector<char> > board; 
    char currentPlayer;
    int movesCount;

public:
    TicTacToe() {
        resetBoard();
    }

    void resetBoard() {
        board = vector<vector<char> >(3, vector<char>(3, ' ')); 
        currentPlayer = 'X';
        movesCount = 0;
    }

    void displayBoard() {
        cout << "\n  Tic-Tac-Toe Board\n";
        for (int i = 0; i < 3; i++) {
            cout << "  ";
            for (int j = 0; j < 3; j++) {
                cout << board[i][j];
                if (j < 2) cout << " | ";
            }
            cout << "\n";
            if (i < 2) cout << "  ---------\n";
        }
        cout << endl;
    }

    bool makeMove(int row, int col) {
        if (row < 0 || row > 2 || col < 0 || col > 2 || board[row][col] != ' ') {
            cout << "⚠ Invalid move! Try again.\n";
            return false;
        }
        board[row][col] = currentPlayer;
        movesCount++;
        return true;
    }

    bool checkWin() {
        for (int i = 0; i < 3; i++) {
            if (board[i][0] == currentPlayer && board[i][1] == currentPlayer && board[i][2] == currentPlayer)
                return true;
            if (board[0][i] == currentPlayer && board[1][i] == currentPlayer && board[2][i] == currentPlayer)
                return true;
        }
        if (board[0][0] == currentPlayer && board[1][1] == currentPlayer && board[2][2] == currentPlayer)
            return true;
        if (board[0][2] == currentPlayer && board[1][1] == currentPlayer && board[2][0] == currentPlayer)
            return true;
        return false;
    }

    bool checkDraw() {
        return movesCount == 9;
    }

    void switchPlayer() {
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }

    void playGame() {
        int row, col;
        while (true) {
            displayBoard();
            cout << "Player " << currentPlayer << ", enter row (0-2) and column (0-2): ";
            cin >> row >> col;

            if (!makeMove(row, col)) continue;

            if (checkWin()) {
                displayBoard();
                cout << "🎉 Player " << currentPlayer << " wins!\n";
                break;
            }

            if (checkDraw()) {
                displayBoard();
                cout << "⚖ It's a draw! No more valid moves left.\n";
                break;
            }

            switchPlayer();
        }
    }

    bool playAgain() {
        char choice;
        cout << "Do you want to play again? (y/n): ";
        cin >> choice;
        return (choice == 'y' || choice == 'Y');
    }
};

int main() {
    TicTacToe game;
    do {
        game.resetBoard();
        game.playGame();
    } while (game.playAgain());

    cout << "Thanks for playing! 🎮\n";
    return 0;
}
