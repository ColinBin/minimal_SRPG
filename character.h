#ifndef CHARACTER_H
#define CHARACTER_H
#include "position.h"
#include "constants.h"
#include <string>
using namespace std;
class Position;
class Character{
protected:
	string name;		// character name
	int hp;				// hit-point
	Position* position;	// pointer to its position
	bool is_alive;		// flag
	Career career;		// enum CAREER
	Camp camp;			// defender or invader
	int att;			// attack value
	int def;			// defense value
	int mob;			// mobility
	int range;			// attack range
	int cooldown;		// cooldown time
	

public:
	Character(string name);
	Character(string name,bool is_alive,Camp camp,Career career);
	void SetBasic(Career career);						
	void SetPosition(Position* position);		// connect characters with positions in the map
	Position* GetPosition();					// return the character's position
	Career GetCareer();							// return the career of the career
	Camp GetCamp();								// return the camp
	int GetHP();								// return HP
	int GetMob();								// return mob
	int GetAtt();								// return att
	int GetDef();								// return def
	int GetRange();								// return attack range
	bool GetIsAlive();							// return true if is alive
	int GetCooldown();							// return cooldown time
	string GetName();							// return name
	void SetCooldown(int difference);			// add difference to current cooldown
	void ResetCooldown();						// reset cooldown to the career's cooldown
	bool IsInMoveRange(int,int);				// return true if the position is accessible
	bool IsInAttackRange(int,int);				// return true if the position is within attack range
	int TakeDamage(int damage);					// substract damage from hp and return the new hp
};

#endif
