#include <iostream>
#include "Board.h"

class qwirkle {

    public: 
        qwirkle();
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

    private:
        LinkedList* bag;
        Board* board;
        std::vector<Player*> players;

        int numPlayers = 0;
        int turn = 0;
        bool quit = false;
        bool skip = false;
};
