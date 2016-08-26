#include <iostream>
#include <iomanip>
#include <cmath>
#include "map.h"
using namespace std;
Map::Map(int length,int width){
	this->length=length;
	this->width=width;
	SetMap(this->length,this->width);
}
Map::Map(){
	length=20;
	width=20;
	SetMap(length,width);
}
Map::~Map(){
	// free Position arrays first
	for(int i=0;i<length;i++){
		delete [] atlas[i];
	}
	// free Position pointer array
	delete [] atlas;
}
void Map::SetMap(int length,int width){
	// space for position pointer array
	atlas=new Position*[length];
	for(int i=0;i<length;i++){
		// space for position arrays
		atlas[i]=new Position[width];
		for(int j=0;j<width;j++){
			atlas[i][j].SetXY(i,j);
		}
	}
}
void Map::PlaceCharacter(Character* character,int x,int y){
	atlas[x][y].SetCharacter(character);
	character->SetPosition(&atlas[x][y]);
}
void Map::MoveCharacter(Character* character,int x,int y){
	character->GetPosition()->UnsetCharacter();
	PlaceCharacter(character,x,y);
}

void Map::Show(){
	for(int i=0;i<length;i++){
    	for(int j=0;j<width;j++){
    		Character* temp=atlas[i][j].GetCharacter();
    		// set background color
    		cout<<((i+j)%2?BG_BLACK:BG_WHITE);
    		if(temp!=NULL){
    			string stamp=temp->GetCareerStamp();
    			cout<<((temp->GetCamp()==DEFENDER)?F_RED:F_BLUE)<<HIGHLIGHT;
    			cout.width(2);
    			cout<<stamp<<OFF;
    		}else{
    			cout.width(2);
    			cout<<" ";
    		}
    	}
    	cout<<OFF<<endl;
    }
}
void Map::ShowMove(Character* character,int cursor_x,int cursor_y){
	int x=character->GetPosition()->GetX();
	int y=character->GetPosition()->GetY();
	for(int i=0;i<length;i++){
		for(int j=0;j<width;j++){
			if(x==i&&y==j){
				// twinkle effect on current character
				cout<<TWINKLE;
			}
			Character* temp=atlas[i][j].GetCharacter();
			int difference_sum=abs(x-i)+abs(y-j);
			// set base background color
			if(i==cursor_x&&j==cursor_y){
				// if current location is where the cursor is
				cout<<BG_PURPLE;
			}else if(character->IsInMoveRange(i,j)&&temp==NULL){
				// if current location is accessible
				cout<<((difference_sum%2)?BG_D_GREEN:BG_GREEN);
			}else{
				// inaccessible location
				cout<<((i+j)%2?BG_BLACK:BG_WHITE);
			}
			if(temp!=NULL){
				string stamp=temp->GetCareerStamp();
				cout<<((temp->GetCamp()==DEFENDER)?F_RED:F_BLUE)<<HIGHLIGHT;
				cout.width(2);
				cout<<stamp<<OFF;
			}else{
				cout.width(2);
				cout<<" ";
			}
		}		
		cout<<OFF<<endl;
	}	
}
void Map::ShowAttack(Character* character,int cursor_x,int cursor_y){
	int x=character->GetPosition()->GetX();
	int y=character->GetPosition()->GetY();
	for(int i=0;i<length;i++){
		for(int j=0;j<width;j++){
			if(x==i&&y==j){
				// twinkle effect on current character
				cout<<TWINKLE;
			}
			Character* temp=atlas[i][j].GetCharacter();
			int difference_sum=abs(x-i)+abs(y-j);
			// set base background color
			if(i==cursor_x&&j==cursor_y){
				// if current location is where the cursor is
				cout<<BG_PURPLE;
			}else if(character->IsInAttackRange(i,j)){
				// in attack range
				cout<<((difference_sum%2)?BG_RED:BG_YELLOW);
			}else{
				// inaccessible location
				cout<<(((i+j)%2)?BG_BLACK:BG_WHITE);
			}
			if(temp!=NULL){
				string stamp=temp->GetCareerStamp();
				cout<<((temp->GetCamp()==DEFENDER)?F_RED:F_BLUE)<<HIGHLIGHT;
				cout.width(2);
				cout<<stamp<<OFF;
			}else{
				cout.width(2);
				cout<<" "<<OFF;
			}
		}
		cout<<OFF<<endl;
	}
}

int Map::GetLength(){
	return length;
}
int Map::GetWidth(){
	return width;
}
Character* Map::IsOccupied(int x,int y){
	return atlas[x][y].GetCharacter();
}
