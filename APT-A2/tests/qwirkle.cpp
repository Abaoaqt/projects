#include "LinkedList.h"
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <vector> 
#include "Board.h"
#include "bag.h"
#include <ctype.h>


#define EXIT_SUCCESS    0

void studentInformation();
void menu();
void menuSelection(std::string option);
void createPlayers();
void swapTile(Player* player, char colour, int shape);
void playerTurn(Player* player);
bool checkInput(std::string input);
bool saveGame(std::string fName, std::vector<Player*> players, Board* board, LinkedList* bag, int turn);
bool loadGame(std::string fName, std::vector<Player*> &players, Board* board, LinkedList* bag, int* turn);
LinkedList* stoList(std::string line);
void endTurn(Player* player, char c, int s);
void quitGame();
void endGame();
void playGame();

LinkedList* bag;
Board* board;
std::vector<Player*> players;

int numPlayers = 0;
int turn = 0;

//sets the flag to continue the game
bool quit = false;

int main(void) {
   //system("Clear");

   //sets up the initial structures for the game
   //namely the players, bag, and the board.
   players = {};
   bag = new LinkedList();
   bag = fillBag();
   board = new Board(6, 6, true);
   menu();

   return EXIT_SUCCESS;
}

//main menu function
void menu() {
   
   //main loop for the menu options
   while (!quit)
   {
      std::string option = "0";
      std::cout << "Menu" << std::endl;
      std::cout << "----" << std::endl;
      std::cout << "1. New Game" << std::endl;
      std::cout << "2. Load Game" << std::endl;
      std::cout << "3. Show Student Information" << std::endl;
      std::cout << "4. Quit" << std::endl;
      std::cin >> option;
      menuSelection(option);
   }
   
   quitGame();
}

//function to handle the options selection on the main menu
void menuSelection(std::string option) {

   //option 1 - start a new game
   if(option == "1")
   {
       createPlayers();
   }

   //option 2 - load a saved game
   else if(option == "2") {
      std::cout << "Enter the file name for the game you want to load: " << std::endl;
      std::string file;
      std::cin.clear();
      std::cin.ignore(10000, '\n');
      std::getline(std::cin, file);
 
      //on a successful load
      if(loadGame(file, players, board, bag, &turn)){
         std::cout << "Game succesfully loaded" << std::endl;
         //start game 
         playerTurn(players[turn]);
      }

      //otherwise load fails
      else{
         std::cout << "Could not load game, please try again" << std::endl;
      }
   }

   //option 3 - call student information
   else if(option == "3") studentInformation();

   //option 4 - quit the game
   else if(option == "4") {
      quit = true;    
   }

   //invalid option
   else if(option != "1" || option != "2" || option != "3" || option != "4") {
      //system("Clear");
      std::cout << "Invalid input. Please type in a number (1-4)!" << std::endl;
      }
   }

//quit game function
void quitGame()
{
      std::cout << "Goodbye" << std::endl;
      free(bag);
}

//displays the student information
void studentInformation() {
   //system("Clear");
   std::cout << "----------------------" << std::endl;
   std::cout << "Name: Benjamin Fynch" << std::endl;
   std::cout << "Student ID: s3589828" << std::endl;
   std::cout << "Email: s3589828@student.rmit.edu.au" << std::endl << std::endl;
   
   std::cout << "Name: David Sarkies" << std::endl;
   std::cout << "Student ID: s3664099" << std::endl;
   std::cout << "Email: s3664099@student.rmit.edu.au" << std::endl << std::endl;
   
   std::cout << "Name: Jack Crellin" << std::endl;
   std::cout << "Student ID: s3542902" << std::endl;
   std::cout << "Email: s3542902@student.rmit.edu.au" << std::endl << std::endl;

   std::cout << "Name: Jeremy Kane" << std::endl;
   std::cout << "Student ID: s3700178" << std::endl;
   std::cout << "s3700178@student.rmit.edu.au" << std::endl;
   std::cout << "----------------------" << std::endl << std::endl;
   
   std::string s = "";
   std::cout << "Press any key to continue" << std::endl;
   std::cin >> s;
   //system("Clear");
   menu();
}

