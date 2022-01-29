//
// Auguste Brown
// Modified: 25 February, 2020
// Project 1: CalcYouLater
// RPNCalc.cpp: implements the RPNCalc class
//

#include "RPNCalc.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

RPNCalc::RPNCalc(){

}

// Name: got_int
// Parameters: string s, int *resultp
// Returns: integer value of string s, if s can be represented as an int
// Effects: Nothing
bool RPNCalc::got_int(string s, int *resultp){
    return sscanf(s.c_str(), "%d", resultp) == 1;
}

// Name: parseRString
// Parameters: istream &input
// Returns: string representing complete RString
// Does: Takes input from a stream and returns after a closing "}" is input
string RPNCalc::parseRString(istream &input){
    string rstring = "{";
    string current; //holds value of current input

    input >> current;
    while(current != "}"){
        if (current == "{") //if a nested RString
            rstring = rstring + " " + parseRString(input);
        else
            rstring = rstring + " " + current;

        input >> current; //get next input from stream
    }

    rstring += " }";
    return rstring;
}

// Name: run
// Purpose: Control input and output of CalcYouLater
// Parameters: None
// Returns: None
// Effects: None
void RPNCalc::run(){
    runLoop(cin);
    cerr << "Thank you for using CalcYouLater.\n";
}

// Name: handleInput
// Purpose: Takes input and performs the appropriate operations
// Parameters: string input, istream &current_stream
// Returns: None
// Effects: May change size of stack or output messages
void RPNCalc::handleInput(string input, istream &current_stream){
    int value;
    if (got_int(input, &value)){ //if input is an int
        stack.push(Datum(value));
    }
    else if (input == "#t"){ //if input is a true bool
        stack.push(Datum(true));
    }
    else if (input == "#f"){ //if input is a false bool
        stack.push(Datum(false));
    }
    else if (input == "{"){ //if input is an rstring
        stack.push(Datum(parseRString(current_stream)));
    }
    else { //otherwise input is a command, or unimplemented
        commandHandler(input);
    }
}

// Name: commandHandler
// Purpose: Takes command input and calls the corresponding command function
// Parameters: string input
// Returns: None
// Effects: May change size of stack or output messages
void RPNCalc::commandHandler(string input){
    if (input == "not")
        inverseBool();
    else if (input == "print")
        print();
    else if (input == "clear")
        clear();
    else if (input == "drop")
        drop();
    else if (input == "dup")
        duplicate();
    else if (input == "swap")
        swap();
    else if (input == "+" or input == "-" or input == "*" or input == "/" 
             or input == "mod")
        operationHandler(input);
    else if (input == "==")
        checkEqual();
    else if (input == ">" or input == "<" or input == ">=" or input == "<=")
        comparisonHandler(input);
    else if (input == "exec")
        exec();
    else if (input == "file")
        file();
    else if (input == "if")
        conditional();
    else{
        cerr << input << ":  unimplemented\n";
    }
}

// Name: inverseBool
// Purpose: Inverses the top of the stack if it is a bool
// Parameters: None
// Returns: None
void RPNCalc::inverseBool(){
    if (stack.top().isBool()){
        bool old_data = stack.top().getBool();
        stack.pop();
        stack.push(Datum(!old_data));
    }
    else {
        cerr << "Top is not a bool you fuckwad\n"; //TODO
    }

}

// Name: print
// Purpose: Prints the top of the stack to the console
// Parameters: None
// Returns: None
void RPNCalc::print(){
    if (checkEmpty())
        return; //leave the function if the stack is empty
    else
        cout << stack.top().toString() << endl;
}

// Name: clear
// Purpose: Clears the stack
// Parameters: None
// Returns: None
// Effects: All Datums are removed from the stack
void RPNCalc::clear(){
    stack.clear();
}

// Name: clear
// Purpose: Removes the top element on the stack
// Parameters: None
// Returns: None
void RPNCalc::drop(){
    if (checkEmpty())
        return; //leave the function if the stack is empty
    else
        stack.pop();
}

// Name: duplicate
// Purpose: Creates a copy of the element on top of the stack and adds it to
//          the stack
// Parameters: None
// Returns: None
void RPNCalc::duplicate(){
    if (checkEmpty())
        return; //leave the function if the stack is empty
    else
        stack.push(stack.top());
}

// Name: swap
// Purpose: Switches the places of the top two elements of the stack
// Parameters: None
// Returns: None
void RPNCalc::swap(){
    if (checkEmpty()) return; //leave the function if the stack is empty

    Datum old_top = stack.top(); // get first element
    stack.pop();

    if (checkEmpty()) return; //leave the function if the stack is empty

    Datum old_bottom = stack.top(); //get second element
    stack.pop();

    stack.push(old_top);
    stack.push(old_bottom);
}

// Name: operationHandler
// Purpose: Handles any situation where mathematical operations are entered
// Parameters: string input
// Returns: None
// Effects: Combines the top two integers on the stack into the appropriate
//          result integer
void RPNCalc::operationHandler(string input){
    if (checkEmpty()) return; //leave the function if the stack is empty

    Datum old_top = stack.top();
    stack.pop();

    if (!old_top.isInt()){ //check if elements are int
        cerr << "Error: datum_not_int\n";
        return;
    }
    if (checkEmpty()) return; //leave the function if the stack is empty

    Datum old_bottom = stack.top();
    stack.pop();
    if (!old_bottom.isInt()){ //check if elements are int
        cerr << "Error: datum_not_int\n";
        return;
    }

    if (input == "+")
        stack.push(Datum(old_bottom.getInt() + old_top.getInt()));
    else if (input == "-")
        stack.push(Datum(old_bottom.getInt() - old_top.getInt()));
    else if (input == "*")
        stack.push(Datum(old_bottom.getInt() * old_top.getInt()));
    else if (input == "/")
        stack.push(Datum(old_bottom.getInt() / old_top.getInt()));
    else if (input == "mod")
        stack.push(Datum(old_bottom.getInt() % old_top.getInt()));
}

