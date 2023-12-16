#include <cstdlib>   // used for srand and rand
#include <exception> // used for error handling
#include <fstream>   // used to include files
#include <iomanip>   // used for setw
#include <iostream>  // used for cin and cout
#include <limits>    // used for the numeric input
#include <string>    // allows to use strings
#include <vector>    // allows you to use vectors

using namespace std;

/******************************************************************************************
  Program: Math tutor for beginners.
  Programmer: Nicolas Tagliafichi
  Date: 12/09/2022
  repl.it: https://replit.com/@NicolasTagliafi/mathtutor301#main.cpp
  Description: This program contains all the functions that will be called when
  the math tutor program is running.
  *****************************************************************************************/

const int MAX_ATTEMPTS = 3;
const string FILE_NAME = "mathTutor.txt"; // File used to save the game
const vector<char> MATH_OPERATORS = {'+', '-', '*', '/'};
enum MathTypes { ADITION, SUBTRACTION, MULTIPLICATION, DIVISION };

/*****************************************************************************
This function will display the game header, gets the user name, displays a
welcome message, and explains the basic rules of the program.
******************************************************************************/
void DisplayGameHeader() {
  string userName = "?";
  cout << "+------------------------------------------------------+" << endl;
  cout << "|                       MATH TUTOR                     |" << endl;
  cout << "+------------------------------------------------------+" << endl;
  cout << endl;
  cout << "Please enter your name: ";
  getline(cin, userName); // Get the user's name
  cout << endl;
  cout << "Hello " << userName << "!" << endl;
  cout << "Lets begin with your math tutor!" << endl;
  cout << "You have 3 attempts to answer each math problem." << endl;
  cout << endl;
}

/*****************************************************************************
This function will loop until the user eneters a numeric input and returns the
value entered .
******************************************************************************/
int GetNumericValue() {
  int userNumber = 0;

  while (!(cin >> userNumber)) {
    cin.clear(); // clear the error flag on cin
    cin.ignore(numeric_limits<streamsize>::max(),
               '\n'); // ignore the max input, up to '/n'
    cout << "Invalid Input. Please enter a valid number!" << endl;
    cout << "Please enter a number:  ";
  }
  return userNumber;
}

/*****************************************************************************
This function displays the main menu, gets the user's choice, and returns
that value.
******************************************************************************/
int GetUserMenuChoice() {
  int userChoice = 0;

  // math tutor menu
  cout << "==========================" << endl;
  cout << "| Simple Math Tutor Menu |" << endl;
  cout << "==========================" << endl;
  cout << "   1 = (+) Addition       " << endl;
  cout << "   2 = (-) Subtraction    " << endl;
  cout << "   3 = (*) Multiplication " << endl;
  cout << "   4 = (/) Division       " << endl;
  cout << "--------------------------" << endl;
  cout << "   5 = Status report      " << endl;
  cout << "   6 = Save Current Game  " << endl;
  cout << "   7 = Load Previous Game " << endl;
  cout << "   8 = Reset Game         " << endl;
  cout << "--------------------------" << endl;
  cout << "   0 = Quit               " << endl;
  cout << "--------------------------" << endl << endl;

  // loops until the user enters a valid option from the menu
  while (true) {
    cout << "Enter choice: ";
    userChoice = GetNumericValue();
    if (userChoice >= 0 && userChoice <= 8)
      break;
    else {
      cout << "Invalid input! Please try again..." << endl;
    }
    cout << endl;
  }
  cout << endl;
  return userChoice;
}

/*****************************************************************************
This function will generate two random numbers to generate the math questions
and will return a vector populated with both numbers and the question type that
the user chose in the main menu.
Also, if the number in the left is smaller than the one at the right it will
switch them to avoid negative answers, and it changes the value to make the
numbers divisable.
******************************************************************************/
vector<int> CreateQuestion(int questType) {
  int temp = 0;
  int leftNum = 0;
  int rightNum = 0;

  leftNum =
      (rand() % 10 +
       1); // Generate the random number that will be displayed at the left side
  rightNum = (rand() % 10 + 1); // Generate the random number that will be
                                // displayed at the right side

  // make sure that the left number is larger to avoid negative answers
  if (leftNum < rightNum) {
    temp = leftNum;
    leftNum = rightNum;
    rightNum = temp;
  }
  // avoid decimal numbers as answers
  if (questType == DIVISION)
    leftNum *= rightNum;

  return {leftNum, questType, rightNum}; // start to populate the 2D vector
}

