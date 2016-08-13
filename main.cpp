#include<iostream>
#include<string>
#include<cstdlib>
#include"constants.h"
#include"game.h"
using namespace std;

int main(int argc,char* argv[]){
	
	int defender_count;
	int invader_count;
	int map_length;
	int map_width;
	system("clear");
	cout<<"Defender count:"<<endl;
	cin>>defender_count;
	cout<<"Invader count:"<<endl;
	cin>>invader_count;
	cout<<"Map length:"<<endl;
	cin>>map_length;
	cout<<"Map width:"<<endl;
	cin>>map_width;
	
	Game game(defender_count,invader_count,map_length,map_width);
	game.Start();

	return 0;
}
