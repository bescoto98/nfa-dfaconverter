/**
Brenda Escoto
escot105@mail.chapman.edu
CPSC 406-01 Algorithm Analysis
February 26, 2019
**/

#include "Mapping.h"

Mapping::Mapping()
{
  startState ="";
  pwrSetSize=0;
  numStates =0;
  transCount=0;
  languageCounter=0;
  acceptCounter=0;
  newTransCounter=0;
  newStatesCounter=0;

  //in order to make a 2D array
  dfa= new string*[512];
  for(int i=0;i<512;i++)
  {
    dfa[i] = new string[512];
  }

}

//destructor
Mapping::~Mapping()
{
  for(int i=0;i<512;i++)
  {
    delete[] dfa[i];
  }

}


void Mapping::printGraph()
{
  cout << "|\n\t\tDFA\t\t\n|\n";
  for(int i=0; i<pwrSetSize;i++)
  {
    for(int j=0; j<pwrSetSize;j++)
    {
      cout << "{" << dfa[i][j] << "}" << " \t";
    }
    cout << "\n";
  }

}

void Mapping::createGraph()
{
  for(int i=0;i<pwrSetSize;i++)
  {
    dfa[0][i]=pwrSet[i];
    dfa[i][0]=pwrSet[i];
  }
  //now that graph is made, fill it out
  setTransFun();
}


void Mapping::createPwrSet(string a[], int arrSize)
{
  pwrSetSize=pow(2,arrSize);//2^n
  string index = " ";//value that will go into the powerset
  int owo = -1;//index of power set

  for(int i =0; i< pwrSetSize; i++)
  {

    for(int j =0; j<arrSize; j++)
    {
      if(i & (1<<j))
      {
        /**
        (1<<j) is a binary counter used to go from 000...0 to 111...1 this allows us to loop until all elements have been accounted for
        basically first loop generates all cominations possible in array, second loop makes sure you don't print duplicates
        **/
        index += a[j];
      }

    }
    owo++;
    pwrSet[owo] = index;
    index="";
  }

  //call function to make the map from the power set:
  createGraph();

}

void Mapping::inputFile(string name)
{
  int counter =0;//used to keep track of indexes for arrays
  int linecount =0;//used to iterate through each line
  string line ="";

  ifstream myfile (name); //name of file comes from command line argument
  if(myfile.is_open())
  {
    while(getline(myfile,line))
    {
      if(linecount==0)//list of states
      {

        counter=0;
        for(int s=0; s<line.length(); s++)
        {
          if(line[s]=='}'||line[s]=='{')
          {
            continue;//go to next character
          }
          if(line[s]!='\t'&&s!=line.length()-1)
          {

            states[counter]=line[s];

            counter++;
            numStates++;

          }
        }
      }
      if(linecount==1)//language of NFA
      {

        counter =0;
        for(int l=0; l<line.length(); l++)
        {
          if(line[l]!='\t')
          {
            language[counter] = line[l];

            counter++;
            languageCounter++;
          }
        }
      }
      if(linecount==2)//the start state-will only have one
      {
        startState=line;

      }
      if(linecount==3)//accept states, could have more than one
      {

        counter=0;
        for(int a =0; a<line.length();a++)
        {
          if(line[a]=='}'||line[a]=='{')
          {
            continue;//go to next character
          }
          if(line[a]!='\t'&&a!=line.length()-1)
          {
            accept[counter]=line[a];

            counter++;
            acceptCounter++;
          }
        }
      }
      if(linecount>=4)
      {
        transFun[linecount-4]=line;
        transCount++;

      }
      linecount++;
    }
    myfile.close();
  }
  else
  {
    cout << "error opening file" << endl;
  }

  //generate power set from values
  createPwrSet(states, numStates);

}

int Mapping::findIndx(string f)
{
  int sameChars=0;
  string temp="";

  //iterates through to find the index
  for(int i=0;i<pwrSetSize;i++)
  {
    if(dfa[0][i]==f)//the easy way
    {
      return i;
    }
    else if(dfa[0][i].length()==f.length())//if the member is not in order :(
    {
      sameChars=0;
      temp=dfa[0][i];
      for(int q=0;q<f.length();q++)
      {
        for(int s=0; s<f.length();s++)
        {
          if(temp[q]==f[s])
          {
            sameChars++;
            break;
          }
        }
      }
      if(sameChars==f.length())
      {
        return i;
      }
    }

  }
  return -1;
}

void Mapping::setTransFun()
{
  string state1="";
  string letter="";
  string state2="";
  string tempindx="";//used to hold member of transFun array & iterate through
  string pwr1="";
  bool inside =false;
  int p=0;
  int s =0;
  int indx1=-1;//to map states
  int indx2=-1;//to map states

  for(int t=0;t<transCount;t++)//for each index in transition function array
  {

    //clearing out variables for next index
    tempindx=transFun[t];
    state1="";
    letter="";
    state2="";
    p=0;
    s=0;

    for(int i=0;i<tempindx.length();i++)//to fill out 3 variables
    {

      if(tempindx[i]=='{')//is state
      {
        s++;
        inside=true;
        continue;//skip to next index

      }
      else if(tempindx[i]=='}')//state done
      {
        inside=false;
        continue;//skip to next index
      }
      if(tempindx[i]==' '||tempindx[i]==' '||tempindx[i]=='\t')//either member of language or =/,
      {
          p++;
          continue;
      }
      if(s==1&&inside)//first state
      {
        state1 += tempindx[i];

      }
      if(p==1)//member of language
      {
        letter += tempindx[i];

      }
      if(s==2&&inside)//next state
      {
        state2+=tempindx[i];

      }



    }


    //epsilon transitions
    if(letter=="EPS")
    {
      pwr1=state1+state2;
      pwr1=stringCleaning(pwr1);
      epsilon(state1, pwr1);
      continue;
    }

    //if there's nothing wrong, just map it
    indx1=findIndx(state1);
    indx2=findIndx(state2);

    if(indx1>0&&indx2>0)//if both are values in the dfa
    {
      dfa[indx1][indx2]=letter;
    }
    else
    {
      cout << "error, values not valid\n";
    }
  }
  //check for multiple transitions
  doublesCheck();

}

