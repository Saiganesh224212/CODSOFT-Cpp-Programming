/*NUMBER GUESSING GAME
Create a program that generates a random number and asks the
user to guess it. Provide feedback on whether the guess is too
high or too low until the user guesses the correct number.*/
#include <iostream>
#include <cstdlib>
#include <ctime>

void playGame() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));  
    int target = std::rand() % 100 + 1;  
    int userGuess = 0;

    std::cout << "Try to guess the number (between 1 and 100):\n";

    while (userGuess != target) {
        std::cout << "Enter your guess: ";
        std::cin >> userGuess;

        if (userGuess > target) {
            std::cout << "📈 Too high! Give it another shot.\n";
        } else if (userGuess < target) {
            std::cout << "📉 Too low! Try again.\n";
        } else {
            std::cout << "🎯 Bingo! You nailed it. The number was " << target << ".\n";
        }
    }
}

int main() {
    std::cout << "🎮 Welcome to the Number Guessing Game! 🎮\n";
    playGame();
    std::cout << "Thanks for playing! 🎉\n";
    return 0;
}
