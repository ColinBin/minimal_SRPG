# About
A minimal SRPG game implemented with C++. The game has 3 basic types of characters and the number of characters as well as the scale of the map can be customized. Although some effects(twinkle) are only supported on certain OS(supported on CentOS 7 but not on Ubuntu 14.04), most effects are supported on all Linux. 

# Build
The current version could build & run on **Linux** with **g++**. Change to minimal_SRPG directory
> make   
> ./srpg_game   

# Idea
This game is customizable in three aspects:

1. The scale of the map can be customized
2. The number of characters for each side(defender and invader) can be cusomized
3. The character(name, career, hp, cooldown, etc) can be customized

The scale of the map as well as the number of characters are determined by player's input. The attributes of characters are specified in file "character.h" and "character.cpp". To customize your character:

1. Add a new line to career_list as specifying attributes of the new character in "character.h"
2. Add necessary logic to functions IsInMoveRange and IsInAttackRange in "character.cpp"

# TODO
1. Rewrite functions related to character to make customization more concise
2. Rewrite PlaceCharacters to generate relatively random and reasonable positions(currently, it is barely a reasonable function)
3. Change the structure to make it more compact(e.g.,move some functions from Character to Career)
4. Write some logic of actions for each round(currently for all characters, it is move+attack)
5. **Expand this idea**
