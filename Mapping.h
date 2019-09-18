/**
Brenda Escoto
escot105@mail.chapman.edu
CPSC 406-01 Algorithm Analysis
February 26, 2019
**/

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>

using namespace std;

class Mapping
{

  string states[50];//all states
  string newStates[50];//states after transition function has been applied
  string newTransition[50];//all transitions
  string language[50];//language of the nfa
  string accept[50];//accept states, can be >1
  string pwrSet[512];//1D array, highest value is 2^9
  string transFun[512];//will hold transition function values before they can be modified
  string **dfa;

  string startState;//there will only be one

  //counters needed to output correctly to file
  int acceptCounter;
  int newStatesCounter;
  int newTransCounter;
  int languageCounter;

  int pwrSetSize;//the size of the power set
  int numStates;//needed to generate power set
  int transCount;//keep track of how many transitions were done


public:
  Mapping();
  ~Mapping();

  void createPwrSet(string a[], int arrSize);
  void createGraph();//used to create the dfa
  void inputFile(string name);//take in the file, fill in arrays
  int findIndx(string f);//will return the index in power set of a value
  void printGraph();//mostly for debugging
  void setTransFun();//map values and then deal w/ special cases
  void doublesCheck();//for each row, will make sure no single input leads to two places, used to tell when there are multiple transitions
  void multTrans(string st1, string input, string nextSt);//when a state has more than one transition ex: 2,a=2,3
  void epsilon(string fstate, string pwrMember);//needs the first state and the state we will go to
  string stringCleaning(string s);//takes double characters out of strings, needed in order to find the correct value in power set
  void allDone();//writes to file when program is finished
  void outputHelper();//formats the states and transitions between them correctly

};
