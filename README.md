# Onecard-Uno

**Onecard (Uno) simulator written in C.**

**Introduction**
<br> This is a simple command-line UNO card game written in C. UNO is a classic card game where the objective is to be the first to play all your cards or score the fewest penalty points when someone else does.

**Features**
- Play UNO in your terminal with up to 8 players.
- Supports classic UNO rules, including Skip, Reverse, Draw Two, and Wild cards.
- Customizable game settings, such as the number of players and player names.

**How to Play**
<br> Please familiarize yourself with the UNO rules before playing. A good place to start is: https://www.instructables.com/How-to-play-UNO-with-regular-playing-cards/

**Compilation:** 
<br> Compile the game by running the following command in your terminal: 

<br> make
<br> ./onecard --[commands]

**NOTE:** You may have to try mingw32-make on windows if "make" fails.
<br>The supported CLI are:
- --help -h to get the help message.
- --log -l to indicate the name of the logfile to save all the game-related data, onecard.log by default.
- -n number of players, 4 by default.
- -r number of round, 1 by default.
- -d number of decks used, 2 by default.
- -c number of cards at each player at start, 5 by default.
- -a auto mode activation.


**Game setup:**

<br> The game starts by shuffling the deck and deciding the order of players, the default orientation is clockwise.

**Specific rules:**

<br> If the player cannot make a move they must take a card from the pile, if no 2 or 3 were played previously, the player takes one card and gives the place to the next player.

**License**
<br> This UNO game is open-source software released under the MIT License. You are free to use, modify, and distribute it as you like.

**Acknowledgments**
<br> This project was inspired by the classic UNO card game and was developed during the course ENGR1510J Accelerated Introduction to Programming at UM-SJTU JI.
Special thanks to Professor Manuel Charlamagne and the whole teaching team.

**Author**
<br> Gor Tadevosyan