void Mapping::multTrans(string st1, string input, string nextSts)
{
  int t1 = findIndx(st1);
  int t2 = findIndx(nextSts);

  if(t1>0&&t2>0)//values exist in dfa
  {
    for(int i=0;i<pwrSetSize;i++)
    {
      if(dfa[t1][i]==input)
      {
        dfa[t1][i]="";
      }
    }
    dfa[t1][t2]=input;
  }
  else
  {
    cout << "error, values not valid\n";
  }

}

void Mapping::epsilon(string fState, string pwrMember)
{
  int indx1 = findIndx(fState);
  int indx2 = findIndx(pwrMember);

  if(indx1>0&&indx2>0)//values exist in dfa
  {
    for(int i =1;i<pwrSetSize;i++)
    {
      dfa[indx2][i]=dfa[indx1][i];
      dfa[i][indx2]=dfa[i][indx1];
      dfa[indx1][i]="";
      dfa[i][indx1]="";
    }
  }
  else
  {
    cout << "error, values not valid\n";
  }
}

void Mapping::doublesCheck()
{

  string a = language[0];//ideally it would be able to be done for more inputs but i ran out of time :(
  string b = language[1];

  int aCount=0;
  int bCount=0;

  string nxtState1="";
  string nxtState2="";

  for(int i=1;i<pwrSetSize;i++)//zero index does not have language values
  {
    aCount=0;
    bCount=0;
    for(int j=1;j<pwrSetSize;j++)
    {

      if(dfa[i][j]==a)
      {
        aCount++;
        nxtState1=nxtState1+dfa[0][j];
      }
      if(dfa[i][j]==b)
      {
        bCount++;
        nxtState2=nxtState2+dfa[0][j];
      }
      if(j==pwrSetSize-1&&aCount>1)//last index per row
      {
        nxtState1=stringCleaning(nxtState1);

        multTrans(dfa[i][0], "a", nxtState1);
      }
      if(j==pwrSetSize-1&&bCount>1)
      {
        nxtState2=stringCleaning(nxtState2);
        multTrans(dfa[i][0], "b", nxtState2);
      }


    }
  }

}

string Mapping::stringCleaning(string s)
{
  string n="";
  int j=0;

  //checks indexes before it in order to tell if there's a duplicate value
  for(int i=0; i<s.length();i++)
  {
    for(j=0; j<i;j++)
    {
      if(s[i]==s[j])
      {
        break;
      }
    }
    if(j==i)
    {
      n+=s[i];
    }
  }

  return n;
}

void Mapping::outputHelper()//used to format output
{
  string temp="";
  string state="";
  string trans="";
  string n="";

  bool sameState=false;//so that a state doesn't get added more than once to newstates array


  for(int i=0;i<pwrSetSize;i++)
  {

    for(int j=0;j<pwrSetSize;j++)
    {
      if(dfa[i][j]=="a"||dfa[i][j]=="b")//not an empty index
      {
        //add state to new states with formatting
        temp=dfa[i][0];
        n="{";
        for(int s=0;s<dfa[i][0].length();s++)
        {
          n=n+temp[s];
          if(s!=temp.length()-1)
          {
            n=n+",";
          }

        }
        n=n+"}";
        if(!sameState)//so that a state does not get added more than once
        {
          newStates[newStatesCounter]=n;
          newStatesCounter++;
          sameState=true;

        }
        //add state to newTransition with formatting
        temp=dfa[0][j];
        trans += "{";
        for(int l=0;l<dfa[0][j].length();l++)
        {
          trans+=temp[l];
          if(l!=temp.length()-1)
          {
            trans+=",";
          }

        }

        trans+="}";

        newTransition[newTransCounter]=n + "," + dfa[i][j] + "="+ trans;
        newTransCounter++;

        n="";
        trans="";
        temp="";


      }
    }
    sameState=false;
  }


  //if the accept state is part of a new set of states or the start changes
  for(int q=0;q<acceptCounter;q++)
  {
    n=accept[q];
    for(int s=0;s<newStatesCounter;s++)
    {
      temp=newStates[s];
      for(int y=0;y<temp.length();y++)
      {
        if(n[0]==temp[y])
        {
          accept[q]=temp;
          q++;
          acceptCounter++;
        }
        if(startState[0]==temp[y])
        {
          startState=temp;
        }
      }
    }
  }

  n="";
  temp="";
}

void Mapping::allDone()
{
  outputHelper();
  ofstream myfile ("output.dfa");
  if(myfile.is_open())
  {
    for(int i=0;i<newStatesCounter;i++)
    {
      myfile << newStates[i]<< "\t";
    }

    myfile << "\n";

    for(int j=0;j<languageCounter;j++)
    {
      myfile << language[j] <<"\t";
    }
    myfile << "\n";
    myfile << startState << "\n";

    for(int q=0;q<acceptCounter-1;q++)
    {
        myfile << accept[q] << "\t";
    }

    myfile << "\n";

    for(int z=0;z<newTransCounter;z++)
    {
      myfile << newTransition[z] <<"\n";
    }


    myfile.close();
  }
  else
  {
    cout << "unable to open file\n";
  }
}
