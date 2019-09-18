//Brenda Escoto
//2281135
//escot105@mail.chapman.edu
//CPSC 406-01
//Assignment 1

#include <stdio.h>
#include <iostream>
#include <string>
#include "Mapping.h"

using namespace std;

int main(int argc, char **argv)
{
  string enteredFile = argv[1];

  Mapping s;
  s.inputFile(enteredFile);
  s.allDone();//so that its for sure the last thing that happens



}
