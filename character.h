#ifndef CHARACTER_H
#define CHARACTER_H
#include <iostream>
#include "position.h"
#include "constants.h"
#include <string>
using namespace std;
enum Camp{DEFENDER,INVADER};
// base for character, store basic information for each career
class Career{
protected:
	string career_label;	// career label
	string career_stamp;	// career stamp for display on map
	int hp;					// hit-point
	int att;				// attack value
	int def;				// defense value
	int mob;				// mobility
	int range;				// attack range
	int cooldown;			// cooldown time
	int cooldown_original;	// basic cooldown for this career
public:
	Career();
	Career(string career_label,string career_stamp,int hp,int att,int def,int mob,int range,int cooldown);
	string GetCareerLabel()const;						// return the label
	string GetCareerStamp()const;						// return the stamp
	int GetHP()const;									// return HP
	int GetMob()const;									// return mob
	int GetAtt()const;									// return att
	int GetDef()const;									// return def
	int GetRange()const;								// return attack range
	int GetCooldown()const;								// return cooldown time
protected:
	bool IsInMoveRange(int base_x,int base_y,int target_x,int target_y);	// return true if the position is accessible
	bool IsInAttackRange(int base_x,int base_y,int target_x,int target_y);	// return true if the position is within attack range
};
class Position;
class Character:public Career{
protected:
	string name;		// character name
	Position* position;	// pointer to its position
	bool is_alive;		// flag
	Camp camp;			// defender or invader

public:
	Character(Camp camp);
	Character(string name,bool is_alive,Camp camp,Career career);
	void SetPosition(Position* position);			// connect characters with positions in the map
	Position* GetPosition();						// return the character's position
	Camp GetCamp()const;							// return the camp
	bool GetIsAlive()const;							// return true if is alive
	string GetName()const;							// return name
	void SetCooldown(int difference);				// add difference to current cooldown
	void ResetCooldown();							// reset cooldown to the career's cooldown
	bool CheckMoveRange(int target_x,int target_y);					// return true if the position is accessible
	bool CheckAttackRange(int target_x,int target_y);					// return true if the position is within attack range
	int TakeDamage(int damage);					 	// substract damage from hp and return the new hp
	Character operator=(Career career);
	friend istream& operator>>(istream&,Character&);
	friend ostream& operator<<(ostream&,Character&);
};
/* TODO multiple initialization of career_list and career_count */
/* initialize career info(customize)*/
const Career career_list[]={
	// label, stamp, hp, att, def, mob, range, cooldown
	Career("Warrior","WA",20,10,5,3,1,80),
	Career("Wizard","WI",15,12,4,1,6,100),
	Career("Archer","AR",12,8,6,2,8,70),
	Career("Knight","KN",15,16,10,4,2,150)
};
const int career_count=sizeof(career_list)/sizeof(career_list[0]);

#endif
