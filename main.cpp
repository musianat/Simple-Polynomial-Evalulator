// Nathan Musial ntm160030 CS 1337.002 Smith 11/15/16
#include <iostream>
#include "LinkedList.h"
#include "LinkedList.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ctype.h>
#include <cmath>
#include <iomanip>
using namespace std;
void readInFile(string,LinkedList);

int main()
{
     LinkedList l; //linked list that hold the equation
     readInFile("poly.txt",l); //reads in file

}

void readInFile(string filename,LinkedList l)
{
    ifstream file;
    ofstream outfile;
    outfile.open("answers.txt"); //open output file
    file.open(filename,ios::binary);
    if(!file)
    {
        cout<< "can't open file";
        return;
    }
    string line="";
    double fnum=0;
    double exp=0;
    char beg=' ';
    double coef;
//    bool negative=false;

    while(getline(file,line)) //goes through line by line
    {
        stringstream ss(line);
        ss.ignore(2,'(');
        ss >> fnum;
        ss.ignore(2,'='); // ignores up to equal sign
       // char c;
        while(ss)
            {
                exp=0;
                coef=0;
                beg=' ';

        ss >> beg; //checks first charactewre
        if(beg==' ') // could break reading in file
            break;
        if(isdigit(beg)) //if first charcter is a digit
        {
        ss.seekg(-1,ios::cur);
        ss >> coef;
        }
        else if(beg=='x') // if no coeficient
            coef=1;
        else if(beg=='-') // if negative in front
        {
            char test=ss.get();
            //cout<<" Test "<<test <<endl;
            if(ss.get()=='x'&&!isdigit(test)) // edge case for negative
            {

                ss.seekg(-1,ios::cur);
                coef=-1;
            }

            else // normal negative
            {
            ss.seekg(-1,ios::cur);
            if(isdigit(test))
               ss.seekg(-1,ios::cur);
            ss >> coef;
                 coef=coef*-1;
            }
            //coef=coef*-1;
        }
        else if(beg=='+') // if plus in front
        {
            ss.get();
            if(ss.get()=='x') //if it is only X
            {
                ss.seekg(-1,ios::cur);
                coef=1;
            }
            else //read in coefficient
            {
            ss.seekg(-1,ios::cur);
            ss >> coef;
            }
        }

        if(ss.get()=='x') //if there is an exponent
        {
            if(ss.get()=='^')
                 ss >> exp;
            else
                exp=1;
        }
        else{
            exp=0; //no ^ so exponent is zero
            ss.get();
        }
            l.AddNode(coef,exp); // adds node
          //  cout <<fnum << " "<<beg<< " " <<coef <<" "<<exp <<endl;

        }

     //  cout<<"f("<<fnum<<") =";
      // l.PrintToScreen();
       l.PrintToFile(fnum, outfile);

      // cout <<"= "<< fixed << setprecision(3)<< l.evaluateList(fnum) << setprecision(6) << endl;
      // cout.unsetf(ios_base::fixed);
       l.deleteList(); // deltes list to use again
      //  cout << line<< endl;
    }

    outfile.close();
    file.close();

}
