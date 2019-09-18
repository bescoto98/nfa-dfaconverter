> Brenda Escoto; escot105@mail.chapman.edu

Files:
- main.cpp
- Mapping.h
- Mapping.cpp
- input.nfa
- output.dfa

Assignment specifications called for a program written in C++ or Java that would take the specification for an NFA as the input, and produce a DFA from the arguments. The user would input the name of the file where an NFA was defined in the following format:
1. This line would have the list of states, separated by tabs.
2. This line would have a list of the language of the NFA, separated by tabs.
3. This line would have the start state.
4. This line would have the set of accept states.
5. This line would continue to the end of the file, and define the transition function.

Resources:
- https://www.geeksforgeeks.org/power-set/
> In order to generate the power set I did some research about the different ways it could be done. Eventually, I settled on the geeksforgeeks method linked, looking up how the binary counter worked, and how this method was able to produce the correct results.

- http://www.cplusplus.com

Issues: The only problem I ran into occurred when a state is given with a normal transition, and then the inverse is given with an epsilon transition. For example, if the states {1}, a = {3} and {3}, EPS = {1}, then I cannot guarantee that the values would be correct, because I could not figure out a way to swap the values of the first state to the values of the same state and the state that epsilon transitions into it. Other than that, my program should work as specified, given that the source file is correctly formatted.

To run the program, simply compile in C++ then run ./a.out, the program will prompt user for an input file and then terminate when it is finished.
