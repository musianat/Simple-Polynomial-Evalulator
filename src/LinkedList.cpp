// Nathan Musial 11/15/16
#include "LinkedList.h"
#include "Node.h"
#include <iostream>
#include <stdio.h>
#include <cmath>
#include <fstream>
#include <iomanip>

using namespace std;
LinkedList::LinkedList()
{
    head=nullptr;
    //head->setCoefficient(0);
    //head->setExponent(0);
    //ctor
}

void LinkedList::deleteList() //recursively deletes the linked list
{
    deleteLink(head);
}
node* LinkedList::deleteLink(node* ptr)
{

    if(ptr)
    {

        node* hold=ptr; //hold pointer to node being delted
        head=ptr->getNext(); // moves list to next node
        delete hold; // deletes node
        return deleteLink(ptr->getNext());

    }
    else return ptr;
}
node* LinkedList::printRecursive(node* ptr)
{

    char conCat=' ';
        if (ptr ==nullptr)
            return ptr;

               double coef=ptr->getCoefficient(); //gets values
                double exp=ptr->getExponent();
                if(coef>0)
                    conCat='+'; // if starts with +
                if(ptr==head)
                    conCat=' '; //if starts with a blank
                if(coef<0){
                    conCat='-'; //if starts with a -
                    coef*=-1;

                }
                if(conCat==' ') //if blank
                    cout<<conCat;
                else if(conCat=='-'&&ptr==head) //if negative and first node
                {
                    cout << " "<<conCat;
                }
                else // add a space
                    cout << conCat <<" ";
                if(exp==0) // if there is no X
                {
                    cout  << coef <<  " "; //
                }
                else if(coef==1&&exp==1) // if it is just X
                {
                    cout << "x ";
                }
                 else if(exp==1) //if it is a coeficient and X
                {
                    cout << coef << "x "; //
                }
                else if(coef==1) // if coeficeint is one
                {
                    cout  << "x^"  << exp << " ";
                }
                else
                    cout << coef << "x^"  << exp << " ";

            return printRecursive(ptr->getNext());

}

void LinkedList::PrintToScreen() // print out linked list to screen
{
    printRecursive(head);
           // counter++; // goes to next node
}
void LinkedList::PrintToFile(double fnum,ofstream  & outfile)
{
    outfile<<"f("<<fnum<<") ="; // print first half of equation to file
     recursiveFilePrint(head, outfile);
            outfile <<"= "<< fixed << setprecision(3)<< evaluateList(fnum) <<setprecision(6) << endl;//formats for printing
            outfile.unsetf(ios_base::fixed); // fixes printing
}
node* LinkedList::recursiveFilePrint(node* ptr,ofstream  & outfile)
{
        char conCat=' ';
        if (ptr ==nullptr)
            return ptr;

               double coef=ptr->getCoefficient();
                double exp=ptr->getExponent();
                if(coef>0)
                    conCat='+'; // if positive
                if(ptr==head)
                    conCat=' '; // if first
                if(coef<0){
                    conCat='-'; // if negative
                    coef*=-1;
                    if(ptr==head)
                        outfile<<" ";
                }
                if(conCat==' ') //if head
                    outfile<<conCat;
                     else if(conCat=='-'&&ptr==head) //if head and negative
                {
                    outfile << " "<<conCat;
                }
                else
                    outfile << conCat <<" ";
                if(exp==0) //if no X
                {
                    outfile  << coef <<  " "; //
                }
                else if(coef==1&&exp==1) //if just X
                {
                    outfile << "x ";
                }
                 else if(exp==1) //if X and coefficient
                {
                    outfile << coef << "x "; //
                }
                else if(coef==1) //if coefficient equals one
                {
                    outfile  << "x^"  << exp << " ";
                }
                else //normal
                    outfile << coef << "x^"  << exp << " ";

            return recursiveFilePrint(ptr->getNext(),outfile);
}
void LinkedList::AddNode(double coef,double exp)
{
    insertNode(head,coef,exp);
}

node* LinkedList::insertNode(node* ptr,double coef, double exp) // adds nodes to linked list
{


	node* hold = new node; // creates new node
	hold->setExponent(exp); // inputs data into the node
	hold->setCoefficient(coef);
	hold->setNext(nullptr);
	//cout << hold->arabic << endl;
	//cout <<head<< endl;
	if(!head){ // if this is the first node
        head=hold; // make the new node the first node
        return head;
	}
	if(ptr->getExponent()==exp)
    {
        ptr->setCoefficient(ptr->getCoefficient()+coef);
        return ptr;
    }

	if(head->getExponent()< exp)
    {
        hold->setNext(head);
        head=hold;
        return hold;
    }
    if(ptr->getNext() != nullptr){ // move to last node
			if(ptr->getNext()->getExponent() < exp)
            {
                hold->setNext(ptr->getNext());
                ptr->setNext(hold); //adds new node to last node
                return hold;
            }
			//ptr=ptr->getNext();
			return insertNode(ptr->getNext(),coef,exp);
    }

		ptr->setNext(hold);
		return ptr; //adds new node to last node

	return hold;

}

double LinkedList::evaluateList(double fnum)
{
    node* ptr=head; // moves to first node
        double result=0.0;
        while(ptr !=NULL)
            {
             result+=ptr->getCoefficient()* pow((fnum) , ptr->getExponent()); // evaluates the node
            ptr=ptr->getNext();

           // counter++; // goes to next node
            }
            result=round(result*1000.0)/1000.0;
            //cout<<ceil(result)<< endl;
            return result;
}
