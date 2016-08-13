#ifndef CHARACTER_H
#define CHARACTER_H
#include "position.h"
#include "constants.h"
#include <string>
using namespace std;
class Position;
class Character{
protected:
	string name;		//character name
	int hp;				//hit-point
	Position* position;	//pointer to its position
	bool is_alive;		//flag
	Career career;		//enum CAREER
	Camp camp;			//defender or invader
	int att;			//attack value
	int def;			//defense value
	int mob;			//mobility
	int range;			//attack range
	int cooldown;		//cooldown time
	

public:
	Character(string name);
	Character(string name,bool is_alive,Camp camp,Career career);
	void SetBasic(Career career);
	void SetPosition(Position* position);
	Position* GetPosition();
	Career GetCareer();
	Camp GetCamp();
	int GetHP();
	int GetMob();
	int GetAtt();
	int GetDef();
	int GetRange();
	bool GetIsAlive();
	int GetCooldown();
	string GetName();
	void SetCooldown(int difference);
	void ResetCooldown();
	int TakeDamage(int damage);
};

#endif
