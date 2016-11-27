This is a project that I independently created to better
understand how game trees, and computer decision making 
worked. This project is NOT complete and it still very
buggy, however I have included it in here because I believe
it also displays my curiosity as a programmer. 

Note: This is still an ongoing project, and there are a few
bugs in it. For example in Ubuntu when you cross out a line
it will print a ? character instead of a line that is crossed
out. 

How to compile: 
	- On Ubuntu type g++ main.cpp NimbAi.cpp Board.cpp -o Nimb
	then type ./Nimb to run it

	- On windows 32 or 64 bit simply click the Nimb.exe in the
	release folder

How to Play Nimb:

Each move you can cross off one, two, or three lines in a row.
The lines you cross off must be consecutive, there must not
be any lines crossed off in-between them. The last person to 
cross off a line loses the game.

How to set up the game:
Enter the player names and DO NOT enter a name that is 
less than two characters long. If the name has the 
prefix AI the player would be an AI. The program may take
a little while to initially set up the AI. For debugging 
purposes the AI will output all of the possible moves it 
can make along with some statistics about each move.

How to enter a move: 

To make your move type the coordinate of the first line you
want to cross off. Then type a space Then type the number of 
lines you want to cross off (either 1, 2 or 3).

for example 

  A B C D E 
1     |
2   | | | 
3 | | | | | 

you type: b2 2
the next board is

  A B C D E 
1     |
2   � � | 
3 | | | | | 



