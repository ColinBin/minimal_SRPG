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
	for(int i=0;i<length;i++){
		delete [] atlas[i];
	}
	delete [] atlas;
}
void Map::SetMap(int length,int width){
	atlas=new Position*[length];
	for(int i=0;i<length;i++){
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
    			string stamp;
    			switch(temp->GetCareer()){
    				case WARRIOR:
    					stamp=WARRIOR_STAMP;							
    					break;
    				case WIZARD:
    					stamp=WIZARD_STAMP;
    					break;
    				case ARCHER:
    					stamp=ARCHER_STAMP;
    					break;
    			}
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
void Map::ShowMove(Character* character,int target_x,int target_y){
	int mob=character->GetMob();
	int x=character->GetPosition()->GetX();
	int y=character->GetPosition()->GetY();
	for(int i=0;i<length;i++){
		for(int j=0;j<width;j++){
			if(x==i&&y==j){
				cout<<TWINKLE;
			}
			Character* temp=atlas[i][j].GetCharacter();
			int difference_sum=abs(x-i)+abs(y-j);
			// set base background color
			if(i==target_x&&j==target_y){
				cout<<BG_PURPLE;
			}else if(difference_sum<=mob&&temp==NULL){
				cout<<((difference_sum%2)?BG_D_GREEN:BG_GREEN);
			}else{
				cout<<((i+j)%2?BG_BLACK:BG_WHITE);
			}
			if(temp!=NULL){
				string stamp;
				switch(temp->GetCareer()){
					case WARRIOR:
					 	stamp=WARRIOR_STAMP;
						break;
					case WIZARD:
						stamp=WIZARD_STAMP;
						break;
					case ARCHER:
						stamp=ARCHER_STAMP;
						break;
				}
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
void Map::ShowAttack(Character* character,int target_x,int target_y){
	int x=character->GetPosition()->GetX();
	int y=character->GetPosition()->GetY();
	int range=character->GetRange();
	Career career=character->GetCareer();
	for(int i=0;i<length;i++){
		for(int j=0;j<width;j++){
			if(x==i&&y==j){
				cout<<TWINKLE;
			}
			Character* temp=atlas[i][j].GetCharacter();
			int difference_sum=abs(x-i)+abs(y-j);
			// set base background color
			if(i==target_x&&j==target_y){
				cout<<BG_PURPLE;
			}else if((career==WARRIOR||career==WIZARD)&&difference_sum<=range){
				cout<<((difference_sum%2)?BG_RED:BG_YELLOW);
			}else if(career==ARCHER&&((x==i&&abs(y-j)<=range)||(y==j&&abs(x-i)<=range))){
				cout<<((difference_sum%2)?BG_RED:BG_YELLOW);
			}else{
				cout<<(((i+j)%2)?BG_BLACK:BG_WHITE);
			}
			if(temp!=NULL){
				string stamp;
				switch(temp->GetCareer()){
					case WARRIOR:
						stamp=WARRIOR_STAMP;
						break;
					case WIZARD:
						stamp=WIZARD_STAMP;
						break;
					case ARCHER:
						stamp=ARCHER_STAMP;
						break;
				}
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
