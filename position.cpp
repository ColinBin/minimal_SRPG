#include "position.h"
Position::Position(){
	x=-1;
	y=-1;
	character=NULL;
}
Position::Position(int x,int y){
	this->x=x;
	this->y=y;
	character=NULL;
}
int Position::GetX(){
	return x;
}
int Position::GetY(){
	return y;
}
void Position::SetXY(int x,int y){
	this->x=x;
	this->y=y;
}
void Position::SetCharacter(Character* character){
	this->character=character;
}
Character* Position::GetCharacter(){
	return character;
}
void Position::UnsetCharacter(){
	this->character=NULL;
}