// Prompts user to enter number of players for the game
// Then runs a loop to create the number of players based on the user input
// Player hand is filled with 5 random tiles
void createPlayers() {
   //system("Clear");
   std::cout << "Starting a new game" << std::endl << std::endl;
   bool validAnswer = false;
   int numPlayers = 0;
   
   //loop which is escaped by entering a valid answer
   //number of players between 1 and 4
   while(!validAnswer)
   {
      std::cout << "Enter number of players: " << std::endl;
      std::cin.clear();
      std::cin.ignore(10000, '\n');
      std::cin >> numPlayers;
   
      if (numPlayers < 1 || numPlayers > 4) {
         std::cout << "Invalid number of players entered." << std::endl;
      } else {
         validAnswer = true;
      }
   }
   
   //loop to generate each of the players
   for(int i = 1; i <= numPlayers; i++) {
      std::cout << "Enter a name for player " << i << " (uppercase characters only)"<<std::endl;
      std::string playerName = "";
      std::cin >> playerName;
      Player* player = new Player(playerName);
      players.push_back(player);
      for(int x = 0; x < 6; x++) {
         Tile* tile = getRandomTile(bag);
         player->getHand()->addFront(tile);
      }
   }

   //if the number of players is 1, the option of playing against the computer is provided
   //the difficulty is then easy or hard

   //once the players are generated, the game begins
   turn += numPlayers;
   std::cout<<"Let's Play!"<<std::endl;
   playGame();
}

// The swap tile function
// player enters the colour and shape of a tile, eg: G3, and the tile is removed from their hand,
// placed back in the bag, and the player receives a random tile from the bag.
void swapTile(Player* player, char colour, int shape) {

   //checks to see if the tile is in the player's hand
   if(player->getHand()->getTile(colour, shape) != nullptr) {

      std::cout << "Removing " << colour << shape << " from " << player->getName() << "'s hand." << std::endl;

      //the tile is placed back into the bag
      bag->addBack(player->getHand()->getTile(colour, shape));

      //the tile is then removed from the player's hand
      player->getHand()->removeTile(colour, shape);

      //a random tile is then selected
      Tile* t = getRandomTile(bag);      

      //this tile is then given back to the player
      player->getHand()->addBack(t);
      std::cout << player->getName() << " receives " << t->getColour() << t->getShape() << "." << std::endl;
   }
   else {
      std::cout << "Invalid tile." << std::endl;
   }
}

//The save game function
bool saveGame(std::string fName, std::vector<Player*> players, Board* board, LinkedList* bag, int turn){
   bool success = false;
   std::ofstream outFile;
   std::string tail = ".txt";
   fName = fName + tail;
   outFile.open(fName);

   if(!outFile.fail()){
      //add the player information 
      for(int i = 0; i < int(players.size()); i++){
         outFile << players[i]->getName() << std::endl;
         outFile << players[i]->getScore() << std::endl;
         LinkedList* hand = players[i]->getHand();
         for(int j = 1; j <= hand->size(); j++){
            outFile << hand->get(j)->getColour() << hand->get(j)->getShape();
            if(j < hand->size()){
               outFile << ",";
            }
         }
         outFile << std::endl;
      }

      //add the board
      board->saveBoard(outFile);

      //add the bag
      for(int i = 1; i <= bag->size(); i++){
         Tile* tile = bag->get(i);
         outFile << tile->getColour() << tile->getShape();
         if(i < bag->size()){
            outFile << ",";
         }
      }
      outFile << std::endl;

      //add the current player
      outFile << players[turn%players.size()]->getName();
      success = true;
   }

   outFile.close();
   return success;

}

