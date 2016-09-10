#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <cctype>
#include "game.h"

#define GIVE_UP	0
#define ERROR 	1
#define OK 		2
#define DONE 	3

using namespace std;

Game::Game(){
	defender_count=3;
	invader_count=3;
	defender_kill=0;
	invader_kill=0;
	map=new Map(15,15);
	defender=new Character*[defender_count];
	invader=new Character*[invader_count];
	Initialize();
}

Game::Game(int defender_count,int invader_count,int map_length,int map_width){
	this->defender_count=defender_count;
	this->invader_count=invader_count;
	defender_kill=0;
	invader_kill=0;
	map=new Map(map_length,map_width);
	defender=new Character*[defender_count];
	invader=new Character*[invader_count];
}
Game::~Game(){
	// free characters
	for(int i=0;i<invader_count+defender_count+1;i++){
		delete heap[i];	
	}
	// free heap pointers
	delete [] heap;
	heap=NULL;
	// free defender pointers
	delete [] defender;
	defender=NULL;
	// free invader pointers
	delete [] invader;
	invader=NULL;
}

void Game::Initialize(){
	void ShowCareerInfo();
	for(int i=0;i<defender_count;i++){
		defender[i]=new Character(DEFENDER);
		system("clear");
		ShowCareerInfo();
		cout<<"Input defender #"<<i+1<<" information:"<<endl;
		cin>>*defender[i];
	}
	for(int i=0;i<invader_count;i++){
		invader[i]=new Character(INVADER);
		system("clear");
		ShowCareerInfo();
		cout<<"Input invader #"<<i+1<<" information:"<<endl;
		cin>>*invader[i];
		invader[i]->SetCooldown(10);
	}
	PlaceCharacters();
	BuildHeap();
}

void Game::BuildHeap(){
	int heap_size=defender_count+invader_count;
	heap=new Character*[defender_count+invader_count+1];
	for(int i=0;i<defender_count;i++){
		heap[i+1]=defender[i];
	}
	for(int j=0;j<invader_count;j++){
		heap[defender_count+j+1]=invader[j];
	}
	for(int i=heap_size/2;i>=1;i--){
		AdjustHeap(i,heap_size);
	}
}
void Game::AdjustHeap(int i,int heap_size){
	// adjust the heap according to cooldown
	int value=heap[i]->GetCooldown();
	while(true){
		if(i*2+1<=heap_size){
			int min=(heap[i*2+1]->GetCooldown()<heap[i*2]->GetCooldown())?i*2+1:i*2;
			if(value<heap[min]->GetCooldown()){
				break;
			}else{
				//swap
				Character* temp;
				temp=heap[min];
				heap[min]=heap[i];
				heap[i]=temp;
				i=min;
			}
		}else if(i*2<=heap_size){
			if(value>heap[i*2]->GetCooldown()){
				Character* temp;
				temp=heap[i*2];
				heap[i*2]=heap[i];
				heap[i]=temp;
			}
			break;
		}else{
			break;
		}
	}
}
void Game::PlaceCharacters(){
	// TODO a random position(x,y) generator
	for(int i=0;i<defender_count;i++){
		map->PlaceCharacter(defender[i],i,i);
	}
	for(int i=0;i<invader_count;i++){
		map->PlaceCharacter(invader[i],map->GetLength()-i-1,map->GetWidth()-i-1);
	}
}

Character* Game::NextTurnCharacter(){	
	Character* next_turn_character;
	next_turn_character=heap[1];
	int current_cooldown=heap[1]->GetCooldown();
	int heap_size=defender_count+invader_count;
	for(int i=2;i<=heap_size;i++){
		heap[i]->SetCooldown(-current_cooldown);
	}
	heap[1]->ResetCooldown();
	AdjustHeap(1,heap_size);
	return next_turn_character;
}

void ShowCommand(){
	cout<<F_YELLOW;
	cout<<"Input command:"<<endl;
	cout<<"UP:\t\t\'"<<UP<<"\'"<<endl;
	cout<<"DOWN:\t\t\'"<<DOWN<<"\'"<<endl;
	cout<<"LEFT:\t\t\'"<<LEFT<<"\'"<<endl;
	cout<<"RIGHT:\t\t\'"<<RIGHT<<"\'"<<endl;
	cout<<"CONFIRM:\t\'"<<CONFIRM<<"\'"<<endl;
	cout<<"FORSAKE:\t\'"<<FORSAKE<<"\'"<<endl;
	cout<<OFF;
}
void ShowCareerInfo(){
	cout<<HIGHLIGHT;
	for(int i=0;i<career_count;i++){
		switch(i%3){
			case 0:
				cout<<F_GREEN;
			 	break;
			case 1:
				cout<<F_BLUE;
				break;
			case 2:
				cout<<F_YELLOW;
				break;
		}
		cout<<career_list[i].GetCareerLabel()<<endl;
		cout<<"HP:\t"<<career_list[i].GetHP()<<endl;
		cout<<"ATT:\t"<<career_list[i].GetAtt()<<endl;
		cout<<"DEF:\t"<<career_list[i].GetDef()<<endl;
		cout<<"MOB:\t"<<career_list[i].GetMob()<<endl;
		cout<<"RANGE:\t"<<career_list[i].GetRange()<<endl;
	}
	cout<<OFF;
}
int Game::HandleCommand(const int x,const int y,int& x_difference,int& y_difference){
	string command;
	bool error=false;
	bool done=false;
	bool forsake=false;
	cin>>command;
	for(int i=0;i<command.length();i++){
		// check one character a time
		switch(command[i]){
			case UP:
				if(x+x_difference>0){
					x_difference-=1;
				}
				break;
			case DOWN:
				if(x+x_difference<map->GetLength()-1){
					x_difference+=1;
				}
				break;
			case LEFT:
				if(y+y_difference>0){
					y_difference-=1;
				}
				break;
			case RIGHT:	
				if(y+y_difference<map->GetWidth()-1){
					y_difference+=1;
				}
				break;
			case FORSAKE:
				forsake=true;
				break;
			case CONFIRM:
				done=true;
				break;
			default:
				if(!error){
					// first wrong character
					system("clear");
					error=true;
				}
				cout<<F_YELLOW<<"Unknown command "<<command[i]<<OFF<<endl;
				break;
		}
		if(!error){
			// no error, done or forsake
			if(forsake){
				return GIVE_UP;
			}
			if(done){
				return DONE;
			}
		}	
	}
	if(error){
		return ERROR;
	}else{
		return OK;
	}
} 

