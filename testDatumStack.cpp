//
// Auguste Brown
// Modified: 18 February, 2020
// Project 1: CalcYouLater
// testDatumStack.cpp: tests DatumStack
// Notes: Instances// where printStack() is called were commented out. To test,
//      //  make printStack() public in DatumStack.h and uncomment these.
//

#include "DatumStack.h"
#include <iostream>

using namespace std;

void testIsEmpty(DatumStack *stack);
void testClear(DatumStack *stack);
void testSize(DatumStack *stack);
void testTop(DatumStack *stack);
void testPop(DatumStack *stack);
void testPush(DatumStack *stack, Datum new_datum);

int main(){
    cout << endl << endl;
    DatumStack dstack_default; //test default constructor

    //test array constructor
    Datum data_array[3] = {Datum(3), Datum("#t"), Datum("Gus")};
    DatumStack dstack_array = DatumStack(data_array, 3);

    cout << "Testing empty stack from default constructor:\n";
    testIsEmpty(&dstack_default);
    testSize(&dstack_default);
    testPush(&dstack_array, Datum(4));
    cout << "Testing stack from array constructor:\n";
    testIsEmpty(&dstack_array);
    testSize(&dstack_array);
    testTop(&dstack_array);
    testPop(&dstack_array);
    testPush(&dstack_array, Datum(4));
    testPush(&dstack_array, Datum("Shark Meldon"));
    testPush(&dstack_array, Datum("{ 4 3 + 5 * }"));
    testClear(&dstack_array);
    testIsEmpty(&dstack_array);
    testSize(&dstack_array);
    return 0;
}

// Tests the isEmpty() function in DatumStack
void testIsEmpty(DatumStack *stack){
    if (stack->isEmpty())
        cout << "Stack is empty\n";
    else
        cout << "Stack is not empty\n";
}

// Tests the clear() function in DatumStack
void testClear(DatumStack *stack){
    cout << "––Clearing stack:\n";
    stack->clear();
    //stack->printStack();
}

// Tests the size() function in DatumStack
void testSize(DatumStack *stack){
    cout << "-–Size of stack: " << stack->size() << endl;
}

// Tests the top() function in DatumStack
void testTop(DatumStack *stack){
    cout << "-–Element on top of the stack: " << stack->top().toString()
         << endl;
}

// Tests the pop() function in DatumStack
void testPop(DatumStack *stack){
    cout << "-–Removing top of stack:\n";
    stack->pop();
    //stack->printStack();
}

// Tests the push() function in DatumStack
void testPush(DatumStack *stack, Datum new_datum){
    cout << "-–Pushing " << new_datum.toString() << " onto the stack:\n";
    stack->push(new_datum);
    //stack->printStack();
}