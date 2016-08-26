srpg_game: main.o game.o map.o character.o position.o constants.h character.h
	g++ main.o game.o map.o character.o position.o -o srpg_game
character.o: character.cpp character.h constants.h
	g++ -c character.cpp -o character.o
position.o: position.cpp position.h constants.h
	g++ -c position.cpp -o position.o
main.o: main.cpp constants.h
	g++ -c main.cpp -o main.o
map.o: map.cpp map.h character.h position.h constants.h
	g++ -c map.cpp -o map.o
game.o: game.cpp map.h constants.h
	g++ -c game.cpp -o game.o
.PHONY: clean
clean:
	-rm srpg_game main.o game.o map.o character.o position.o
