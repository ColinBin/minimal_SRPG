#include <cmath>
#include "character.h"
Character::Character(string name,bool is_alive,Camp camp,Career career){
	this->name=name;
	this->is_alive=is_alive;
	this->career=career;
	this->camp=camp;
	SetBasic(this->career);
}

Character::Character(string name){
	this->name=name;
	this->is_alive=true;
	this->camp=DEFENDER;
	this->career=WARRIOR;
	SetBasic(this->career);
}
void Character::SetBasic(Career career){
	switch(career){
		case WARRIOR:
			hp=WARRIOR_BASE_HP;
			att=WARRIOR_BASE_ATT;
			def=WARRIOR_BASE_DEF;
			mob=WARRIOR_BASE_MOB;
			range=WARRIOR_BASE_RANGE;
			cooldown=WARRIOR_BASE_COOLDOWN;
			break;
		case WIZARD:
			hp=WIZARD_BASE_HP;
			att=WIZARD_BASE_ATT;
			def=WIZARD_BASE_DEF;
			mob=WIZARD_BASE_MOB;
			range=WIZARD_BASE_RANGE;
			cooldown=WIZARD_BASE_COOLDOWN;
			break;
		case ARCHER:
			hp=ARCHER_BASE_HP;
			att=ARCHER_BASE_ATT;
			def=ARCHER_BASE_DEF;
			mob=ARCHER_BASE_MOB;
			range=ARCHER_BASE_RANGE;
			cooldown=ARCHER_BASE_COOLDOWN;
			break;
	}
}

void Character::SetPosition(Position* position){
	this->position=position;
}
Position* Character::GetPosition(){
	return this->position;
}
Camp Character::GetCamp(){
	return camp;
}
Career Character::GetCareer(){
	return career;
}
int Character::GetMob(){
	return this->mob;
}
int Character::GetAtt(){
	return this->att;
}
int Character::GetDef(){
	return this->def;
}
bool Character::GetIsAlive(){
	return this->is_alive;
}
int Character::GetRange(){
	return this->range;
}
void Character::SetCooldown(int difference){
	cooldown=cooldown+difference;
}
int Character::GetCooldown(){
	return this->cooldown;
}
void Character::ResetCooldown(){
	switch(career){
		case WARRIOR:
			cooldown=WARRIOR_BASE_COOLDOWN;
			break;
		case WIZARD:
			cooldown=WIZARD_BASE_COOLDOWN;
			break;
		case ARCHER:
			cooldown=ARCHER_BASE_COOLDOWN;
			break;
	}
}
int Character::TakeDamage(int damage){
	if(damage>0){
		hp-=damage;
	}
	if(hp<=0){
		hp=0;
		is_alive=false;
	}
	return hp;
}
string Character::GetName(){
	return name;
}
int Character::GetHP(){
	return hp;
}

/* customize move patterns */
bool Character::IsInMoveRange(int target_x,int target_y){
	int current_position_x=position->GetX();
	int current_position_y=position->GetY();
	switch(career){
		case WARRIOR:
			if(abs(current_position_x-target_x)+abs(current_position_y-target_y)<=mob){
				return true;
			}
			break;
		case WIZARD:
			if(abs(current_position_x-target_x)+abs(current_position_y-target_y)<=mob){
				return true;
			}
			break;
		case ARCHER:
			if(abs(current_position_x-target_x)+abs(current_position_y-target_y)<=mob){
				return true;
			}
			break;
	}
	return false;
}
/* customize attack patterns */
bool Character::IsInAttackRange(int target_x,int target_y){
	int current_position_x=position->GetX();
	int current_position_y=position->GetY();
	switch(career){
		case WARRIOR:
			if(abs(current_position_x-target_x)+abs(current_position_y-target_y)<=range){
				return true;
			}
			break;
		case WIZARD:	
			if(abs(current_position_x-target_x)+abs(current_position_y-target_y)<=range){
				return true;
			}
			break;
		case ARCHER:
			int difference_x=abs(current_position_x-target_x);
			int difference_y=abs(current_position_y-target_y);
			if(difference_x==0&&difference_y<=range||difference_y==0&&difference_x<=range){
				return true;
			}
			break;
	}
	return false;
}
