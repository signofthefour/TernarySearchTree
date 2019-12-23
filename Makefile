all: tst

DEFS = -DUSE_SOME_DEF

tst: tst.o
	g++ tst.o -std=c++11 -o tst $(DEFS)
tst.o: TST.cpp
	g++ -c TST.cpp -o tst.o -std=c++11 $(DEFS)
clean:
	rm *.o tst