// Name: checkEmpty
// Purpose: Checks if the stack is empty
// Parameters: None
// Returns: True if stack is empty, false otherwise
// Effects: Prints a message to the console if stack is empty
bool RPNCalc::checkEmpty(){
    if (stack.isEmpty()){
        cerr << "Error: empty_stack\n";
        return true;
    }
    else
        return false;
}

// Name: checkEqual
// Purpose: Pushes the boolean result of comparing the top to elements of the
//          stack 
// Parameters: None
// Returns: None
// Effects: Removes the previous top two elements and replaces them with a bool
void RPNCalc::checkEqual(){
    //get first element
    if (checkEmpty()) return; //leave the function if the stack is empty
    Datum old_top = stack.top();
    stack.pop();
    //get second element
    if (checkEmpty()) return; //leave the function if the stack is empty
    Datum old_bottom = stack.top();
    stack.pop();
    stack.push(Datum(old_bottom == old_top));
}

// Name: comparisonHandler
// Purpose: Handles any situation where >, >=, <, <= are entered
// Parameters: None
// Returns: None
// Effects: Combines the top two integers on the stack into the appropriate
//          result bool
// Note: Does not work on non integers
void RPNCalc::comparisonHandler(std::string input){
    //get first element
    if (checkEmpty()) return; //leave the function if the stack is empty
    Datum old_top = stack.top();
    stack.pop();
    //get second element
    if (checkEmpty()) return; //leave the function if the stack is empty
    if (!old_top.isInt() or !stack.top().isInt()){ //check if elements are int
        cerr << "Error: datum_not_int\n";
        return;
    }
    Datum old_bottom = stack.top();
    stack.pop();

    if (input == "<")
        stack.push(Datum(old_bottom < old_top));
    else if (input == ">")
        stack.push(Datum(old_top < old_bottom));
    else if (input == "<=")
        stack.push(Datum(old_bottom < old_top or old_bottom == old_top));
    else if (input == ">=")
        stack.push(Datum(old_top < old_bottom or old_bottom == old_top));
}

// Name: exec
// Purpose: Removes the top elements of the stack (an rstring) and executes
//          its contents
// Parameters: None
// Returns: None
// Effects: Combines the top two integers on the stack into the appropriate
//          result bool
// Note: Does not work on non rstrings
void RPNCalc::exec(){
    if (checkEmpty()) return; //leave the function if the stack is empty

    Datum executed = stack.top();
    drop();
    if (!executed.isRString()){
        cerr << "Error: cannot execute non rstring\n";
        return;
    }
    string rstring = executed.getRString();

    //turn into a stringstream, removing the curly braces on the ends
    istringstream rstringstream(rstring.substr(2, rstring.size() - 3));
    
    runLoop(rstringstream);
}

// Name: file
// Purpose: Runs the contents of a file as an input stream
// Parameters: None
// Returns: None
// Effects: Changes the stack however the file tells it to
// Note: Does not work on non rstrings
void RPNCalc::file(){
    //first perform checks to make sure a valid rstring is on top if stack
    if (checkEmpty()) return;
    if (!stack.top().isRString()){
        cerr << "Error: file operand not rstring\n";
        return;
    }

    string rstring = stack.top().getRString();
    drop(); //remove file name rstring from stack
    string filename = rstring.substr(2, rstring.size() - 4);
    
    ifstream input;
    input.open(filename);
    if (not input.is_open()){
        cerr << "Unable to read " << filename << endl;
        return;
    }

    runLoop(input);
}

// Name: conditional
// Purpose: Performs if conditional functionality
// Parameters: None
// Returns: None
// Effects: Pops 3 elements off the stack and executes the appropriate rstring
// Note: Only works if first two items on stack are rstrings and 3rd item
//       is a boolean
void RPNCalc::conditional(){
    if (checkEmpty()) return;
    if (!stack.top().isRString()){
        cerr << "Error: expected rstring in if branch\n";
        return;
    }
    string false_case = stack.top().getRString();
    drop();
    if (checkEmpty()) return;
    if (!stack.top().isRString()){
        cerr << "Error: expected rstring in if branch\n";
        return;
    }
    string true_case = stack.top().getRString();
    drop();

    if (checkEmpty()) return;
    if (!stack.top().isBool()){
        cerr << "Error: expected boolean in if test\n";
        return;
    }
    bool test_condition = stack.top().getBool();
    drop();
    istringstream executed;
    if (test_condition)
        executed = istringstream(true_case.substr(2, true_case.size() - 3));
    else
        executed = istringstream(false_case.substr(2, false_case.size() - 3));

    runLoop(executed);
}

// Name: runLoop
// Purpose: Helper function which can run the control loop from any istream
// Parameters: istream &input
// Returns: None
// Effects: Runs the control loop
void RPNCalc::runLoop(istream &input){
    string command;
    input >> command;
    while (!input.eof() or command == "quit"){
        if (command == "quit"){
            cerr << "Thank you for using CalcYouLater.\n";
            exit(1);
        }
        handleInput(command, input);
        input >> command;
    }
}
