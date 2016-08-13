#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include "game.h"

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
	Initialize();
}

void Game::Initialize(){
	void ShowCareerInfo();
	for(int i=0;i<defender_count;i++){
		system("clear");
		ShowCareerInfo();
		cout<<"Input defender#"<<i<<" information:"<<endl;
		string name;
		cout<<"Input name:"<<endl;
		cin>>name;
		Career career;
		int career_option;
		cout<<"Input career:"<<endl;
		cout<<"1. Warrior\n"<<"2. Wizard\n"<<"3. Archer"<<endl;
		cin>>career_option;
		switch(career_option){
			case 1:
				career=WARRIOR;
				break;
			case 2:
				career=WIZARD;
				break;
			case 3:
				career=ARCHER;
				break;
		}
		defender[i]=new Character(name,true,DEFENDER,career);
	}
	for(int i=0;i<invader_count;i++){
		system("clear");
		ShowCareerInfo();
		cout<<"Input invader#"<<i<<" information:"<<endl;
		string name;
		cout<<"Input name:"<<endl;
		cin>>name;
		Career career;
		int career_option;
		cout<<"Input career:"<<endl;
		cout<<"1. Warrior\n"<<"2. Wizard\n"<<"3. Archer"<<endl;
		cin>>career_option;
		switch(career_option){
			case 1:
				career=WARRIOR;
				break;
			case 2:
				career=WIZARD;
				break;
			case 3:
				career=ARCHER;
				break;
		}
		invader[i]=new Character(name,true,INVADER,career);
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
	cout<<F_GREEN;
	cout<<"Warrior"<<endl;
	cout<<"HP:\t"<<WARRIOR_BASE_HP<<endl;
	cout<<"ATT:\t"<<WARRIOR_BASE_ATT<<endl;
	cout<<"DEF:\t"<<WARRIOR_BASE_DEF<<endl;
	cout<<"MOB:\t"<<WARRIOR_BASE_MOB<<endl;
	cout<<"RANGE\t"<<WARRIOR_BASE_RANGE<<endl;
	cout<<F_BLUE;
	cout<<"Wizard"<<endl;
	cout<<"HP:\t"<<WIZARD_BASE_HP<<endl;
	cout<<"ATT:\t"<<WIZARD_BASE_ATT<<endl;
	cout<<"DEF:\t"<<WIZARD_BASE_DEF<<endl;
	cout<<"MOB:\t"<<WIZARD_BASE_MOB<<endl;
	cout<<"RANGE\t"<<WIZARD_BASE_RANGE<<endl;
	cout<<F_YELLOW;
	cout<<"Archer"<<endl;
	cout<<"HP:\t"<<ARCHER_BASE_HP<<endl;
	cout<<"ATT:\t"<<ARCHER_BASE_ATT<<endl;
	cout<<"DEF:\t"<<ARCHER_BASE_DEF<<endl;
	cout<<"MOB:\t"<<ARCHER_BASE_MOB<<endl;
	cout<<"RANGE\t"<<ARCHER_BASE_RANGE<<endl;
	cout<<OFF;
}
void Game::Attack(Character* character){
	int x;
	int y;
	int x_attack;
	int y_attack;
	int range;
	Camp camp;
	Career career;
	x=character->GetPosition()->GetX();
	y=character->GetPosition()->GetY();
	x_attack=x;
	y_attack=y;
	range=character->GetRange();
	career=character->GetCareer();
	camp=character->GetCamp();
	system("clear");
	cout<<endl;
	map->ShowAttack(character,x_attack,y_attack);
	ShowStatus();
	bool done=false;
	bool forsake=false;
	while(!done){
		string attack_command;
		int x_difference=0;
		int y_difference=0;
		bool error=false;
		cin>>attack_command;
		system("clear");
		for(int i=0;i<attack_command.length();i++){
			switch(attack_command[i]){
				case UP:
					if(x_attack+x_difference>0){
						x_difference-=1;
					}
					break;
				case DOWN:
					if(x_attack+x_difference<map->GetLength()-1){
						x_difference+=1;
					}
					break;
				case LEFT:
					if(y_attack+y_difference>0){
						y_difference-=1;
					}
					break;
				case RIGHT:	
					if(y_attack+y_difference<map->GetWidth()-1){
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
					error=true;
					cout<<F_YELLOW<<"Unknown command "<<attack_command[i]<<OFF<<endl;
					break;
			}
			if(done||forsake){
				break;
			}
			
		}
		if(error){
			done=false;
			forsake=false;
			cout<<"Press Enter to continue"<<endl;
			while(cin.get()!='c')
				;
			system("clear");
			cout<<endl;
			map->ShowAttack(character,x_attack,y_attack);
			ShowStatus();
			ShowCommand();
			continue;
		}
		if(forsake){
			break;
		}
		//validate player's attack
		Character* target;
		target=map->IsOccupied(x_attack+x_difference,y_attack+y_difference);
		int difference_x=abs(x-(x_attack+x_difference));
		int difference_y=abs(y-(y_attack+y_difference));
		int difference_sum=difference_x+difference_y;
		if(difference_sum<=range&&(career==WARRIOR||career==WIZARD||(career==ARCHER&&(difference_x==0||difference_y==0)))){
			if(done){
				if(target!=NULL){
					if(target->GetCamp()!=camp){
						int left_hp=target->TakeDamage(character->GetAtt()-target->GetDef());
						if(left_hp==0){
							//unlink from the map
							target->GetPosition()->UnsetCharacter();
							//update game info
							if(camp==DEFENDER){
								defender_kill++;
							}else{
								invader_kill++;
							}	
						}
						cout<<endl;
						map->Show();
					}else{
						if(target==character){
							cout<<"Can not attack yourself"<<endl;
						}else{
							cout<<"Can not attack your allies!"<<endl;
						}
						done=false;
						map->ShowAttack(character,x_attack,y_attack);
					}
				}else{
					done=false;
					cout<<"Invalid attack: no target"<<endl;
					map->ShowAttack(character,x_attack,y_attack);
				}
			}else{
				if(target!=NULL&&target->GetCamp()==camp&&target!=character){
					cout<<"Can not attack your allies!"<<endl;
					map->ShowAttack(character,x_attack,y_attack);

				}else{
					cout<<endl;
					x_attack+=x_difference;
					y_attack+=y_difference;
					map->ShowAttack(character,x_attack,y_attack);
				}
			}
		}else{
			cout<<"Invalid attack: beyond range"<<endl;
			map->ShowAttack(character,x_attack,y_attack);
		}
		ShowStatus();
		ShowCommand();
	}

}
void Game::Move(Character* character){
	int x;
	int y;
	int x_move;
	int y_move;
	int mob;
	x=character->GetPosition()->GetX();
	y=character->GetPosition()->GetY();
	x_move=x;
	y_move=y;
	mob=character->GetMob();
	system("clear");
	cout<<endl;
	map->ShowMove(character,x_move,y_move);
	ShowStatus();
	ShowCommand();
	bool done=false;
	bool forsake=false;
	while(!done){
		string move_command;
		int x_difference=0;
		int y_difference=0;
		bool error=false;
		cin>>move_command;
		system("clear");
		for(int i=0;i<move_command.length();i++){
			switch(move_command[i]){
				case UP:
					if(x_move+x_difference>0){
						x_difference-=1;
					}
					break;
				case DOWN:
					if(x_move+x_difference<map->GetLength()-1){
						x_difference+=1;
					}
					break;
				case LEFT:
					if(y_move+y_difference>0){
						y_difference-=1;
					}
					break;
				case RIGHT:
					if(y_move+y_difference<map->GetWidth()-1){
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
					error=true;
					cout<<"Unknown command "<<move_command[i]<<endl;
					break;
			}
			if(done||forsake){
				break;
			}
		}
		if(error){
			done=false;
			forsake=false;
			cout<<"Press c to continue"<<endl;
			while(cin.get()!='c')
				;
			system("clear");
			cout<<endl;
			map->ShowMove(character,x_move,y_move);
			ShowStatus();
			ShowCommand();
			continue;
		}
		if(forsake){
			break;
		}
		//validate player's move
		Character* target;
		target=map->IsOccupied(x_move+x_difference,y_move+y_difference);
		int difference_sum=abs(x-(x_move+x_difference))+abs(y-(y_move+y_difference));
		if(difference_sum<=mob&&target==NULL||target==character){
			//spare a empty line to make display nice
			cout<<endl;
			x_move+=x_difference;
			y_move+=y_difference;
			if(done){
				map->MoveCharacter(character,x_move,y_move);
				map->Show();
			}else{
				map->ShowMove(character,x_move,y_move);	
			}
		}else{
			if(target!=NULL){
				cout<<"Invalid move: position already occupied"<<endl;
			}else{
				cout<<"Invalid move: beyond range"<<endl;
			}
			done=false;
			map->ShowMove(character,x_move,y_move);
		}
		ShowStatus();
		ShowCommand();
	}

}
void Game::ShowStatus(){
	cout<<"Score\nDefender:"<<defender_kill<<"\tInvader:"<<invader_kill<<endl;
	for(int i=0;i<defender_count;i++){
		if(defender[i]->GetIsAlive()==false){
			continue;
		}
		cout<<F_RED<<"[Defender]\t";
		switch(defender[i]->GetCareer()){
			case WARRIOR:
				cout<<"(Warrior)\t";
				break;
			case WIZARD:
				cout<<"(Wizard)\t";
				break;
			case ARCHER:
				cout<<"(Archer)\t";
				break;
		}
		cout<<defender[i]->GetName()<<"\t";
		cout<<defender[i]->GetCooldown()<<"\t";
		cout.width(4);
		cout<<defender[i]->GetHP();
		cout<<" ";
		for(int j=0;j<defender[i]->GetHP();j++){
			cout<<"@";
		}
		cout<<OFF<<endl;
	}
	for(int i=0;i<invader_count;i++){
		if(invader[i]->GetIsAlive()==false){
			continue;
		}
		cout<<F_BLUE<<"[Invader]\t";
		switch(invader[i]->GetCareer()){
			case WARRIOR:
				cout<<"(Warrior)\t";
				break;
			case WIZARD:
				cout<<"(Wizard)\t";
				break;
			case ARCHER:
				cout<<"(Archer)\t";
				break;
		}
		cout<<invader[i]->GetName()<<"\t";
		cout<<invader[i]->GetCooldown()<<"\t";
		cout.width(4);
		cout<<invader[i]->GetHP();
		cout<<" ";
		for(int j=0;j<invader[i]->GetHP();j++){
			cout<<"@";
		}
		cout<<OFF<<endl;
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
		current_character=NextTurnCharacter();
		if(current_character->GetIsAlive()){
			Round(current_character);
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

