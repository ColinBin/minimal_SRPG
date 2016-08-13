#ifndef GAME_H
#define GAME_H

#include "map.h"
class Game{
private:
	Character** heap;
	Character** defender;
	Character** invader;
	Map* map;
	int defender_count;
	int invader_count;
	int defender_kill;
	int invader_kill;
public:
	Game();
	Game(int defender_count,int invader_count,int map_length,int map_width);
	void Initialize();
	Character* NextTurnCharacter();
	void PlaceCharacters();
	void Start();
	void Round(Character* character);
	void Move(Character* character);
	void Attack(Character* character);
	void ShowStatus();
	void BuildHeap();
	void AdjustHeap(int i,int heap_size);
};

#endif
