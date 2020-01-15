# Verly's Initiative Tracker
This is a tool to help dungeon/game masters keep track of their player's initiative orders. It allows the user to populate an initiative list, assign initiative scores to actors, and run a combat encounter. It also keeps a database of default partymembers in a txt file, which can be imported each session.

Once combat has begun, user can 'rotate' the initiative list each time a player finishes their turn. They can also remove actors from combat at any time.

## Dependencies
This program uses various c++ libraries that must be present in order to run it successfully:
* libgcc_s_dw2-1.dll
* libstdc++-6.dll
* libwinpthread-1.dll

## Installation
If your machine already has the libraries listed in 'dependencies' installed, just compile the .cpp via cmd prompt or IDE and you'll be all set. If the machine in question does not already have these libraries, just copy/paste them into the local folder and it will run fine.

You will need to alter _partydb.txt_ to reflect your current gaming group. Follow the example listed in _partydb.txt_ by entering a name (first letter capitalization) followed by a return. The program reads in the names for default partymembers by line so don't include anything on each line except for the character's name.

_e.g._

Johnny
Sally
James
Jack

_not_

Johnny, Sally, James, Jack

## Use Instructions
This program does not roll initiative for the players. Instead, it relies on the user to prompt the players for their initiative scores. It was intentially designed in this way because players enjoy rolling their own dice.

### Standard Use Case
1. Select _Create Combat Encounter_ default party (optional)
2. Select _Load Party From File_ (optional)
3. Select _Add Ally/Enemy to Combat_
4. Enter name of ally/enemy type _e.g._ skeleton archer
5. Enter number of allies/enemies in that group
*(repeat steps 4 and 5 until all actors are added)
6. Select _Back to Main Menu_
7. Select _Fight_
8. Prompt each player for their initiative roll as the program requests it
9. Enter remaining actor initiative scores


## Known bugs and issues
* If the user enters an actor name longer than 20 characters, the 'scroll' image during combat will become warped. It will not affect the performance of the program, but it will look gross.
