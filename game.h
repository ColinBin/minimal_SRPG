#ifndef GAME_H
#define GAME_H

#include "map.h"
class Game{
private:
	Character** heap;			// maintain a (min)heap to find a character for each round (according to characters' cooldown)
	Character** defender;		// defender array
	Character** invader;		// invader array
	Map* map;					// the map
	int defender_count;			// the number of defender,input by user
	int invader_count;			// the number of invader,input by user
	int defender_kill;			// updated after each round, the number of invader defeated by defender
	int invader_kill;			// updated after each round, the number of defender defeated by invader
public:
	Game();
	~Game();
	Game(int defender_count,int invader_count,int map_length,int map_width);	
	void Initialize();										// initilize, prompt players to input info about characters				
	Character* NextTurnCharacter();							// find the next character from the heap
	void PlaceCharacters();									// part of the initialization
	void Start();											// overall logic is find the character for each turn, move, attack
	void Round(Character* character);						// simply call Move and Attack
	void Move(Character* character);						// player input move command and get validated
	void Attack(Character* character);						// player input attack command and get validated
	int HandleCommand(const int,const int,int&,int&);		// subroutine for Move and Attack handling user command input
	void ShowStatus();										// simply display detailed information about characters 
	void BuildHeap();										// part of the initialization
	void AdjustHeap(int i,int heap_size);					// subroutine of building the heap and fetching the next character
};

#endif
