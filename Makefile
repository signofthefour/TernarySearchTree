all: trie

DEFS = -DUSE_SOME_DEF

trie: trie.o
	g++ trie.o -std=c++11 -o tst $(DEFS)
trie.o: Trie.cpp
	g++ -c Trie.cpp -o trie.o -std=c++11 $(DEFS)
clean:
	rm *.o trie