/*****************************************************************************
This programs uses a switch to calulate the right answer. It uses the values
entered in the 2D vector populated at the function CreateQuestion. It returns
the correct answer value.
******************************************************************************/
int GetCorrectAnswer(const vector<int> &row) {
  int leftNum = row.at(0);
  int questType = row.at(1);
  int rightNum = row.at(2);
  int correctAnswer = 0;

  // switch used to calculate the right answer
  switch (questType) {
  case 0:
    correctAnswer = leftNum + rightNum;
    break;
  case 1:
    correctAnswer = leftNum - rightNum;
    break;
  case 2:
    correctAnswer = leftNum * rightNum;
    break;
  case 3:
    correctAnswer = leftNum / rightNum;
    break;
  default:
    cout << "Unable to get the correct Answer: -2 Error Code" << endl;
    cout << "Invalid question type: " << questType << endl;
    exit(-2); // end the program immediately (do NOT return -2)
  }           // close the switch
  return correctAnswer;
}

/*****************************************************************************
This function displays the math question generated in the previous functions
and loops until the user inputs the right answer or runs out of attempts.
When the user gets the correct answer it saves the attempts needed to answer in
the 2D vector.
******************************************************************************/
void AskMathQuestion(int questType, vector<vector<int>> &mathQuestions) {
  char questOp = MATH_OPERATORS.at(questType);

  vector<int> row = CreateQuestion(questType);

  int leftNum = row.at(0);
  int rightNum = row.at(2);
  int correctAnswer = GetCorrectAnswer(row);
  int userAnswer = 0;
  int questNum = mathQuestions.size() + 1;

  for (int i = 1; i <= MAX_ATTEMPTS; i++) {
    cout << questNum << " --> "
         << "What is " << leftNum << " " << questOp << " " << rightNum
         << " = "; // Display the math question
    userAnswer = GetNumericValue();

    // Display a congratulation message if the user got the answer right.
    if (userAnswer == correctAnswer) {
      cout << "GREAT JOB !!! " << correctAnswer << " is the correct answer! =) "
           << endl
           << endl;
      row.push_back(
          i); // Add the attempts used to answer correctly to the 2D vector
      break;
    }
    // If the answer the user gave is wrong, give the user another chance if
    // they still have attempts left.
    else {
      if (i == MAX_ATTEMPTS) {
        row.push_back(0); // add to the 2D vector that the user was not able to
                          // answer correctly
        cout << "You ran out of attempts. The answer was: " << correctAnswer
             << endl;
        cout << endl;
      } else {
        cout << "That is not the correct answer." << endl;
        if (MAX_ATTEMPTS - i != 1)
          cout << "[You have " << MAX_ATTEMPTS - i << " attempts left]" << endl;
        else {
          cout << "[You have just " << MAX_ATTEMPTS - i << " attempt left]"
               << endl;
        }
        cout << endl;
      }                         // close inner else
    }                           // close outer else
  }                             // close of for loop
  mathQuestions.push_back(row); // Adds the current question to the 2D vector
}

