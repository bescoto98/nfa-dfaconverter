/**
Brenda Escoto
escot105@mail.chapman.edu
February 26, 2019
**/

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