//the load game function
bool loadGame(std::string fName, std::vector<Player*> &players, Board* board, LinkedList* bag, int* turn){
   bool success;
   std::ifstream inFile;
   std::string tail = ".txt";
   fName = fName + tail;
   std::string line;

   inFile.open(fName);
   if(inFile.fail()){
      success = false;
   }

   else{
      // bools used to switch between methods
      bool parsePlayers = true;
      bool parseBoard = false;
      bool parseTiles = false;
      int count = 0;
      std::string currPlayer;

      std::vector<std::string> playerNames;
      std::vector<int> playerScores;
      std::vector<LinkedList*> playerHands;
      std::vector<std::string> boardLines;

      while(getline(inFile, line)){
         // stop getting player information once board lines appear
         // player names cannot start with ' '!
         if(line.at(0) == ' '){
            parsePlayers = false;
            parseBoard = true;
         }
         // stop getting the board lines 
         else if(parseBoard){
            if(line.at(1) != ' '){
               parseBoard = false;
               parseTiles = true;
            }
         }

         // collect the player information
         if(parsePlayers){
            if(count % 3 == 0){
               playerNames.push_back(line);
            }
            else if(count % 3 == 1){
               playerScores.push_back(std::stoi(line));
            }
            else{
               playerHands.push_back(stoList(line));
            }
            count++;
         }
         // collect all of the board lines
         else if(parseBoard){
            boardLines.push_back(line);
         }
         // set tiles in the bag
         else if(parseTiles){
            bag = stoList(line);
            parseTiles = false;
         }
         else{
            currPlayer = line;
         }
      }
      inFile.close();

      // combine all of the player info
      for(int i = 0; i < int(playerNames.size()); i++){
         Player* p = new Player(playerNames[i], playerScores[i], playerHands[i]);
         players.push_back(p);
      }


      // parse the board lines to get the dims and tiles
      int rows = int(boardLines.size()) - 2;
      int cols = int(boardLines[0][int(boardLines[0].length())-2]-47);

      board->resize(cols, rows);

      // parse the tiles for each row
      for(int rows = 2; rows < int(boardLines.size()); rows++){
         for(int cols = 3;  cols < int(boardLines[rows].length()); cols += 3){
            if(boardLines[rows].at(cols) == ' '){
               board->setTile(nullptr, (cols/3)-1, rows-2);
            }
            else{
               board->setState(); 
               Tile* tile = new Tile(boardLines[rows].at(cols), int(boardLines[rows].at(cols+1)-47));
               board->setTile(tile, (cols/3)-1, rows-2);
            }
         }
      }

      // determine the current turn
      for (int i = 0; i < int(players.size()); i++){
         if(currPlayer == players[i]->getName()){
            *turn = i;
         }
      }
      success = true;
   }
   return success;
}

// parsing a string into a LinkedList
LinkedList* stoList(std::string line){
   LinkedList* list = new LinkedList(); 
   int count = 0;
   while(count < int(line.length())){
         Tile* t = new Tile(line[count], int(line[count+1]-48));
         list->addBack(t);
         count +=3;
   }
   return list;
}

void playGame()
{
   while(!quit)
   {
      playerTurn(players.at(turn%players.size()));
   }
} 

