// Name: Gabrial Nell
// Email: gjn96p@mail.umkc.edu
// Class: CS 201R @ 5:30-6:45 T/Th
// Instructor: Michael Essmyer
// Project #1

#include <iostream>
using namespace std;
#include <cstdlib>

int computerTurn(int currentRoll, int pot, int computerScore) {
    currentRoll = (rand() % 6) + 1;
    // the AI automatically ends its turn at a pot value of 20, so loop continues until either
    // 1.) the pot reaches 20 or 2.) the dice roll is a 1
    while (pot < 20) {
        // if a one is roled, per the rules of the game, pot becomes zero and AIs turn ends
        if (currentRoll == 1) {
            pot = 0;
            cout << "Die roll : " << currentRoll << " : BUST" << endl;
            return 0;
        }
        if (computerScore + pot >= 50) {
            cout << "Die roll : " << currentRoll << "     Pot : " << pot;
            return pot;
        }
        // so long as pot < 20 and a 1 isn't roled, the loop will continue until uninterrupted
        pot += currentRoll;
        cout << "Die roll : " << currentRoll << "     Pot : " << pot << endl;
        currentRoll = (rand() % 6) + 1;
    }
    return pot;
}

int playerTurn(int currentRoll, int pot, int playerScore) {
    char playerChoice;
    currentRoll = (rand() % 6) + 1;
    // continues to roll dice until either 1.) player presses h to hold or 2.) a 1 is rolled
    while (true) {
        // if a one is roled, per the rules of the game, pot becomes zero and players turn ends
        if (currentRoll == 1) {
            pot = 0;
            cout << "Die roll : " << currentRoll << " : BUST" << endl;
            return 0;
        }
        pot += currentRoll;
        if (playerScore + pot >= 50) {
            cout << "Die roll : " << currentRoll << "     Pot : " << pot;
            return pot;
        }
        cout << "Die roll : " << currentRoll << "     Pot : " << pot << "     (R)oll again or (H)old? ";
        // gets input from user and continues to do so until r(R) h(H) are entered
        cin >> playerChoice;
        while (playerChoice != 'r' && playerChoice != 'R' && playerChoice != 'h' && playerChoice != 'H') {
            cout << "You must enter R or H" << endl;
            cout << "     (R)oll again or (H)old? ";
            cin >> playerChoice;
        }
        cin.ignore();
        // r(R) means player wants to roll again, so gets new roll and restarts loop
        if (playerChoice == 'r' || playerChoice == 'R') {
            currentRoll = (rand() % 6) + 1;
        // h(H) means the player wants to end their turn, so pot is returned and function ends
        } else if (playerChoice == 'h' || playerChoice == 'H') {
            return pot;
        }
    }
}

int turn(bool whosTurn, int playerScore, int computerScore) {
    // If player turn is true, it is the user's turn. Else, it is the AI's turn
    int currentRoll;
    int pot = 0;
    // If this evaluates to true, then it is the user's turn. This requires input from the user
    // so it needs its own individual block seperate from the AI functionality
    if (whosTurn) {
        cout << "Players Turn";
        cin.ignore();
        pot = playerTurn(currentRoll, pot, playerScore);    
    } else {
        cout << "AI Turn";
        cin.ignore();
        pot = computerTurn(currentRoll, pot, computerScore);
    }
    return pot;
}

int main() {
    int playerScore = 0;
    int computerScore = 0;
    bool playerTurn = true;
    char playerChoice;
    srand(time(0));

    // main loop that continues until user enters N(n) to quit the program
    while(true) {
        // main game loop that goes until either player reaches threshold to when game of 50 points
        while(playerScore < 50 && computerScore < 50) {
            cout << endl;
            cout << "Score   You : " << playerScore << " AI : " << computerScore << endl;
            cout << endl;
            if (playerTurn) {
                playerScore += turn(playerTurn, playerScore, computerScore);
            } else {
                computerScore += turn(playerTurn, playerScore, computerScore);
            }
            playerTurn = !playerTurn;
        }
        cout << endl << endl;
        if (playerScore >= 50) {
            cout << "Player wins!" << endl;
        } else {
            cout << "AI wins!" << endl;
        }
        cout << endl << "Total Scores   Player : " << playerScore << " AI : " << computerScore << endl;
        // initial prompt to user if they wish to play again until Y(y) or N(n) entered
        cout << endl;
        cout << "Would you like to play again? Y/N ";
        cin >> playerChoice;
        // continues to prompt user to input if they wish to play again until Y(y) or N(n) entered
        while (playerChoice != 'y' && playerChoice != 'Y' && playerChoice != 'n' && playerChoice != 'N') {
                cout << "You must enter Y or N" << endl;
                cout << "Would you like to play again? Y/N ";
                cin >> playerChoice;
                cout << endl;
        }
        // if Y(y) is entered, player scores get reset and new game starts
        if (playerChoice == 'y' || playerChoice == 'Y') {
            computerScore = 0;
            playerScore = 0;
        // else, N(n) was entered and the program terminates
        } else {
            cout << endl;
            cout << "Thanks for playing!" << endl;
            break;
        }
    }

    return 0;
}

