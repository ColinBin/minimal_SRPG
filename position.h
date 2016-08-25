#ifndef POSITION_H
#define POSITION_H
#include "character.h"
class Character;
class Position{
private:
	int x;					// actual x coordinate
	int y;					// actual y coordinate
	Character* character;	// connected character pointer
public:
	Position();
	Position(int x,int y);
	int GetX();									// return x
	int GetY();									// return y
	void SetXY(int x,int y);					// set position
	void SetCharacter(Character* character);	// connect character
	Character* GetCharacter();					// return connected character
	void UnsetCharacter();						// unlink character from the position
};
#endif