// The player turn function
// Board is printed, player name is printed, player tiles are printed.
// User enters their move. If the first word is "place" and the input format
// is the correct length, then the tile, and xy coordinates are evaluated. 
// Then checks if the tile is valid, and if the move is valid. If it is valid,
// then the tile is removed from the player's hand and the player draws another 
// tile from the bag. Then goes to the next player.
void playerTurn(Player* player) {
   bool move = false;

   //loop which escapes when a valid move is completed
   while(!move) {

      //checks to see if the current player is an AI
      //if so, then the AI turn is called


      //otherwise the human player turn is executed
      //The current board is displayed
      board->printBoard();
      std::cout << "Player: " << player->getName() << " -- Score: " << player->getScore() << std::endl;
      std::cout << "Your hand is" << std::endl;

      //the hand of the current player is displayed
      player->printList();
      std::cout << std::endl;
      std::string input = "place x at xx";
      std::getline(std::cin, input);

      if(!input.substr(0,3).compare("end")){
         endGame();
      }

      //checks to see is a save game is requested
      if(!input.substr(0,4).compare("save")){
        try{
           std::string file = "";
           for(int i = 5; i < int(input.length()); i++){
                file += input[i];
            }

            saveGame(file, players, board, bag, turn);
            std::cout << "Game saved" << std::endl;
        }
        catch(std::string in){
            std::cout << "Error saving game" << std::endl;
            std::cout << "caught " << in << std::endl;
        }
    }

      // checks if user has entered "place" and the input format is correct
      if(!input.substr(0, 5).compare("place") && input.length() == 14) { 
         // takes the character from the string by index and converts to a char/int
         if(checkInput(input)){
            const char *colour = input.substr(6,1).c_str();
            char c = *colour;
            const char *shape = input.substr(7,1).c_str();
            int s = *shape - '0';
                     
            // mod the ASCII value of the char by the ASCII value of 'A' to receive Y coordinate, A % 65 = 0, B % 65 = 1, etc
            const char *y = input.substr(12,1).c_str();
            int yint = *y % 65;
            const char *x = input.substr(13,1).c_str();
            int xint = *x - '0';
            c = toupper(c);

            // checks if the player has the tile in their hand and if the placement is valid
            if(player->getHand()->getTile(c, s) != nullptr && board->putTile(player, player->getHand()->getTile(c, s), xint, yint)) {
               endTurn(player, c, s);
               move = true;
            }
         }
      }

      if(!input.substr(0, 5).compare("place") && input.length() == 15 && board->getXEnd() >= 10) { 
         // takes the character from the string by index and converts to a char/int
         const char *colour = input.substr(6,1).c_str();
         char c = *colour;
         const char *shape = input.substr(7,1).c_str();
         int s = *shape - '0';
                  
         // mod the ASCII value of the char by the ASCII value of 'A' to receive Y coordinate, A % 65 = 0, B % 65 = 1, etc
         const char *y = input.substr(12,1).c_str();
         int yint = *y % 65;
         const char *x = input.substr(13,2).c_str();
         int xint = (int)strtol(x, (char **)NULL, 10);

         // checks if the player has the tile in their hand and if the placement is valid
         if(player->getHand()->getTile(c, s) != nullptr && board->putTile(player, player->getHand()->getTile(c, s), xint, yint)) {
            endTurn(player, c, s);
            move = true;
         }
      }
      // checks if the user has entered "replace" and if the input format is correct
      else if(!input.substr(0,7).compare("replace") && input.length() == 10 && bag->size() > 0) {
         ++turn;
         const char *colour = input.substr(8,1).c_str();
         char c = toupper(*colour);
         const char *shape = input.substr(9,1).c_str();
         int t = *shape - '0';
         swapTile(player, c, t);
         move = true;
      }

      if(!input.substr(0, 4).compare("exit") || std::cin.eof()){
         move = true;
         quit = true;
      }
   }
}


bool checkInput(std::string input){
   //declaring a string for checking if it's a digit or not
   std::string check = "1234567890";

   //declaring 2 bool, for checking digit and alphabets
   bool result = false;
   bool result2 = true;
   
   //loop through the string check
    for(int i = 0; i < 9 ; i ++){
            if (input[7]==check[i]){result = true;}
            if (input[6]==check[i]){result2= false;}
            if (input[13]==check[i]){result = true;}
            if (input[12]==check[i]){result2= false;}
         }
         
         //only return true if both of the bool are true
         return result & result2;
}

//End turn function
void endTurn(Player* player, char c, int s) {
   ++turn;
   player->getHand()->removeTile(c, s);
   player->getHand()->addBack((getRandomTile(bag)));
}

// iterates through players and finds player with the highest score
void endGame() {
   int score = 0;
   std::string player = "";

   for(int i = 0; i < players.size(); i++)     {
      if(players.at(i)->getScore() > score) {
         score = players.at(i)->getScore();
         player = players.at(i)->getName();
      }
    }
    std::cout << player << " wins with a score of " << score << std::endl;
    exit(0);
}
