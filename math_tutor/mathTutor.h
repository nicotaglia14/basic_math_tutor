#include <vector>
using namespace std;
/******************************************************************************************
  Program: Math tutor for beginners.
  Programmer: Nicolas Tagliafichi
  Date: 12/09/2022
  repl.it: https://replit.com/@NicolasTagliafi/mathtutor301#main.cpp
  Description: This program contains all the prototypes of the functions that
  are used to run the math tutor.
  *****************************************************************************************/
#ifndef MATHTUTOR_H
#define MATHTUTOR_H

// All the prototypes of the functions used by the program
void DisplayGameHeader();
int GetNumericValue();
int GetUserMenuChoice();
vector<int> CreateQuestion(int questType);
int GetCorrectAnswer(const vector<int> &row);
void AskMathQuestion(int questType, vector<vector<int>> &mathQuestions);
void DisplayStatusReport(const vector<vector<int>> &mathQuestions);
void SaveCurrentGame(const vector<vector<int>> &mathQuestions);
void LoadPreviousGame(vector<vector<int>> &mathQuestions);
bool userContinueFunction();
#endif