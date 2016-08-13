#ifndef CONSTANTS_H
#define CONSTANTS_H
/*career*/
enum Career{WARRIOR,WIZARD,ARCHER};
/*camp*/
enum Camp{DEFENDER,INVADER};
/*direction command*/
#define CONFIRM			'o'
#define FORSAKE			'f'
#define UP 				'w'
#define DOWN			's'
#define LEFT			'a'
#define RIGHT			'd'
/*stamp*/
#define WARRIOR_STAMP 	"WA"
#define WIZARD_STAMP 	"WI"
#define ARCHER_STAMP 	"AR"

/*character related*/
#define WARRIOR_BASE_ATT 		10
#define WARRIOR_BASE_DEF 		5
#define WARRIOR_BASE_MOB 		3
#define WARRIOR_BASE_HP 		20
#define WARRIOR_BASE_RANGE		1
#define WARRIOR_BASE_COOLDOWN 	80

#define WIZARD_BASE_ATT 		12
#define WIZARD_BASE_DEF 		4
#define WIZARD_BASE_MOB 		1
#define WIZARD_BASE_HP 			15
#define WIZARD_BASE_RANGE		6
#define WIZARD_BASE_COOLDOWN	100

#define ARCHER_BASE_ATT 		8
#define ARCHER_BASE_DEF 		6
#define ARCHER_BASE_MOB 		2
#define ARCHER_BASE_HP 			12
#define ARCHER_BASE_RANGE		8
#define ARCHER_BASE_COOLDOWN	70

/*output style*/
#define BG_BLACK 	"\033[40m"
#define BG_RED 		"\033[41m"
#define BG_GREEN 	"\033[42m"
#define BG_YELLOW 	"\033[43m"
#define BG_BLUE 	"\033[44m"
#define BG_PURPLE 	"\033[45m"
#define BG_D_GREEN 	"\033[46m"
#define BG_WHITE 	"\033[47m"
#define F_BLACK 	"\033[30m"
#define F_RED 		"\033[31m"
#define F_GREEN 	"\033[32m"
#define F_YELLOW 	"\033[33m"
#define F_BLUE 		"\033[34m"
#define F_PURPLE 	"\033[35m"
#define F_D_GREEN 	"\033[36m"
#define F_WHITE 	"\033[37m"

#define OFF			"\033[0m"
#define HIGHLIGHT 	"\033[1m"
#define TWINKLE		"\033[5m"

#endif
