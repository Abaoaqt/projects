# APT-A2

//Fire up game with welcome and option;

//New Game;
//Load Game;
//Show Student Info;
//Quit;

//Student info - classes containing student details;

//Load game - loads file into system;

//New Game;
//Get player details - name;
   //is player computer;
      //create computer player;
      //set score to 0;
      //create linked list player-hand;
   //else;
     //ask name;
     //set score to 0;
     //create linked list player-hand;

//Start Game;
   //create board;
   //create tiles;
   //randomise tiles and place in linked list - bag;
   //set hand - player;
     //set hand piece (5);
       //remove tile and add to player-hand;
   
   //Turn;
      //player;
          //place piece;
          //check if peice l/r u/d valid (ie same colour/same shape);
          //no?;
             //reject move;
          //yes?;
             //check if place occupied;
                //yes?;
                   //reject move; 
                //no?;
                  //Place tile;
                  //calculate score;
                  //get new tile from bag;
                  //add tile to end of hand;
          //swap piece;
             //confirm piece in hand;
             //No?;
                //reject move;
             //yes?;
                //remove piece from hand;
                //randomly place it in bag;
                //remove first piece from bag;
                //add to hand;
                
             
   
