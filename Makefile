#
# Auguste Brown
# Modified: 25 February, 2020
# Project 1: CalcYouLater
# Makefile: builds executables
#



##
## Put your variables and rules here.  You can use previous Makefiles
## as examples, and you can refer to the "make" documentation on the
## course Reference page.
##  --- Delete this comment and put appropriate comments in ---
CXX      = clang++
CXXFLAGS = -g3  -std=c++11 -Wall -Wextra  -Wpedantic -Wshadow
LDFLAGS  = -g3

#rule to compile CalcYouLater
CalcYouLater: main.o RPNCalc.o Datum.o DatumStack.o
	${CXX} ${LDFLAGS} -o $@ $^

#rule to compile test for DatumStack
DatumStackTest: testDatumStack.o DatumStack.o Datum.o
	${CXX} ${LDFLAGS} -o DatumStackTest testDatumStack.o DatumStack.o Datum.o

#rule to compile parser.cpp
Parser: parser.cpp
	${CXX} ${LDFLAGS} -o Parser parser.cpp

#rule to compile testRPNCalc.cpp
testRPNCalc: testRPNCalc.o RPNCalc.o Datum.o DatumStack.o
	${CXX} ${LDFLAGS} -o $@ $^

testDatumStack.o: testDatumStack.cpp DatumStack.h
main.o:   main.cpp   DatumStack.h
DatumStack.o:     DatumStack.cpp     DatumStack.h
RPNCalc.o:        RPNCalc.cpp        DatumStack.h   RPNCalc.h
testRPNCalc.o: testRPNCalc.cpp   DatumStack.h

.PHONY: clean
clean:
	rm -f CalcYouLater DatumStack.o RPNCalc.o *.dSYM./

provide:
	 provide comp15 proj1 DatumStack.h DatumStack.cpp testDatumStack.cpp \
             main.cpp RPNCalc.h RPNCalc.cpp README Datum.h Makefile  \
             testRPNCalc.cpp testRPNCalc.cyl fact.cylc


##
## Here is a rule for compiling .cyl files for use in your testing
##
%.cylc:  %.cyl
	./cylc $^
