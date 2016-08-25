#ifndef MAP_H
#define MAP_H

#include "position.h"
#include "character.h"
#include "constants.h"
class Map{
private:
	int length;				// the scale of the map, customized by player
	int width;				// the scale of the map, customized by player
	Position** atlas;		// pointer to arrays of positions
public:
	Map(int length,int width);
	Map();
	void SetMap(int length,int width);
	~Map();																// for destruction of atlas and pointers		
	void PlaceCharacter(Character* character,int x,int y);				// connect characters with positions
	void MoveCharacter(Character* character,int x,int y);				// move character to (x,y)
	void Show();														// simple display
	void ShowMove(Character* character,int target_x,int target_y);		// display move patterns of characters with cursor
	void ShowAttack(Character* character,int target_x,int target_y);	// display attack patters of characters with cursor
	int GetLength();													// return map length
	int GetWidth();														// return map width
	Character* IsOccupied(int x,int y);									// return character pointer if occupied, NULL if not
};
#endif

