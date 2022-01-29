//
// Auguste Brown
// Modified: 25 February, 2020
// Project 1: CalcYouLater
// RPNCalc.h: defines RPNCalc class
//

#ifndef RPNCALC_H
#define RPNCALC_H

#include "DatumStack.h"
#include <cstdio>

class RPNCalc{
    public:
        RPNCalc();
        void handleInput(std::string input, std::istream &current_stream);
        void run();
        void print();
        void clear();
        void drop();
        void duplicate();
        void swap();
        void checkEqual();
        void comparisonHandler(std::string input);
        void inverseBool();
        void exec();
        void file();
        void conditional();

    private:
        DatumStack stack;

        bool got_int(std::string s, int *resultp);
        std::string parseRString(std::istream &input);
        void runLoop(std::istream &input);
        void commandHandler(std::string input);
        void operationHandler(std::string input);
        bool checkEmpty();
};

#endif