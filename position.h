#ifndef POSITION_H
#define POSITION_H
#include "character.h"
class Character;
class Position{
private:
	int x;
	int y;
	Character* character;
public:
	Position();
	Position(int x,int y);
	int GetX();
	int GetY();
	void SetXY(int x,int y);
	void SetCharacter(Character* character);
	Character* GetCharacter();
	void UnsetCharacter();
};
#endif
