#include <iostream>
#include <fstream>
#include <string>
#include <ctime>      
#include <cstdlib>    
using namespace std;

struct Question {
    string text;
    string optionA;
    string optionB;
    string optionC;
    char correctAnswer;
};


void playQuiz();

int main() {
    char replay;
    cout << "==============================\n";
    cout << "     Welcome to the Quiz!     \n";
    cout << "==============================\n";

    do {
        playQuiz(); // play one round
        cout << "\nDo you want to play again? (y/n): ";
        cin >> replay;
    } while (replay == 'y' || replay == 'Y');

    cout << "\nThank you for playing! Goodbye!\n";
    return 0;
}

void playQuiz() {
    
    srand(time(0));

    string name;
    int score = 0;
    char answer;

    // Take player name
    cout << "\n Enter your name: ";
    
    getline(cin, name);

    cout << "\nHello, " << name << "! Let's start the quiz.\n\n";

    // ----- Create an array of questions -----
    Question q[5] = {
        {"What is the capital of India?", "Mumbai", "Delhi", "Chennai", 'b'},
        {"Which planet is known as the Red Planet?", "Jupiter", "Mars","Saturn", 'b'},
        {"Which is the longest river in the world?", "Ganga", "Amazon", "Nile", 'c'},
        {"What is the chemical symbol for Gold?", "Au", "Ag", "Hg", 'a'},
        {"Which country is known as the Land of the Rising Sun?", "Japan", "Korea", "India", 'a'}
    };

    // ----- Create an array of indices -----
    int order[5] = {0, 1, 2, 3, 4};

    // ----- Shuffle question order -----
    for (int i = 0; i < 5; i++) {
        int randomIndex = rand() % 5;
        swap(order[i], order[randomIndex]);
    }

    // ----- Ask questions in random order -----
    for (int i = 0; i < 5; i++) {
        int idx = order[i];
        cout << i + 1 << ". " << q[idx].text << endl;
        cout << "a) " << q[idx].optionA << endl;
        cout << "b) " << q[idx].optionB << endl;
        cout << "c) " << q[idx].optionC << endl;
        cout << "Enter your answer: ";
        cin >> answer;

        if (answer == q[idx].correctAnswer || answer == toupper(q[idx].correctAnswer)) {
            cout << "? Correct!\n\n";
            score++;
        } else {
            cout << "? Wrong! The correct answer is '" << q[idx].correctAnswer << "'.\n\n";
        }
    }

    // ----- Show Result -----
    cout << "=================================\n";
    cout << "Quiz Over! Your score: " << score << " out of 5\n";
    cout << "=================================\n";

    // ----- Save score in file -----
    ofstream file("scores.txt", ios::app);
    if (file.is_open()) {
        file << name << " - " << score << "/5\n";
        file.close();
        cout << "Your score has been saved in 'scores.txt'.\n";
    } else {
        cout << "Error: Unable to open file!\n";
    }

    // ----- Show previous scores -----
    cout << "\nDo you want to see previous scores? (y/n): ";
    char seeScores;
    cin >> seeScores;

    if (seeScores == 'y' || seeScores == 'Y') {
        ifstream infile("scores.txt");
        string line;
        cout << "\n----- Previous Player Scores -----\n";
        while (getline(infile, line)) {
            cout << line << endl;
        }
        infile.close();
        cout << "----------------------------------\n";
    }
}