void Game::Attack(Character* character){
	// current position
	int x;
	int y;
	// attack target location
	int x_attack;
	int y_attack;
	int range;
	Camp camp;
	x=character->GetPosition()->GetX();
	y=character->GetPosition()->GetY();
	// initialize
	x_attack=x;
	y_attack=y;
	range=character->GetRange();
	camp=character->GetCamp();
	string command_error_info="";
	while(true){
		// display the map and related information
		system("clear");
		cout<<command_error_info<<endl;
		command_error_info="";
		map->ShowAttack(character,x_attack,y_attack);
		ShowStatus();
		ShowCommand();

		int command_status;
		int x_difference=0;
		int y_difference=0;
		// get status of command input
		command_status=HandleCommand(x_attack,y_attack,x_difference,y_difference);
		// if error in user input, restart input
		if(command_status==ERROR){
			cout<<"Press c to continue"<<endl;
			while(cin.get()!='c')
				;
			continue;
		}else if(command_status==GIVE_UP){
			// if no error and user gives up movements
			break;
		}

		// validate player's attack
		// if beyond range
		if(!character->CheckAttackRange(x_attack+x_difference,y_attack+y_difference)){	
			command_error_info="Invalid attack: beyond range";
			continue;
		}
		// within range and not done, update x_attack, y_attack
		if(command_status==OK){
			x_attack=x_attack+x_difference;
			y_attack=y_attack+y_difference;
			continue;
		}
		// within range and done, validate
		if(command_status==DONE){
			Character* target=map->IsOccupied(x_attack+x_difference,y_attack+y_difference);
			if(target==NULL||target->GetCamp()==camp){
				// no target or invalid target
				if(target==NULL){
					command_error_info="Invalid attack: no target";
				}else if(target==character){
					command_error_info="Can not attack yourself";
				}else{
					command_error_info="Can not attack your allies!";
				}
				// next loop
				continue;
			}else{
				// valid attack
				int left_hp=target->TakeDamage(character->GetAtt()-target->GetDef());
				if(left_hp==0){
					//unlink from the map
					target->GetPosition()->UnsetCharacter();
					if(camp==DEFENDER){
						defender_kill++;
					}else{
						invader_kill++;
					}
				}
				// finish
				break;
			}
		}
	}
}
void Game::Move(Character* character){
	// character position
	int x;
	int y;
	// valid target position for character move
	int x_move;
	int y_move;
	x=character->GetPosition()->GetX();
	y=character->GetPosition()->GetY();
	// initialize target position 
	x_move=x;
	y_move=y;

	string command_error_info="";
	while(true){
		// display map with related information
		system("clear");
		cout<<command_error_info<<endl;
		command_error_info="";
		map->ShowMove(character,x_move,y_move);
		ShowStatus();
		ShowCommand();

		int command_status;
		int x_difference=0;
		int y_difference=0;
		// get command status
		command_status=HandleCommand(x_move,y_move,x_difference,y_difference);
		// error in user input, restart input
		if(command_status==ERROR){
			cout<<"Press c to continue"<<endl;
			while(cin.get()!='c')
				;
			continue;
		}	
		// no error and give up
		if(command_status==GIVE_UP){
			break;
		}
		// done or ok, validate move
		// beyond range
		if(!character->CheckMoveRange(x_move+x_difference,y_move+y_difference)){
			command_error_info="Invalid move: beyond range";
			continue;
		}
		Character* target=map->IsOccupied(x_move+x_difference,y_move+y_difference);	
		// within range but occupied
		if(target!=NULL&&target!=character){
			command_error_info="Invalid move: position already occupied";
			continue;
		}
		// valid
		x_move=x_move+x_difference;
		y_move=y_move+y_difference;
		if(command_status==OK){
			continue;
		}
		if(command_status==DONE){
			map->MoveCharacter(character,x_move,y_move);
			break;
		}			
	}

}
void Game::ShowStatus(){
	cout<<"Score\nDefender:"<<defender_kill<<"\tInvader:"<<invader_kill<<endl;
	cout<<F_GREEN<<"Camp\t\tCareer\t\tName\tCooldown\tHP"<<OFF<<endl;
	for(int i=0;i<defender_count;i++){
		if(defender[i]->GetIsAlive()==false){
			continue;
		}
		cout<<*defender[i];
	}
	for(int i=0;i<invader_count;i++){
		if(invader[i]->GetIsAlive()==false){
			continue;
		}
		cout<<*invader[i];

	}
}
void Game::Round(Character* character){
	Move(character);
	Attack(character);
}


void Game::Start(){
	Character* current_character;
	map->Show();
	while(true){
		// find next (alive) character
		current_character=NextTurnCharacter();
		if(current_character->GetIsAlive()){
			// enter each round
			Round(current_character);
			// until one team wins
			if(defender_kill==invader_count){
				cout<<"Defender Win!!!"<<endl;
				break;
			}else if(invader_kill==defender_count){
				cout<<"Invader Win!!!"<<endl;
				break;
			}
		}
	}
}
