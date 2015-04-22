All: LibraryCrawl
LibraryCrawl: LibraryCrawl.o Level.o
	g++ -lSDL2 -lSDL2_image -O0 -g3 Level.o LibraryCrawl.o -o LibraryCrawl
LibraryCrawl.o: LibraryCrawl.cpp
	g++ -lSDL2 -lSDL2_image -O0 -g3 -c LibraryCrawl.cpp
Level.o: Level.cpp Level.h
	g++ -lSDL2 -lSDL2_image -O0 -g3 -c Level.cpp
	
clean:
	-rm *.o LibraryCrawl
	
