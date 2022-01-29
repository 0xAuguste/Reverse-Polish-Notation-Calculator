//
// Auguste Brown
// Modified: 18 February, 2020
// Project 1: CalcYouLater
// DatumStack.cpp: implements DatumStack class
// Notes: to test, make printStack() public in DatumStack.h
//

#include "DatumStack.h"
#include <iostream>

using namespace std;

// Default constructor. The vector, stack, is automatically initialized, so
// this constructor does need to do anything
DatumStack::DatumStack(){
    // Vector is initialized
}

// Constructor. Takes an array of Datum objects and initilizes a DatumStack
// with the last element of the array on the top of the stack
// NOTE: int size must be the actual size of the input array
DatumStack::DatumStack(Datum elements[], int size){
    for (int i = 0; i < size; i++){
        push(elements[i]);
    }
}

// Name: isEmpty
// Parameters: None
// Returns: True if stack is empty, false otherwise
// Does: Nothing
bool DatumStack::isEmpty(){
    return stack.empty();
}

// Name: size
// Parameters: None
// Returns: int size of the stack
// Does: Nothing
int DatumStack::size(){
    return stack.size();
}

// Name: top
// Parameters: None
// Returns: Datum on top of the stack
// Does: Nothing
Datum DatumStack::top(){
    checkEmpty();

    return stack[size() - 1];
}

// Name: pop
// Parameters: None
// Returns: Nothing
// Does: Removes top elements of the stack
void DatumStack::pop(){
    checkEmpty();
    stack.pop_back();
}

// Name: push
// Parameters: Datum element to add to stack
// Returns: Nothing
// Does: Adds parameter element to the top of the stack
void DatumStack::push(Datum element){
    stack.push_back(element);
}

// Name: clear
// Parameters: None
// Returns: Nothing
// Does: Removes all elements from the stack
void DatumStack::clear(){
    stack.clear();
}

// Name: checkEmpty
// Parameters: None
// Returns: Nothing
// Does: Helper function which throws a runtime error if the stack is empty
void DatumStack::checkEmpty(){
    if (isEmpty())
        throw runtime_error("empty_stack");
}

// Name: printStack
// Parameters: None
// Returns: Nothing
// Does: Prints the stack for debugging purposes
// Notes: Private function, just for debugging
void DatumStack::printStack(){
    for (int i = size() - 1; i >= 0; i--){
        cout << stack[i].toString() << endl;
    }
}