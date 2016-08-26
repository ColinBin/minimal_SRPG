#include <iostream>
#include <cmath>
#include "character.h"
using namespace std;
Career::Career(string career_label,string career_stamp,int hp,int att,int def,int mob,int range,int cooldown){
	this->career_label=career_label;
	// in case the length of career stamp is not 2
	int stamp_length=career_stamp.length();
	if(stamp_length==2){
		this->career_stamp=career_stamp;
	}else if(stamp_length<2){
		if(stamp_length==1){
			this->career_stamp=career_stamp+" ";
		}else{
			this->career_stamp="  ";
		}
	}else{
		this->career_stamp=career_stamp.substr(0,2);
	}
	this->hp=hp;
	this->att=att;
	this->def=def;
	this->mob=mob;
	this->range=range;
	this->cooldown=cooldown;
	this->cooldown_original=cooldown;		// maintain a copy of original cooldown
}
Career::Career(){}
string Career::GetCareerLabel()const{
	return this->career_label;
}
string Career::GetCareerStamp()const{
	return this->career_stamp;
}
int Career::GetMob()const{
	return this->mob;
}
int Career::GetAtt()const{
	return this->att;
}
int Career::GetDef()const{
	return this->def;
}
int Career::GetHP()const{
	return this->hp;
}
int Career::GetRange()const{
	return this->range;
}
int Career::GetCooldown()const{
	return this->cooldown;
}
Character::Character(string name,bool is_alive,Camp camp,Career career):Career(career){
	this->name=name;
	this->is_alive=is_alive;
	this->camp=camp;
}
Character::Character(Camp camp){
	this->camp=camp;
	this->is_alive=true;
}

void Character::SetPosition(Position* position){
	this->position=position;
}
Position* Character::GetPosition(){
	return this->position;
}
Camp Character::GetCamp()const{
	return camp;
}

bool Character::GetIsAlive()const{
	return this->is_alive;
}

void Character::SetCooldown(int difference){
	cooldown=cooldown+difference;
}
string Character::GetName()const{
	return name;
}

void Character::ResetCooldown(){
	cooldown=cooldown_original;	
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


/* customize move patterns */
bool Character::IsInMoveRange(int target_x,int target_y){
	int current_position_x=position->GetX();
	int current_position_y=position->GetY();
	if(career_label=="Warrior"){
		if(abs(current_position_x-target_x)+abs(current_position_y-target_y)<=mob){
			return true;
		}
	}else if(career_label=="Wizard"){
		if(abs(current_position_x-target_x)+abs(current_position_y-target_y)<=mob){
			return true;
		}
	}else if(career_label=="Archer"){
		if(abs(current_position_x-target_x)+abs(current_position_y-target_y)<=mob){
			return true;
		}
	}else if(career_label=="Knight"){
		if(abs(current_position_x-target_x)+abs(current_position_y-target_y)<=mob){
			return true;
		}
	}
	return false;
}
/* customize attack patterns */
bool Character::IsInAttackRange(int target_x,int target_y){
	int current_position_x=position->GetX();
	int current_position_y=position->GetY();
	if(career_label=="Warrior"){
		if(abs(current_position_x-target_x)+abs(current_position_y-target_y)<=range){
			return true;
		}
	}else if(career_label=="Wizard"){
		if(abs(current_position_x-target_x)+abs(current_position_y-target_y)<=range){
			return true;
		}

	}else if(career_label=="Archer"){
		int difference_x=abs(current_position_x-target_x);
		int difference_y=abs(current_position_y-target_y);
		if(difference_x==0&&difference_y<=range||difference_y==0&&difference_x<=range){
			return true;
		}
	}else if(career_label=="Knight"){
		if(abs(current_position_x-target_x)<=range&&abs(current_position_y-target_y)<=range){
			return true;
		}
	}
	return false;
}
Character Character::operator=(Career career){
	this->career_label=career.GetCareerLabel();
	this->career_stamp=career.GetCareerStamp();
	this->hp=career.GetHP();
	this->att=career.GetAtt();
	this->def=career.GetDef();
	this->mob=career.GetMob();
	this->range=career.GetRange();
	this->cooldown=career.GetCooldown();
	this->cooldown_original=career.GetCooldown();
	return *this;
}
istream& operator>>(istream& input,Character& character){
	cout<<"Input name:"<<endl;
	input>>character.name;
	char career_option;
	cout<<"Input career:"<<endl;
	for(int i=0;i<career_count;i++){
		cout<<i+1<<". "<<career_list[i].GetCareerLabel()<<endl;
	}
	while(true){
		input.ignore();
		career_option=cin.get();
		if(career_option>='1'&&career_option<='0'+career_count){
			break;
		}else{
			cout<<F_RED<<"Input the number of career(1,2,3......)"<<OFF<<endl;
		}
	}
	character=career_list[career_option-'0'-1];
	return input;
}
ostream& operator<<(ostream& output,Character& character){
	if(character.GetCamp()==DEFENDER){
		output<<DEFENDER_INFO_COLOR<<"[Defender]\t";
	}else{
		output<<INVADER_INFO_COLOR<<"[Invader]\t";
	}
	output<<"("<<character.GetCareerLabel()<<")\t";
	output<<character.GetName()<<"\t";
	output<<character.GetCooldown()<<"\t";
	output.width(4);
	output<<character.GetHP();
	output<<" ";
	for(int i=0;i<character.GetHP();i++){
		output<<"@";
	}
	output<<OFF<<endl;
	return output;
}
