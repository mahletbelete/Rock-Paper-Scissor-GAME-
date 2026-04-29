#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iomanip> // For setw()

using namespace std;

const int MAX_PLAYERS = 100;

struct Player {
    string name;
    int wins;
    int losses;
    int ties;
};

void saveLeaderboard(Player leaderboard[], int playerCount) {
    ofstream file("leaderboard.txt");
    for (int i = 0; i < playerCount; ++i) {
        file << leaderboard[i].name << " " << leaderboard[i].wins << " " << leaderboard[i].losses << " " << leaderboard[i].ties << endl;
    }
    file.close();
}

int loadLeaderboard(Player leaderboard[]) {
    int playerCount = 0;
    ifstream file("leaderboard.txt");
    while (file >> leaderboard[playerCount].name >> leaderboard[playerCount].wins >> leaderboard[playerCount].losses >> leaderboard[playerCount].ties) {
        playerCount++;
    }
    file.close();
    return playerCount;
}

void displayLeaderboard(Player leaderboard[], int playerCount) {
    cout << "\nLeaderboard:\n";
    cout << "_________________________________________\n";
    cout << "| Name       | Wins | Losses | Ties     |\n";
    cout << "|____________|______|________|__________|\n";
    for (int i = 0; i < playerCount; ++i) {
        cout << "| " << setw(10) << left << leaderboard[i].name
             << " | " << setw(4) << leaderboard[i].wins
             << " | " << setw(6) << leaderboard[i].losses
             << " | " << setw(8) << leaderboard[i].ties << " |\n";
    }
    cout << "|____________|______|________|__________|\n";
}

void printChoice(int choice) {
    if (choice == 0) {
        cout << "Rock:" << endl;
        cout << "    ____" << endl;
        cout << "   /    \\" << endl;
        cout << "  | Rock |" << endl;
        cout << "   \\____/" << endl;
    } else if (choice == 1) {
        cout << "Paper:" << endl;
        cout << "   ______" << endl;
        cout << "  |      |" << endl;
        cout << "  |Paper |" << endl;
        cout << "  |______|" << endl;
    } else {
        cout << "Scissors:" << endl;
        cout << "    _  _" << endl;
        cout << "   ( o o )" << endl;
        cout << "    \\ - /" << endl;
        cout << "     | |" << endl;
        cout << "    (_|_)" << endl;
    }
}

void loadingAnimation(const string& message, int duration) {
    cout << message;
    for (int i = 0; i < duration; ++i) {
        cout << ".";
        cout.flush();
        for (int j = 0; j < 100000000; ++j); // This introduces a delay; adjust the value as needed.
    }
    cout << endl;
}

int main() {
    srand(static_cast<unsigned int>(time(0)));

    cout << "***************************************" << endl;
    cout << "*                                     *" << endl;
    cout << "*    Welcome to Rock Paper Scissors   *" << endl;
    cout << "*                                     *" << endl;
    cout << "***************************************" << endl;

    cout << "\nGame Rules:\n";
    cout << "1. Rock beats Scissors\n";
    cout << "2. Scissors beats Paper\n";
    cout << "3. Paper beats Rock\n";
    cout << "4. If both players choose the same option, it's a tie\n";
    cout << "---------------------------------------\n";

    string playerName;
    cout << "Enter your name: ";
    cin >> playerName;
    loadingAnimation("Preparing your game", 3);

    int rounds;
    cout << "Enter the number of rounds you want to play: ";
    cin >> rounds;

    string choices[3] = {"Rock", "Paper", "Scissors"};
    char playAgain;
    int totalWins = 0, totalLosses = 0, totalTies = 0, gamesPlayed = 0;
    int computerWins = 0, computerLosses = 0;

    Player leaderboard[MAX_PLAYERS];
    int playerCount = loadLeaderboard(leaderboard);

    while (gamesPlayed < rounds) {
        int computerChoice = rand() % 3;
        int userChoice = -1;
        string userInput;

        cout << "\nRound " << gamesPlayed + 1 << " of " << rounds << "!" << endl;
        cout << "===============================" << endl;
        cout << "(0: Rock)" << endl;
        cout << "(1: Paper)" << endl;
        cout << "(2: Scissors)" << endl;
        cout << "Enter your choice (rock, paper, scissors or 0, 1, 2): ";
        cout << "You can enter either a string or a number." << endl;
        cin >> userInput;

        transform(userInput.begin(), userInput.end(), userInput.begin(), ::tolower);

        if (userInput == "rock" || userInput == "0") {
            userChoice = 0;
        } else if (userInput == "paper" || userInput == "1") {
            userChoice = 1;
        } else if (userInput == "scissors" || userInput == "2") {
            userChoice = 2;
        } else {
            cout << "Invalid choice! Please try again." << endl;
            continue;
        }

        cout << "You chose: " << choices[userChoice] << endl;
        printChoice(userChoice);
        cout << "Computer chose: " << choices[computerChoice] << endl;
        printChoice(computerChoice);

        if (userChoice == computerChoice) {
            cout << "***************************************" << endl;
            cout << "It's a tie! Well played!" << endl;
            cout << "***************************************" << endl;
            totalTies++;
        } else if ((userChoice == 0 && computerChoice == 2) ||
                   (userChoice == 1 && computerChoice == 0) ||
                   (userChoice == 2 && computerChoice == 1)) {
            cout << "***************************************" << endl;
            cout << "You win! Congratulations!" << endl;
            cout << "***************************************" << endl;
            totalWins++;
            computerLosses++;
        } else {
            cout << "***************************************" << endl;
            cout << "You lose! Better luck next time!" << endl;
            cout << "***************************************" << endl;
            totalLosses++;
            computerWins++;
        }

        gamesPlayed++;
    }

    cout << "\nThanks for playing! Goodbye!" << endl;

    cout << "\nGame Statistics:\n";
    cout << "===============================\n";
    cout << "Games Played: " << gamesPlayed << endl;
    cout << "Wins: " << totalWins << endl;
    cout << "Losses: " << totalLosses << endl;
    cout << "Ties: " << totalTies << endl;

    bool playerFound = false;
    for (int i = 0; i < playerCount; ++i) {
        if (leaderboard[i].name == playerName) {
            leaderboard[i].wins += totalWins;
            leaderboard[i].losses += totalLosses;
            leaderboard[i].ties += totalTies;
            playerFound = true;
            break;
        }
    }
    if (!playerFound && playerCount < MAX_PLAYERS) {
        leaderboard[playerCount++] = {playerName, totalWins, totalLosses, totalTies};
    }

    bool computerFound = false;
    for (int i = 0; i < playerCount; ++i) {
        if (leaderboard[i].name == "Computer") {
            leaderboard[i].wins += computerWins;
            leaderboard[i].losses += computerLosses;
            computerFound = true;
            break;
        }
    }
    if (!computerFound && playerCount < MAX_PLAYERS) {
        leaderboard[playerCount++] = {"Computer", computerWins, computerLosses, 0};
    }

    saveLeaderboard(leaderboard, playerCount);
    displayLeaderboard(leaderboard, playerCount);

    return 0;
}
