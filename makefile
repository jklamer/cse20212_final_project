All: LibraryCrawl
LibraryCrawl: LibraryCrawl.o Level.o Person.o Player.o
	g++ -lSDL2 -lSDL2_image -lSDL2_ttf -O0 -g3 Level.o Person.o Player.o LibraryCrawl.o -o LibraryCrawl
LibraryCrawl.o: LibraryCrawl.cpp
	g++ -lSDL2 -lSDL2_image -lSDL2_ttf -O0 -g3 -c LibraryCrawl.cpp
Level.o: Level.cpp Level.h Person.o
	g++ -lSDL2 -lSDL2_image -lSDL2_ttf -O0 -g3 -c Level.cpp
Person.o: Person.cpp Person.h
	g++ -c Person.cpp
Player.o: Player.cpp Player.h Person.o
	g++ -c Player.cpp	
clean:
	-rm *.o LibraryCrawl
	
