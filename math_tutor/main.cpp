#include "mathTutor.h" // includes to the program the header file
#include <iostream>    // used for cin and cout
#include <string>      // allows to use strings
#include <vector>      // allows you to use vectors

using namespace std;

/******************************************************************************************
  Program: Math tutor for beginners.
  Programmer: Nicolas Tagliafichi
  Date: 12/09/2022
  repl.it: https://replit.com/@NicolasTagliafi/mathtutor301#main.cpp
  Description: This program will loop calling the different functions until the
  user chooses to end the program.
  *****************************************************************************************/

int main() {
    int choice;
    string inputGarbage;
    vector<vector<int>> mathQuestions;
    bool userContinue = true;

    srand(time(0)); // seed the random method with the currect time

    DisplayGameHeader();

    while ((choice = GetUserMenuChoice())) {
        switch (choice) {
            case 1:
            case 2:
            case 3:
            case 4: // The options 1-4 will display a different math question
                while (userContinue) {
                    AskMathQuestion(choice - 1, mathQuestions);
                    userContinue = userContinueFunction();
                }
                break;
            case 5:
                DisplayStatusReport(mathQuestions); // Option 5 will display the stats
                // from the user's game
                break;
            case 6:
                try {
                    SaveCurrentGame(
                            mathQuestions); // Option 6 will save the user's game in a .txt file
                } catch (runtime_error &excpt) {
                    cout << endl;
                    cout << excpt.what() << endl;
                }
                break;
            case 7:
                try {
                    LoadPreviousGame(
                            mathQuestions); // Option 7 will load the previously saved game
                } catch (runtime_error &excpt) {
                    cout << endl;
                    cout << excpt.what() << endl;
                }
                break;
            case 8:
                mathQuestions.clear(); // Option 8 will reset the user's game. It does not
                // reset the saved game.
                cout << "Game Reset." << endl;
                break;
            default:
                cout << endl;
                cout << "Invalid Choice: " << choice << endl;
                cout << "Program ended with an -1 error code." << endl;
                cout << "Please contact Princess Debbie Johnson." << endl;
                return -1;
        }
        getline(cin, inputGarbage); // clear anything still in the input buffer
        cout << "Press the enter key to continue...";
        getline(cin, inputGarbage); // wait until the user presses the enter key
        cout << endl;
    }
    cout << "Goodbye! I hope you had fun playing with your MATH TUTOR" << endl;

    return 0;
} // end of main
