//
// Auguste Brown
// Modified: 25 February, 2020
// Project 1: CalcYouLater
// DatumStack.h: defines DatumStack class
//

#ifndef DATUMSTACK_H
#define DATUMSTACK_H

#include "Datum.h"
#include <vector>

class DatumStack{
    public:
        DatumStack();
        DatumStack(Datum elements[], int size);
        bool isEmpty();
        void clear();
        int size();
        Datum top();
        void pop();
        void push(Datum element);
    private:
        std::vector<Datum> stack;

        void checkEmpty();
        void printStack();
};

#endif