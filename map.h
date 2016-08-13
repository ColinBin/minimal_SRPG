#ifndef MAP_H
#define MAP_H

#include "position.h"
#include "character.h"
#include "constants.h"
class Map{
private:
	int length;
	int width;
	Position** atlas;
public:
	Map(int length,int width);
	Map();
	void SetMap(int length,int width);
	~Map();
	void PlaceCharacter(Character* character,int x,int y);
	void MoveCharacter(Character* character,int x,int y);
	void Show();
	void ShowMove(Character* character,int target_x,int target_y);
	void ShowAttack(Character* character,int target_x,int target_y);
	int GetLength();
	int GetWidth();
	Character* IsOccupied(int x,int y);
};
#endif