/*****************************************************************************
Display a detailed report including each question asked with its correct answer
and the attempts used to answer correctly and displays the results that the user
got.
******************************************************************************/
void DisplayStatusReport(const vector<vector<int>> &mathQuestions) {
  int leftNum = 0;
  int mathType = 0;
  int rightNum = 0;
  int correctAnswer = 0;
  int attempts = 0;
  int totalCorrect = 0;
  int totalQuestions = 0;
  int userPercent = 0;
  char questOp = '?';

  totalQuestions = mathQuestions.size();

  if (mathQuestions.size() == 0) {
    cout << "NO DATA. " << endl;
    return;
  } else {
    cout << "+========================================+" << endl;
    cout << "|         MATH DETAILED REPORT           |" << endl;
    cout << "|========================================|" << endl;
    cout << "|     Questions      |     Attempts      |" << endl;
    cout << "+----------------------------------------+" << endl;

    for (int i = 0; i < mathQuestions.size(); i++) {
      for (int j = 0; j < mathQuestions.at(i).size(); j++) {
        leftNum = mathQuestions.at(i).at(0);
        mathType = mathQuestions.at(i).at(1);
        rightNum = mathQuestions.at(i).at(2);
        attempts = mathQuestions.at(i).at(3);
      } // close inner for loop

      correctAnswer = GetCorrectAnswer(mathQuestions.at(i));
      questOp = MATH_OPERATORS.at(mathType);

      cout << "| " << setw(3) << right << leftNum << " " << questOp << " "
           << setw(3) << left << rightNum << "=  " << setw(3) << correctAnswer
           << "    |";

      if (attempts == 0) {
        cout << setw(14) << right << "Incorrect" << setw(6) << "|" << endl;
      } else {
        totalCorrect++;
        cout << setw(10) << right << attempts << setw(10) << "|" << endl;
      }
    } // close outer for loop
    cout << "+========================================+" << endl;
    cout << endl;
    userPercent =
        (totalCorrect * 100) /
        totalQuestions; // calculate the percentage of correct questions

    // display the results that the user got
    cout << "+~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+" << endl;
    cout << "|  Total questions answers   : " << setw(4) << totalQuestions
         << "  |" << endl;
    cout << "|  Total questions correct   : " << setw(4) << totalCorrect
         << "  |" << endl;
    cout << "|  Total questions incorrect : " << setw(4)
         << totalQuestions - totalCorrect << "  |" << endl;
    cout << "|  Your percentage was       : " << setw(3) << userPercent << "%"
         << "  |" << endl;
    cout << "+~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+" << endl << endl;
    return;
  }
}

/*****************************************************************************
This function will open the mathTutor.txt file. Then, it analyzes if there is
any data to save. If there is any data to save, it reads the values saved in the
2D vector and outputs the values to the file. After finished, it will close the
file.
******************************************************************************/
void SaveCurrentGame(const vector<vector<int>> &mathQuestions) {
  ofstream outFS; // Output file stream handle

  if (mathQuestions.empty()) {
    cout << "NO DATA TO SAVE. Try again later." << endl;
    return;
  }
  cout << "Saving game. Please wait..." << endl;

  outFS.open(FILE_NAME); // opens FILE_NAME

  if (!outFS.is_open()) {
    throw runtime_error(
        "Could not open file " + FILE_NAME +
        " for writing"); // throw a runtime error if the file cannot open.
  }
  // Use a for loop to move the data from the 2D vector to the .txt file
  for (int i = 0; i < mathQuestions.size(); i++) {
    outFS << mathQuestions.at(i).at(0) << " " << mathQuestions.at(i).at(1)
          << " " << mathQuestions.at(i).at(2) << " "
          << mathQuestions.at(i).at(3) << endl;
  }
  outFS.close(); // Done with file, so close it

  cout << mathQuestions.size() << " questions were saved succesfully to "
       << FILE_NAME << endl
       << endl;
}

/*****************************************************************************
This function will open the .txt file and checks if there is any information
to load. It will clear the 2D vector so that is empty, and then it starts to
populated with the values saved at the mathTutor.txt file.
******************************************************************************/
void LoadPreviousGame(vector<vector<int>> &mathQuestions) {
  int leftNum = 0;
  int mathType = 0;
  int rightNum = 0;
  int attempts = 0;
  ifstream inFS; // Input stream file handle

  mathQuestions
      .clear(); // make sure the vectors are empty before loading the file
  inFS.open(FILE_NAME); // opens the file

  if (!inFS.is_open()) {
    cout << "No previous game to load " << endl;
  }
  while (inFS >> leftNum >> mathType >> rightNum >> attempts) {
    mathQuestions.push_back({leftNum, mathType, rightNum, attempts});
  }
  if (!inFS.eof()) {
    throw runtime_error("Something went wrong with reading the " + FILE_NAME +
                        " file.");
  }
  inFS.close(); // Done with file, so close it
  cout << "Previous game loaded successfully! " << endl << endl;
}

bool userContinueFunction() {
  char userCont = '?';
  bool keepLoop = true;

  cout << "Enter 'q' to return to the main menu or any other key to continue "
          "playing. "
       << endl;
  cout << "---> ";
  cin >> userCont;
  cout << endl;

  if (userCont == 'q')
    keepLoop = false;

  return keepLoop;
}
