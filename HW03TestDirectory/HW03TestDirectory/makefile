GPP = g++ -O3 -Wall

UTILS = ../../Utilities

A = Main.o
E = EditDistance.o
S = Scanner.o
SL = ScanLine.o
U = Utils.o

Aprog: $A $E $S $(SL) $U
	$(GPP) -o Aprog $A $E $S $(SL) $U

Main.o: Main.h Main.cpp
	$(GPP) -c Main.cpp

EditDistance.o: EditDistance.h EditDistance.cpp
	$(GPP) -c -DEBUG EditDistance.cpp

Scanner.o: $(UTILS)/Scanner.h $(UTILS)/Scanner.cpp
	$(GPP) -c $(UTILS)/Scanner.cpp

ScanLine.o: $(UTILS)/ScanLine.h $(UTILS)/ScanLine.cpp
	$(GPP) -c $(UTILS)/ScanLine.cpp

Utils.o: $(UTILS)/Utils.h $(UTILS)/Utils.cpp
	$(GPP) -c $(UTILS)/Utils.cpp
