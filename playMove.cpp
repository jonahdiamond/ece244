#include "GameState.h"
#include "globals.h"

// Function prototypes (if you need)

void playMove(GameState& game_state) {
  // Change turn if move is valid,
  //some logic to check move validity
  game_state.set_moveValid(true);
  int currentPlayer = (game_state.get_turn()) ? R : Y;
  int oppPlayer = (game_state.get_turn()) ? Y : R;
  int i = game_state.get_selectedRow(), j = game_state.get_selectedColumn();
  if (game_state.get_moveValid()){
    game_state.set_gameBoard( i, j, currentPlayer);
  }
  //set movevalid
  //game_state.set_moveValid(true);
  // Change gameOver
  
  int xCount = 1, yCount = 1, slope1Count = 1, slopeNeg1Count = 1;
  int xIter, yIter;
  for (int xDir = -1; xDir <= 1; xDir++){
    for (int yDir = -1; yDir <= 1; yDir++){
      xIter = xDir;
      yIter = yDir;
      if (i + xDir < 0 || i + xDir >= boardSize || j + yDir < 0 || j + yDir >= boardSize || xDir == 0 && yDir == 0){
        continue; //skip condition if out of bounds of board
      }
       while (//i + xIter >= 0 && i + xIter < boardSize && j + yIter >= 0 && j + yIter < boardSize && //keep iterators in bounds
       game_state.get_gameBoard( i + xIter, j + yIter) == currentPlayer){   //iterate if same colour
        if (xDir == -1 && yDir == -1 || xDir == 1 && yDir == 1){
          slope1Count++;    //add 1 in direction of slope 1
        }
        if (xDir == 0 && yDir == 1 || xDir == 0 && yDir == -1){
          yCount++;         //add 1 in direction of y axis
        }
        if (xDir == 1 && yDir == -1 || xDir == -1 && yDir == 1){
          slopeNeg1Count++; //add 1 in direction of slope -1
        }
        if (xDir == 1 && yDir == 0 || xDir == -1 && yDir == 0){
          xCount++;         //add 1 in direction of x axis
        }
        xIter+=xDir;
        yIter+=yDir;
        if (i + xIter < 0 || i + xIter >= boardSize || j + yIter < 0 || j + yIter >= boardSize){
          break; //skip condition if out of bounds of board
        }
      }
    }
  }
  if (xCount >= 4 || yCount >= 4 || slope1Count >= 4 || slopeNeg1Count >= 4){
    game_state.set_gameOver(true);
  }

  // Change winner
  if (game_state.get_gameOver()){
    game_state.set_winner(currentPlayer); //set winner to the player that just moved
  }

  // change turn
  game_state.set_turn(!game_state.get_turn());
}
