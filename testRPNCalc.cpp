//
// Auguste Brown
// Modified: 25 February, 2020
// Project 1: CalcYouLater
// testRPNCalc.cpp: tests RPNCalc class
// NOTE: Many of the rstring functionality is tested through testRPNCalc.cyl
//

#include "RPNCalc.h"
#include <iostream>

using namespace std;

void testPush(RPNCalc *calc, string input);
void testPrint(RPNCalc *calc);
void testClear(RPNCalc *calc);
void testDrop(RPNCalc *calc);
void testDuplicate(RPNCalc *calc);
void testSwap(RPNCalc *calc);
void testEqual(RPNCalc *calc);
void testComparisons(RPNCalc *calc);
void testInverseBool(RPNCalc *calc);

int main(){
    RPNCalc CalcYouLater;

    testPush(&CalcYouLater, "3");
    testPush(&CalcYouLater, "#t");
    testPrint(&CalcYouLater);
    testClear(&CalcYouLater);
    testPush(&CalcYouLater, "3");
    testPush(&CalcYouLater, "10");
    testDrop(&CalcYouLater);
    testDuplicate(&CalcYouLater);
    testPush(&CalcYouLater, "20");
    testSwap(&CalcYouLater);
    testEqual(&CalcYouLater);
    testComparisons(&CalcYouLater);
    testInverseBool(&CalcYouLater);
}

// Tests the push functionality
void testPush(RPNCalc *calc, string input){
    cout << "Pushing " << input << " on stack\n";
    calc->handleInput(input, cin);
}

// Tests the print functionality
void testPrint(RPNCalc *calc){
    calc->print();
}

// Tests the clear functionality
void testClear(RPNCalc *calc){
    cout << "Clearing stack\n";
    calc->clear();
}

// Tests the drop functionality
void testDrop(RPNCalc *calc){
    cout << "Removing top of stack\n";
    calc->drop();
}

// Tests the dup functionality
void testDuplicate(RPNCalc *calc){
    cout << "Duplicating top of stack\n";
    calc->duplicate();
}

// Tests the swap functionality
void testSwap(RPNCalc *calc){
    cout << "Swapping top two elements of stack\n";
    calc->swap();
}

// Tests the == functionality
void testEqual(RPNCalc *calc){
    cout << "Checking == of top two elements\n";
    calc->checkEqual();
    testPrint(calc);
}

// Tests the >, <, >=, <= functionality
void testComparisons(RPNCalc *calc){
    calc->handleInput("3", cin);
    calc->handleInput("4", cin);
    cout << "Checking 3 > 4\n";
    calc->comparisonHandler(">");
    testPrint(calc);

    calc->handleInput("3", cin);
    calc->handleInput("4", cin);
    cout << "Checking 3 < 4\n";
    calc->comparisonHandler("<");
    testPrint(calc);

    calc->handleInput("3", cin);
    calc->handleInput("4", cin);
    cout << "Checking 3 >= 4\n";
    calc->comparisonHandler(">=");
    testPrint(calc);

    calc->handleInput("3", cin);
    calc->handleInput("4", cin);
    cout << "Checking 3 <= 4\n";
    calc->comparisonHandler("<=");
    testPrint(calc);
}

// Tests the not functionality
void testInverseBool(RPNCalc *calc){
    cout << "Inversing bool on top of stack\n";
    calc->inverseBool();
    testPrint(calc);
}
